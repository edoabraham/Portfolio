/// OCComponent.cs - OCComponent Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;
using Artemis.Interface;

/// Object Controller Component
/// 
public sealed class OCComponent : IComponent {

	/// Constructor
	public OCComponent(ObjectController objController) {
		this.ObjController_ = objController;
	}

	/// Controls a game object in Unity.
	private ObjectController ObjController_;
	public ObjectController ObjController {
		get { return this.ObjController_; }
	}
}

