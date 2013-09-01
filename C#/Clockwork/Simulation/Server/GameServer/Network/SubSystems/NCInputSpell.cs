/// NCInputSpell.cs - NCInputSpell Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using System.Collections.Generic;

using Artemis;
using Artemis.Utils;
using Artemis.System;
using NetworkEvents;
using Utilities;
#endregion

/// Game Server
namespace GameServer {

	/// Spell Input Network System
	public sealed class NCInputSpell : 
		ServerProcessingSystem {

		/// Packet Structure (In Only)
		/// 0 Target Position X
		/// 1 Target Position Y
		/// 2 Spell Flags

		#region Data Type Settings
		/// Floating point bit length resolution
		private const int FloatResolution = GlobalData.FloatResolution;

		/// The Range for Floating Point Numbers
		private const float MaxFloatValue = GlobalData.MaxFloatValue;
		private const float MinFloatValue = GlobalData.MinFloatValue;

		/// Max number of spells a player can control
		private const int MaxSpells = GlobalData.MaxPlayerSpells;
		#endregion

		/// Constructor
		public NCInputSpell(int interval,
			ServerSystem serverSystem) :
			base(interval, serverSystem, 
			ENetEventType.SpellInput, true) {

			this.PowersOfTwo_ = new int[MaxSpells];
			for (int i = 0; i < MaxSpells; i++)
				this.PowersOfTwo_[i] = (int)Math.Pow(2, i);
		}

		/// Load Content
		public override void LoadContent() {

		}

		/// Register the input to the respective player controller
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {

			// Iterate through the whole queue and process player inputs.
			while (this.InNetEventList_.Count > 0) {
				KeyValuePair<PlayerController, NetEvent> inNetEvent = this.InNetEventList_.Dequeue();

				// Only process if state is attack or idle, otherwise throw away the packet.
				if ((inNetEvent.Key.State == EAction.Attack) || (inNetEvent.Key.State == EAction.Idle)) {

					// Pull the spell target position
					float xPosition = 0.0f;
					inNetEvent.Value.Data.ReadCustomResolutionSingle(out xPosition,
						MinFloatValue, MaxFloatValue, FloatResolution);
					float yPosition = 0.0f;
					inNetEvent.Value.Data.ReadCustomResolutionSingle(out yPosition,
						MinFloatValue, MaxFloatValue, FloatResolution);

					// Set the new spell target
					inNetEvent.Key.SpellTarget = new Vector2(xPosition, yPosition);

					// Pull the spell flags
					uint spellFlags = 0;
					inNetEvent.Value.Data.ReadDynamicUInt(out spellFlags, MaxSpells);

					// Set the spell flags
					System.Diagnostics.Debug.Assert(inNetEvent.Key.SpellInput.Count == MaxSpells);
					for (int i = 0; i < MaxSpells; i++) {
						bool isActive = (spellFlags / this.PowersOfTwo_[i]) >= 1;

						// If the input is active, set the input entry to true and increment time.
						if (isActive)
							inNetEvent.Key.SpellInput[i] = new KeyValuePair<bool,
								long>(isActive, inNetEvent.Key.SpellInput[i].Value + this.Interval_);

						// If the input is NO LONGER active, set the input entry to false but
						// still continue to increment time to account for delays in handling.
						else if (inNetEvent.Key.SpellInput[i].Key)
							inNetEvent.Key.SpellInput[i] = new KeyValuePair<bool,
								long>(false, inNetEvent.Key.SpellInput[i].Value + this.Interval_);

						// Otherwise, if it was not and it is still not active, set it to false.
						else
							inNetEvent.Key.SpellInput[i] = new KeyValuePair<bool,
								long>(false, inNetEvent.Key.SpellInput[i].Value);
					}

					// Set the player's state to Attack if a spell is active
					if (spellFlags != 0)
						inNetEvent.Key.State = EAction.Attack;
					else
						inNetEvent.Key.State = EAction.Idle;
				}
			}
		}

		/// Array used to store the powers of two,
		/// which is used to test for spell flags.
		private int[] PowersOfTwo_;
	}
}
