/// MDLoginConfirmation.cs - MDLoginConfirmation Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Network Events
namespace NetworkEvents {

	/// Sends Information from the Server
	/// to a Client Informing if it has
	/// been Accepted by the Server or Not
	public class MDLoginConfirmation {

		/// Constructor
		public MDLoginConfirmation(bool isAccepted) {
			IsAccepted_ = isAccepted;
		}

		/// True - Login Information Accepted
		/// False - Login Information Denied
		private bool IsAccepted_;
		public bool IsAccepted {
			get { return IsAccepted_; }
			set { IsAccepted_ = value; }
		}

		/// Writes Login Confirmation Info
		public NetEvent Write(NetEvent netEvent) {
			netEvent.Data.WriteBool(IsAccepted_);
			return netEvent;
		}

		/// Reads a Login Confirmation Info
		public static MDLoginConfirmation Read(NetEvent netEvent) {
			bool isAccepted = false;
			netEvent.Data.ReadBool(out isAccepted);
			return new MDLoginConfirmation(isAccepted);
		}
	}
}
