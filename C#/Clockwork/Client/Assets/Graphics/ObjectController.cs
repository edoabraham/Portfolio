/// ObjectController.cs - ObjectController Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
#endregion

/// Houses all of the necessary information
/// to create and manipulate an in game object.
public class ObjectController : ScriptableObject {

	#region Public Accessors
	/// The current action state of an object.
	public EActionState ActionState {
		get { return this.ActionState_; }
		set { this.ActionState_ = value; }
	}

	/// The position of the game object.
	public Vector3 Position {
		set {
			if (this.CharacterObject_ != null)
				this.CharacterObject_.transform.position = value;
		}
		get {
			if (this.CharacterObject_ != null)
				return this.CharacterObject_.transform.position;
			else
				return Vector3.zero;
		}
	}

	/// The name of the graphics asset used.
	public String AssetName {
		set { this.AssetName_ = value; }
		get { return this.AssetName_; }
	}

	/// The increment value at which velocity increases at.
	public float MovementSpeed {
		set { MovementSpeed_ = value; }
	}

	/// Desired location that an object wishes to move to.
	public Vector3 TargetLocation {
		set { this.TargetLocation_ = value; }
		get { return this.TargetLocation_; }
	}

	/// Keeps track if new movement input is requested.
	public bool NewMovement {
		get { return this.NewMovement_; }
		set { this.NewMovement_ = value; }
	}

	/// Calculates the angle at which the object is facing.
	public float DirectionAngle {
		get {
			if (this.CharacterObject_ != null) {
				Vector3 direction = this.TargetLocation_
					- this.CharacterObject_.transform.position;
				if ((direction.y == 0.0f) && (direction.x == 0.0f))
					return 0.0f;
				return (float)Math.Atan2(direction.z, direction.x);
			} else
				return 0.0f;
		}
	}

	/// Calculates the vector direction the object is facing.
	public Vector3 Direction {
		get {
			if (this.CharacterObject_ != null) {
				Vector3 direction = this.TargetLocation_
					- this.CharacterObject_.transform.position;
				direction.Normalize();
				return direction;
			} else
				return Vector3.zero;
		}
	}
	#endregion
	
	/// Constructor
	public ObjectController() {

		// Initialize values.
		this.MovementSpeed_ = 0.0f;
		this.ActionState_ = EActionState.Idle;
		this.TargetLocation_ = Vector3.zero;
	}

	/// Update Transform and Animations
	public void Update() {
		#region Asset Checking and Loading
		// Load a transform if it's not already loaded.
		if (this.CharacterObject_ == null) {

			// Look up and assign asset, and then assign a transform.
			System.Diagnostics.Debug.Assert(this.AssetName_ != null);
			this.CharacterObject_ = (GameObject)Instantiate(GraphicsAssets.GetTransformAsset(this.AssetName_), 
				this.Position, Quaternion.identity);

			// Set animation settings.
			this.AnimationSettings();
		}
		#endregion
		#region Animation States Handling
		if (this.CharacterObject_ != null) {

			// Update Animation According Control Status
			switch (this.ActionState_) {
				case EActionState.Idle:
					CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Idle1]);
					// TODO: Idle Sequence
					break;
				case EActionState.Running:
					CharacterObject_.transform.rotation = Quaternion.Euler(0,
						DirectionOffset - (float)(this.DirectionAngle * (180 / Math.PI)), 0);
					CharacterObject_.animation[AnimStateMap[EAnimationState.Running]].speed = MovementSpeed_ * MovementToAnimationRatio;
					CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Running]);
					break;
				case EActionState.Attacking:
					CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Attack1]);
					// TODO: Change Later When Attack System is
					// Implemented
					break;
				case EActionState.Spell1:
					// Check if Looping Skill or Not
					if (CharacterObject_.animation[AnimStateMap[EAnimationState.Spell1]] != null)
						CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Spell1]);
					else {
						CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Spell1Loop]);
					}
					break;
				case EActionState.Spell2:
					// Check if Looping Skill or Not
					if (CharacterObject_.animation[AnimStateMap[EAnimationState.Spell2]] != null)
						CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Spell2]);
					else {
						CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Spell2Loop]);
					}
					break;
				case EActionState.Spell3:
					// Check if Looping Skill or Not
					if (CharacterObject_.animation[AnimStateMap[EAnimationState.Spell3]] != null)
						CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Spell3]);
					else {
						CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Spell3Loop]);
					}
					break;
				case EActionState.Spell4:
					// Check if Looping Skill or Not
					if (CharacterObject_.animation[AnimStateMap[EAnimationState.Spell4]] != null)
						CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Spell4]);
					else {
						CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Spell4Loop]);
					}
					break;
				case EActionState.Death:
					CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Death]);
					break;
				case EActionState.Taunt:
					CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Taunt]);
					break;
				case EActionState.Laugh:
					CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Laugh]);
					break;
				case EActionState.Dance:
					CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Dance]);
					break;
				default:
					CharacterObject_.animation.CrossFade(AnimStateMap[EAnimationState.Idle1]);
					break;
			}
		}
		#endregion
	}

	#region Private Members
	/// The name of the graphics asset used.
	private String AssetName_;

	/// Reference to the parent game object.
	private GameObject CharacterObject_;

	/// Increment value at which velocity is increased by.
	private float MovementSpeed_;

	/// The current action state of an object.
	private EActionState ActionState_;

	/// Desired location that an object wishes to move to.
	private Vector3 TargetLocation_;
	
	/// Keeps track if new movement input is requested.
	private bool NewMovement_;

	/// Sets the Animation Wrap and Layer Settings
	private void AnimationSettings() {

		if (this.CharacterObject_ != null) {

			#region Wrap Mode for Animation Play Style
			// Calculate divide point
			int dividePoint = (NumOfLoopAnims < AnimStates.Length)
				? NumOfLoopAnims : AnimStates.Length;

			// Loop Animations
			for (int i = 0; i < dividePoint; i++)
				ChangeWrapMode(AnimStates[i], WrapMode.Loop);

			// Once Animations
			for (int i = dividePoint, j = AnimStates.Length; i < j; i++)
				ChangeWrapMode(AnimStates[i], WrapMode.Once);
			#endregion
			#region Animation Layering Settings
			for (int i = 0, j = AnimStates.Length; i < j; i++)
				ChangeAnimLayer(AnimStates[i], 0);
			#endregion

			// Stop Animations if They Are Playing
			CharacterObject_.animation.Stop();
		}
	}

	#region Private Helper Methods
	/// Change Wrap Mode
	private void ChangeWrapMode(String clipName, WrapMode mode) {
		if (CharacterObject_.animation[clipName] != null)
			CharacterObject_.animation[clipName].wrapMode = mode;
	}

	/// Change Animation Layer
	private void ChangeAnimLayer(String clipName, int layerNumber) {
		if (CharacterObject_.animation[clipName] != null)
			CharacterObject_.animation[clipName].layer = layerNumber;
	}
	#endregion
	#region Static Members
	/// Static Constructor
	static ObjectController() {

		// Initialize the animation state names.
		AnimStates = Enum.GetNames(typeof(EAnimationState));
		AnimStateMap = new Dictionary<EAnimationState, string>();
		foreach (EAnimationState item in Enum.GetValues(typeof(EAnimationState))) {
			AnimStateMap.Add(item, item.ToString());
		}
	}

	/// Array of animation states in string form.
	private static string[] AnimStates;
	private static Dictionary<EAnimationState, string> AnimStateMap;
	private const int NumOfLoopAnims = 9;

	/// Angular offset for an asset when rendering.
	private const float DirectionOffset = 90.0f;

	/// The ratio of movement speed to animation speed.
	private const float MovementToAnimationRatio = 25.0f;
	#endregion
	#endregion
}

/// Enumerates All Possible States
public enum EActionState : uint {
	Idle = 0,
	Running,
	Attacking,
	Spell1,
	Spell2,
	Spell3,
	Spell4,
	Death,
	Taunt,
	Laugh,
	Dance,
	Channel
}