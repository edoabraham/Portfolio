/// NetEventArgs.cs - NetEventArgs Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

using System.Text;
using System.Net;
using System.Net.Sockets;

using NetworkEvents;

/// Server Network
namespace ServerNetwork {

	/// Net Event Arguments
	public class NetEventArgs : EventArgs {

		/// Constructor
		public NetEventArgs(NetEvent netEvent) {
			this.NetEvent_ = netEvent;
		}

		/// Net Event Instance
		private NetEvent NetEvent_;
		public NetEvent NetEvent {
			get { return this.NetEvent_; }
		}
	}

	/// Client Net Event Arguments
	public class ClientEventArgs : EventArgs {

		/// Constructor
		public ClientEventArgs(Socket clientManagerSocket) {
			this.Socket_ = clientManagerSocket;
		}

		/// Client Socket
		private Socket Socket_;

		/// Client IP Address
		public IPAddress IP {
			get { return ((IPEndPoint)this.Socket_.RemoteEndPoint).Address; }
		}

		/// Client Port
		public int Port {
			get { return ((IPEndPoint)this.Socket_.RemoteEndPoint).Port; }
		}
	}

	/// 
	/// HANDLE DELEGATES
	/// 

	/// Procured when an Net Event is Received for the Client
	public delegate void NetEventReceivedHandler(object sender, NetEventArgs e);

	/// Procured when a Net Event is Successfully Sent to the Client
	public delegate void NetEventSentHandler(object sender, EventArgs e);

	/// Procured when a Net Event is Fails, Due to Disconnection or Transfer Exception
	public delegate void NetEventSendFailHandler(object sender, EventArgs e);

	/// Procured when the Client Disconnects from the Server
	public delegate void DisconnectedHandler(object sender, ClientEventArgs e);
}
