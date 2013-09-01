/// GroupManager.cs - GroupManager Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Artemis
namespace ArtemisUnity {

	/// Group Manger
	public sealed class GroupManager {

		/// Instance of World for Reference
		private Bag<Entity> EmptyBag_ = new Bag<Entity>();
		private Dictionary<String, Bag<Entity>> EntitiesByGroup = new Dictionary<String, Bag<Entity>>();
		private Bag<String> GroupByEntity = new Bag<String>();

		/// Internal Constructor
		internal GroupManager() {

		}

		/// Set Group of Entities
		internal void Set(String group, Entity e) {
			System.Diagnostics.Debug.Assert(!String.IsNullOrEmpty(group));
			System.Diagnostics.Debug.Assert(e != null);
			Remove(e); // Entity can only belong to one group.

			Bag<Entity> entities;
			if (!EntitiesByGroup.TryGetValue(group, out entities)) {
				entities = new Bag<Entity>();
				EntitiesByGroup.Add(group, entities);
			}
			entities.Add(e);

			GroupByEntity.Set(e.ID, group);
		}

		/// Get All Entities of Given Group
		public Bag<Entity> GetEntities(String group) {
			System.Diagnostics.Debug.Assert(!String.IsNullOrEmpty(group));

			Bag<Entity> bag;
			if (!EntitiesByGroup.TryGetValue(group, out bag))
				return EmptyBag_;
			return bag;
		}

		/// Removes an Entity From the Group it is Assigned to, if Any
		internal void Remove(Entity e) {
			System.Diagnostics.Debug.Assert(e != null);
			int entityID = e.ID;
			if (entityID < GroupByEntity.Capacity) {
				String group = GroupByEntity.Get(entityID);
				if (group != null) {
					GroupByEntity.Set(entityID, null);

					Bag<Entity> entities;
					if (EntitiesByGroup.TryGetValue(group, out entities)) {
						entities.Remove(e);
					}
				}
			}
		}

		/// Returns the Name of the Group that the Given Entity Belongs to, if Any
		public String GetGroupOf(Entity e) {
			System.Diagnostics.Debug.Assert(e != null);
			int entityID = e.ID;
			if (entityID < GroupByEntity.Capacity) {
				return GroupByEntity.Get(entityID);
			}
			return null;
		}

		/// Check if the Given Entity Belongs to a Group
		public bool IsGrouped(Entity e) {
			System.Diagnostics.Debug.Assert(e != null);
			return GetGroupOf(e) != null;
		}
	}
}
