/// SimpleTrigger.cs - SimpleTrigger Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Artemis
namespace ArtemisUnity {

	/// Simple Trigger
	public class SimpleTrigger : Trigger {

		Func<BlackBoard, TriggerState, bool> Condition;
		Action<TriggerState> onFire;

		/// Constructor
		public SimpleTrigger(String Name, Func<BlackBoard, TriggerState, bool> Condition, Action<TriggerState> onFire = null) {
			this.WorldPropertiesMonitored.Add(Name);
			this.Condition = Condition;
			this.onFire = onFire;
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
