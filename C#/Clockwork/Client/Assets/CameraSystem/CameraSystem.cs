/// CameraSystem.cs - CameraSystem Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;
using UnityEngine;
#endregion

/// Camera System
/// NOTE: Player currently is an empty component 
/// at the moment; It's only purpose is to direct 
/// the player's entity to this camera system
public sealed class CameraSystem : EntityProcessingSystem {

	/// Constructor
	public CameraSystem() : 
		base(typeof(OCComponent), typeof(Player)) {

	}

	/// Initialize
	public override void LoadContent() {
		this.OCCMapper_ = new ComponentMapper<OCComponent>(this.EntityWorld);
		this.PlayerMapper_ = new ComponentMapper<Player>(this.EntityWorld);
	}

	/// Update the camera's position
	public override void Process(Entity e) {

		// Localize
		OCComponent objController = this.OCCMapper_.Get(e);

		// Sync the camera's position with the target object
		PlayerCamera.Target.transform.position = objController.ObjController.Position;
	}

	#region Component Mappers
	private ComponentMapper<OCComponent> OCCMapper_;
	private ComponentMapper<Player> PlayerMapper_;
	#endregion
}
