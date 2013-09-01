/// NetEventType.cs - NetEventType Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Network Events
namespace NetworkEvents {

	/// Enumerate All the Event Types
	public enum ENetEventType : uint {

		/// CLIENT & SERVER EVENTS
		/// ======================

		/// Ping for response time
		Ping = 0,

		/// Houses a Message stSring
		Message,

		/// Makes a Connection between server and client
		Connect,

		/// CLIENT EVENTS
		/// =============

		/// Player request to move character
		MoveInput,

		/// Player request to cast spell
		SpellInput,

		/// SERVER EVENTS
		/// =============

		/// Send world initialization info about 
		/// players, characters, bosses, and the map
		/// Informs reconnecting players of changes
		WorldLoad,

		/// Send viewable changes to each player
		WorldUpdate,

		/// Informs everyone of a player or boss death
		CharacterDeath,

		/// Indicates that a packet is unreadable.
		Invalid
	}
}
