/// Bleeding.cs - Bleeding Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Linq;
using Artemis.Interface;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Bleeding Status Effect
	/// Causes the character to constantly receive physical Damage
	/// for a certain amount of time.
	/// Does base damage depending on how many damage stacks there
	/// are and extra damage when moving or using spells.
	/// Only the Action damage is listed separately.
	/// Class keeps track of base percent damage, action damage, and times.
	/// NOTE: Base Percent Damage does percentage damage whereas action damage
	/// is applied flat damage. Make sure to keep track of this!

	/// Programming Note: There has been some consideration
	/// whether or not to use advanced sorting algorithms.
	/// Since the number of entries will be small, there
	/// will be too much overhead using more complex algorithms.
	/// Therefore, a simple insertion method was used instead.

	/// This Component is Applied Directly the Character's Entity
	public class Bleeding : IComponent {

		/// Base Percent Damage per Stack
		private const float BasePercentDamage = 1.5f;

		/// Damage Frequency in Milliseconds
		private const int DamageFrequency = 1000;

		/// Constructor
		public Bleeding(int damage, int time) {
			Bleeding_ = new List<KeyValuePair<int, int>>();
			Bleeding_.Add(new KeyValuePair<int, int>(damage, time));
			Timer_ = 0;
		}

		/// Flat Action Damage, Time Left
		private List<KeyValuePair<int, int>> Bleeding_;

		/// Returns if the Damage has Procured or Not
		public bool Procure {
			get { return (Timer_ == 0); }
		}

		/// Returns the Total Amount of Base Damage
		public float PercentDamage {
			get {
				return BasePercentDamage * Bleeding_.Count;
			}
		}

		/// Returns the Total Action Damage
		/// Call Only When Needed
		public int ActionDamage {
			get {
				int sum = 0;
				foreach (KeyValuePair<int, int> item in Bleeding_) {
					sum += item.Key;
				}
				return sum;
			}
		}

		/// Adds a new Bleed to the List
		public void Add(int damage, int time) {
			if (Bleeding_.Any()) {
				int i = 0;
				int j = Bleeding_.Count;
				for (; i < j; i++) {
					// Pushes the lower one down
					if (Bleeding_[i].Value < time) {
						Bleeding_.Insert(i, new KeyValuePair<int, int>(damage, time));
						break;
					}
					
				}
				if (i >= j)
					Bleeding_.Add(new KeyValuePair<int, int>(damage, time));
			} else
				Bleeding_.Add(new KeyValuePair<int, int>(damage, time));
		}

		/// Updates the Bleeding Times
		/// Params: Time Elapsed since last call
		public void Update(int elapsedTime) {

			for (int i = 0, j = Bleeding_.Count; i < j; i++) {
				Bleeding_[i] = new KeyValuePair<int, int>(Bleeding_[i].Key,
					Bleeding_[i].Value - elapsedTime);
			}

			Timer_ += elapsedTime;
			if (Timer_ >= DamageFrequency)
				Timer_ = 0;

			// Clean up Expired Items
			CleanUp();
		}

		/// Checks if there is any Bleeding
		public bool Any {
			get {
				return Bleeding_.Any();
			}
		}

		/// Pushes Back all Expired Times
		private void CleanUp() {
			if (Bleeding_.Any()) {
				for (int i = Bleeding_.Count - 1; i >= 0; i++) {
					if(Bleeding_[i].Value > 0)
						break;
					Bleeding_.RemoveAt(i);
				}
			}
		}

		/// Timer for Damage
		private int Timer_;
	}
}
