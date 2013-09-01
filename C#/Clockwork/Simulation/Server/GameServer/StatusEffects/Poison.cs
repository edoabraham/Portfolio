/// Poison.cs - Poison Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Linq;
using Artemis.Interface;
using System.Collections.Generic;

/// Game Servers
namespace GameServer {

	/// Poison Status Effect
	/// Causes a character to continually receive Magical Damage
	/// and weakens a player's Magical and Physical Defense.
	/// 

	/// Programming Note: There has been some consideration
	/// whether or not to use advanced sorting algorithms.
	/// Since the number of entries will be small, there
	/// will be too much overhead using more complex algorithms.
	/// Therefore, a simple insertion method was used instead.

	/// This Component is Applied Directly the Character's Entity
	public class Poison : IComponent {

		/// Percent Damage per Stack
		private const float PercentDamage = 1.5f;

		/// Percent Magical Defense Debuff per Stack
		private const float MagicalDefenseDebuffPercent = 6.0f;

		/// Percent Physical Defense Debuff per Stack
		private const float PhysicalDefenseDebuffPercent = 8.0f;

		/// Max Magical Debuff Percentage
		private const float MaxMagicalDefDebuff = 30.0f;

		/// Damage Frequency in Milliseconds
		private const int DamageFrequency = 1000;

		/// Max Physical Debuff Percentage
		private const float MaxPhysicalDefDebuff = 40.0f;

		/// Constructor
		public Poison(int damage, int time) {
			Poison_ = new List<KeyValuePair<int, int>>();
			Poison_.Add(new KeyValuePair<int, int>(damage, time));
			Timer_ = 0;
		}

		/// Flat Damage, Time Left
		private List<KeyValuePair<int, int>> Poison_;

		/// Returns if the Damage has Procured or Not
		public bool Procure {
			get { return (Timer_ == 0); }
		}

		/// Returns the total Damage Percent based on
		/// the number of Poison Stacks
		public float DamagePercent {
			get { return PercentDamage * Poison_.Count; }
		}

		/// Returns the total Magical Defense Debuff
		/// based on the number of Poison Stacks
		public float MagicDefenseDebuff {
			get {
				float product = MagicalDefenseDebuffPercent *
					Poison_.Count;

				System.Diagnostics.Debug.Assert(product >= 0);

				if (product > MaxMagicalDefDebuff)
					return MaxMagicalDefDebuff;
				else return product;
			}
		}

		/// Returns the total Magical Defense Debuff
		public float PhysicalDefenseDebuff {
			get {
				float product = PhysicalDefenseDebuffPercent *
					Poison_.Count;

				System.Diagnostics.Debug.Assert(product >= 0);

				if (product > MaxPhysicalDefDebuff)
					return MaxPhysicalDefDebuff;
				else return product;
			}
		}

		/// Returns the total Flat Magic Damage
		/// Call only when needed
		public int FlatDamage {
			get {
				int sum = 0;
				foreach (KeyValuePair<int, int> item in Poison_) {
					sum += item.Key;
				}
				return sum;
			}
		}

		/// Adds a new Poison Stack to the List
		public void Add(int damage, int time) {
			if (Poison_.Any()) {
				int i = 0;
				int j = Poison_.Count;
				for (; i < j; i++) {
					// Pushes the lower one down
					if (Poison_[i].Value < time) {
						Poison_.Insert(i, new KeyValuePair<int, int>(damage, time));
						break;
					}
				}
				if (i >= j)
					Poison_.Add(new KeyValuePair<int, int>(damage, time));
			} else
				Poison_.Add(new KeyValuePair<int, int>(damage, time));
		}

		/// Updates the Poison Times
		/// ParamsL Time Elapsed since last call
		public void Update(int elapsedTIme) {

			for (int i = 0, j = Poison_.Count; i < j; i++) {
				Poison_[i] = new KeyValuePair<int, int>(Poison_[i].Key,
					Poison_[i].Value - elapsedTIme);
			}

			Timer_ += elapsedTIme;
			if (Timer_ >= DamageFrequency)
				Timer_ = 0;

			// Clean up Expired Times
			CleanUp();
		}

		/// Checks if there are any Poisons
		public bool Any {
			get { return Poison_.Any(); }
		}

		/// Pushes Back all Expired Times
		private void CleanUp() {
			if (Poison_.Any()) {
				for (int i = Poison_.Count - 1; i >= 0; i++) {
					if(Poison_[i].Value > 0)
						break;
					Poison_.RemoveAt(i);
				}
			}
		}

		/// Timer of Damage
		private int Timer_;
	}
}
