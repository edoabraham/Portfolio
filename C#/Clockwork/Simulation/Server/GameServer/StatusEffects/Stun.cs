/// Stun.cs - Stun Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis.Interface;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Stun Status Effect
	/// Prevents a character from moving or using spells.
	/// Class keeps track of stun times.
	/// NOTE: Stuns do not stack, but the harder stun (max time)
	/// takes over.

	/// This Component is Applied Directly the Character's Entity
	public class Stun : IComponent {

		/// Constructor
		public Stun(int stunTime) {
			StunTime_ = stunTime;
		}

		/// Stun Time Left
		private int StunTime_;

		/// Returns if a Character is still Stunned or Not
		public bool Stunned {
			get {
				if(StunTime_ > 0)
					return true;
				return false;
			}
		}

		/// Update the Time on the Stun
		public void Update(int elapsedTime) {
			StunTime_ -= elapsedTime;
		}

		/// Applies a new Stun to the Entity
		/// Takes the max of the current Stun
		/// time left and the newly applied Stun.
		public void Apply(int stunTime) {
			StunTime_ = (stunTime > StunTime_) 
				? stunTime : StunTime_;
		}
	}
}
