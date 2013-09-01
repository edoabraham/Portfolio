/// NPCInfo.cs - NPC Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// NPC Info
public class NPCInfo {

	/// The maximum number of NPC
	/// auxiliary spells allowed.
	private const int MaxNPCAuxiliarySpells = 
		GlobalData.MaxNPCAuxiliarySpells;

	/// The maximum number of NPC items allowed.
	private const int MaxItems = GlobalData.MaxItems;

	/// Default Constructor
	public NPCInfo() {

		this.CharacterID_ = ECharacter.Derp;
		this.TeamID_ = 0;
		this.AuxiliarySpells_ = new ESpell[MaxNPCAuxiliarySpells];
		this.Items_ = new EItem[MaxItems];
	}

	///  Constructor
	public NPCInfo(ECharacter characterID, byte teamID) {

		this.CharacterID_ = characterID;
		this.TeamID_ = teamID;
		this.AuxiliarySpells_ = new ESpell[MaxNPCAuxiliarySpells];
		this.Items_ = new EItem[MaxItems];
	}

	/// ID of the NPC character.
	private ECharacter CharacterID_;
	public ECharacter CharacterID {
		get { return this.CharacterID_; }
		set { this.CharacterID_ = value; }
	}

	/// List of NPC auxiliary spells.
	private ESpell[] AuxiliarySpells_;
	public ESpell[] AuxiliarySpells {
		get { return this.AuxiliarySpells_; }
		set { this.AuxiliarySpells_ = value; }
	}

	/// List of NPC items.
	private EItem[] Items_;
	public EItem[] Items {
		get { return this.Items_; }
		set { this.Items_ = value; }
	}

	/// The ID of the team the NPC belongs to.
	private byte TeamID_;
	public byte TeamID {
		get { return this.TeamID_; }
		set { this.TeamID_ = value; }
	}
}

