/// TriggerMultiCondition.cs - TriggerMultiCondition Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Artemis
namespace ArtemisUnity {

	/// Trigger Multi Condition
	public class TriggerMultiCondition : Trigger {

		Func<BlackBoard, TriggerState, bool> Condition;
		Action<TriggerState> onFire;

		/// Constructor
		public TriggerMultiCondition(Func<BlackBoard, TriggerState, bool> Condition, Action<TriggerState> onFire = null, params String[] Names) {
			this.WorldPropertiesMonitored.AddRange(Names);
			this.Condition = Condition;
			this.onFire = onFire;
		}

		public void RemoveThisMultiConditionTrigger() {
			BlackBoard.RemoveTrigger(this);
		}

		protected override bool CheckConditionToFire() {
			return Condition(BlackBoard, TriggerState);
		}

		protected override void CalledOnFire(TriggerState TriggerState) {
			if (onFire != null)
				onFire(TriggerState);
		}

	}
}
