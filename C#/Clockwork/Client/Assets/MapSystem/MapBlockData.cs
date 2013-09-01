/// MapBlockData.cs - Map Block Data Structure Implementation
/// Written By Jesse Z. Zhong

#region System Directives
using System;
using System.Collections.Generic;
#endregion

/// Represents the Data Packet Used to
/// Store Outgoing Data from a Map Block
public struct MapBlockData {

	/// Default Stored Value
	private const float DEFAULT_VALUE = 1.0f;

	/// Constructor
	public MapBlockData(EMapBlockState blockState) {

		// Initialize to Allocate the Correct
		// Amount of Stack Space for the Data
		Attributes_ = new Dictionary<EElements, float>();
		MapBlockState_ = blockState;
		PreviousMapBlockState_ = blockState;

		// Initialize Attributes
		IsInitialized_ = true;
		Initialize();
	}

	/// Defines the Elemental Attributes of a Map Block
	private Dictionary<EElements, float> Attributes_;
	public Dictionary<EElements, float> Attributes {
		get {
			// Ensures Initialization
			if (!IsInitialized_) {
				Initialize();
				IsInitialized_ = true;
			}

			// Checks For Changes First Before Updating
			// to Ensure there is no Unnecessary Overhead
			if (PreviousMapBlockState_ != MapBlockState_)
				Update();
			PreviousMapBlockState_ = MapBlockState_;
			return Attributes_; 
		}
	}

	/// Dictates the Attributes that a
	/// Map Block can Have at a Given Time 
	private EMapBlockState MapBlockState_;
	public EMapBlockState MapBlockState {
		set { MapBlockState_ = value; }
	}

	/// Saves the Previous Map Block State
	private EMapBlockState PreviousMapBlockState_;

	/// Updates the Attributes Depending
	/// on the State of the Map Block
	private void Update() {
		switch (MapBlockState_) {
			case EMapBlockState.Neutral:
				ChangeValue(EElements.Neutral,	1.0f);
				ChangeValue(EElements.Fire,		1.0f);
				ChangeValue(EElements.Water,	1.0f);
				ChangeValue(EElements.Wind,		1.0f);
				ChangeValue(EElements.Earth,	1.0f);
				ChangeValue(EElements.Wood,		1.0f);
				break;
			case EMapBlockState.DampGround:
				ChangeValue(EElements.Neutral,	1.0f);
				ChangeValue(EElements.Fire,		1.0f);
				ChangeValue(EElements.Water,	1.0f);
				ChangeValue(EElements.Wind,		1.0f);
				ChangeValue(EElements.Earth,	1.0f);
				ChangeValue(EElements.Wood,		1.0f);
				break;
			case EMapBlockState.Foliage:
				ChangeValue(EElements.Neutral,	1.0f);
				ChangeValue(EElements.Fire,		1.0f);
				ChangeValue(EElements.Water,	1.0f);
				ChangeValue(EElements.Wind,		1.0f);
				ChangeValue(EElements.Earth,	1.0f);
				ChangeValue(EElements.Wood,		1.0f);
				break;
			case EMapBlockState.BurningFoliage:
				ChangeValue(EElements.Neutral,	1.0f);
				ChangeValue(EElements.Fire,		1.0f);
				ChangeValue(EElements.Water,	1.0f);
				ChangeValue(EElements.Wind,		1.0f);
				ChangeValue(EElements.Earth,	1.0f);
				ChangeValue(EElements.Wood,		1.0f);
				break;
			case EMapBlockState.Water:
				ChangeValue(EElements.Neutral,	1.0f);
				ChangeValue(EElements.Fire,		1.0f);
				ChangeValue(EElements.Water,	1.0f);
				ChangeValue(EElements.Wind,		1.0f);
				ChangeValue(EElements.Earth,	1.0f);
				ChangeValue(EElements.Wood,		1.0f);
				break;
			default:
				ChangeValue(EElements.Neutral,	1.0f);
				ChangeValue(EElements.Fire,		1.0f);
				ChangeValue(EElements.Water,	1.0f);
				ChangeValue(EElements.Wind,		1.0f);
				ChangeValue(EElements.Earth,	1.0f);
				ChangeValue(EElements.Wood,		1.0f);
				break;
		}
	}

	/// Change the Value of a Single Attribute
	private void ChangeValue(EElements element, float modifier) {
		if(Attributes_.ContainsKey(element))
			Attributes_[element] = modifier;
	}

	/// Populate the Attributes Dictionary
	private void Initialize() {
		for (int i = 0, j = Enum.GetNames(typeof(EElements)).Length; i < j; i++)
			Attributes_.Add((EElements)i, DEFAULT_VALUE);
	}

	/// Initialization State
	private bool IsInitialized_;
}

/// Details the Various Main 
/// Types of Map Block States
public enum EMapBlockState : int {
	Neutral,
	DampGround,
	Foliage,
	BurningFoliage,
	Water
}