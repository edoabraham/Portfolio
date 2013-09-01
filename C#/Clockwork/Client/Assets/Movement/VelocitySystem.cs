/// VelocitySystem.cs - VelocitySystem Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;
#endregion

/// Velocity System
public class VelocitySystem : EntityProcessingSystem {
	/// TODO: Differentiate walking and running.

	/// The rate at which movement speed scales with stats.
	private const float MovementSpeedScale = 
		GlobalData.MovementSpeedModifier;

	/// Constructor
	public VelocitySystem()
		: base(typeof(Velocity), typeof(OCComponent)) {

	}

	/// Initialize
	public override void LoadContent() {
		this.VelocityMapper_ = new ComponentMapper<Velocity>(this.EntityWorld);
		this.OCCMapper_ = new ComponentMapper<OCComponent>(this.EntityWorld);
	}

	/// Processes movement requests and performs changes to velocity.
	public override void Process(Entity e) {

		// Localize 
		OCComponent control = this.OCCMapper_.Get(e);
		Velocity velocity = this.VelocityMapper_.Get(e);

		// Check if There is Movement
		if (control.ObjController.ActionState == EActionState.Running) {

			// Calculate Velocity
			velocity.Value = control.ObjController.Direction * MovementSpeedScale/* * agility*/;

		} else {
			// Zero the Velocity
			velocity.Value = Vector3.zero;
		}

		// Update Control Movement Speed
		control.ObjController.MovementSpeed = velocity.Value.magnitude;
	}

	#region Component Mappers
	private ComponentMapper<Velocity> VelocityMapper_;
	private ComponentMapper<OCComponent> OCCMapper_;
	#endregion

}

