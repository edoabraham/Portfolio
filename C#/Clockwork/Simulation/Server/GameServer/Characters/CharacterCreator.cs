/// CharacterCreation.cs - CharacterCreation Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Linq;
using System.Collections.Generic;

using Artemis;
using Artemis.Interface;


/// Game Server
namespace GameServer {

	/// Object used to create a new character
	public sealed class CharacterCreator : IEntityTemplate {

		/// Fill the entity with the basic settings and components for a character
		/// Params:
		///		InitProperties initProps : Properties, like starting positions, used to initialize a character
		public Entity BuildEntity(Entity e, EntityWorld entityWorld, 
			PlayerInfo info, InitializationProperties initProperties) {

				// Set the group of the entity to characters
				e.Group = EntityGroupName.Characters;

				// Add character components
				e = Character.Characters[info.CharacterID].AddComponents(e, info);

				// Add and change initialization relevant components
				e = initProperties.EnactChanges(e);

				// Refresh the entity's state and return the changed entity
				return e;
		}
		#region Private Members
		public Entity BuildEntity(Entity e, EntityWorld entityWorld, params object[] args) {

			// Refresh the entity's state and return the changed entity
			e.Refresh();
			return e;
		}
		#endregion
	}
}
