/// EntitySystem.cs - EntitySystem Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Define Type BigInteger
using BigInteger = System.Int64;

/// Artemis
namespace ArtemisUnity {

	/// Entity System
	public class EntitySystem {

		protected static BlackBoard BlackBoard_ = new BlackBoard();

		public static BlackBoard BlackBoard {
			get {
				return BlackBoard_;
			}
		}

		private BigInteger SystemBit_ = 0;

		private BigInteger TypeFlags_ = 0;

		protected bool Enabled_ = true;

		protected EntityWorld World_;

		private Dictionary<int, Entity> Actives_ = new Dictionary<int, Entity>();

		public EntitySystem() {

		}

		public EntitySystem(params Type[] types) {
			for (int i = 0, j = types.Length; i < j; i++) {
				Type type = types[i];
				ComponentType ct = ComponentTypeManager.GetTypeFor(type);
				TypeFlags_ |= ct.Bit;
			}
		}

		internal BigInteger SystemBit {
			set { SystemBit_ = value; }
		}

		/// Called Before Processing Entities Begins
		protected virtual void Begin() { }

		public virtual void Process() {
			if (CheckProcessing()) {
				Begin();
				ProcessEntities(Actives_);
				End();
			}
		}

		/// Called After Processing Entities Ends
		protected virtual void End() { }

		/**
		 * Any implementing entity system must implement this method and the logic
		 * to process the given entities of the system.
		 * 
		 * @param entities the entities this system contains.
		 */
		protected virtual void ProcessEntities(Dictionary<int, Entity> entities) { }

		/// Returns True if the System Should Be Processed, False Otherwise
		protected virtual bool CheckProcessing() { return Enabled_; }

		/// Executed When System is Initialized
		public virtual void Initialize() { }

		/**
		 * Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
		 * @param e the entity that was added to this system.
		 */
		public virtual void Added(Entity e) { }
		/**
		 * Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
		 * @param e the entity that was removed from this system.
		 */
		public virtual void OnRemoved(Entity e) { }

		public virtual void OnEnabled(Entity e) { }

		public virtual void OnDisabled(Entity e) { }

		public virtual void OnChange(Entity e) {
			System.Diagnostics.Debug.Assert(e != null);
			bool contains = (SystemBit_ & e.SystemBits) == SystemBit_;
			bool interest = (TypeFlags_ & e.TypeBits) == TypeFlags_;

			if (interest && !contains && TypeFlags_ > 0) {
				Add(e);
			} else if (!interest && contains && TypeFlags_ > 0) {
				Remove(e);
			} else if (interest && contains && e.Enabled == true && TypeFlags_ > 0) {
				Enable(e);
			} else if (interest && contains && e.Enabled == false && TypeFlags_ > 0) {
				Disable(e);
			}
		}

		protected void Add(Entity e) {
			System.Diagnostics.Debug.Assert(e != null);
			e.AddSystemBit(SystemBit_);
			if (e.Enabled == true) {
				Enable(e);
			}
			Added(e);
		}

		protected void Remove(Entity e) {
			System.Diagnostics.Debug.Assert(e != null);
			e.RemoveSystemBit(SystemBit_);
			if (e.Enabled == true) {
				Disable(e);
			}
			OnRemoved(e);
		}

		private void Enable(Entity e) {
			System.Diagnostics.Debug.Assert(e != null);
			if (Actives_.ContainsKey(e.ID)) {
				return;
			}
			Actives_.Add(e.ID, e);
			OnEnabled(e);
		}

		private void Disable(Entity e) {
			System.Diagnostics.Debug.Assert(e != null);

			if (!Actives_.ContainsKey(e.ID)) {
				return;
			}
			Actives_.Remove(e.ID);
			OnDisabled(e);
		}

		public EntityWorld World {
			internal set { World_ = value; }
			get { return World_; }

		}

		public void Toggle() {
			Enabled_ = !Enabled_;
		}

		public bool Enabled {
			set { this.Enabled_ = value; }
			get { return Enabled_; }
		}


		/**
		 * Merge together a required type and a array of other types. Used in derived systems.
		 * @param requiredType
		 * @param otherTypes
		 * @return
		 */
		public static Type[] GetMergedTypes(Type requiredType, params Type[] otherTypes) {
			System.Diagnostics.Debug.Assert(requiredType != null);
			Type[] types = new Type[1 + otherTypes.Length];
			types[0] = requiredType;
			for (int i = 0, j = otherTypes.Length; j > i; i++) {
				types[i + 1] = otherTypes[i];
			}
			return types;
		}

	}
}
