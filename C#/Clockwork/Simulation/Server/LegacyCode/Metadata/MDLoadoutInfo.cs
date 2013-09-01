/// MDLoadoutInfo.cs - MDLoadoutInfo Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Network Events
namespace NetworkEvents {

	/// Sends Information about Player's Character
	/// and the Player's Auxiliary Spell Choices
	public class MDLoadoutInfo : IMetaData<MDLoadoutInfo> {


		/// 

		/// Write
		public NetEvent Write(NetEvent netEvent) {
			return netEvent;
		}

		/// Read
		public MDLoadoutInfo Read(NetEvent netEvent) {
			return this;
		}
	}
}
