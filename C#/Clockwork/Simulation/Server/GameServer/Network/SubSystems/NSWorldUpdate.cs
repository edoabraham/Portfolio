/// NSWorldUpdate.cs - NSWorldUpdate Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using System.Linq;
using System.Collections.Generic;

using Artemis;
using Artemis.Utils;
using Artemis.System;
using NetworkEvents;
using Utilities;
#endregion

/// Game Server
namespace GameServer {

	/// World Update Network System
	public sealed class NSWorldUpdate : 
		ServerProcessingSystem {

		#region Data Type Settings
		/// Main Player ID Bit Resolution
		private const int PlayerIDResolution = 4;

		/// Player State Resolution
		private const int PlayerStateResolution = 4;

		/// Floating Point Resolution
		private const int FloatingPointResolution = 16;

		/// The Range for Floating Point Numbers
		private const float MaxFloatValue = 327.67f;
		private const float MinFloatValue = -MaxFloatValue;

		/// Player update subsection length in bytes
		private const int PlayerSubSectionLength = (int)((PlayerIDResolution 
			+ PlayerStateResolution + FloatingPointResolution * 2) / 8);

		/// Map Cell update subsection length in bytes
		private const int MapCellSubSectionLength = (int)(4);

		/// Spell update subsection length in bytes
		private const int SpellSubSectionLength = (int)(0);
		#endregion

		/// Constructor
		public NSWorldUpdate(int interval, 
			ServerSystem serverSystem) :
			base(interval, serverSystem, 
			ENetEventType.WorldUpdate, false) {

		}

		/// Load Content
		public override void LoadContent() {
			this.PCMapper_ = new ComponentMapper<PlayerController>(EntityWorld);
			this.TransformMapper_ = new ComponentMapper<Transform>(EntityWorld);
			this.CurrentStatsMapper_ = new ComponentMapper<CurrentStats>(EntityWorld);
			this.MapCellMapper_ = new ComponentMapper<MapCell>(EntityWorld);
		}

		/// Run through the entities checking which ones were in view of a player
		/// and organizing them into readable packets to be sent out to player clients
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {

			// Grab bag of entities that have Player Controllers as their Components
			// These entities are player entities that require this world update information
			Bag<Entity> PCEntities = this.EntityWorld.ComponentManager.GetEntities<PlayerController>();
			if (PCEntities != null) {

				// Iterate through all of the PC Entities and run their "radars"
				for (int i = 0, j = PCEntities.Count; i < j; i++) {

					// Localize Client Entity
					Entity PCEntity = PCEntities[i];

					if(PCEntity.HasComponent<Transform>() && 
						PCEntity.HasComponent<CurrentStats>()) {

						Transform PCTransform = TransformMapper_.Get(PCEntity);
						PlayerController PCController = PCMapper_.Get(PCEntity);
						CurrentStats PCStats = CurrentStatsMapper_.Get(PCEntity);

						// Field of Vision Entities
						// Create a bag that will store all of the Entities within the radar
						Bag<Entity> FoVPlayers = new Bag<Entity>();
						Bag<Entity> FoVMapCells = new Bag<Entity>();
						Bag<Entity> FoVSpells = new Bag<Entity>();
						Bag<Entity> FoVNPC = new Bag<Entity>();

						// Put this Entity in first
						FoVPlayers.Add(PCEntity);

						// Sight Range (radius) squared
						float radarSquared = PCStats.SightRange * PCStats.SightRange;

						// Iterate through all other entities, as long as they are
						// not the same entity, to see if that entity is within
						// the radar's range
						foreach (Entity entity in entities.Values) {

							// Make sure it is not the same entity as the CM Entity
							if (PCEntity != entity) {

								// Localize Component items of this entity
								Transform transform = TransformMapper_.Get(entity);

								// Perform Radar Check
								if (radarSquared >= ((Vector2)(transform.Position -
									PCTransform.Position)).SquaredLength) {

										// Check if Entity is another Player
										if (entity.HasComponent<PlayerController>())
											FoVPlayers.Add(entity);

										// Check if Entity is a monster, boss, or NPC
										else if (entity.HasComponent<CurrentStats>())
											FoVNPC.Add(entity);

										// Check if Entity is a Map Cell
										else if (entity.HasComponent<MapCell>()) {

											// Localize
											MapCell mapCell = MapCellMapper_.Get(entity);
											short x = mapCell.X;
											short y = mapCell.Y;

											// Check if an encountered cell needs updating
											if ((PCController.MapTable.GetLength(0) > x) && (x >= 0) &&
												(PCController.MapTable.GetLength(1) > y) && (y >= 0)) {

												// Add Map Cell to list if it needs updating
												if(PCController.MapTable[x,y])
													FoVMapCells.Add(entity);
											}
										}

										// Check if Entity is a Spell
										else if (entity.HasComponent<SpellAI>())
											FoVSpells.Add(entity);
								}
							}
						}

						/// Prepare and Send Net Event

						// Create net Net Event
						NetEvent netEvent = this.CreateNetEvent(PCController);

						#region Location Section
						// Calculate the Map Cell Location and write to buffer
						UInt16 mapCellLocation = (UInt16)(FoVPlayers.Count * PlayerSubSectionLength);
						if(FoVMapCells.Any())
							netEvent.Data.WriteUint16(mapCellLocation);
						else
							netEvent.Data.WriteUint16(0);

						// Calculate the Spells Location and write to buffer
						UInt16 spellsLocation = (UInt16)(FoVMapCells.Count * 
							MapCellSubSectionLength + mapCellLocation);
						if(FoVSpells.Any())
							netEvent.Data.WriteUint16(spellsLocation);
						else
							netEvent.Data.WriteUint16(0);

						// Calculate the NPC Location and write to buffer
						UInt16 npcLocation = (UInt16)(FoVSpells.Count * 
							SpellSubSectionLength + spellsLocation);
						if (FoVNPC.Any())
							netEvent.Data.WriteUint16(npcLocation);
						else
							netEvent.Data.WriteUint16(0);
						#endregion

						#region Player Section
						// Write Players to buffer
						foreach(Entity entity in FoVPlayers) {
						
							// Localize
							PlayerController controller = PCMapper_.Get(entity);
							Transform transform = TransformMapper_.Get(entity);

							// Write the Player ID
							netEvent.Data.WriteDynamicUInt(controller.ID, PlayerIDResolution);

							// Write the Player State
							netEvent.Data.WriteDynamicUInt((uint)controller.State, PlayerStateResolution);

							// Write the Player Position X
							netEvent.Data.WriteCustomResolutionSingle(transform.Position.X, 
								MinFloatValue, MaxFloatValue, FloatingPointResolution);

							// Write the Player Position Y
							netEvent.Data.WriteCustomResolutionSingle(transform.Position.Y,
								MinFloatValue, MaxFloatValue, FloatingPointResolution);
						}
						#endregion

						#region Map Cell Section
						// Write Map Cells to buffer
						#endregion

						/// Enqueue new Net Event
						this.EnqueueOutNetEvent(netEvent);
					}
				}
			}
		}

		#region Component Mapper
		private ComponentMapper<PlayerController> PCMapper_;
		private ComponentMapper<Transform> TransformMapper_;
		private ComponentMapper<CurrentStats> CurrentStatsMapper_;
		private ComponentMapper<MapCell> MapCellMapper_;
		#endregion
	}
}
