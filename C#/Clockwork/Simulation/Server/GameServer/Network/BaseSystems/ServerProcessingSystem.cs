/// ServerProcessingSystem.cs - 
/// ServerProcessingSystem Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;
using NetworkEvents;

/// Game Server
namespace GameServer {

	/// A Network Entity Processing System that does not
	/// require a specific component to process an entity.
	public abstract class ServerProcessingSystem : 
		IntervalEntitySystem {

		/// Constructor
		/// NOTE: The PlayerController is not a required type
		/// as there are systems, most in fact, that require
		/// updating with the client but are not player related.
		/// Making PlayerController required restricts entity
		/// updating to player entities, which is not wanted
		/// and a miscalculation in logic.
		public ServerProcessingSystem(int interval,
			ServerSystem serverSystem,
			ENetEventType netEventType,
			bool isReceiving,
			params Type[] types) : base(interval, types) {
				this.Interval_ = interval;
				this.ServerSystem_ = serverSystem;
				this.NetEventType_ = netEventType;
				this.InNetEventList_ = new Queue<KeyValuePair<PlayerController, NetEvent>>();

				// If this subsystem is receiving data, register it with the server system
				if(isReceiving)
					this.ServerSystem_.RegisterDelegate(this.NetEventType_, EnqueueInNetEvent);
		}

		/// The time required to have passed before
		/// the system can be refreshed and updated.
		protected int Interval_;

		/// The Server System that manages the clients.
		protected ServerSystem ServerSystem_;

		/// The type of Net Event this
		/// system is supposed to serve.
		protected ENetEventType NetEventType_;

		/// Creates a new Net Event
		protected NetEvent CreateNetEvent(PlayerController controller) {
			return new NetEvent(this.NetEventType_, 
				this.ServerSystem_.ServerIPEndPoint,
				controller.Info.ClientEndPoint);
		}

		/// Enqueues a new Net Event into the Networking Processing System
		protected void EnqueueOutNetEvent(NetEvent netEvent) {
			this.ServerSystem_.Enqueue(netEvent);
		}

		/// Enqueues a received Net Event into this system so it can be processed
		protected void EnqueueInNetEvent(KeyValuePair<PlayerController, NetEvent> netEvent) {
			this.InNetEventList_.Enqueue(netEvent);
		}

		/// List of queued received Net Events that need processing
		protected Queue<KeyValuePair<PlayerController, NetEvent>> InNetEventList_;
	}
}
