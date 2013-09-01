/// EntitySystem.cs - EntitySystem Class Implementation
/// Written By Jesse Z. Zhong

using System;

/// Artemis
namespace ArtemisUnity {

	/// Handles Calls for Adding and Removing Entities and Components
	public delegate void RemovedComponentHandler(Entity e, ArtemisComponent c);
	public delegate void RemovedEntityHandler(Entity e);
	public delegate void AddedComponentHandler(Entity e, ArtemisComponent c);
	public delegate void AddedEntityHandler(Entity e);

	/// Entity Manager
	public sealed class EntityManager {

		/// World Instance for Reference
		private EntityWorld World_;

		/// Collection of Entities
		private Bag<Entity> ActiveEntities_ = new Bag<Entity>();
		private Bag<Entity> RemovedAndAvailableEntities_ = new Bag<Entity>();

		/// Assigns New Entities with Next Available ID
		private int NextAvailableID_;

		/// Number of Active Entities
		private int Count_;

		/// Assigns New Entities with a Unique ID
		private long UniqueEntityID_;

		/// Entities' Statistical Data
		private long TotalEntitiesCreated_;
		private long TotalEntitiesRemoved_;

		/// Events for Handling Adds and Removes of Entities and Components
		public event RemovedComponentHandler RemovedComponentEvent;
		public event RemovedEntityHandler RemovedEntityEvent;
		public event AddedComponentHandler AddedComponentEvent;
		public event AddedEntityHandler AddedEntityEvent;

		/// Collection of Components Organized by Type
		private Bag<Bag<ArtemisComponent>> ComponentsByType_ = new Bag<Bag<ArtemisComponent>>();

		/// Collection of Entity Components
		private Bag<ArtemisComponent> EntityComponents_ = new Bag<ArtemisComponent>();

		/// Constructor
		public EntityManager(EntityWorld world) {
			System.Diagnostics.Debug.Assert(world != null);
			this.World_ = world;
		}

		/// Create a New Entity
		public Entity Create() {
			// Recycle an Unused Entity, if There is One
			Entity e = RemovedAndAvailableEntities_.RemoveLast();
			if (e == null)
				e = new Entity(World_, NextAvailableID_++);
			else
				e.Reset();

			// Assign a New Unique ID
			e.UniqueID = UniqueEntityID_++;

			// Push into Active Entities Container
			ActiveEntities_.Set(e.ID, e);

			// Update Statistics
			Count_++;
			TotalEntitiesCreated_++;

			// Call the Event
			if (AddedEntityEvent != null)
				AddedEntityEvent(e);

			// Return Reference to the New Entity
			return e;
		}

		/// Remove an Entity from the World
		public void Remove(Entity e) {
			System.Diagnostics.Debug.Assert(e != null);
			ActiveEntities_.Set(e.ID, null);

			e.TypeBits = 0;

			Refresh(e);

			RemoveComponentsOfEntity(e);

			// Update Statistics
			Count_--;
			TotalEntitiesCreated_++;

			// Push into Non-Active but 
			// Available Entities Container
			RemovedAndAvailableEntities_.Add(e);

			// Call the Event
			if (RemovedEntityEvent != null)
				RemovedEntityEvent(e);
		}

		/// Strips All Components from a Given Entity
		internal void RemoveComponentsOfEntity(Entity e) {
			System.Diagnostics.Debug.Assert(e != null);

			// Iterate through and Detach Components
			int entityID = e.ID;
			for (int i = 0, j = ComponentsByType_.Size; i < j; i++) {
				Bag<ArtemisComponent> components = ComponentsByType_.Get(i);
				if ((components != null) && (entityID < components.Size)) {

					// Remove the Component
					if (RemovedComponentEvent != null)
						RemovedComponentEvent(e, components.Get(entityID));
				}
				components.Set(entityID, null);
			}
		}

		/// Check if This Entity is Active
		public bool IsActive(int entityID) {
			return ActiveEntities_.Get(entityID) != null;
		}

		/// Add a Given Component to a Given Entity
		internal void AddComponent(Entity e, ArtemisComponent component) {
			System.Diagnostics.Debug.Assert(e != null);
			System.Diagnostics.Debug.Assert(component != null);

			ComponentType type = ComponentTypeManager.GetTypeFor(component.GetType());

			if (type.ID >= ComponentsByType_.Capacity) {
				ComponentsByType_.Set(type.ID, null);
			}

			Bag<ArtemisComponent> components = ComponentsByType_.Get(type.ID);
			if (components == null) {
				components = new Bag<ArtemisComponent>();
				ComponentsByType_.Set(type.ID, components);
			}

			components.Set(e.ID, component);

			e.AddTypeBit(type.Bit);
			if (AddedComponentEvent != null) {
				AddedComponentEvent(e, component);
			}
		}

		/// Add a Given Component to a Given Entity
		internal void AddComponent<T>(Entity e, ArtemisComponent component) where T : ArtemisComponent {
			System.Diagnostics.Debug.Assert(component != null);
			System.Diagnostics.Debug.Assert(e != null);
			ComponentType type = ComponentTypeManager.GetTypeFor<T>();

			if (type.ID >= ComponentsByType_.Capacity) {
				ComponentsByType_.Set(type.ID, null);
			}

			Bag<ArtemisComponent> components = ComponentsByType_.Get(type.ID);
			if (components == null) {
				components = new Bag<ArtemisComponent>();
				ComponentsByType_.Set(type.ID, components);
			}

			components.Set(e.ID, component);

			e.AddTypeBit(type.Bit);
			if (AddedComponentEvent != null) {
				AddedComponentEvent(e, component);
			}
		}

		/// Ensures that Any Changes to 
		/// Components are Synced Up with the Entity
		internal void Refresh(Entity e) {
			SystemManager systemManager = World_.SystemManager;
			Bag<EntitySystem> Systems_ = systemManager.Systems;
			for (int i = 0, s = Systems_.Size; s > i; i++) {
				Systems_.Get(i).OnChange(e);
			}
		}

		/// Removes a Given Component Type from a Given Entity
		internal void RemoveComponent<T>(Entity e, ArtemisComponent component) where T : ArtemisComponent {
			System.Diagnostics.Debug.Assert(component != null);
			System.Diagnostics.Debug.Assert(e != null);
			ComponentType type = ComponentTypeManager.GetTypeFor<T>();
			RemoveComponent(e, type);
		}

		internal void RemoveComponent(Entity e, ComponentType type) {
			System.Diagnostics.Debug.Assert(e != null);
			System.Diagnostics.Debug.Assert(type != null);
			int entityId = e.ID;
			Bag<ArtemisComponent> components = ComponentsByType_.Get(type.ID);
			if (RemovedComponentEvent != null) {
				RemovedComponentEvent(e, components.Get(entityId));
			}
			components.Set(entityId, null);
			e.RemoveTypeBit(type.Bit);
		}

		/// Get the Component Instance of a 
		/// Given Component Type for a Given Entity
		internal ArtemisComponent GetComponent(Entity e, ComponentType type) {
			System.Diagnostics.Debug.Assert(e != null);
			System.Diagnostics.Debug.Assert(type != null);
			int entityId = e.ID;
			Bag<ArtemisComponent> bag = ComponentsByType_.Get(type.ID);
			if (type.ID >= ComponentsByType_.Capacity) {
				return null;
			}
			if (bag != null && entityId < bag.Capacity)
				return bag.Get(entityId);
			return null;
		}

		/// Get the Entity for a Given Entity ID
		public Entity GetEntity(int entityId) {
			System.Diagnostics.Debug.Assert(entityId >= 0);
			return ActiveEntities_.Get(entityId);
		}

		/// Return the Amount of Entities Currently Active
		public int ActiveEntitiesCount {
			get { return Count_; }
		}

		/// Return the Total Number of Entities Created
		public long TotalCreated {
			get { return TotalEntitiesCreated_; }
		}

		/// Return the Total Number of Entities Removed
		public long TotalRemoved {
			get { return TotalEntitiesCreated_; }
		}

		/// Get All the Components Assigned to a Given Entity
		public Bag<ArtemisComponent> GetComponents(Entity e) {
			System.Diagnostics.Debug.Assert(e != null);
			EntityComponents_.Clear();
			int entityId = e.ID;
			for (int a = 0, b = ComponentsByType_.Size; b > a; a++) {
				Bag<ArtemisComponent> components = ComponentsByType_.Get(a);
				if (components != null && entityId < components.Size) {
					ArtemisComponent component = components.Get(entityId);
					if (component != null) {
						EntityComponents_.Add(component);
					}
				}
			}
			return EntityComponents_;
		}

		/// Return All Active Entities
		public Bag<Entity> ActiveEntities {
			get { return ActiveEntities_; }
		}
	}
}
