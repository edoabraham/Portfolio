/// Character.cs - Character Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.Interface;
using System.Collections.Generic;
using System.Xml.Serialization;
using System.ComponentModel;
using Utilities;
using System.IO;

/// Game Server
namespace GameServer {

	/// Used to parse a character's data file
	/// and store all relevant information to
	/// make a character.
	public class Character {

		/// Max number of spells that are exclusively from the character.
		private const int MaxCharacterSpells = GlobalData.MaxCharacterSpells;

		/// Static Constructor
		static Character() {

			// Initialize
			ParentDirectory = "";
			DirectoryPath = ParentDirectory + ChildDirectory;
			Characters_ = new Dictionary<ECharacter, Character>();
			
			// Get the values for the enum.
			Array eCharacterValues = Enum.GetValues(typeof(ECharacter));

			// Add in characters
			for (int i = 0, j = eCharacterValues.Length; i < j; i++) {

				// Create character instance
				ECharacter eCharacter = (ECharacter)eCharacterValues.GetValue(i);
				Character character = new Character(eCharacter);

				// Read stat files
				character = character.FileDeserialization(DirectoryPath + eCharacter.ToString());

				// Store into list
				Characters_.Add(eCharacter, character);
			}
		}

		/// Character data directory
		private static string DirectoryPath;

		/// The main directory path to the character data.
		private static string ParentDirectory;

		/// Modifies a passed directory path and amends
		/// this string to reach the character's directory.
		private const string ChildDirectory = "/Characters/";

		/// List of playable characters in the game.
		private static Dictionary<ECharacter, Character> Characters_;
		public static Dictionary<ECharacter, Character> Characters {
			get { return Characters_; }
		}

		#region Character
		/// Constructor
		public Character() {
			this.ID_ = ECharacter.Derp;
			this.Name_ = "";
			this.Statistics_ = new Statistics();
			this.CurrentStats_ = new CurrentStats();
			this.Transform_ = new Transform(Vector3.Zero);
			this.Velocity_ = new Velocity();
			this.Elemental_ = new Elemental(EElements.Neutral);
			this.CharacterSpells_ = new CharacterSpells();
			this.SpellList_ = new ESpell[MaxCharacterSpells];
		}

		/// Init-Constructor
		public Character(ECharacter character) {
			this.ID_ = character;
			this.Name_ = "";
			this.Statistics_ = new Statistics();
			this.CurrentStats_ = new CurrentStats();
			this.Transform_ = new Transform(Vector3.Zero);
			this.Velocity_ = new Velocity();
			this.Elemental_ = new Elemental(EElements.Neutral);
			this.CharacterSpells_ = new CharacterSpells();
			this.SpellList_ = new ESpell[MaxCharacterSpells];
		}

		/// Return ID
		private ECharacter ID_;
		public ECharacter ID {
			get { return this.ID_; }
			set { this.ID_ = value; }
		}

		/// Character name
		private string Name_;
		public string Name {
			get { return this.Name_; }
			set { this.Name_ = value; }
		}

		/// The base stats and the updated (current)
		/// stats that represent the details of the
		/// character and the players progression.
		private CurrentStats CurrentStats_;
		private Statistics Statistics_;
		public Statistics Statistics {
			get { return this.Statistics_; }
			set { this.Statistics_ = value; }
		}

		/// The position and the collision zones that
		/// physically represent a character's presence.
		private Transform Transform_;
		public Transform Transform {
			get { return this.Transform_; }
			set { this.Transform_ = value; }
		}

		/// The speed and movement direction
		/// of a a character at a given time.
		private Velocity Velocity_;
		[XmlIgnore]
		[Browsable(false)]
		public Velocity Velocity {
			get { return this.Velocity_; }
			set { this.Velocity_ = value; }
		}

		/// Represents the elemental property
		/// (defensively) of the character.
		private Elemental Elemental_;
		public Elemental Elemental {
			get { return this.Elemental_; }
			set { this.Elemental_ = value; }
		}

		/// The usable spells, both character and
		/// auxiliary, of a character/player.
		private CharacterSpells CharacterSpells_;
		[XmlIgnore]
		[Browsable(false)]
		public CharacterSpells CharacterSpells {
			get { return this.CharacterSpells_; }
			set { this.CharacterSpells_ = value; }
		}

		/// The spells of this specific character.
		private ESpell[] SpellList_;
		public ESpell[] SpellList {
			get { return this.SpellList_; }
			set { this.SpellList_ = value; }
		}

		/// Adds components of an this character to an entity.
		internal Entity AddComponents(Entity e, PlayerInfo playerInfo) {

			// Load spells
			for (int i = 0, l = this.CharacterSpells_.SpellList.Length,
				m = this.SpellList_.Length, n = playerInfo.AuxiliarySpells.Length;
				i < l; i++) 
					this.CharacterSpells_.SpellList[i] = (i < m) 
						? (this.SpellList_[i]) : ((ESpell)playerInfo.AuxiliarySpells[(i - m)]);

			e.AddComponent(new Statistics(this.Statistics_));
			e.AddComponent(new CurrentStats(this.CurrentStats_));
			e.AddComponent(new Transform(this.Transform_));
			e.AddComponent(new Velocity(this.Velocity_));
			e.AddComponent(new Elemental(this.Elemental_));
			e.AddComponent(new CharacterSpells(this.CharacterSpells_));
			return e;
		}

		/// Deserializes the file storing character data.
		public Character FileDeserialization(string fileName) {
			return Serializer.FromXML<Character>(fileName);
		}
		#endregion
	}
}
