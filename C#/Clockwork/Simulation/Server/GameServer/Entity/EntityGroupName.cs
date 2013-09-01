/// EntityGroupName.cs - EntityGroupName Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Enumerates all of the Group Names for Entities
	public sealed class EntityGroupName {
		public const string Characters = "Character";
		public const string Spells = "Spell";
		public const string MapCells = "MapCell";
	}
}
