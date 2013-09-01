/// PlayerInfo.cs - PlayerInfo Class Implementation
/// Written by Jesse Z. Zhong

using System;
using System.Collections.Generic;
using System.Net;

/// Account, player, and connection information
/// that is passed at the game server instance
public class PlayerInfo {

	/// The maximum number of player auxiliary spells allowed.
	private const int MaxCharAuxiliarySpells = 
		GlobalData.MaxCharAuxiliarySpells;

	/// The maximum number of player items allowed.
	private const int MaxItems = GlobalData.MaxItems;

	/// Default Constructor
	public PlayerInfo() {
		
		this.ID_ = 0;
		this.Name_ = "";
		this.CharacterID_ = ECharacter.Derp;
		this.TeamID_ = 0;
		this.AuxiliarySpells_ = new ESpell[MaxCharAuxiliarySpells];
		this.Items_ = new EItem[MaxItems];
	}

	/// Constructor
	public PlayerInfo(uint id, string name, 
		ECharacter characterID, byte teamID) {
		this.ID_ = id;
		this.Name_ = name;
		this.CharacterID_ = characterID;
		this.TeamID_ = teamID;
		this.AuxiliarySpells_ = new ESpell[MaxCharAuxiliarySpells];
		this.Items_ = new EItem[MaxItems];
	}

	/// The player's account ID
	/// Used to reference the player after the match
	private UInt32 ID_;
	public UInt32 ID {
		get { return ID_; }
	}

	/// The player's display name
	private string Name_;
	public string Name {
		get { return Name_; }
	}

	/// The ID of the character the player
	/// chose to play for this match
	private ECharacter CharacterID_;
	public ECharacter CharacterID {
		get { return CharacterID_; }
	}

	/// List of player auxiliary spells by ID
	private ESpell[] AuxiliarySpells_;
	public ESpell[] AuxiliarySpells {
		get { return this.AuxiliarySpells_; }
		set {
			System.Diagnostics.Debug.Assert(value.Length == MaxCharAuxiliarySpells);
			this.AuxiliarySpells_ = value; 
		}
	}

	/// List of player items by ID
	private EItem[] Items_;
	public EItem[] Items {
		get { return this.Items_; }
		set {
			System.Diagnostics.Debug.Assert(value.Length == MaxItems);
			this.Items_ = value; 
		}
	}

	/// The ID of the team the player belongs to
	private byte TeamID_;
	public byte TeamID {
		get { return TeamID_; }
	}

	/// The socket of the player's client
	/// This can change if the player logs 
	/// in with a different client (implicitly, computer)
	public IPEndPoint ClientEndPoint;
}

