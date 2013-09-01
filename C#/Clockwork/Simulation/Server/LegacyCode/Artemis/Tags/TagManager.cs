/// TagManager.cs - TagManager Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Artemis
namespace ArtemisUnity {

	/// Tag Manager
	public sealed class TagManager {

		/// Dictionary for Tag, Entity Value Pair
		private Dictionary<String, Entity> EntityByTag_ = new Dictionary<String, Entity>();

		/// Internal Constructor
		internal TagManager() {

		}

		/// Registers a Tag Name for an Entity
		internal void Register(String tag, Entity e) {
			System.Diagnostics.Debug.Assert(e != null);
			System.Diagnostics.Debug.Assert(!String.IsNullOrEmpty(tag));
			EntityByTag_.Add(tag, e);
		}

		/// Unregisters a Tag Name from Dictionary
		internal void Unregister(String tag) {
			System.Diagnostics.Debug.Assert(!String.IsNullOrEmpty(tag));
			EntityByTag_.Remove(tag);
		}

		/// Checks if a Given Tag Name is Registered
		public bool IsRegistered(String tag) {
			System.Diagnostics.Debug.Assert(!String.IsNullOrEmpty(tag));
			return EntityByTag_.ContainsKey(tag);
		}

		/// Returns the Entity of a Given Tag Name
		public Entity GetEntity(String tag) {
			System.Diagnostics.Debug.Assert(!String.IsNullOrEmpty(tag));

			// Attempt to Get Entity from Dictionary
			Entity e;
			EntityByTag_.TryGetValue(tag, out e);

			// Check if an Entity was Found and Stored
			if ((e == null) || e.IsActive)
				return e;
			else {
				// Attempt to Unregister Tag if Entity
				// was Not Found
				Unregister(tag);
				return null;
			}

		}

		/// Returns the Tag Name of a Given Entity
		public String GetTagOfEntity(Entity e) {
			System.Diagnostics.Debug.Assert(e != null);

			// Attempt to Locate Key (Tag Name)
			String tag = "";
			foreach (var pair in EntityByTag_) {
				if (pair.Value.Equals(e)) {
					tag = pair.Key;
					break;
				}
			}

			return tag;
		}
	}
}
