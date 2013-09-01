/// PlayerController.cs - Player Controller Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using System.Collections.Generic;
using Utilities;
#endregion

/// Game Server
namespace GameServer {

	/// Player Controller
	/// Controller specifically designed for a player
	/// Provides information about the player's socket
	public sealed class PlayerController : Controller {

		/// Max number of spells a player can control
		private const int MaxSpells = GlobalData.MaxPlayerSpells;

		/// Temp Variables
		private const int Width = 128;
		private const int Height = 128;

		/// Constructor
		public PlayerController(PlayerInfo playerInfo) 
			: base() {
				this.SpellTarget_ = Vector2.Zero;
				this.State_ = EAction.Idle;
				this.SpellInput_ = new List<KeyValuePair<bool, long>>(MaxSpells);
				for (int i = 0, j = this.SpellInput_.Count; i < j; i++)
					this.SpellInput_[i] = new KeyValuePair<bool, long>(false, 0);

				this.Info_ = playerInfo;
				this.MapTable_ = new bool[Width, Height];
		}

		/// The target location that the
		/// player chose to cast the spell.
		private Vector2 SpellTarget_;
		public Vector2 SpellTarget {
			get { return this.SpellTarget_; }
			set { this.SpellTarget_ = value; }
		}

		/// Action state of a Player
		/// Set also sets the previous state.
		private EAction State_;
		public EAction State {
			set { this.State_ = value; }
			get { return this.State_; }
		}

		/// Keeps track of the last time
		/// a movement packet was received.
		private long LastMoveCommandTime_;
		public long LastMoveCommandTime {
			get { return this.LastMoveCommandTime_; }
			set { this.LastMoveCommandTime_ = value; }
		}

		/// Stores the player spell input
		private List<KeyValuePair<bool, long>> SpellInput_;
		public List<KeyValuePair<bool, long>> SpellInput {
			get { return this.SpellInput_; }
			set {
				// Test if the value is the appropriate
				// size and that it is fully initialized
				if ((value == null) || (value.Count != this.SpellInput_.Count))
					throw new Exception("Illegal assignment to SpellInput."
				+ "Assigned value must be of the same size and be fully initialized.");

				// If all checks pass, assign the value
				this.SpellInput_ = value;
			}
		}

		/// Map Table that keeps track of
		/// changes to the map that the 
		/// player is not aware of yet
		private bool[,] MapTable_;
		public bool[,] MapTable {
			get { return this.MapTable_; }
			set { this.MapTable_ = value; }
		}

		/// Player's connection
		/// and account information
		private PlayerInfo Info_;
		public PlayerInfo Info {
			get { return Info_; }
			set {
				// Only alter the Client Endpoint
				this.Info_.ClientEndPoint = value.ClientEndPoint;
			}
		}
	}

	/// Enumerates All Possible States
	public enum EAction : int {

		/// Character is either moving
		/// or standing still, nothing else.
		Idle = 0,

		/// Running state allows a character
		/// to move faster than normal but
		/// it prevents them from being able
		/// to cast spells and perform attacks.
		Running,

		/// Any spell or attack
		/// will procure this state
		Attack,

		/// Occurs when a character's
		/// health reaches zero
		Death
	}
}
