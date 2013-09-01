/// EntityProcessingSystem.cs - EntityProcessingSystem Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Artemis
namespace ArtemisUnity {

	/// Entity Processing System
	public abstract class EntityProcessingSystem : EntitySystem {

		/// Constructor
		public EntityProcessingSystem(Type requiredType, params Type[] otherTypes)
			: base(GetMergedTypes(requiredType, otherTypes)) {
		}

		public abstract void Process(Entity e);

		protected override void ProcessEntities(Dictionary<int, Entity> entities) {
			foreach (Entity item in entities.Values) {
				Process(item);
			}
		}
	}
}
