/// MDLoginInfo.cs - MDLoginInfo Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Network Events
namespace NetworkEvents {

	/// Handles Login Data
	public class MDLoginInfo {

		/// Max Lengths
		public const int MaxUsernameLength = 24;
		public const int MaxPasswordLength = 24;

		/// Compression Step (ASCII)
		private const int COMPRESSION_STEP = 7;

		/// Constructor
		public MDLoginInfo(string username, string password) {
			Username_ = username;
			Password_ = password;
		}

		/// Username
		private string Username_;
		public string Username {
			get { return Username_; }
			set { Username_ = value; }
		}

		/// Password
		private string Password_;
		public string Password {
			get { return Password_; }
			set { Password_ = value; }
		}

		/// Writes a Login Info Net Event
		public NetEvent Write(NetEvent netEvent) {
			netEvent.Data.WriteString(Username_, COMPRESSION_STEP);
			netEvent.Data.WriteString(Password_, COMPRESSION_STEP);
			return netEvent;
		}

		/// Reads a Login Info Net Event
		public static MDLoginInfo Read(NetEvent netEvent) {
			string username = "";
			string password = "";
			netEvent.Data.ReadString(out username, COMPRESSION_STEP);
			netEvent.Data.ReadString(out password, COMPRESSION_STEP);
			return new MDLoginInfo(username, password);
		}
	}
}
