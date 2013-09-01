/// SpellDB.cs - SpellDB Class implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

using Artemis;
using Artemis.Interface;

/// Game Server
namespace GameServer {

	/// Spell Database
	/// This class is where all of the game's spells are stored.
	/// The logic for creating spells with the right stats and
	/// behavior is detailed in this class as well.
	public static class SpellDB {

		/// Default Constructor
		static SpellDB() {

			// Load spells
			Spells_ = new Dictionary<ESpell, Spell>();
			ListSpells();
		}

		/// Lists the spells and their logic
		private static void ListSpells() {

			#region Ciel : Thrust
			Spells_.Add(ESpell.Ciel_Thrust, 
				new Spell((Spell spell) => {


			},
			(Spell spell, Entity character) => {



			}));
			#endregion

			#region Ciel : Impale
			Spells_.Add(ESpell.Ciel_Impale, 
				new Spell((Spell spell) => {


			},
			(Spell spell, Entity character) => {



			}));
			#endregion

			#region Ciel : Snipe/Recall
			Spells_.Add(ESpell.Ciel_SnipeRecall, 
				new Spell((Spell spell) => {

			},
			(Spell spell, Entity character) => {

				// Use minion

			}));
			#endregion

			#region Ciel : Block/Parry
			Spells_.Add(ESpell.Ciel_BlockParry,
				new Spell((Spell spell) => {


				},
			(Spell spell, Entity character) => {



			}));
			#endregion

			#region Ciel : Lunge/Drift
			Spells_.Add(ESpell.Ciel_LungeDrift,
				new Spell((Spell spell) => {


				},
			(Spell spell, Entity character) => {



			}));
			#endregion

			#region Ciel : Siren's Song
			Spells_.Add(ESpell.Ciel_SirensSong,
				new Spell((Spell spell) => {


				},
			(Spell spell, Entity character) => {



			}));
			#endregion
		}

		/// Database of all the spells in the game.
		/// Spells are listed by ID. Returns/gets only.
		private static Dictionary<ESpell, Spell> Spells_;
		public static Dictionary<ESpell, Spell> Spells {
			get { return Spells_; }
		}

	}
}
