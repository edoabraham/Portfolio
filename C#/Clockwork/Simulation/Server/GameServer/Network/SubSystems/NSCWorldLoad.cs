/// NSCWorldLoad.cs - NSCWoldLoad Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using System.Linq;
using System.Collections.Generic;

using Artemis;
using Artemis.Utils;
using Artemis.System;
using NetworkEvents;
#endregion

/// Game Server
namespace GameServer {

	/// World Load
	public sealed class NSCWorldLoad : 
		ServerProcessingSystem {

		#region Packet Structures
		/// In Packet Structure
		/// 0 Packet Type
		/// 1 Metadata
		///     Request - No metadata
		///     Progress - Percentage
		///     Completion - No metadata

		/// Out Packet Structure (Info Packet)
		/// 0 Packet Type
		/// 1 Map ID
		/// 2 Number of Players
		///   a Player Name
		///   b Player Game ID (also Controller ID)
		///	  c Character ID
		///   d Spells
		///   e Auxiliary Spells
		///   f Items
		///   f -> repeat
		/// 3 Number of NPC's
		///   a NPC Game ID (also Controller ID)
		///   b Character ID
		///   c Spells
		///   d Auxiliary Spells
		///   e Number of Items
		///   f -> repeat
		/// 4 Clean Map Flag
		///   a Player Map Reveal if applicable

		/// Out Packet Structure (Progress Packet)
		/// 0 Packet Type
		/// 1 Player ID
		/// 2 Percentage Complete

		/// Out Packet Structure (Completion Packet)
		/// 0 Packet Type
		/// 1 Player ID
		#endregion

		#region Data Type Settings
		/// Length of the load phase type
		private static readonly int LoadPhaseBitLength =
			NetworkConstants.LoadPhaseBitLength;

		/// Max bit length for a player ID
		private const int PlayerIDBitLength =
			NetworkConstants.PlayerIDBitLength;

		/// Max bit length for a character ID
		private static readonly int CharacterIDBitLength =
			NetworkConstants.CharacterIDBitLength;

		/// Max bit length for a map ID
		private static readonly int MapIDBitLength =
			NetworkConstants.MapIDBitLength;

		/// Max bit length for a spell ID
		private static readonly int SpellIDBitLength =
			NetworkConstants.SpellIDBitLength;

		/// Max bit length for a item ID
		private static readonly int ItemIDBitLength =
			NetworkConstants.ItemIDBitLength;

		/// The maximum number of spells a character may have.
		private const int MaxCharacterSpells =
			GlobalData.MaxCharacterSpells;

		/// The maximum number of auxiliary spells allowed.
		private const int MaxCharAuxiliarySpells =
			GlobalData.MaxCharAuxiliarySpells;

		/// The maximum number of items allowed to be equipped.
		private const int MaxItems =
			GlobalData.MaxItems;

		/// The maximum number of spells a NPC can have.
		private const int MaxNPCSpells =
			GlobalData.MaxNPCSpells;

		/// The maximum number of auxiliary spells an NPC is allowed.
		public const int MaxNPCAuxiliarySpells =
			GlobalData.MaxNPCAuxiliarySpells;

		/// The bit length of the progress percent number
		private const int MaxProgressBitLength =
			NetworkConstants.MaxProgressBitLength;

		/// Time before an unanswered packet
		/// request requires another request.
		private const int TimeOut = 1000;
		#endregion

		/// Constructor
		public NSCWorldLoad(int interval,
			ServerSystem serverSystem) :
			base(interval, serverSystem,
			ENetEventType.WorldLoad, true) {

				// TODO: Pass map id
				this.MapID_ = EMap.DerpMap;
		}

		/// Load Content
		public override void LoadContent() {
			this.PCMapper_ = new ComponentMapper<PlayerController>(this.EntityWorld);
			this.NPCMapper_ = new ComponentMapper<NPCController>(this.EntityWorld);
		}

		/// 
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {

			// Grab bag of entities that have Player Controllers
			Bag<Entity> PCEntities = this.EntityWorld.ComponentManager.GetEntities<PlayerController>();

			// Grab bag of entities that have NPC Controllers
			Bag<Entity> NPCEntities = this.EntityWorld.ComponentManager.GetEntities<NPCController>();

			/// Dequeue requests for game info and send the data
			while (this.InNetEventList_.Count > 0) {
				KeyValuePair<PlayerController, NetEvent> inNetEvent = this.InNetEventList_.Dequeue();

				// Read the packet type
				uint type = 0;
				inNetEvent.Value.Data.ReadDynamicUInt(out type, LoadPhaseBitLength);
				var loadPhase = (NetworkConstants.ELoadPhase)type;

				// React according to the in packet type
				switch (loadPhase) {
					#region Info
					case NetworkConstants.ELoadPhase.Info: {
							// Check to see if the main system has finished creating characters yet.
							if (this.ServerSystem_.CharactersInitialized) {
								try {
									// Create net event
									NetEvent outNetEvent = this.CreateNetEvent(inNetEvent.Key);

									// 0 Packet Type
									// Write the packet type
									outNetEvent.Data.WriteDynamicUInt((uint)loadPhase, LoadPhaseBitLength);

									// 1 Map ID
									// Write the map ID
									outNetEvent.Data.WriteDynamicUInt((uint)this.MapID_, MapIDBitLength);

									#region Players
									// 2 Number of Players
									// Write the number of players
									uint numOfPlayers = (uint)PCEntities.Count;
									outNetEvent.Data.WriteDynamicUInt(numOfPlayers, PlayerIDBitLength);

									// Write the info for each player
									for (int i = 0; i < numOfPlayers; i++) {

										// Localize a player controller
										PlayerController pc = this.PCMapper_.Get(PCEntities[i]);

										// 2a Player Name
										// Write the player name
										outNetEvent.Data.WriteString(pc.Info.Name, NetworkConstants.CompressionStep);

										// 2b Player Game ID
										// Write the player game ID
										outNetEvent.Data.WriteDynamicUInt(pc.ID, PlayerIDBitLength);

										// 2c Character ID
										// Write the character ID
										outNetEvent.Data.WriteDynamicUInt((uint)pc.Info.CharacterID, CharacterIDBitLength);

										// Localize the character
										Character character = Character.Characters[pc.Info.CharacterID];
										if (character == null)
											throw new Exception("Character was not found in the character list.");

										// 2d Spell IDs
										ESpell[] spellIDs = character.CharacterSpells.SpellList;
										System.Diagnostics.Debug.Assert(spellIDs.Length == MaxCharacterSpells);
										for (int j = 0, m = spellIDs.Length; j < m; j++) {
											outNetEvent.Data.WriteDynamicUInt((uint)spellIDs[j], SpellIDBitLength);
										}

										// 2e Auxiliary Spells IDs
										ESpell[] auxSpellIDs = pc.Info.AuxiliarySpells;
										System.Diagnostics.Debug.Assert(auxSpellIDs.Length == MaxCharAuxiliarySpells);
										for (int j = 0, m = auxSpellIDs.Length; j < m; j++) {
											outNetEvent.Data.WriteDynamicUInt((uint)auxSpellIDs[j], SpellIDBitLength);
										}

										// 2f Item IDs
										EItem[] itemIDs = pc.Info.Items;
										System.Diagnostics.Debug.Assert(itemIDs.Length == MaxItems);
										for (int k = 0, m = itemIDs.Length; k < m; k++) {
											outNetEvent.Data.WriteDynamicUInt((uint)itemIDs[k], ItemIDBitLength);
										}
									}
									#endregion

									#region NPCs
									// 3 Number of Players
									uint numOfNPCs = (uint)NPCEntities.Count;
									outNetEvent.Data.WriteDynamicUInt(numOfNPCs, PlayerIDBitLength);

									// Write the info for each NPC
									for (int i = 0; i < numOfNPCs; i++) {

										// Localize a NPC controller
										NPCController npc = this.NPCMapper_.Get(NPCEntities[i]);

										// 3a NPC Game ID
										outNetEvent.Data.WriteDynamicUInt(npc.ID, PlayerIDBitLength);

										// 3b Character ID
										outNetEvent.Data.WriteDynamicUInt((uint)npc.Info.CharacterID, CharacterIDBitLength);

										// Localize the character
										Character character = Character.Characters[npc.Info.CharacterID];
										if (character == null)
											throw new Exception("Character was not found in the character list.");

										// 3c Spell IDs
										ESpell[] spellIDs = character.CharacterSpells.SpellList;
										System.Diagnostics.Debug.Assert(spellIDs.Length == MaxCharacterSpells);
										for (int j = 0, m = spellIDs.Length; j < m; j++) {
											outNetEvent.Data.WriteDynamicUInt((uint)spellIDs[j], SpellIDBitLength);
										}

										// 3d Auxiliary Spells IDs
										ESpell[] auxSpellIDs = npc.Info.AuxiliarySpells;
										System.Diagnostics.Debug.Assert(auxSpellIDs.Length == MaxCharAuxiliarySpells);
										for (int j = 0, m = auxSpellIDs.Length; j < m; j++) {
											outNetEvent.Data.WriteDynamicUInt((uint)auxSpellIDs[j], SpellIDBitLength);
										}

										// 3e Item IDs
										EItem[] itemIDs = npc.Info.Items;
										System.Diagnostics.Debug.Assert(itemIDs.Length == MaxItems);
										for (int k = 0, m = itemIDs.Length; k < m; k++) {
											outNetEvent.Data.WriteDynamicUInt((uint)itemIDs[k], ItemIDBitLength);
										}
									}
									#endregion
								} catch (Exception exception) {
									Console.WriteLine(exception.Message);
								}
							}
							break;
						}
					#endregion
					#region Progress
					case NetworkConstants.ELoadPhase.Progress: {
						// Broadcast the progress to all other clients

							// Read progress from in packet
							uint progress = 0;
							inNetEvent.Value.Data.ReadDynamicUInt(out progress, MaxProgressBitLength);

							// Write progress to out packets
							for (int i = 0, j = PCEntities.Count; i < j; i++) {
								PlayerController pc = this.PCMapper_.Get(PCEntities[i]);

								// Ensure that broadcast doesn't include sender
								if (pc != inNetEvent.Key) {

									// Create new net event
									NetEvent outNetEvent = this.CreateNetEvent(pc);

									// Write the type
									outNetEvent.Data.WriteDynamicUInt((uint)loadPhase, LoadPhaseBitLength);

									// Write the player ID
									outNetEvent.Data.WriteDynamicUInt(pc.ID, PlayerIDBitLength);

									// Write the progress
									outNetEvent.Data.WriteDynamicUInt(progress, MaxProgressBitLength);

									// Enqueue the net event to be sent
									this.EnqueueOutNetEvent(outNetEvent);
								}
							}
						}
						break;
					#endregion
					#region Completion
					case NetworkConstants.ELoadPhase.Completion: {
						// Broadcast completion to all other clients

							// Write progress to out packets
							for (int i = 0, j = PCEntities.Count; i < j; i++) {
								PlayerController pc = this.PCMapper_.Get(PCEntities[i]);

								// Ensure that broadcast doesn't include sender
								if (pc != inNetEvent.Key) {

									// Create new net event
									NetEvent outNetEvent = this.CreateNetEvent(pc);

									// Write the type
									outNetEvent.Data.WriteDynamicUInt((uint)loadPhase, LoadPhaseBitLength);

									// Write the player ID
									outNetEvent.Data.WriteDynamicUInt(pc.ID, PlayerIDBitLength);

									// Enqueue the net event to be sent
									this.EnqueueOutNetEvent(outNetEvent);
								}
							}
						}
						break;
					#endregion
					#region Default
					default:
						// Do nothing
						break;
					#endregion
				}
			}
		}

		#region Component Mapper
		private ComponentMapper<PlayerController> PCMapper_;
		private ComponentMapper<NPCController> NPCMapper_;
		#endregion

		/// The map ID of the game's map
		private EMap MapID_;
		public EMap MapID {
			get { return this.MapID_; }
		}
	}
}
