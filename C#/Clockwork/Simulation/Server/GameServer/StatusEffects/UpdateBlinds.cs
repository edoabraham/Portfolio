/// UpdateBlinds.cs - UpdateBlinds Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Update Blinds System
	public class UpdateBlinds : IntervalEntityProcessingSystem {

		/// Constructor
		public UpdateBlinds(int interval) : 
			base(interval, typeof(Blind)) {
				Interval_ = interval;
		}

		/// Load Content
		public override void LoadContent() {
			BlindMapper_ = new ComponentMapper<Blind>(EntityWorld);
		}

		/// Process Entities
		public override void Process(Entity e) {
			
			// Localize
			Blind blind = BlindMapper_.Get(e);

			// Update Blind Times
			blind.Update(Interval_);

			// Get rid of expired Blind Components
			if (!blind.Blinded)
				e.RemoveComponent<Blind>();
		}

		#region Component Mapper
		private ComponentMapper<Blind> BlindMapper_;
		#endregion
		private int Interval_;
	}
}
