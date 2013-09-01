/// Trigger.cs - Trigger Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Artemis
namespace ArtemisUnity {

	/// Trigger
	public class Trigger {

		/// Constructor
		public Trigger(params String[] PropertyName) {
			WorldPropertiesMonitored = new List<string>();
			foreach (var item in PropertyName)
				WorldPropertiesMonitored.Add(item);
		}

		public List<String> WorldPropertiesMonitored {
			get;
			protected set;
		}

		public TriggerState TriggerState {
			get;
			private set;
		}

		public BlackBoard BlackBoard {
			get;
			internal set;
		}

		public void RemoveThisTrigger() {
			BlackBoard.RemoveTrigger(this);
		}

		internal bool Fired = false;
		internal void Fire(TriggerState TriggerState) {
			Fired = true;
			this.TriggerState = TriggerState;
			if (CheckConditionToFire()) {
				CalledOnFire(TriggerState);
				if (OnFire != null)
					OnFire(this);
			}
			Fired = false;
		}

		public event Action<Trigger> OnFire;

		protected virtual bool CheckConditionToFire() {
			return true;
		}

		protected virtual void CalledOnFire(TriggerState TriggerState) {

		}
	}

	public enum TriggerState : long {
		VALUE_ADDED = 0x00001,
		VALUE_REMOVED = 0x00010,
		VALUE_CHANGED = 0x00100,
		TRIGGER_ADDED = 0x01000
    }
}
