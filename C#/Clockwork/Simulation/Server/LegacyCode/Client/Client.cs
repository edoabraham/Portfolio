/// Client.cs - Client Class Implementation
/// Written By Jesse Z. Zhong


#region Assemblies
using System;
using System.Collections.Generic;

using System.Net;
using System.Net.Sockets;
using System.ComponentModel;
using System.Windows.Forms;

using NetworkEvents;
#endregion

/// Server Network
namespace ClientNetwork {

	/// Client Manager
	public class Client {

		/// Constructor
		public Client(IPEndPoint serverEndPoint, GameTime gameTime) {
			this.ServerEndPoint_ = serverEndPoint;
			System.Net.NetworkInformation.NetworkChange.NetworkAvailabilityChanged +=
				new System.Net.NetworkInformation.NetworkAvailabilityChangedEventHandler(NetworkAvailabilityChanged);

			this.TimeAdjustment_ = 0;
		}

		/// Constructor
		public Client(IPAddress serverIPAddress, int port, GameTime gameTime) {
			this.ServerEndPoint_ = new IPEndPoint(serverIPAddress, port);
			System.Net.NetworkInformation.NetworkChange.NetworkAvailabilityChanged +=
				new System.Net.NetworkInformation.NetworkAvailabilityChangedEventHandler(NetworkAvailabilityChanged);

			this.TimeAdjustment_ = 0;
		}

		/// Returns the IP Address of the Server
		/// Returns "IPAdress.None" if it is Not Connected
		public IPAddress IP {
			get {
				if (this.IsConnected)
					return this.ServerEndPoint_.Address;
				else
					return IPAddress.None;
			}
		}

		/// Returns the Port Number of the Server
		/// Returns -1 if the Client is Not Connected
		public int Port {
			get {
				if (this.IsConnected)
					return ((IPEndPoint)this.Client_.Client.LocalEndPoint).Port;
				else
					return -1;
			}
		}

		/// Checks if this Specific Client is Connected to the Server
		public bool IsConnected {
			get {
				if ((IPEndPoint)this.Client_.Client.RemoteEndPoint != null)
					return this.Client_.Client.Connected;
				else
					return false;
			}
		}

		/// UDP Client instance used for
		/// UDP Communications with a Server
		private UdpClient Client_;

		/// Network Stream to Client
		private NetworkStream NetworkStream_;

		/// Server Endpoint
		private IPEndPoint ServerEndPoint_;

		/// Background Worker Used to Maintain
		/// Reception on a Separate Thread
		private BackgroundWorker BackgroundWorkerReceiver_;

		/// Checks if Network (Server) is Online and Available for Access
		private void NetworkAvailabilityChanged(object sender, System.Net.NetworkInformation.NetworkAvailabilityEventArgs e) {
			if (!e.IsAvailable) {
				this.OnNetworkDead(new EventArgs());
				this.OnClientDisconnect(new EventArgs());
			} else 
				this.OnNetworkAlive(new EventArgs());
		}

		/// Method Used to Receive Buffer Feed from Server
		private void StartReceive(object sender, DoWorkEventArgs e) {

			while (this.Client_.Client.Connected) {

				// Create IP Endpoint to store
				// the information of the sender
				IPEndPoint remoteIPEndpoint = new IPEndPoint(IPAddress.Any, 0);

				// Receive the datagram
				byte[] buffer = Client_.Receive(ref remoteIPEndpoint);

				// Check for minimum packet size, otherwise discard
				// the packet and send a new request (or drop completely)
				if (buffer.Length >= NetEvent.MinimumPacketLength) {

					// Pull time, and compare if it is the most recent
					// Drop the packet if the packet is not recent
					NetEvent netEvent = new NetEvent(buffer);
					UInt16 uintVal = 0;
					netEvent.Data.ReadUInt16(out uintVal);
					if (uintVal >= ClientTime_) {

						// Update to current time
						ClientTime_ = uintVal;

						// Update the Net Event Type
						netEvent.Data.ReadUInt16(out uintVal);
						netEvent.NetEventType = (ENetEventType)uintVal;

						netEvent.SenderIPAddress = this.IP;
						this.OnNetEventReceived(new NetEventArgs(netEvent));
					}
				}

				// Create New Net Event
				NetEvent netEvent = new NetEvent(eventID,
					IPAddress.Parse(targetIPAddress), buffer);

				netEvent.SenderIPAddress = this.IP;
				this.OnNetEventReceived(new NetEventArgs(netEvent));
			}
			this.OnClientDisconnect(new ServerEventArgs(this.Client_.Client));
			this.Disconnect();
		}

		/// Method Used to Handle Post Transfer Processes and Cleanup
		private void SenderRunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e) {
			if (!(e.Cancelled) && (e.Error == null) && ((bool)e.Result))
				this.OnNetEventSent(new EventArgs());
			else
				this.OnNetSendFailure(new EventArgs());

			((BackgroundWorker)sender).Dispose();
			GC.Collect();
		}

		/// Method Used to Help Send Packet to Server
		private void SenderDoWork(object sender, DoWorkEventArgs e) {
			NetEvent netEvent = (NetEvent)e.Argument;
			e.Result = this.SendNetEventToServer(netEvent);
		}

		/// Prepares Packet and Sends it to the Server : Critical Region
		System.Threading.Semaphore Semaphore_ = new System.Threading.Semaphore(1, 1);
		private bool SendNetEventToServer(NetEvent netEvent) {
			try {
				// * Start Critical Region
				Semaphore_.WaitOne();

				// Write the NetEvent to a Packet
				// Add adjustment
				byte[] buffer = netEvent.GetData(RealTime).Buffer;
				Client_.Send(buffer, buffer.Length);

				// * End Critical Region
				Semaphore_.Release();
				return true;
			} catch {
				// * End Critical Region
				Semaphore_.Release();
				return false;
			}
		}

		/// Attempts to Connect the Client to the Server
		public void ConnectToServer() {
			BackgroundWorker BWConnector = new BackgroundWorker();
			BWConnector.DoWork += new DoWorkEventHandler(ConnectorDoWork);
			BWConnector.RunWorkerCompleted += new RunWorkerCompletedEventHandler(ConnectorRunWorkerCompleted);
			BWConnector.RunWorkerAsync();
		}

		/// Method Used to Handle Post Transfer Processes and Cleanup
		private void ConnectorRunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e) {
			if (!((bool)e.Result))
				this.OnConnectionFail(new EventArgs());
			else
				this.OnConnectionSuccess(new EventArgs());
			((BackgroundWorker)sender).Dispose();
		}

		/// Method Used to Help Send Packet to Server
		private void ConnectorDoWork(object sender, DoWorkEventArgs e) {
			try {
				this.Client_.Client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
				this.Client_.Client.Connect(this.ServerEndPoint_);
				e.Result = true;
				this.NetworkStream_ = new NetworkStream(this.Client_.Client);
				this.BackgroundWorkerReceiver_ = new BackgroundWorker();
				this.BackgroundWorkerReceiver_.DoWork += new DoWorkEventHandler(StartReceive);
				this.BackgroundWorkerReceiver_.RunWorkerAsync();
			} catch {
				e.Result = false;
			}
		}

		/// Send Net Event to the Server
		public void SendNetEvent(NetEvent netEvent) {
			if ((this.Client_.Client != null) && this.Client_.Client.Connected) {
				BackgroundWorker BWSender = new BackgroundWorker();
				BWSender.DoWork += new DoWorkEventHandler(SenderDoWork);
				BWSender.RunWorkerCompleted += new RunWorkerCompletedEventHandler(SenderRunWorkerCompleted);
				BWSender.WorkerSupportsCancellation = true;
				BWSender.RunWorkerAsync(netEvent);
			} else
				this.OnNetSendFailure(new EventArgs());
		}

		/// Disconnects the Socket of the Client
		public bool Disconnect() {
			if ((this.Client_.Client != null) && (this.Client_.Client.Connected)) {

				// Attempt to Shutdown Socket
				try {
					this.Client_.Client.Shutdown(SocketShutdown.Both);
					this.Client_.Client.Close();
					this.BackgroundWorkerReceiver_.CancelAsync();
					this.OnClientDisconnect(new EventArgs());
					return true;
				} catch {
					return false;
				}
			} else
				return false;
		}

		/// References the client's timer since acknowledging the start of a match
		/// Used to provide the server with a time reference of where the client is at
		private GameTime GameTime_;

		/// Calculated time adjustment that takes into account any desynchronization
		/// differences in server and client time; Used to for actual adjustment of
		/// the time, factoring both the ping and the difference in time
		private short TimeAdjustment_;
		public short TimeAdjustment {
			get { return TimeAdjustment_; }
		}

		/// Returns the actual adjusted time
		private long RealTime {
			get { return GameTime_.ElapsedTime + TimeAdjustment_; }
		}

		#region Events
		/// Procures when a Net Event is Received from the Server
		public event NetEventReceivedHandler NetEventReceived;
		protected virtual void OnNetEventReceived(NetEventArgs e) {
			if (NetEventReceived != null) {
				Control target = NetEventReceived.Target as Control;
				if ((target != null) && target.InvokeRequired)
					target.Invoke(NetEventReceived, new object[] { this, e });
				else
					NetEventReceived(this, e);
			}
		}

		/// Procures when a Net Event is Successfully Sent to the Server
		public event NetEventSentHandler NetEventSent;
		protected virtual void OnNetEventSent(EventArgs e) {
			if (NetEventSent != null) {
				Control target = NetEventSent.Target as Control;
				if ((target != null) && target.InvokeRequired)
					target.Invoke(NetEventSent, new object[] { this, e });
				else
					NetEventSent(this, e);
			}
		}

		/// Procures when a Net Event Fails to be Sent to the Server
		public event NetEventSendFailHandler NetEventSendFailure;
		protected virtual void OnNetSendFailure(EventArgs e) {
			if (NetEventSendFailure != null) {
				Control target = NetEventSendFailure.Target as Control;
				if ((target != null) && target.InvokeRequired)
					target.Invoke(NetEventSendFailure, new object[] { this, e });
				else
					NetEventSendFailure(this, e);
			}
		}

		/// Procures when a Client Disconnects from the Server
		public event ClientDisconnectedHandler ClientDisconnected;
		protected virtual void OnClientDisconnect(EventArgs e) {
			if (ClientDisconnected != null) {
				Control target = ClientDisconnected.Target as Control;
				if ((target != null) && target.InvokeRequired)
					target.Invoke(ClientDisconnected, new object[] { this, e });
				else
					ClientDisconnected(this, e);
			}
		}

		/// Procures when the Server Disconnects from the Client
		public event ServerDisconnectedHandler ServerDisconnected;
		protected virtual void OnServerDisconnect(ServerEventArgs e) {
			if (ServerDisconnected != null) {
				Control target = ServerDisconnected.Target as Control;
				if ((target != null) && target.InvokeRequired)
					target.Invoke(ServerDisconnected, new object[] { this, e });
				else
					ServerDisconnected(this, e);
			}
		}

		/// Procures when this Client Successfully Connects to the Server
		public event ConnectionSuccessHandler ConnectionSuccess;
		protected virtual void OnConnectionSuccess(EventArgs e) {
			if (ConnectionSuccess != null) {
				Control target = ConnectionSuccess.Target as Control;
				if ((target != null) && target.InvokeRequired)
					target.Invoke(ConnectionSuccess, new object[] { this, e });
				else
					ConnectionSuccess(this, e);
			}
		}

		/// Procures when this Client Fails to Connect to the Server
		public event ConnectionFailedHandler ConnectionFailed;
		protected virtual void OnConnectionFail(EventArgs e) {
			if (ConnectionFailed != null) {
				Control target = ConnectionFailed.Target as Control;
				if ((target != null) && target.InvokeRequired)
					target.Invoke(ConnectionFailed, new object[] { this, e });
				else
					ConnectionFailed(this, e);
			}
		}

		/// Procures when there is a Network Failure
		public event NetworkDeadHandler NetworkDead;
		protected virtual void OnNetworkDead(EventArgs e) {
			if (NetworkDead != null) {
				Control target = NetworkDead.Target as Control;
				if ((target != null) && target.InvokeRequired)
					target.Invoke(NetworkDead, new object[] { this, e });
				else
					NetworkDead(this, e);
			}
		}

		/// Procures when the Network is Alive
		public event NetworkAliveHandler NetworkAlive;
		protected virtual void OnNetworkAlive(EventArgs e) {
			if (NetworkAlive != null) {
				Control target = NetworkAlive.Target as Control;
				if ((target != null) && target.InvokeRequired)
					target.Invoke(NetworkAlive, new object[] { this, e });
				else
					NetworkAlive(this, e);
			}
		}
		#endregion
	}
}
