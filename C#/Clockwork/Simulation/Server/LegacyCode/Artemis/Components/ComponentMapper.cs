/// ComponentMapper.cs - ComponentMapper Class Implementation
/// Written By Jesse Z. Zhong

using System;

/// Artemis
namespace ArtemisUnity {

	/// Maps Components Out for 
	/// Eventual Systems Processing
	public sealed class ComponentMapper<T> where T : ArtemisComponent  {

		/// Component Type Represented
		/// by This Component Mapper
		private ComponentType Type_;

		private EntityManager EntityManager_;

		/// Constructor
		public ComponentMapper() { }

		/// <summary>
		/// Creates a component mapper within the given Entity World
		/// </summary>
		/// <param name="world">EntityWorld</param>
		public ComponentMapper(EntityWorld world) {
			System.Diagnostics.Debug.Assert(world != null);
			EntityManager_ = world.EntityManager;
			Type_ = ComponentTypeManager.GetTypeFor<T>();
		}

		/// <summary>
		/// Sets the entity manager for this component mapper
		/// </summary>
		/// <param name="em">Entity Manager that manages the component</param>
		public EntityManager EntityManager {
			set { EntityManager_ = value; }
		}

		/// <summary>
		/// Gets the component for the given entity/component type combo
		/// </summary>
		/// <param name="e">Entity in which you are interested</param>
		/// <returns>Component</returns>
		public T Get(Entity e) {
			System.Diagnostics.Debug.Assert(e != null);
			return (T)EntityManager_.GetComponent(e, Type_);
		}

	}
}
