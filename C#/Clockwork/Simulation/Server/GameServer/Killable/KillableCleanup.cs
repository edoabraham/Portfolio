/// KillableCleanup.cs - KillableCleanup Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Kills Any Entities that have Expired
	public class KillableCleanup : EntityProcessingSystem {

		/// Constructor
		public KillableCleanup() : base(typeof(Killable)) {
			
		}

		/// Load Content
		public override void LoadContent() {
			KillableMapper_ = new ComponentMapper<Killable>(EntityWorld);
		}

		/// Process Entities
		public override void Process(Entity e) {

			// Localize
			Killable killable = KillableMapper_.Get(e);

			// Checks if an Entity is still Active or Not
			// Kills those that are no Longer Active
			if (!killable.IsAlive) {
				e.Delete();
			}
		}

		#region Component Mapper
		private ComponentMapper<Killable> KillableMapper_;
		#endregion
	}
}
