/// NetEventArgs.cs - NetEventArgs Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

using System.Text;
using System.Net;
using System.Net.Sockets;

using NetworkEvents;

/// Client Network
namespace ClientNetwork {

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
	public class ServerEventArgs : EventArgs {

		/// Constructor
		public ServerEventArgs(Socket clientManagerSocket) {
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

	/// Procured when an Net Event is Received for the Server
	public delegate void NetEventReceivedHandler(object sender, NetEventArgs e);

	/// Procured when a Net Event is Successfully Sent to the Server
	public delegate void NetEventSentHandler(object sender, EventArgs e);

	/// Procured when a Net Event is Fails, Due to Disconnection or Transfer Exception
	public delegate void NetEventSendFailHandler(object sender, EventArgs e);

	/// Procured when the Server Disconnects from the Client
	public delegate void ServerDisconnectedHandler(object sender, ServerEventArgs e);

	/// Procured when the Client Disconnects from the Server
	public delegate void ClientDisconnectedHandler(object sender, EventArgs e);

	/// Procured when this Client Successfully Connects to the Server
	public delegate void ConnectionSuccessHandler(object sender, EventArgs e);

	/// Procured when this Client Fails to Connect to the Server
	public delegate void ConnectionFailedHandler(object sender, EventArgs e);

	/// Procured when the Network Fails
	public delegate void NetworkDeadHandler(object sender, EventArgs e);

	/// Procured when the Network Begins to Work
	public delegate void NetworkAliveHandler(object sender, EventArgs e);
}
