/// Elemental.cs - Elemental Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using Artemis;
using Artemis.Interface;
using System.Collections.Generic;
using System.IO;
#endregion

/// Game Entity/Object Type Data
/// Dictates the Behavior of Elements
/// in the Game
public class Elemental : IComponent {

	/// Constructor
	public Elemental(EElements element = EElements.Neutral) {
		Element = element;
	}

	/// The Element Value of this Component
	public EElements Element {
		set;
		get;
	}
}

/// Enumeration of Possible Elements
public enum EElements : int {
	Neutral = 0,
	Fire,
	Water,
	Wind,
	Earth,
	Wood
}
