/// MovementSystem.cs - Movement System Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;
using UnityEngine;
#endregion

/// Movement System
public class MovementSystem : EntityProcessingSystem {

	/// Inherited Constructor
	public MovementSystem() : 
		base(typeof(OCComponent), typeof(Velocity)) {

	}

	/// Initialize
	public override void LoadContent() {
		this.VelocityMapper_ = new ComponentMapper<Velocity>(this.EntityWorld);
		this.OCCMapper_ = new ComponentMapper<OCComponent>(this.EntityWorld);
	}

	/// Processes Entities with Their Velocities
	/// to Procure Possible Translation
	public override void Process(Entity e) {

		// Localize an Instance of Velocity
		Velocity velocity = this.VelocityMapper_.Get(e);

		// Localize an Instance of Transform
		OCComponent occ = this.OCCMapper_.Get(e);

		// Perform Translation
		occ.ObjController.Position += velocity.Value;
	}

	#region Component Mappers
	private ComponentMapper<Velocity> VelocityMapper_;
	private ComponentMapper<OCComponent> OCCMapper_;
	#endregion
}

