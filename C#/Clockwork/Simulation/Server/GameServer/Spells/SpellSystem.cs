/// SpellSystem.cs - SpellSystem class implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

using Artemis;
using Artemis.Utils;
using Artemis.System;

/// Game Server
namespace GameServer {

	/// In charge of checking controllers for activated spells
	/// and creating spells for those that are activated
	public class SpellSystem : EntityProcessingSystem {

		/// Grace period for charging spells over their
		/// time limit. This is the amount of time that
		/// a player can hold a spell before it begins
		/// to take a toll on his or her mana, stamina
		/// and/or health, depending on the spell.
		/// This value is measured in milliseconds.
		private const long ChargeGracePeriod = GlobalData.SpellChargeGracePeriod;

		/// Constructor
		public SpellSystem()
			: base(Aspect.One(typeof(PlayerController), typeof(NPCController))) {

		}

		/// Load Content
		public override void LoadContent() {
			this.PCControllerMapper_ = new ComponentMapper<PlayerController>(this.EntityWorld);
			this.NPCControllerMapper_ = new ComponentMapper<NPCController>(this.EntityWorld);
			this.CharacterSpellsMapper_ = new ComponentMapper<CharacterSpells>(this.EntityWorld);
		}

		/// 
		public override void Process(Entity entity) {

			// Handle player controller
			if (entity.HasComponent<PlayerController>() && entity.HasComponent<CharacterSpells>()) {

				// Localize player control
				PlayerController PCController = this.PCControllerMapper_.Get(entity);

				// Establish variables for storing the indexes of the
				// elements with the longest times, one that is still
				// charging and one that has finished charging.
				// Initialize them with the size of the SpellInput.
				int count = PCController.SpellInput.Count;
				int stillChargingIndex = count;
				long stillChargingValue = 0;
				int finishedChargingIndex = count;
				long finishedChargingValue = 0;

				// Iterate through the spell input to find the indexes.
				for (int i = 0; i < count; i++) {

					// Localize element
					KeyValuePair<bool, long> valuePair = PCController.SpellInput[i];

					// Pressed and still holding (obvious non-zero time and 'true' for press)
					if (valuePair.Key) {

						// Test for largest
						if (stillChargingValue < valuePair.Value) {
							stillChargingValue = valuePair.Value;
							stillChargingIndex = i;
						}

						// Clean up all but the max by zeroing (max will be put back later)
						// Reason: Only the largest charging matters, as it was the first 
						// key pressed. No other spell matters while the first one is still
						// active. Therefore, all other times are flushed by default. We
						// don't want a spell to be immediately charged as soon as the first
						// spell is released due the next one's timer ticking away while the
						// first was charging. The max value will be added back at the end.
						PCController.SpellInput[i] = new KeyValuePair<bool, long>(true, 0);

					} else 
						// Pressed and released (non-zero time, but 'false' for key press)
						if (valuePair.Value != 0) {

						// Test for largest
						if (finishedChargingValue < valuePair.Value) {
							finishedChargingValue = valuePair.Value;
							finishedChargingIndex = i;
						}

						// Clean up by zeroing the time section
						// Reason: Only the longest time matters, as it was the key that was
						// pressed first. All other keys that were pressed and let go in the
						// process mean nothing as only the longest pressed matters. They
						// need to be cleaned up however, since their times will be added
						// to later time updates, which can cause weird, unintended values.
						PCController.SpellInput[i] = new KeyValuePair<bool, long>(false, 0);
					}
				}

				// Localize character spells
				CharacterSpells characterSpells = this.CharacterSpellsMapper_.Get(entity);

				// Check if the earliest spell is a regular no charge spell
				if ((stillChargingIndex != count) && 
					(stillChargingValue >= finishedChargingValue) &&
					SpellDB.Spells[characterSpells.SpellList[stillChargingIndex]].HasCharge) {



				} else
					// Create a spell if 
					if (finishedChargingIndex != count) {


				} else 
					// 
					if (stillChargingIndex != count) {

						// Check if the charge time has exceeded the spell's
						// limit or not. Handle accordingly if it has.


						// Max value added back
						PCController.SpellInput[stillChargingIndex] = 
							new KeyValuePair<bool, long>(true, stillChargingValue);
				}

			} else if (entity.HasComponent<NPCController>()) {

			}
		}

		#region Component Mapper
		private ComponentMapper<PlayerController> PCControllerMapper_;
		private ComponentMapper<NPCController> NPCControllerMapper_;
		private ComponentMapper<CharacterSpells> CharacterSpellsMapper_;
		#endregion
	}
}
