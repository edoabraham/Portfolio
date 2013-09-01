/// Blink.cs - Blink Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis.Interface;
using System.Collections.Generic;
using Utilities;

/// Game Server
namespace GameServer {

	/// Blink
	/// Blink is rapid travel directly to a certain target spot.
	/// Blink will allow a character to pass through walls (ignores Wall Collision).
	/// Unlike the Velocity Component, Blink finishes after it has traveled
	/// a certain distance. It will also adjust the last call so that
	/// the velocity will not cause the Character to overshoot the target.
	/// Blink will change the facing direction of the character.
	public class Blink : IComponent {

		/// Constructor
		public Blink(Vector3 startPosition, 
			Vector3 target, float speed) {
				StartPosition_ = startPosition;
				Target_ = target;
				Speed_ = speed;
				Distance_ = (Target_ - StartPosition_).Length;
				CalculateVelocity();
		}

		/// Starting Position
		private Vector3 StartPosition_;

		/// Blink Target
		private Vector3 Target_;

		/// Speed of the Blink
		private float Speed_;

		/// Distance to Travel
		private float Distance_;

		/// Direction of the Blink
		private float Direction_;
		public float Direction {
			get { return Direction_; }
		}

		/// Returns the Velocity of the Blink
		private Vector3 Velocity_;
		public Vector3 Velocity {
			get {
				CalculateLastStep();
				Distance_ -= Speed_;
				return Velocity_; 
			}
		}

		/// Calculates the Velocity of the Blink
		private void CalculateVelocity() {

			Vector3 normVector = (Target_ - StartPosition_).Normalized;

			if ((Distance_ - Speed_) < 0) {
				Velocity_ = normVector * (Distance_ - Speed_);
			} else {
				Velocity_ = normVector * Speed_;
			}

			Direction_ = (float)Math.Atan(normVector.X / normVector.Y);
		}

		/// Calculates the last Velocity step when needed
		private void CalculateLastStep() {
			if ((Distance_ - Speed_) < 0) {
				Velocity_ = (Target_ - StartPosition_).Normalized * (Distance_ - Speed_);
			}
		}

		/// Returns if the Travel has Completed or Not
		public bool Finished {
			get { return (Distance_ <= 0); }
		}
	}
}
