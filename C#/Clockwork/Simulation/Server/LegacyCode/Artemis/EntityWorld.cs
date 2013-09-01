/// EntityWorld.cs - EntityWorld Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Artemis
namespace ArtemisUnity {

	/// Entity World
	public sealed class EntityWorld {

		/// Main Managers for the World
		private SystemManager SystemManager_;
		private EntityManager EntityManager_;
		private TagManager TagManager_;
		private GroupManager GroupManager_;

		private Bag<Entity> Refreshed_ = new Bag<Entity>();
		private Bag<Entity> Deleted_ = new Bag<Entity>();
		private int Delta_;

		/// Constructor
		public EntityWorld() {
			EntityManager_ = new EntityManager(this);
			SystemManager_ = new SystemManager(this);
			TagManager_ = new TagManager();
			GroupManager_ = new GroupManager();
		}

		public GroupManager GroupManager {
			get { return GroupManager_; }
		}

		public SystemManager SystemManager {
			get { return SystemManager_; }
		}

		public EntityManager EntityManager {
			get { return EntityManager_; }
		}

		public TagManager TagManager {
			get { return TagManager_; }
		}

		/// Returns the Time Since Last Update
		public int Delta {
			get { return Delta_; }
			set { Delta_ = value; }
		}

		/// Deletes Given Entity From the World
		public void DeleteEntity(Entity e) {
			System.Diagnostics.Debug.Assert(e != null);
			Deleted_.Add(e);
		}

		/// Ensures All Systems are Informed on
		/// This Entity's Changes
		internal void RefreshEntity(Entity e) {
			System.Diagnostics.Debug.Assert(e != null);
			Refreshed_.Add(e);
		}

		/// Return New or Unused Entity Instance
		public Entity CreateEntity() {
			return EntityManager_.Create();
		}

		public Entity CreateEntity(string tag) {
			System.Diagnostics.Debug.Assert(!String.IsNullOrEmpty(tag));
			Entity e = EntityManager_.Create();
			TagManager_.Register(tag, e);
			return e;
		}

		/// Returns the Entity of the Given ID
		public Entity GetEntity(int entityId) {
			System.Diagnostics.Debug.Assert(entityId >= 0);
			return EntityManager_.GetEntity(entityId);
		}


		public void LoopStart() {
			if (!Deleted_.IsEmpty) {
				for (int i = 0, j = Deleted_.Size; j > i; i++) {
					Entity e = Deleted_.Get(i);
					EntityManager_.Remove(e);
					GroupManager_.Remove(e);
					e.DeletingState = false;
				}
				Deleted_.Clear();
			}

			if (!Refreshed_.IsEmpty) {
				for (int i = 0, j = Refreshed_.Size; j > i; i++) {
					Entity e = Refreshed_.Get(i);
					EntityManager_.Refresh(e);
					e.RefreshingState = false;
				}
				Refreshed_.Clear();
			}
		}

		public Dictionary<Entity, Bag<ArtemisComponent>> CurrentState {
			get {
				Bag<Entity> entities = EntityManager_.ActiveEntities;
				Dictionary<Entity, Bag<ArtemisComponent>> currentState = new Dictionary<Entity, Bag<ArtemisComponent>>();
				for (int i = 0, j = entities.Size; i < j; i++) {
					Entity e = entities.Get(i);
					Bag<ArtemisComponent> components = e.Components;
					currentState.Add(e, components);
				}
				return currentState;
			}
		}

		/// Load the State of the Entity
		public void LoadEntityState(String tag, String groupName, Bag<ArtemisComponent> components) {
			System.Diagnostics.Debug.Assert(components != null);
			Entity e;
			if (!String.IsNullOrEmpty(tag)) {
				e = CreateEntity(tag);
			} else {
				e = CreateEntity();
			}
			if (String.IsNullOrEmpty(groupName)) {
				GroupManager_.Set(groupName, e);
			}
			for (int i = 0, j = components.Size; i < j; i++) {
				e.AddComponent(components.Get(i));
			}
		}

	}
}
