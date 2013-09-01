/// UpdateKillableTime.cs - UpdateKillableTime Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Updates the Time Elapsed Since Entities Creation
	public class UpdateKillableTime : EntityProcessingSystem {

		/// Constructor
		public UpdateKillableTime() : base(typeof(Killable)) {
			
		}

		/// Load Content
		public override void LoadContent() {
			KillableMapper_ = new ComponentMapper<Killable>(EntityWorld);
		}

		/// Process Entities
		public override void Process(Entity e) {
			
			// Localize
			Killable killable = KillableMapper_.Get(e);

			// Add Delta Time
			killable.ElapsedTime += (int)EntityWorld.Delta;
		}

		#region Component Mapper
		private ComponentMapper<Killable> KillableMapper_;
		#endregion
	}
}
