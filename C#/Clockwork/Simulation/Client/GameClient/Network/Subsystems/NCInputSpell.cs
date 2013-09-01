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

/// Game Client
namespace GameClient {

	/// Spell Input Network System
	public sealed class NCInputSpell : 
		ClientProcessingSystem {

		/// Packet Structure (Out Only)
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
			ClientSystem clientSystem)
			: base(interval, clientSystem, 
			ENetEventType.SpellInput, false) {

				this.TargetLocation_ = Vector2.Zero;
				this.InputFlags_ = 0;
				this.NewInput_ = false;
		}

		/// Load Content
		public override void LoadContent() {
			
		}

		/// 
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {

			if (this.NewInput_) {

				// Create new net event
				NetEvent netEvent = this.CreateNetEvent();

				// Write spell target location
				netEvent.Data.WriteCustomResolutionSingle(this.TargetLocation_.X, 
					MinFloatValue, MaxFloatValue, FloatResolution);
				netEvent.Data.WriteCustomResolutionSingle(this.TargetLocation_.Y,
					MinFloatValue, MaxFloatValue, FloatResolution);

				// Write spell flags
				netEvent.Data.WriteDynamicUInt(this.InputFlags_, MaxSpells);

				// Set NewInput_ to false to prevent
				// processing the same input more than once
				this.NewInput_ = false;

				// Queue up net event
				this.EnqueueOutNetEvent(netEvent);
			}
		}

		/// 
		public void Cast(Vector2 target, uint flag) {
			this.TargetLocation_ = target;
			this.InputFlags_ = flag;
			this.NewInput_ = true;
		}

		/// The target location the mouse is over
		/// when the player is casting a spell.
		private Vector2 TargetLocation_;
		
		/// 
		private uint InputFlags_;

		/// 
		private bool NewInput_;
	}
}
