/// Burning.cs - Burning Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Linq;
using Artemis.Interface;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Burning Status Effect
	/// Causes character to receive Magical Damage and 
	/// reduces the damage of the character by percentage.
	/// Class keeps track of damage, debuff percents, and time left.

	/// Programming Note: There has been some consideration
	/// whether or not to use advanced sorting algorithms.
	/// Since the number of entries will be small, there
	/// will be too much overhead using more complex algorithms.
	/// Therefore, a simple insertion method was used instead.

	/// This Component is Applied Directly the Character's Entity
	public class Burning : IComponent {

		/// Damage Frequency in Milliseconds
		private const int DamageFrequency = 1000;

		/// Constructor
		public Burning(int burnDamage, float damageDebuff, int time) {
			Burning_ = new List<Tuple<int, float, int>>();
			Burning_.Add(new Tuple<int, float, int>(burnDamage, 
				damageDebuff, time));
			Timer_ = 0;
		}

		/// Damage, Attack Debuff, Time Left
		private List<Tuple<int, float, int>> Burning_;

		/// Returns if the Damage has Procured or Not
		public bool Procure {
			get { return (Timer_ == 0); }
		}

		/// Returns the Total Burn Damage
		/// Call Only when Needed
		public int BurnDamage {
			get {
				int sum = 0;
				foreach (Tuple<int, float, int> item in Burning_) {
					sum += item.Item1;
				}
				return sum;
			}
		}

		/// Returns the Total Debuff Percentage
		/// Call Only when Needed
		public float DamageDebuff {
			get {
				float sum = 0;
				foreach (Tuple<int, float, int> item in Burning_) {
					sum += item.Item2;
				}

				// Return within Bounds
				if (sum > 100)
					return 100;
				else if (sum < 0)
					return 0;
				else
					return sum;
			}
		}

		/// Adds a new Burn to the List
		public void Add(int burnDamage, float damageDebuff, int time) {
			if (Burning_.Any()) {
				int i = 0;
				int j = Burning_.Count;
				for (; i < j; i++) {
					// Pushes the lower one down
					if (Burning_[i].Item3 < time) {
						Burning_.Insert(i, new Tuple<int, float, int>(burnDamage, damageDebuff, time));
						break;
					}
				}
				if (i >= j)
					Burning_.Add(new Tuple<int, float, int>(burnDamage, damageDebuff, time));
			} else
				Burning_.Add(new Tuple<int, float, int>(burnDamage, damageDebuff, time));
		}

		/// Updates the Burning Times;
		/// Params: Time Elapsed Since Last Call
		public void Update(int elapsedTime) {

			for (int i = 0, j = Burning_.Count; i < j; i++) {
				Burning_[i] = new Tuple<int, float, int>(Burning_[i].Item1,
					Burning_[i].Item2, Burning_[i].Item3 - elapsedTime);
			}

			Timer_ += elapsedTime;
			if (Timer_ >= DamageFrequency)
				Timer_ = 0;

			// Clean Up Expired Items
			CleanUp();
		}

		/// Checks if there is any Burning
		public bool Any {
			get { return Burning_.Any(); }
		}

		/// Pushes Back all Expired Times
		private void CleanUp() {
			if (Burning_.Any()) {
				for (int i = Burning_.Count - 1; i >= 0; i++) {
					if(Burning_[i].Item3 > 0)
						break;
					Burning_.RemoveAt(i);
				}
			}
		}

		/// Timer for Damage
		private int Timer_;
	}
}
