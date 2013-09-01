/// GameInfo.cs - GameInfo Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Game info
	/// Used to store info of the map, game
	/// mode, NPC character, spells, and items
	public class GameInfo {

		/// Default Constructor
		public GameInfo() {
			this.MapID_ = EMap.DerpMap;
			this.GameModeID_ = EGameMode.TestMode;
			this.PCInfoList_ = new List<PlayerInfo>();
			this.NPCInfoList_ = new List<NPCInfo>();
		}

		/// The id of the user chosen map.
		private EMap MapID_;
		public EMap MapID {
			get { return this.MapID_; }
			set { this.MapID_ = value; }
		}

		/// The id of the game mode.
		private EGameMode GameModeID_;
		public EGameMode GameModeID {
			get { return this.GameModeID_; }
			set { this.GameModeID_ = value; }
		}

		/// List of Players and their setups
		private List<PlayerInfo> PCInfoList_;
		public List<PlayerInfo> PCInfoList {
			get { return this.PCInfoList_; }
			set { this.PCInfoList_ = value; }
		}

		/// List of NPCs and their setups
		private List<NPCInfo> NPCInfoList_;
		public List<NPCInfo> NPCInfoList {
			get { return this.NPCInfoList_; }
			set { this.NPCInfoList_ = value; }
		}
	}
}
