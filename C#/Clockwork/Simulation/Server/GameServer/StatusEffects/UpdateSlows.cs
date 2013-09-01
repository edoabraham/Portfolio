/// UpdateSlows.cs - UpdateSlows Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;
using Utilities;

/// Game Server
namespace GameServer {

	/// Update Slows System
	/// NOTE: Must come after the Velocity System
	public class UpdateSlows : IntervalEntityProcessingSystem {

		/// Constructor
		public UpdateSlows(int interval) : 
			base(interval, typeof(Slow), typeof(Velocity)) {
				Interval_ = interval;
		}

		/// Load Content
		public override void LoadContent() {
			SlowMapper_ = new ComponentMapper<Slow>(EntityWorld);
			VelocityMapper_ = new ComponentMapper<Velocity>(EntityWorld);
		}

		/// Process Entity
		public override void Process(Entity e) {
			
			// Localize
			Slow slow = SlowMapper_.Get(e);
			Velocity velocity = VelocityMapper_.Get(e);

			// Update Time
			slow.Update(Interval_);

			// Localize and Get a Normalized version of the Velocity
			Vector3 initVelocity = velocity.Value;
			Vector3 normVelocity = initVelocity.Normalized;
			float slows = slow.Slows;

			// Apply Slow if there is Any
			if (slow.Any)
				velocity.Value = new Vector3(initVelocity - (normVelocity * slows));

			// If there are no Slows left, remove Component
			// This will save this system from processing
			// Entities that no longer have Slows on them
			else
				e.RemoveComponent<Slow>();
		}

		#region Component Mapper
		private ComponentMapper<Slow> SlowMapper_;
		private ComponentMapper<Velocity> VelocityMapper_;
		#endregion
		private int Interval_;
	}
}
