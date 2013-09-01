/// ClientProcessingSystem.cs - ClientProcessingSystem Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;
using NetworkEvents;

/// Game Client
namespace GameClient {

	/// A Network Entity Processing System that does not
	/// require a specific component to process an entity.
	public abstract class ClientProcessingSystem :
		IntervalEntitySystem {

		/// Constructor
		public ClientProcessingSystem(int interval,
			ClientSystem clientSystem,
			ENetEventType netEventType,
			bool isReceiving,
			params Type[] types) : base(interval, types) {

				this.Interval_ = interval;
				this.ClientSystem_ = clientSystem;
				this.NetEventType_ = netEventType;
				this.InNetEventList_ = new Queue<NetEvent>();

				// If this subsystem is receiving data, register it with the client system
				if (isReceiving)
					this.ClientSystem_.RegisterDelegate(this.NetEventType_, EnqueueInNetEvent);
		}

		/// The time required to have passed before
		/// the system can be refreshed and updated.
		protected int Interval_;

		/// The Client System that manages the clients.
		protected ClientSystem ClientSystem_;

		/// The type of Net Event this
		/// system is supposed to serve.
		protected ENetEventType NetEventType_;

		/// Creates a new Net Event
		protected NetEvent CreateNetEvent() {
			return new NetEvent(this.NetEventType_,
				this.ClientSystem_.ClientIPEP,
				this.ClientSystem_.ServerIPEP);
		}

		/// Enqueues a new Net Event into the Networking Processing System
		protected void EnqueueOutNetEvent(NetEvent netEvent) {
			this.ClientSystem_.Enqueue(netEvent);
		}

		/// Enqueues a received Net Event into this system so it can be processed
		protected void EnqueueInNetEvent( NetEvent netEvent) {
			this.InNetEventList_.Enqueue(netEvent);
		}

		/// List of queued received Net Events that need processing
		protected Queue <NetEvent> InNetEventList_;
	}
}
