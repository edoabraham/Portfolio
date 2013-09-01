/// EAnimationState.cs - EAnimationState
/// Written By Jesse Z. Zhong
#region Assemblies
using UnityEngine;
using System.Collections;
#endregion

/// Enumerates the Various Animation States
public enum EAnimationState : uint {

	/// Loop Animations
	Idle1 = 0,
	Idle2,
	Idle3,
	Running,
	Spell1Loop,
	Spell2Loop,
	Spell3Loop,
	Spell4Loop,
	Dance,

	/// Once Animations
	Attack1,
	Attack2,
	Attack3,

	Spell1,
	Spell1Windup,
	Spell1Winddown,

	Spell2,
	Spell2Windup,
	Spell2Winddown,

	Spell3,
	Spell3Windup,
	Spell3Winddown,

	Spell4,
	Spell4Windup,
	Spell4Winddown,

	Death,
	Taunt,
	Laugh

	// Omitted
	//ChannelWindup,
	//Channel
}
