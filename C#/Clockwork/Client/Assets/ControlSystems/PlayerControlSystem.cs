/// PlayerControlSystem.cs - PlayerControlSystem Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;
using UnityEngine;
#endregion

/// Player Control System
public sealed class PlayerControlSystem : EntityProcessingSystem {

	/// Threshold value for movement. (SQUARED)
	private const float THRESHOLD = 0.12f;

	/// 
	public static bool ChatMode = false;

	/// Constructor
	public PlayerControlSystem() : 
		base(typeof(OCComponent), typeof(PlayerMouse)) {
			
	}

	/// Initialize System
	public override void LoadContent() {
		this.OCCMapper_ = new ComponentMapper<OCComponent>(this.EntityWorld);
		this.PlayerMouseMapper_ = new ComponentMapper<PlayerMouse>(this.EntityWorld);
	}

	/// Process Main Player Controller
	public override void Process(Entity e) {
		if (!ChatMode) {
			// Localize
			OCComponent control = this.OCCMapper_.Get(e);
			PlayerMouse playerMouse = this.PlayerMouseMapper_.Get(e);

			// Update Mouse
			playerMouse.Update();

			// Calculate mouse ray intersections and assign to target walking location.
			control.ObjController.TargetLocation = playerMouse.TargetedPoint;

			// Change the movement state when the correct input is entered.
			if ((playerMouse.MouseAction0) && (CheckForMovement(
				control.ObjController.Position, control.ObjController.TargetLocation)))
				control.ObjController.ActionState = EActionState.Running;

			else if ((control.ObjController.ActionState == EActionState.Running) && (CheckForMovement(
				control.ObjController.Position, control.ObjController.TargetLocation)))
				control.ObjController.ActionState = EActionState.Running;

			// Attack
			else if (Input.GetButton("Attack"))
				control.ObjController.ActionState = EActionState.Attacking;

			// Skills
			else if (Input.GetButton("Skill1"))
				control.ObjController.ActionState = EActionState.Spell1;
			else if (Input.GetButton("Skill2"))
				control.ObjController.ActionState = EActionState.Spell2;
			else if (Input.GetButton("Skill3"))
				control.ObjController.ActionState = EActionState.Spell3;
			else if (Input.GetButton("Skill4"))
				control.ObjController.ActionState = EActionState.Spell4;

			// Idle
			else
				control.ObjController.ActionState = EActionState.Idle;
		}
	}

	/// Checks if the distance between the position and
	/// target vectors is large enough to require movement be made.
	private bool CheckForMovement(Vector3 source, Vector3 target) {
		Vector3 displacement = source - target;
		return (displacement.sqrMagnitude > THRESHOLD);
	} 

	#region Component Mappers
	private ComponentMapper<OCComponent> OCCMapper_;
	private ComponentMapper<PlayerMouse> PlayerMouseMapper_;
	#endregion
}

