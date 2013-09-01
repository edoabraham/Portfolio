/// GameTime.cs - GameTime Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Diagnostics;
using System.Collections.Generic;

/// Utilities
namespace Utilities {

	/// Game Time Class
	public class GameTime {

		/// Fixed Time Step Value in Milliseconds
		public const int FixedTimeStepValue = 16;

		/// Constructor
		public GameTime() {
			Stopwatch_ = Stopwatch.StartNew();
			PreviousElapsedTime_ = 0;
			FixedTimeStep_ = true;
		}

		/// Returns the Time in Milliseconds Between
		/// the Current Call and the Previous Call
		public long DeltaTime {
			get {
				// Calculate the Delta Time of Last Previous Reset
				long deltaTime = Stopwatch_.ElapsedMilliseconds
					- PreviousElapsedTime_;

				// Return Delta Time
				return deltaTime;
			}
		}

		/// Time Elapsed from the Start of the Game
		public long ElapsedTime {
			get {
				return Stopwatch_.ElapsedMilliseconds;
			}
		}

		/// Sets Whether a Fixed Time Step is Used or Not
		private bool FixedTimeStep_;
		public bool FixedTimeStep {
			get { return FixedTimeStep_; }
			set { FixedTimeStep_ = value; }
		}

		/// Returns Whether it is Safe to Update the Game Loop
		public bool Update {
			get {
				// Fixed Time Logic
				if (FixedTimeStep_) {

					// Return True when Time is Met
					if (DeltaTime >= FixedTimeStepValue)
						return true;

				} else
					PreviousElapsedTime_ = Stopwatch_.ElapsedMilliseconds;

				// Return False Otherwise
				return false;
			}
		}

		/// Resets the Elapsed Time Timer by Updating the 
		/// Previous Elapsed Time Value with the Current Value
		public void Reset() {
			PreviousElapsedTime_ = Stopwatch_.ElapsedMilliseconds;
		}

		/// Stopwatch that Starts from Startup
		private Stopwatch Stopwatch_;

		/// Records the Elapsed Time from the Start of
		/// the Game from the Previous Call of Delta Time
		private long PreviousElapsedTime_;
	}
}
