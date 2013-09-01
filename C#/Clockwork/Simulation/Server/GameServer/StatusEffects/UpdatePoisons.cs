/// UpdatePoisons.cs - UpdatePoisons Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Update Poison System
	/// NOTE: Must go before all other status effect systems.
	public class UpdatePoisons : IntervalEntityProcessingSystem {

		/// Constructor
		public UpdatePoisons(int interval) : 
			base(interval, typeof(Poison),
			typeof(CurrentStats), typeof(Statistics)) {
				Interval_ = interval;
		}

		/// Load Content
		public override void LoadContent() {
			PoisonMapper_ = new ComponentMapper<Poison>(EntityWorld);
			CurrentStatsMapper_ = new ComponentMapper<CurrentStats>(EntityWorld);
			StatisticsMapper_ = new ComponentMapper<Statistics>(EntityWorld);
		}

		/// Process Entities
		public override void Process(Entity e) {
			
			// Localize
			Poison poison = PoisonMapper_.Get(e);
			CurrentStats currStats = CurrentStatsMapper_.Get(e);
			Statistics stats = StatisticsMapper_.Get(e);

			// Update Poison Time
			poison.Update(Interval_);

			// Apply active effects
			if (poison.Any) {

				// Apply Debuffs
				currStats.MagicalDefense -= (int)(currStats.MagicalDefense *
					poison.MagicDefenseDebuff);
				currStats.PhysicalDefense -= (int)(currStats.PhysicalDefense *
					poison.PhysicalDefenseDebuff);

				// Deal Damage on Procure
				if (poison.Procure) {
					currStats.Health -= Damage.Magical(currStats.MagicalDefense,
						(int)(stats.Health * poison.DamagePercent) + poison.FlatDamage);
				}

			// Get rid of unused Poison Components
			} else e.RemoveComponent<Poison>();
		}

		#region Component Mapper
		private ComponentMapper<Poison> PoisonMapper_;
		private ComponentMapper<CurrentStats> CurrentStatsMapper_;
		private ComponentMapper<Statistics> StatisticsMapper_;
		#endregion
		private int Interval_;
	}
}
