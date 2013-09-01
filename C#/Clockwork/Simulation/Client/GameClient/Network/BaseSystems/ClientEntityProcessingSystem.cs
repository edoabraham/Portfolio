/// ClientEntityProcessingSystem.cs - ClientEntityProcessingSystem Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.Utils;
using Artemis.System;
using System.Collections.Generic;
using NetworkEvents;

/// Game Client
namespace GameClient {

	/// Derivable Network Entity Processing System
	/// Contains delegates that communicate with the networking
	/// system to inform the network system about information
	/// that needs to be sent to clients.
	public abstract class ClientEntityProcessingSystem : 
		ClientProcessingSystem {

		/// Constructor
		public ClientEntityProcessingSystem(int interval,
			ClientSystem clientSystem,
			ENetEventType netEventType,
			bool isReceiving,
			Type requiredType, params Type[] otherTypes)
			: base(interval, clientSystem, netEventType, isReceiving,
			ClientProcessingSystem.GetMergedTypes(requiredType, otherTypes)) {

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
