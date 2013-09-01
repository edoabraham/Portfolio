/// UpdateStuns.cs - UpdateStuns Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;
using Utilities;

/// Game Server
namespace GameServer {

	/// 
	public class UpdateStuns : IntervalEntityProcessingSystem {

		/// Constructor
		public UpdateStuns(int interval) : 
			base(interval, typeof(Stun),
			typeof(PlayerController)) {
				Interval_ = interval;
		}

		/// Load Content
		public override void LoadContent() {
			StunMapper_ = new ComponentMapper<Stun>(EntityWorld);
			VelocityMapper_ = new ComponentMapper<Velocity>(EntityWorld);
			PCControllerMapper_ = new ComponentMapper<PlayerController>(EntityWorld);
		}

		/// Process Entities
		public override void Process(Entity e) {
			
			// Localize
			Stun stun = StunMapper_.Get(e);
			Velocity velocity = VelocityMapper_.Get(e);
			PlayerController PCController = PCControllerMapper_.Get(e);

			// Update Stun Times
			stun.Update(Interval_);

			// Zeros Velocity if the Character is Stunned
			// and Nullifies All Actions
			if (stun.Stunned) {
				velocity.Value = Vector3.Zero;
				PCController.IsMoving = false;
				PCController.State = EAction.Idle;
			// Get rid of the Component to lighten up
			// the amount of processing for this System
			} else
				e.RemoveComponent<Stun>();
		}

		#region Component Mapper
		private ComponentMapper<Stun> StunMapper_;
		private ComponentMapper<Velocity> VelocityMapper_;
		private ComponentMapper<PlayerController> PCControllerMapper_;
		#endregion
		private int Interval_;
	}
}
