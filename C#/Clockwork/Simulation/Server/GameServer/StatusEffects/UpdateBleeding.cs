/// UpdateBleeding.cs - UpdateBleeding Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Update Bleeding System
	public class UpdateBleeding : IntervalEntityProcessingSystem {

		/// Constructor
		public UpdateBleeding(int interval) : 
			base(interval, typeof(Bleeding), typeof(PlayerController), 
			typeof(CurrentStats), typeof(Statistics)) {
				Interval_ = interval;
		}

		/// Load Content
		public override void LoadContent() {
			BleedingMapper_ = new ComponentMapper<Bleeding>(EntityWorld);
			CurrentStatsMapper_ = new ComponentMapper<CurrentStats>(EntityWorld);
			StatisticsMapper_ = new ComponentMapper<Statistics>(EntityWorld);
			PCControllerMapper_ = new ComponentMapper<PlayerController>(EntityWorld);
		}

		/// Process Entities
		public override void Process(Entity e) {
			
			// Localize
			Bleeding bleeding = BleedingMapper_.Get(e);
			CurrentStats currStats = CurrentStatsMapper_.Get(e);
			Statistics stats = StatisticsMapper_.Get(e);
			PlayerController PCController = PCControllerMapper_.Get(e);

			// Update Bleeding Time
			bleeding.Update(Interval_);
			
			// Apply active effects
			if (bleeding.Any) {

				// Deal Damage on Procure
				if (bleeding.Procure) {
					currStats.Health -= Damage.Physical(currStats.PhysicalDefense,
						(int)(stats.Health * bleeding.PercentDamage));

					// Deal Action Damage on Movement or Spell Cast
					if (PCController.IsMoving || (PCController.State != EAction.Idle))
						currStats.Health -= Damage.Physical(currStats.PhysicalDefense,
							bleeding.ActionDamage);
				}
			
			// Get rid of unused Bleeding Components
			} else e.RemoveComponent<Bleeding>();
		}

		#region Component Mapper
		private ComponentMapper<Bleeding> BleedingMapper_;
		private ComponentMapper<CurrentStats> CurrentStatsMapper_;
		private ComponentMapper<Statistics> StatisticsMapper_;
		private ComponentMapper<PlayerController> PCControllerMapper_;
		#endregion
		private int Interval_;
	}
}
