/// Slow.cs - Slow Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Linq;
using Artemis.Interface;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Slow Status Effect
	/// Slow is a penalty against a character's movement speed.
	/// Class keeps track of the slow percentages and time left on the slow.

	/// NOTE: Rooting is a 100% Slow Effect
	/// NOTE: Slowing is Calculated After all speed buffs
	/// That's why it doesn't account for the same system.
	/// This also makes rooting possible.

	/// Programming Note: There has been some consideration
	/// whether or not to use advanced sorting algorithms.
	/// Since the number of entries will be small, there
	/// will be too much overhead using more complex algorithms.
	/// Therefore, a simple insertion method was used instead.

	/// This Component is Applied Directly the Character's Entity
	public class Slow : IComponent {

		/// Constructor
		public Slow(float slowPercent, int time) {
			Slows_ = new List<KeyValuePair<float, int>>();
			Slows_.Add(new KeyValuePair<float, int>(slowPercent, time));
		}

		/// List of Applied Slows
		/// Key Value Pair is [slow value, time remaining]
		private List<KeyValuePair<float, int>> Slows_;

		/// Sums Up All the Slows for the Total Debuff Value
		/// Value Cannot Exceed 100 and Cannot Fall Below 0
		public float Slows {
			get {
				// Total Slows
				float sum = 0;
				foreach (KeyValuePair<float, int> item in Slows_) {
					sum += item.Key;
				}

				// Return Within Bounds
				if (sum < 0)
					return 0;
				else if (sum > 100)
					return 100;
				else 
					return sum;
			}
		}

		/// Adds a new Slow to the List
		public void Add(int value, int time) {
			// Insert by Descending Order
			if(Slows_.Any()) {
				int i = 0;
				int j = Slows_.Count;
				for (; i < j; i++) {
					// Pushes the lower one down
					if(Slows_[i].Value < time) {
						Slows_.Insert(i, new KeyValuePair<float, int>(value, time));
						break;
					}
				}
				if(i >= j)
					Slows_.Add(new KeyValuePair<float, int>(value, time));
			} else
				Slows_.Add(new KeyValuePair<float, int>(value, time));
		}

		/// Updates All the Slow Times
		/// Params: Time Elapsed Since Last Call
		public void Update(int elapsedTime) {
			
			for(int i = 0, j = Slows_.Count; i < j; i++) {
				Slows_[i] = new KeyValuePair<float, int>(Slows_[i].Key, 
					Slows_[i].Value - elapsedTime);
			}

			// Clean Up Expired Items
			CleanUp();
		}

		/// Checks if There Any Slows Left
		public bool Any {
			get { return Slows_.Any(); }
		}

		/// Pushes Back all Expired Times
		private void CleanUp() {
			if (Slows_.Any()) {
				for (int i = Slows_.Count - 1; i >= 0; i++) {
					if(Slows_[i].Value > 0)
						break;
					Slows_.RemoveAt(i);
				}
			}
		}
	}
}
