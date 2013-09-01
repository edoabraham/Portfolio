/// TagSystem.cs - TagSystem Class Implementation
/// Written By Jesse Z. Zhong

using System;
using ArtemisUnity;
using System.Collections.Generic;

/// Artemis
namespace ArtemisUnity {

	/// Tag System Used for Processing Tags
	public abstract class TagSystem : EntitySystem {

		/// Stores Entity Tags
		protected String Tag_;

		/// Constructor
		public TagSystem(String tag) {
			// Check if Legal Tag and Store It
			System.Diagnostics.Debug.Assert(!String.IsNullOrEmpty(tag));
			this.Tag_ = tag;
		}

		/// Processes Entities that This System is Interested In
		public abstract void Process(Entity e);

		/// Internally Process the Entities by Tag
		protected override void ProcessEntities(Dictionary<int, Entity> entities) {
			Entity e = World.TagManager.GetEntity(Tag_);
			if (e != null)
				Process(e);
		}
	}
}
