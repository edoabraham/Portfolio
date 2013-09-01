/// ServerSystem.cs - ServerSystem Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;

using System.Net;
using System.Net.Sockets;

using System.ComponentModel;

using NetworkEvents;
using ServerNetwork;

/// Artemis System
namespace Artemis.System {

	public class ServerSystem : 
		IntervalEntitySystem {

		/// Constructor
		public ServerSystem(int interval,
			GameTime gameTime,
			IPAddress serverIPAdress, 
			int port, int backlog)
			: base(interval) {
				this.Interval_ = interval;
				this.ServerIPAddress_ = serverIPAdress;
				this.ServerPort_ = port;
				this.Backlog_ = backlog;

				this.ClientLoginRequestList_ = new Queue<KeyValuePair<ClientManager, NetEvent>>();
				this.OutboundNetEventQueue_ = new Queue<NetEvent>();

				this.GameTime_ = gameTime;
		}

		/// Process all net events
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {

			#region Login
			// Change the implementation to accommodate new system
			// 			while (ClientLoginRequestList_.Count > 0) {
			// 
			// 				// Dequeues Client Manager for Examination
			// 				KeyValuePair<ClientManager, NetEvent> infoPair = ClientLoginRequestList_.Dequeue();
			// 				ClientManager clientManager = infoPair.Key;
			// 				NetEvent netEvent = infoPair.Value;
			// 
			// 				// Parse for Login Information
			// 				bool isAccepted = false;
			// 				MDLoginInfo loginInfo = MDLoginInfo.Read(netEvent);
			// 
			// 				// Check for Match
			// 				string username = "";
			// 				username = loginInfo.Username;
			// 				if ((username == "Jesse") && (loginInfo.Password == "derp"))
			// 					isAccepted = true;
			// 
			// 				// Flush Net Event for a Confirmation Message
			// 				netEvent = new NetEvent(ENetEventType.LoginConfirmation, clientManager.IP);
			// 
			// 				// Send Confirmation
			// 				SendLoginConfirmation(netEvent, isAccepted);
			// 
			// 				// Create New Entity if Client Manager was Accepted
			// 				if (isAccepted) {
			// 
			// 					// Print Successful Connection
			// 					Message.Info("Player %lite has logged in at %lite:%lite.", username,
			// 						clientManager.IP.ToString(), clientManager.Port.ToString());
			// 
			// 					// Setup Account Information
			// 					AccountInformation accountInfo = new AccountInformation(username);
			// 
			// 					// Create New Entity with the Client Manager and Account Information
			// 					Entity e = EntityWorld.CreateEntity(/*username*/);
			// 					e.AddComponent(clientManager);
			// 					e.AddComponent(accountInfo);
			// 					
			// 				} else {
			// 
			// 				}
			// 			}
			#endregion

			/// Send out the queued Net Events until there are none left
			while (OutboundNetEventQueue_.Count > 0)
				SendNetEventToTarget(OutboundNetEventQueue_.Dequeue());
		}

		/// The time required to have passed before
		/// the system can be refreshed and updated.
		private int Interval_;
		public int Interval {
			set { Interval_ = value; }
			get { return Interval_; }
		}

		/// Sends Net Event to a Target Client
		protected void SendNetEventToTarget(NetEvent netEvent) {
			foreach (ClientManager clientManager in this.ClientList_) {
				if (clientManager.IP.Equals(netEvent.TargetIPAddress)) {
					netEvent.SenderIPAddress = this.ServerIPAddress_;
					clientManager.SendNetEvent(netEvent);
					return;
				}
			}
		}

		/// Sends a Login Confirmation Net Event to Client
		private void SendLoginConfirmation(NetEvent netEvent, bool isAccepted) {
			MDLoginConfirmation loginConfirm = new MDLoginConfirmation(isAccepted);
			netEvent = loginConfirm.Write(netEvent);
			SendNetEventToTarget(netEvent);
		}

		/// Allows outside objects to enqueue net events
		public void Enqueue(NetEvent netEvent) {
			OutboundNetEventQueue_.Enqueue(netEvent);
		}

		/// Returns the server's run time
		internal GameTime GameRunTimer {
			get { return GameTime_; }
		}

		#region Networking
		/// Initialize
		public override void LoadContent() {

			// Initialize Networking
			InitializeNetworkingItems();
		}

		/// Initialize Networking Items
		private void InitializeNetworkingItems() {

			// Initialize Client List
			ClientList_ = new List<ClientManager>();

			// Initialize Background Worker
			ListenerBackgroundWorker_ = new BackgroundWorker();
			ListenerBackgroundWorker_.WorkerSupportsCancellation = true;
			ListenerBackgroundWorker_.DoWork += new DoWorkEventHandler(StartToListen);
			ListenerBackgroundWorker_.RunWorkerAsync();
		}

		/// Initializes the Server Socket and
		/// Begins Listening to Connections
		private void StartToListen(object sender, DoWorkEventArgs e) {
			this.ListeningSocket_ = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
			this.ListeningSocket_.Bind(new IPEndPoint(this.ServerIPAddress_, this.ServerPort_));
			this.ListeningSocket_.Listen(Backlog_);

			// Print Message
			Message.Success("The %lite is now open for client connections.\nListening from IP Address of %lite and Port of %lite.",
				"Server", ServerIPAddress_.ToString(), ServerPort_.ToString());

			while (true)
				this.CreateClientManager(this.ListeningSocket_.Accept());
		}

		/// Creates a New Client Manager for a New Client Connection
		/// Receives the Client Socket Used to Make the Server Connection
		private void CreateClientManager(Socket socket) {
			ClientManager clientManager = new ClientManager(socket, GameTime_);
			clientManager.NetEventReceived += new NetEventReceivedHandler(NetEventReceived);
			clientManager.Disconnected += new DisconnectedHandler(ClientDisconnected);
			this.CheckForAbnormalDC(clientManager);
			ClientList_.Add(clientManager);

			// Print to Console to Inform of Connection
			Message.Info("Client Connected IP Address : %lite Port : %lite.",
				clientManager.IP.ToString(), clientManager.Port.ToString());
		}

		/// Prints to Console when a Client is Abnormally Disconnected
		private void CheckForAbnormalDC(ClientManager clientManager) {
			if (this.RemoveClientManager(clientManager.IP))
				Message.Info("Client Disconnected IP Address : %lite Port : %lite.",
					clientManager.IP.ToString(), clientManager.Port.ToString());
		}

		/// Prints to Console when a Client is Disconnected
		private void ClientDisconnected(object sender, ClientEventArgs e) {
			if (this.RemoveClientManager(e.IP))
				Message.Info("Client Disconnected IP Address : %lite Port : %lite.",
					e.IP.ToString(), e.Port.ToString());
		}

		/// Remove a Client Manager
		private bool RemoveClientManager(IPAddress ip) {
			lock (this) {
				int index = this.IndexOfClient(ip);
				if (index != -1) {
					ClientList_.RemoveAt(index);

					return true;
				}
				return false;
			}
		}

		/// Returns the Index of a Client by its IP Address
		private int IndexOfClient(IPAddress ip) {
			int index = -1;
			foreach (ClientManager clientManager in this.ClientList_) {
				index++;
				if (clientManager.IP.Equals(ip))
					return index;
			}
			return -1;
		}

		/// Handles when Net Events are Received
		private void NetEventReceived(object sender, NetEventArgs e) {

			// Queue Up for Login Check
			// =========== CHANGE!
			if (e.NetEvent.NetEventType == ENetEventType.Ping) {
				ClientLoginRequestList_.Enqueue(new KeyValuePair<ClientManager,
					NetEvent>(ClientList_[IndexOfClient(e.NetEvent.SenderIPAddress)], e.NetEvent));
			}
		}

		/// Disengage the Server Networking Processes
		private void DisconnectServer() {
			if (this.ClientList_ != null) {
				foreach (ClientManager clientManager in this.ClientList_)
					clientManager.Disconnect();

				this.ListenerBackgroundWorker_.CancelAsync();
				this.ListenerBackgroundWorker_.Dispose();
				this.ListeningSocket_.Close();

				// Call Garbage Collector
				GC.Collect();
			}
		}

		/// Destructor
		~ServerSystem() {

			// Disconnect Server Networking
			DisconnectServer();
		}

		#region Private Members
		/// List of ALL Client Connections
		protected List<ClientManager> ClientList_;

		/// Socket that Listens for Client Connections
		protected Socket ListeningSocket_;

		/// IP Address of the Server
		protected IPAddress ServerIPAddress_;

		/// Port of the Server
		protected int ServerPort_;

		/// Max Number of Pending Queued Connections
		protected int Backlog_;

		/// Background Worker for Listening on Another Thread
		private BackgroundWorker ListenerBackgroundWorker_;

		/// Outbound Net Event Queue
		protected Queue<NetEvent> OutboundNetEventQueue_;

		/// Login Queue
		protected Queue<KeyValuePair<ClientManager, NetEvent>> ClientLoginRequestList_;

		/// References a copy of the server's run timer
		protected GameTime GameTime_;
		#endregion
		#endregion
	}
}
