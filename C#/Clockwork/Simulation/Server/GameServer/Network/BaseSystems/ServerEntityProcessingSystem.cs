/// NetworkEntityProcessingSystem.cs - 
/// NetworkEntityProcessingSystem Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.Utils;
using Artemis.System;
using System.Collections.Generic;
using NetworkEvents;

/// Game Server
namespace GameServer {

	/// Derivable Network Entity Processing System
	/// Contains delegates that communicate with the networking
	/// system to inform the network system about information
	/// that needs to be sent to clients.
	public abstract class ServerEntityProcessingSystem : 
		ServerProcessingSystem {

		/// Constructor
		/// NOTE: The PlayerController is not a required type
		/// as there are systems, most in fact, that require
		/// updating with the client but are not player related.
		/// Making PlayerController required restricts entity
		/// updating to player entities, which is not wanted
		/// and a miscalculation in logic.
		public ServerEntityProcessingSystem(int interval,
			ServerSystem serverSystem,
			ENetEventType netEventType,
			bool isReceiving,
			Type requiredType, params Type[] otherTypes)
			: base(interval, serverSystem, netEventType, isReceiving, 
			ServerProcessingSystem.GetMergedTypes(requiredType, otherTypes)) {
				
		}

		/// Processes a specific entity
		public abstract void Process(Entity entity);

		/// Processes all the entities with the Process method
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {
			foreach (Entity item in entities.Values) {
				this.Process(item);
			}
		}
	}
}
