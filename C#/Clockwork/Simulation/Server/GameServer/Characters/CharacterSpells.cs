/// CharacterSpells.cs - CharacterSpells class implementation
/// Written by Jesse Z. Zhong

using System;
using System.Collections.Generic;
using System.Xml.Serialization;
using System.ComponentModel;

using Artemis;
using Artemis.Interface;

/// Game Server
namespace GameServer {

	/// List of spells a character should have
	public class CharacterSpells : Artemis.Interface.IComponent {

		/// Max number of character spells
		private const int MaxSpells = GlobalData.MaxPlayerSpells;

		/// Constructor
		public CharacterSpells(CharacterSpells 
			characterSpells = null) {

				this.SpellList_ = (characterSpells == null) 
					? new ESpell[MaxSpells] : (ESpell[])characterSpells.SpellList.Clone();

				this.MinionSpells_ = new List<Entity>();
		}

		/// Default Constructor (for Serialization)
		private CharacterSpells() {
			this.SpellList_ = new ESpell[MaxSpells];
			this.MinionSpells_ = new List<Entity>();
		}

		/// List of spells, both the spells of
		/// a character and a player's auxiliary.
		private ESpell[] SpellList_;
		[CategoryAttribute("CharacterSpells")]
		public ESpell[] SpellList {
			get { return this.SpellList_; }
			set {
				// Check for size and null
				if ((value == null) || (value.Length
					!= this.SpellList_.Length))
					throw new Exception("Invalid value for SpellList in CharacterSpells.");
				this.SpellList_ = value;
			}
		}

		/// List of active spell entities that
		/// are still under the direct control
		/// of the character that created them.
		/// These can be minions of summons, etc.
		private List<Entity> MinionSpells_;
		[XmlIgnore]
		[Browsable(false)]
		public List<Entity> MinionSpells {
			get {
				// Clears all dead minions first
				this.MinionSpells_.RemoveAll(item 
					=> item == null);
				return this.MinionSpells_;
			}
			set {
				System.Diagnostics.Debug.Assert(value != null);
				this.MinionSpells_ = value;
			}
		}
	}
}
