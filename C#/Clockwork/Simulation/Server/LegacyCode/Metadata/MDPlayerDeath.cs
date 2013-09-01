/// MDPlayerDeath.cs - MDPlayerDeath Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Network Events
namespace NetworkEvents {

	/// Sends Message informing a Player and his or her Client
	/// that the Player's Character has died.
	/// Will also send information about how the Player died
	/// including the name of his or her killer and the
	/// Damage distribution.
	public class MDPlayerDeath : IMetaData<MDPlayerDeath> {

		/// Constructor


		/// Write
		public NetEvent Write(NetEvent netEvent) {
			return netEvent;
		}

		/// Read
		public MDPlayerDeath Read(NetEvent netEvent) {
			return this;
		}
	}
}
