/// Blind.cs - Blind Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis.Interface;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Blind Status Effect
	public class Blind : IComponent {

		/// Constructor
		public Blind(int time) {
			BlindTime_ = time;
		}

		/// Blind Time Left
		private int BlindTime_;

		/// Return whether or not the character is Blinded
		public bool Blinded {
			get { return BlindTime_ > 0; }
		}

		/// Adds more time to the Blindness
		public void Add(int time) {
			if (BlindTime_ > 0)
				BlindTime_ += time;
			else
				BlindTime_ = time;
		}

		/// Updates the remaining time of the Blind
		public void Update(int elapsedTime) {
			BlindTime_ -= elapsedTime;
		}
	}
}
