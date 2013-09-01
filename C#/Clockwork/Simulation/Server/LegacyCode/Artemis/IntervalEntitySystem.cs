using System;

namespace ArtemisUnity {
	public abstract class IntervalEntitySystem : EntitySystem {
		private int ACC_;
		private int Interval_;

		public IntervalEntitySystem(int interval, params Type[] types)
			: base(types) {
				this.Interval_ = interval;
		}

		protected override bool CheckProcessing() {
			ACC_ += World.Delta;
			if (ACC_ >= Interval_) {
				ACC_ -= Interval_;
				return Enabled_;
			}
			return false;
		}
	}
}
