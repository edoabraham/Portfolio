/// Killable.cs - Killable Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis.Interface;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Killables include Spells, Items, and Anything that Expires
	/// in the Game after a certain period of Time

	/// Marks an Entity with a 
	/// Time Limit and/or Distance
	/// Travel Limit; Once the Limits
	/// are Met, the Entity is Killed
	public class Killable : IComponent {

		/// Constructor
		public Killable(int timeLimit, float maxDistance = 1.0f) {

			// Initialize
			ElapsedTime_ = 0;
			DistanceTraveled_ = 0;
			IsAlive_ = true;

			// Assign Values
			TimeLimit_ = timeLimit;
			MaxDistance_ = maxDistance;
		}

		/// Time Limit Before Death
		private int TimeLimit_;
		public int TimeLimit {
			get { return TimeLimit_; }
			set { TimeLimit_ = value; }
		}

		/// Elapsed Time Since Entity's Creation
		private int ElapsedTime_;
		public int ElapsedTime {
			get { return ElapsedTime_; }
			set { ElapsedTime_ = value; }
		}

		/// Max Distance that the Entity can Travel
		private float MaxDistance_;
		public float MaxDistance {
			get { return MaxDistance_; }
			set { MaxDistance_ = value; }
		}

		/// Distance Traveled
		private float DistanceTraveled_;
		public float DistanceTraveled {
			get { return DistanceTraveled_; }
			set { DistanceTraveled_ = value; }
		}

		/// Returns if the Entity is Alive or Not
		/// Can be Determined by External Forces
		private bool IsAlive_;
		public bool IsAlive {
			get {
				if (IsAlive_) {
					if ((ElapsedTime_ >= TimeLimit_) || 
						(DistanceTraveled_ >= MaxDistance_))
						IsAlive_ = false;
				}
				return IsAlive_;
			}
			set { IsAlive_ = value; }
		}
	}
}
