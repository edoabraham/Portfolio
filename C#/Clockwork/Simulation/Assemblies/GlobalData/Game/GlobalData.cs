/// GlobalData.cs - GlobalData Class Implementation.
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Global Data Class
/// This class is used to stored data
/// and information that is shared between
/// both the client and server.
public static class GlobalData {

	#region Floating Point Type Settings
	/// Floating point bit length resolution
	public const int FloatResolution = 16;

	/// The Range for Floating Point Numbers
	public const float MaxFloatValue = 327.67f;
	public const float MinFloatValue = -MaxFloatValue;
	#endregion

	#region Spell Settings
	/// The maximum number of spells a character may have.
	public const int MaxCharacterSpells = 6;

	/// The maximum number of auxiliary spells a player is allowed.
	public const int MaxCharAuxiliarySpells = 2;

	/// This is the maximum number of spells
	/// that a player can have and use in game.
	public const int MaxPlayerSpells = MaxCharacterSpells + MaxCharAuxiliarySpells;

	/// The maximum number of spells a NPC can have.
	public const int MaxNPCSpells = 6;

	/// The maximum number of auxiliary spells an NPC is allowed.
	public const int MaxNPCAuxiliarySpells = 4;

	/// This is the maximum number of spells
	/// that a NPC can have and use in game.
	public const int MaxNPCTotalSpells = MaxNPCSpells + MaxNPCSpells;

	/// Grace period for charging spells over their
	/// time limit. This is the amount of time that
	/// a player can hold a spell before it begins
	/// to take a toll on his or her mana, stamina
	/// and/or health, depending on the spell.
	/// This value is measured in milliseconds.
	public const long SpellChargeGracePeriod = 1000;

	/// The number of milliseconds of charge time
	/// required to increase a spell by one charge.
	public const int SpellMillisecondsToCharge = 100;
	#endregion

	#region Item Settings
	/// The maximum number of items allowed to be equipped.
	public const int MaxItems = 8;
	#endregion

	#region Status Settings
	/// How Often the Status Effect Systems are Updated
	/// Measured in Milliseconds
	public const int StatusEffectRefreshInterval = 100;

	/// Overcharge Interrupting Frequency
	/// Dictates how likely Overcharge will interrupt player actions
	public const float InterruptFrequency = 2.0f;
	#endregion

	#region Movement Settings
	/// Dictates how much actual movement speed there is as
	/// it scales with each point of the movement speed stat
	public const float MovementSpeedModifier = 0.08f;

	/// Dictates how much running speed there is as
	/// it scales with each point of the movement speed stat
	public const float RunningSpeedModifier = 1.24f;
	#endregion
}
