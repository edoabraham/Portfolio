/// UpdateKillableDistance.cs - UpdateKillableDistance Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Updates the Distance Traveled by All Killable Objects
	public class UpdateKillableDistance : EntityProcessingSystem {

		/// Constructor
		public UpdateKillableDistance() : 
			base(typeof(Killable), typeof(Velocity)) {
			
		}

		/// Load Content
		public override void LoadContent() {
			KillableMapper_ = new ComponentMapper<Killable>(EntityWorld);
			VelocityMapper_ = new ComponentMapper<Velocity>(EntityWorld);
		}

		/// Process All Velocity Bound Killables
		public override void Process(Entity e) {
			
			/// Localize
			Killable killable = KillableMapper_.Get(e);
			Velocity velocity = VelocityMapper_.Get(e);

			/// Update Distance
			killable.DistanceTraveled += velocity.Value.Length;
		}

		#region Component Mapper
		private ComponentMapper<Killable> KillableMapper_;
		private ComponentMapper<Velocity> VelocityMapper_;
		#endregion
	}
}
