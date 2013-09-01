/// UpdateBurning.cs - UpdateBurning Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Update Burning System
	public class UpdateBurning : IntervalEntityProcessingSystem {

		/// Constructor
		public UpdateBurning(int interval) : 
			base(interval, typeof(Burning),
			typeof(CurrentStats)) {
				Interval_ = interval;
		}

		/// Load Content
		public override void LoadContent() {
			BurningMapper_ = new ComponentMapper<Burning>(EntityWorld);
			CurrentStatsMapper_ = new ComponentMapper<CurrentStats>(EntityWorld);
		}

		/// Process Entities
		public override void Process(Entity e) {
			
			// Localize
			Burning burning = BurningMapper_.Get(e);
			CurrentStats currStats = CurrentStatsMapper_.Get(e);

			// Update Burning Time
			burning.Update(Interval_);
			
			// Apply effects only if they're still alive
			if (burning.Any) {

				// Deal Damage on Procure
				if (burning.Procure) {
					currStats.Health -= Damage.Magical(currStats.MagicalDefense,
						burning.BurnDamage);
				}

				// Apply Damage Debuffs
				currStats.PhysicalDamage -= Damage.Magical(currStats.MagicalDefense,
					(int)(currStats.PhysicalDamage * burning.DamageDebuff));

			// Get rid of unused Burning Components
			} else e.RemoveComponent<Burning>();
		}

		#region Component Mapper
		private ComponentMapper<Burning> BurningMapper_;
		private ComponentMapper<CurrentStats> CurrentStatsMapper_;
		#endregion
		private int Interval_;
	}
}
