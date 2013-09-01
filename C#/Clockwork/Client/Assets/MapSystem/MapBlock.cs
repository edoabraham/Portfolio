/// MapBlock.cs - MapBlock Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using Artemis.Interface;
using System.Collections.Generic;
#endregion

using UnityEngine;

/// Map Blocks are the Building Blocks of 
/// this Map System; They House Properties
/// that can be Influenced and Changed by
/// External Factors; In the Same Manner
/// Each Instance Block can Influence
/// External Gameplay Factors like Skills
public class MapBlock : IComponent {

	/// Constructor
	public MapBlock() {

	}

	/// Init-Constructor
	public MapBlock(EOverlayProperty overlayProperty) {

	}

	/// Base Property
	private EBaseProperty BaseProperty_;
	public EBaseProperty BaseProperty {
		set { BaseProperty_ = value; }
		get { return BaseProperty_; }
	}

	/// Overlay Property
	private EOverlayProperty OverlayProperty_;
	public EOverlayProperty OverlayProperty {
		set { OverlayProperty_ = value; }
		get { return OverlayProperty_; }
	}

	/// Elevation of the Block
	private int Elevation_;
	public int Elevation {
		set { Elevation_ = value; }
		get { return Elevation_; }
	}

	/// Denotes the Different Types of Edges for a Block
	/// There are Four Sides to a Block Each with Its Own Edge Type
	/// North 0 -> 3, East 4 -> 7, South 8 -> 11, West 12 -> 15
	/// Types:
	///		0 Level
	///			Edge Maintains the Same Level as the Block's Elevation
	///			If the Block Next to This One is of a Lower Elevation
	///			this Block will have a Cliff Side Texture
	///		1 Sloping
	private byte EdgeProperty_;
	public byte EdgeProperty {
		set { EdgeProperty_ = value; }
		get { return EdgeProperty_; }
	}
}

public enum EBaseProperty : int {
	Dirt = 0,
	Sand,
	Earth, // Soil
	Rock
}

public enum EOverlayProperty : int {
	Nothing,
	Grass,
	SingedGrass,
	ShortBrush,
	SingedShortBrush,
	TallBrush,
	SingedTallBrush,
	Tree,
	Ash,
	ShallowWater,
	DeepWater,
	Rock,
	CrackedRock,
	ShatteredRock
}

public enum ESignalInProperty : int {
	None = 0,
	Fire,
	Water,
	Lightning,
}