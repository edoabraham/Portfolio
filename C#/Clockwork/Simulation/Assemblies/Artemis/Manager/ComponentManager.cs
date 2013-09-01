/// ComponentManager.cs - ComponentManager Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.Interface;
using System.Collections.Generic;
using Artemis.Utils;

/// 
namespace Artemis.Manager {

	/// 
	public sealed class ComponentManager {

		/// An empty bag.
		private readonly Bag<Entity> EmptyBag_;

		/// A map of Entities that are organized by Component Type
		private readonly Dictionary<ComponentType, Bag<Entity>> EntitiesByType_;

		/// A bag of Entities grouped by Component Type
		private readonly Bag<ComponentType> GroupByType_;

		/// Constructor
		internal ComponentManager(EntityWorld entityWorld) {
			this.EntityManager_ = entityWorld.EntityManager;
			this.GroupByType_ = new Bag<ComponentType>();
			this.EntitiesByType_ = new Dictionary<ComponentType, Bag<Entity>>();
			this.EmptyBag_ = new Bag<Entity>();
		}

		/// Returns all the Entities of with a specific Component Type
		public Bag<Entity> GetEntities(ComponentType componentType) {

			// Attempts to get a bag of Entities of the passed Type
			// Will return an empty bag if Entities of that Type aren't found.
			Bag<Entity> bag;
			if (!this.EntitiesByType_.TryGetValue(componentType, out bag))
				return this.EmptyBag_;

			return bag;
		}
		public Bag<Entity> GetEntities<T>() where T : IComponent {
			return this.GetEntities(ComponentTypeManager.GetTypeFor<T>());
		}

		/// Sets a new Entity into the listings depending 
		/// on what kind of Component Types it has
		internal void Set(Entity entity, IComponent component) {
			#region Bugged and Depreciated
			/*
			Bag<IComponent> entityComponents = EntityManager_.GetComponents(entity);
			for (int i = 0, j = entityComponents.Count; i < j; i++) {
				ComponentType type = ComponentTypeManager.
					GetTypeFor(entityComponents[i].GetType());
				if (!this.EntitiesByType_.ContainsKey(type)) {
					Bag<Entity> bag = new Bag<Entity>();
					bag.Add(entity);
					this.EntitiesByType_.Add(type, bag);
					
				} else {
					Bag<Entity> bag;
					this.EntitiesByType_.TryGetValue(type, out bag);
					bag.Add(entity);
				}
			}
			*/
			#endregion
			// Get the component type of the component
			ComponentType ct = ComponentTypeManager.GetTypeFor(component.GetType());

			// Add entity to the relative bags.
			// Create a new key and bag if there is none found.
			if (!this.EntitiesByType_.ContainsKey(ct)) {
				Bag<Entity> bag = new Bag<Entity>();
				bag.Add(entity);
				this.EntitiesByType_.Add(ct, bag);
			} else {
				Bag<Entity> bag;
				this.EntitiesByType_.TryGetValue(ct, out bag);
				bag.Add(entity);
			}
		}

		/// Removes Entity from listing
		internal void Remove(Entity entity, IComponent component) {
			#region Bugged and Depreciated
			/*
			Bag<IComponent> entityComponents = EntityManager_.GetComponents(entity);
			for (int i = 0, j = entityComponents.Count; i < j; i++) {
				ComponentType type = ComponentTypeManager.
					GetTypeFor(entityComponents[i].GetType());
				Bag<Entity> bag;
				if (this.EntitiesByType_.TryGetValue(type, out bag)) {
					bag.Remove(entity);
				}
			}
			*/
			#endregion
			// Get the component type of the component
			ComponentType ct = ComponentTypeManager.GetTypeFor(component.GetType());
			this.Remove(entity, ct);
		}
		internal void Remove(Entity entity, ComponentType componentType) {
			Bag<Entity> bag;
			if (this.EntitiesByType_.TryGetValue(componentType, out bag))
				bag.Remove(entity);
		}

		/// Localized Entity Manager
		EntityManager EntityManager_;
	}
}
