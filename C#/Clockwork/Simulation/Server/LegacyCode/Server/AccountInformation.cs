/// AccountInformation.cs - AccountInformation Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.Interface;
using System.Collections.Generic;

/// Login Server
namespace ServerNetwork {

	/// Account Information
	public class AccountInformation : IComponent {

		/// Constructor
		public AccountInformation(string username) {
			Username_ = username;
		}

		/// Username
		private string Username_;
		public string Username {
			get { return Username_; }
			set { Username_ = value; }
		}

		/// Account ID
		private UInt32 ID_;
		public UInt32 ID {
			get { return ID_; }
			set { ID_ = value; }
		}

		/// Stores the Index of the Character the Player
		/// Chose Prior to being moved to the Game Server
		private short CharacterIndex_;
		public short CharacterIndex {
			get { return CharacterIndex_; }
			set { CharacterIndex_ = value; }
		}

		/// List of Personalized Characters
		/// NOTE: Implement Later; Not a necessity at the moment.
	}
}
