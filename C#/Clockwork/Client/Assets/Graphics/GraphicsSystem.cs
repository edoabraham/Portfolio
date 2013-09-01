/// GraphicsSystem.cs - GraphicsSystem Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;
using UnityEngine;
#endregion

/// Graphics System
public class GraphicsSystem : EntityProcessingSystem {

	/// Inherited Constructor
	public GraphicsSystem() : base(typeof(OCComponent)) {

	}

	/// Initialize
	public override void LoadContent() {
		this.OCCMapper_ = new ComponentMapper<OCComponent>(this.EntityWorld);
	}

	/// Processes Graphics and Animation for Unity
	public override void Process(Entity e) {

		// Localize the object controller component.
		OCComponent objController = this.OCCMapper_.Get(e);
 
 		// Call call update to update rendering and animations.
		objController.ObjController.Update();
	}

	#region Component Mappers
	private ComponentMapper<OCComponent> OCCMapper_;
	#endregion
}
