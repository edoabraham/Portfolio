/// UpdateOvercharge.cs - UpdateOvercharge Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Update Overcharge System
	public class UpdateOvercharge : IntervalEntityProcessingSystem {

		/// Resolution of Randomness
		const int ResolutionRandomness = 10;

		/// Constructor
		public UpdateOvercharge(int interval, 
			float interruptFrequency) :
			base(interval, typeof(Overcharge),
			typeof(CurrentStats), typeof(Controller)) {
				Interval_ = interval;
				InterruptFrequency_ = (int) (ResolutionRandomness * interruptFrequency);
				MaxRandomRange_ = ResolutionRandomness * 100;
		}

		/// Load Content
		public override void LoadContent() {
			OverchargeMapper_ = new ComponentMapper<Overcharge>(EntityWorld);
			CurrentStatsMapper_ = new ComponentMapper<CurrentStats>(EntityWorld);
			PCControllerMapper_ = new ComponentMapper<PlayerController>(EntityWorld);
		}

		/// Process Entities
		public override void Process(Entity e) {
			
			// Localize
			Overcharge overcharge = OverchargeMapper_.Get(e);
			CurrentStats currStats = CurrentStatsMapper_.Get(e);
			PlayerController PCController = PCControllerMapper_.Get(e);

			// Update Times
			overcharge.Update(Interval_);

			// Apply active effects
			if (overcharge.Any) {

				// Apply Debuffs
				currStats.MagicalDamage -= (int)(currStats.MagicalDamage * 
					overcharge.ElectricDebuff);

				// Seed Random and Set Range
				Random rand = new Random(DateTime.Now.Millisecond);
				if((rand.Next(0, MaxRandomRange_)) <= InterruptFrequency_) {

					// Interrupt Actions
					PCController.State = EAction.Idle;
					PCController.IsMoving = false;
				}

			// Get rid of expired Overcharge Components
			} else e.RemoveComponent<Overcharge>();
		}

		#region Component Mapper
		private ComponentMapper<Overcharge> OverchargeMapper_;
		private ComponentMapper<CurrentStats> CurrentStatsMapper_;
		private ComponentMapper<PlayerController> PCControllerMapper_;
		#endregion
		private int Interval_;

		/// Frequency of a Character being interrupted
		private int InterruptFrequency_;
		private int MaxRandomRange_;
	}
}
