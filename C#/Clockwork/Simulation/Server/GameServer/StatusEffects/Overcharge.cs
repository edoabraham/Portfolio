/// Overcharge.cs - Overcharge Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Linq;
using Artemis.Interface;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Overcharge Status Effect
	/// Causes a character to randomly get interrupted during
	/// movement or spell usage.
	/// Reduces the amount of Electrical Damage dealt by percentage.
	/// Class keeps track of electric damage debuffs and times.
	/// NOTE: The debuff stacks by a constant value.
	/// NOTE: Overcharge caps at 60% debuff.

	/// Programming Note: There has been some consideration
	/// whether or not to use advanced sorting algorithms.
	/// Since the number of entries will be small, there
	/// will be too much overhead using more complex algorithms.
	/// Therefore, a simple insertion method was used instead.

	/// This Component is Applied Directly the Character's Entity
	public class Overcharge : IComponent {

		/// Electric Damage Debuff Base Percent
		private const float DebuffBasePercent = 20.0f;

		/// Debuff Cap
		private const float DebuffCap = 60.0f;

		/// Constructor
		public Overcharge(int time) {
			Overcharge_ = new List<int>();
			Overcharge_.Add(time);
		}

		/// Times Left
		private List<int> Overcharge_;

		/// Returns the Total Electric Damage Debuff
		public float ElectricDebuff {
			get { 
				float total = DebuffBasePercent * Overcharge_.Count;
				if (total > DebuffCap)
					return DebuffCap;
				else return total;
			}
		}

		/// Adds a new Stack to the List
		public void Add(int time) {
			if (Overcharge_.Any()) {
				int i = 0;
				int j = Overcharge_.Count;
				for (; i < j; i++) {
					// Pushes the lower one down
					if (Overcharge_[i] < time) {
						Overcharge_.Insert(i, time);
						break;
					}
				}
				if (i >= j)
					Overcharge_.Add(time);
			} else
				Overcharge_.Add(time);
		}

		/// Updates the Overcharge Times
		/// Params: Time Elapsed since the last call
		public void Update(int elapsedTime) {
			for (int i = 0, j = Overcharge_.Count; i < j; i++) {
				Overcharge_[i] -= elapsedTime;
			}

			// Clean up Expired Items
			CleanUp();
		}

		/// Checks if there are any Stacks
		public bool Any {
			get { return Overcharge_.Any(); }
		}

		/// Pushes Back all Expired Times
		private void CleanUp() {
			if (Overcharge_.Any()) {
				for (int i = Overcharge_.Count - 1; i >= 0; i++) {
					if(Overcharge_[i] > 0)
						break;
					Overcharge_.RemoveAt(i);
				}
			}
		}
	}
}
