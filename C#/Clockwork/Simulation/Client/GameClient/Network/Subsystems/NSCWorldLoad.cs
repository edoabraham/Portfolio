/// NSCWorldLoad.cs - NSCWoldLoad Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using System.Linq;
using System.Threading;
using System.Collections.Generic;

using Artemis;
using Artemis.Utils;
using Artemis.System;
using NetworkEvents;
#endregion

/// Game Client
namespace GameClient {

	/// World Load
	public sealed class NSCWorldLoad : 
		ClientProcessingSystem {

		#region Packet Structures
		/// Out Packet Structure
		/// 0 Packet Type
		/// 1 Metadata
		///     Request - No metadata
		///     Progress - Percentage
		///     Completion - No metadata

		/// In Packet Structure (Info Packet)
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

		/// In Packet Structure (Progress Packet)
		/// 0 Packet Type
		/// 1 Player ID
		/// 2 Percentage Complete

		/// In Packet Structure (Completion Packet)
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

		/// Hard upper bound for the spell and item lists.
		/// In the event that a packet is corrupted or written
		/// incorrectly, the system will ensure that large values
		/// read for the number of items and spells will be capped.
		/// This will block off performance problems.
		private const uint HardCap = 12;
		#endregion

		/// Constructor
		public NSCWorldLoad(int interval,
			ClientSystem clientSystem) :
			base(interval, clientSystem,
			ENetEventType.WorldLoad, true) {

				this.InfoReceived_ = false;
				this.PlayerInfoList_ = new List<PlayerInfo>();
				this.NPCInfoList_ = new List<NPCInfo>();
				this.MapID_ = 0;
				this.IsCleanMap_ = true;
		}

		/// Load Content
		public override void LoadContent() {

		}

		/// Process received packets for loading information.
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {

			// Handle incoming packets
			while (this.InNetEventList_.Count > 0) {
				NetEvent inNetEvent = this.InNetEventList_.Dequeue();

				// Read the packet type
				uint type = 0;
				inNetEvent.Data.ReadDynamicUInt(out type, LoadPhaseBitLength);
				var loadType = (NetworkConstants.ELoadPhase)type;

				// React according to the in packet type
				switch (loadType) {
					#region Info
					case NetworkConstants.ELoadPhase.Info: {
							try {
								// 1 Map ID
								// Read the map ID
								this.InfoReceived_ &= 
									inNetEvent.Data.ReadDynamicUInt(out this.MapID_, MapIDBitLength);

								#region Players
								// 2 Number of Players
								// Read the number of players
								uint numOfPlayers = 0;
								this.InfoReceived_ &=
									inNetEvent.Data.ReadDynamicUInt(out numOfPlayers, PlayerIDBitLength);
								this.HardCapCheck(numOfPlayers);

								// Extract and store information for each player
								for (int i = 0; i < numOfPlayers; i++) {

									// Create a new player info
									PlayerInfo playerInfo = new PlayerInfo();

									// 2a Player Name
									// Read the player name
									this.InfoReceived_ &=
										inNetEvent.Data.ReadString(out playerInfo.Name, NetworkConstants.CompressionStep);

									// 2b Player Game ID
									// Read the player game ID
									this.InfoReceived_ &=
										inNetEvent.Data.ReadDynamicUInt(out playerInfo.ID, PlayerIDBitLength);

									// 2c Character ID
									// Read the character ID
									this.InfoReceived_ &=
										inNetEvent.Data.ReadDynamicUInt(out playerInfo.CharacterID, CharacterIDBitLength);

									// 2d Spell IDs
									// Create a new list for spell IDs
									List<ESpell> spellIDs = new List<ESpell>();
									for (int j = 0; j < MaxCharAuxiliarySpells; j++) {
										uint spellID = 0;
										this.InfoReceived_ &=
											inNetEvent.Data.ReadDynamicUInt(out spellID, SpellIDBitLength);
										spellIDs.Add((ESpell)spellID);
									}

									// Store list of spell IDs
									playerInfo.Spells = spellIDs;

									// 2e Auxiliary Spell IDs
									// Create a new list for aux spell IDs
									List<ESpell> auxSpellIDs = new List<ESpell>();
									for (int j = 0; j < MaxCharAuxiliarySpells; j++) {
										uint spellID = 0;
										this.InfoReceived_ &=
											inNetEvent.Data.ReadDynamicUInt(out spellID, SpellIDBitLength);
										auxSpellIDs.Add((ESpell)spellID);
									}

									// Store list of aux spell IDs
									playerInfo.AuxiliarySpells = auxSpellIDs;

									// 2f Item IDs
									// Create a new list for item IDs
									List<EItem> itemIDs = new List<EItem>();
									for (int k = 0; k < MaxItems; k++) {
										uint itemID = 0;
										this.InfoReceived_ &=
											inNetEvent.Data.ReadDynamicUInt(out itemID, ItemIDBitLength);
										itemIDs.Add((EItem)itemID);
									}
									
									// Store list of item IDs
									playerInfo.Items = itemIDs;

									// Add the new player info to the list
									this.PlayerInfoList_.Add(playerInfo);
								}
								#endregion

								#region NPCs
								// 3 Number of NPCs
								// Read the number of NPCs
								uint numOfNPCs = 0;
								this.InfoReceived_ &=
									inNetEvent.Data.ReadDynamicUInt(out numOfNPCs, PlayerIDBitLength);
								this.HardCapCheck(numOfNPCs);

								// Extract and store information for each player
								for (int i = 0; i < numOfNPCs; i++) {

									// Create a new NPC info
									NPCInfo npcInfo = new NPCInfo();

									// 3a NPC Game ID
									// Read the player game ID
									this.InfoReceived_ &=
										inNetEvent.Data.ReadDynamicUInt(out npcInfo.ID, PlayerIDBitLength);

									// 3b Character ID
									// Read the character ID
									this.InfoReceived_ &=
										inNetEvent.Data.ReadDynamicUInt(out npcInfo.CharacterID, CharacterIDBitLength);

									// 3c Spell IDs
									// Create a new list for spell IDs
									List<ESpell> spellIDs = new List<ESpell>();
									for (int j = 0; j < MaxNPCSpells; i++) {
										uint spellID = 0;
										this.InfoReceived_ &=
											inNetEvent.Data.ReadDynamicUInt(out spellID, SpellIDBitLength);
										spellIDs.Add((ESpell)spellID);
									}

									// Store list of spell IDs
									npcInfo.AuxiliarySpells = spellIDs;

									// 3d Auxiliary Spell IDs
									// Create a new list for spell IDs
									List<ESpell> auxSpellIDs = new List<ESpell>();
									for (int j = 0; j < MaxNPCSpells; j++) {
										uint spellID = 0;
										this.InfoReceived_ &=
											inNetEvent.Data.ReadDynamicUInt(out spellID, SpellIDBitLength);
										auxSpellIDs.Add((ESpell)spellID);
									}

									// Store list of spell IDs
									npcInfo.AuxiliarySpells = spellIDs;

									// 3e Item IDs
									// Create a new list for item IDs
									List<EItem> itemIDs = new List<EItem>();
									for (int k = 0; k < MaxItems; k++) {
										uint itemID = 0;
										this.InfoReceived_ &=
											inNetEvent.Data.ReadDynamicUInt(out itemID, ItemIDBitLength);
										itemIDs.Add((EItem)itemID);
									}

									// Store list of item IDs
									npcInfo.Items = itemIDs;

									// Add the new player info to the list
									this.NPCInfoList_.Add(npcInfo);
								}
								#endregion

								// 4 Clean Map Flag
								// Read the clean map flag value
								this.InfoReceived_ &=
									inNetEvent.Data.ReadBool(out this.IsCleanMap_);

								// 4a Player Map Reveal if applicable
								if (!this.IsCleanMap_) {

									// TODO: Implement parsing

								}

								// Confirm data received and processed
								this.InfoReceived_ = true;
							} catch (Exception exception) {
								Console.WriteLine(exception.Message);
							}
						}
						break;
					#endregion
					#region Progress
					case NetworkConstants.ELoadPhase.Progress: {
							// Broadcast the progress to all other clients

							// Read player ID from packet
							uint playerID = 0;
							inNetEvent.Data.ReadDynamicUInt(out playerID, PlayerIDBitLength);

							// Read progress from in packet
							uint progress = 0;
							inNetEvent.Data.ReadDynamicUInt(out progress, MaxProgressBitLength);

							// Iterate through the list of player info and assign progress
							for (int i = 0, j = this.PlayerInfoList_.Count; i < j; i++) {
								if (this.PlayerInfoList_[i].ID == playerID) {
									PlayerInfo playerInfo = this.PlayerInfoList_[i];
									playerInfo.Progress = progress;
								}
							}
						}
						break;
					#endregion
					#region Completion
					case NetworkConstants.ELoadPhase.Completion: {
							// Broadcast the progress to all other clients

							// Read player ID from packet
							uint playerID = 0;
							inNetEvent.Data.ReadDynamicUInt(out playerID, PlayerIDBitLength);

							// Iterate through the list of player info and assign progress
							for (int i = 0, j = this.PlayerInfoList_.Count; i < j; i++) {
								if (this.PlayerInfoList_[i].ID == playerID) {
									PlayerInfo playerInfo = this.PlayerInfoList_[i];
									playerInfo.Completed = true;
								}
							}
						}
						break;
					#endregion
					#region Default
					default:
						break;
					#endregion
				}
			}
		}

		/// Request the game info from the server
		private bool InfoReceived_;
		public bool InfoReceived {
			get { return this.InfoReceived_; }
		}
		public void RequestInfo() {

			// Establish that nothing is received yet
			this.InfoReceived_ = false;

			// Start thread for sending a request and waiting for a response
			ThreadStart ts = new ThreadStart(() => {
				while (!this.InfoReceived_) {
					
					// Write the info request packet

					// Create net event
					NetEvent outNetEvent = this.CreateNetEvent();

					// Write packet type
					outNetEvent.Data.WriteDynamicUInt((uint)NetworkConstants.ELoadPhase.Info, LoadPhaseBitLength);

					// Enqueue net event to be sent out
					this.EnqueueOutNetEvent(outNetEvent);

					// Sleep until another check is inquired
					Thread.Sleep(TimeOut);
				}
			});

			// Create and initialize thread
			Thread thread = new Thread(ts);

			// Start thread
			thread.Start();
		}

		/// Send the progress of content loading
		public void SendProgress(int percent) {

			// Check the range of the number
			if (percent < 0)
				percent = 0;
			else if (percent > 100)
				percent = 100;
			else {

				// Create net event
				NetEvent outNetEvent = this.CreateNetEvent();

				// Write packet type
				outNetEvent.Data.WriteDynamicUInt((uint)NetworkConstants.ELoadPhase.Progress, LoadPhaseBitLength);

				// Write the percentage progress
				outNetEvent.Data.WriteDynamicUInt((uint)percent, MaxProgressBitLength);

				// Enqueue net event to be sent out
				this.EnqueueOutNetEvent(outNetEvent);
			}
		}

		/// Send a packet to tell everyone loading is finished
		public void SendCompletion() {

			// Create net event
			NetEvent outNetEvent = this.CreateNetEvent();

			// Write packet type
			outNetEvent.Data.WriteDynamicUInt((uint)NetworkConstants.ELoadPhase.Completion, LoadPhaseBitLength);

			// Enqueue net event to be sent out
			this.EnqueueOutNetEvent(outNetEvent);
		}

		/// 
		public struct PlayerInfo {
			public string Name;
			public uint ID;
			public uint CharacterID;
			public List<ESpell> Spells;
			public List<ESpell> AuxiliarySpells;
			public List<EItem> Items;

			// Logistics
			public uint Progress;
			public bool Completed;
		}

		/// 
		public struct NPCInfo {
			public uint ID;
			public uint CharacterID;
			public List<ESpell> Spells;
			public List<ESpell> AuxiliarySpells;
			public List<EItem> Items;
		}

		/// List of players and their items and auxiliary spells
		private List<PlayerInfo> PlayerInfoList_;
		public List<PlayerInfo> PlayerInfoList {
			get { return this.PlayerInfoList_; }
		}

		/// List of NPC and their items and auxiliary spells
		private List<NPCInfo> NPCInfoList_;
		public List<NPCInfo> NPCInfoList {
			get { return this.NPCInfoList_; }
		}

		/// Map ID
		private uint MapID_;
		public uint MapID {
			get { return this.MapID_; }
		}

		/// Indicates whether this map has been altered
		private bool IsCleanMap_;
		public bool IsCleanMap {
			get { return this.IsCleanMap_; }
		}

		/// Keeps track of the changes that were made to the original map
		/// Implement later


		/// Performs a value check to ensure that passed values are in safe range.
		/// Throws an exception if value exceeds the acceptable range. See HardCap.
		private void HardCapCheck(uint value) {
			if (value > HardCap)
				throw new Exception("Read value " + value.ToString() + 
					" exceed acceptable max of " + HardCap.ToString() + ".");
		}
	}
}
