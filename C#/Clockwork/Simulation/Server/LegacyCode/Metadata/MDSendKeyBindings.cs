/// MDSendKeyBindings.cs - MDSendKeyBindings Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Network Events
namespace NetworkEvents {

	/// Server Sends the Key Bindings of the Player
	/// to the Player's Client at the beginning of the Match
	public class MDSendKeyBindings : IMetaData<MDSendKeyBindings> {

		/// Write
		public NetEvent Write(NetEvent netEvent) {
			return netEvent;
		}

		/// Read
		public MDSendKeyBindings Read(NetEvent netEvent) {
			return this;
		}
	}
}
