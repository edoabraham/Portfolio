/// ClientManager.cs - ClientManager Class Implementation
/// Written By Jesse Z. Zhong

#region Assemblies
using System;
using System.Collections.Generic;

using System.Net;
using System.Net.Sockets;
using System.ComponentModel;

using Artemis;
using Artemis.Interface;

using NetworkEvents;
#endregion

/// Server Network
namespace ServerNetwork {

	/// Client Manager
	public class ClientManager : Artemis.Interface.IComponent {

		/// Constructor
		public ClientManager(Socket clientSocket, GameTime gameTime) {
			this.Server_ = new UdpClient((IPEndPoint) clientSocket.RemoteEndPoint);
			this.BackgroundWorkerReceiver_ = new BackgroundWorker();
			this.BackgroundWorkerReceiver_.DoWork += new DoWorkEventHandler(StartReceive);
			this.BackgroundWorkerReceiver_.RunWorkerAsync();
			this.GameTime_ = gameTime;
			this.ClientTime_ = 0;
		}

		/// Returns the IP Address of the Client
		/// Returns "IPAdress.None" if it is Not Connected
		public IPAddress IP {
			get {
				if ((IPEndPoint)this.Server_.Client.RemoteEndPoint != null)
					return ((IPEndPoint)this.Server_.Client.RemoteEndPoint).Address;
				else
					return IPAddress.None;
			}
		}

		/// Returns the Port Number of the Client
		/// Returns -1 if the Client is Not Connected
		public int Port {
			get {
				if (this.Server_ != null)
					return ((IPEndPoint)this.Server_.Client.RemoteEndPoint).Port;
				else
					return -1;
			}
		}

		/// Checks if a Specific Client is Connected to the Server
		public bool IsConnected {
			get {
				if (this.Server_ != null)
					return this.Server_.Client.Connected;
				else
					return false;
			}
		}

		/// UDP Client instance used for 
		/// UDP Communications with a Client
		private UdpClient Server_;

		/// Background Worker Used to Maintain
		/// Reception on a Separate Thread
		private BackgroundWorker BackgroundWorkerReceiver_;

		/// Method Used to Receive Buffer Feed from Client
		private void StartReceive(object sender, DoWorkEventArgs e) {

			while (this.Server_.Client.Connected) {

				try {

					// Create IP Endpoint to store
					// the information of the sender
					IPEndPoint remoteIPEndpoint = new IPEndPoint(IPAddress.Any, 0);

					// Receive the datagram
					byte[] buffer = Server_.Receive(ref remoteIPEndpoint);

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

				} catch (Exception exception) {
					Console.WriteLine(exception.Message);
				}
			}
			this.OnDisconnected(new ClientEventArgs(this.Server_.Client));
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

		/// Method Used to Help Send Packet to Client
		private void SenderDoWork(object sender, DoWorkEventArgs e) {
			NetEvent netEvent = (NetEvent)e.Argument;
			e.Result = this.SendNetEventToClient(netEvent);
		}

		/// Prepares Packet and Sends it to the Client : Critical Region
		System.Threading.Semaphore Semaphore_ = new System.Threading.Semaphore(1, 1);
		private bool SendNetEventToClient(NetEvent netEvent) {
			try {
				// * Start Critical Region
				Semaphore_.WaitOne();

				// Write the NetEvent to a Packet
				byte[] buffer = netEvent.GetData(GameTime_.ElapsedTime).Buffer;
				Server_.Send(buffer, buffer.Length);

				// * End Critical Region
				Semaphore_.Release();
				return true;
			} catch {
				// * End Critical Region
				Semaphore_.Release();
				return false;
			}
		}

		/// Send Net Event to the Connected Client
		public void SendNetEvent(NetEvent netEvent) {
			if ((this.Server_.Client != null) && this.Server_.Client.Connected) {
				BackgroundWorker BWSender = new BackgroundWorker();
				BWSender.DoWork += new DoWorkEventHandler(SenderDoWork);
				BWSender.RunWorkerCompleted += new RunWorkerCompletedEventHandler(SenderRunWorkerCompleted);
				BWSender.RunWorkerAsync(netEvent);
			} else
				this.OnNetSendFailure(new EventArgs());
		}

		/// Disconnects the Socket of the Client Manager
		public bool Disconnect() {
			if ((this.Server_ != null) && (this.Server_.Client.Connected)) {

				// Attempt to Shutdown Socket
				try {
					this.Server_.Client.Shutdown(SocketShutdown.Both);
					this.Server_.Client.Close();
					return true;
				} catch {
					return false;
				}
			} else
				return false;
		}

		/// Reference to the server's runtime timer
		/// Used to provide accurate game times when sending packets
		private GameTime GameTime_;

		/// Keeps track of the time the client sends
		/// Used to keep track of the most recent packets sent
		/// and to adjust the difference in time between the
		/// client and server; used to sync times
		private UInt16 ClientTime_;

		#region Events
		/// Procures when a Net Event is Received from the Client
		public event NetEventReceivedHandler NetEventReceived;
		protected virtual void OnNetEventReceived(NetEventArgs e) {
			if (NetEventReceived != null)
				NetEventReceived(this, e);
		}
		
		/// Procures when a Net Event is Successfully Sent to the Client
		public event NetEventSentHandler NetEventSent;
		protected virtual void OnNetEventSent(EventArgs e) {
			if (NetEventSent != null)
				NetEventSent(this, e);
		}

		/// Procures when a Net Event Fails to be Sent to the Client
		public event NetEventSendFailHandler NetEventSendFailure;
		protected virtual void OnNetSendFailure(EventArgs e) {
			if (NetEventSendFailure != null)
				NetEventSendFailure(this, e);
		}

		/// Procures when a Client Disconnects from the Server
		public event DisconnectedHandler Disconnected;
		protected virtual void OnDisconnected(ClientEventArgs e) {
			if (Disconnected != null)
				Disconnected(this, e);
		}
		#endregion
	}
}
