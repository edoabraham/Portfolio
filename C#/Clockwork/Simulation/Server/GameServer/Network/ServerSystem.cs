/// ServerSystem.cs - ServerSystem Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Net;
using System.Net.Sockets;
using System.ComponentModel;
using System.Collections.Generic;

using Artemis;
using Artemis.System;
using NetworkEvents;
using Utilities;

/// Game Server
namespace GameServer {

	/// Delegate type in charge of passing net events to sub systems
	public delegate void PassNetEvent(KeyValuePair<PlayerController, NetEvent> netEvent);

	/// Server System
	/// In charge of sending and receiving
	/// data to and from clients
	public sealed class ServerSystem : 
		IntervalEntitySystem {

		/// Default buffer size
		/// Note: Do not exceed 1024,
		/// as performance will be seriously affected
		private const int DefaultBufferSize = 
			NetworkConstants.DefaultBufferSize;

		/// The bit resolution for the ping-pong marker
		private const int PingPongMarkerBitSize = 
			NetworkConstants.PingPongMarkerBitSize;

		/// Constructor
		public ServerSystem(
			int interval, GameTime gameTime, 
			PlayerInfo[] playerInfoList,
			IPAddress serverIPAddress) : base(interval) {

				// Initialize members
				this.Interval_ = interval;
				this.GameTime_ = gameTime;
				this.CharactersInitialized_ = false;

				// Store player information list and player controller list
				this.PlayerInfoList_ = new List<PlayerInfo>(playerInfoList);
				this.PlayerControllerList_ = new List<PlayerController>();

				// Initialize the socket with IPv4, Datagram, and UDP
				this.Server_ = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
				this.ServerIPEndpoint_ = new IPEndPoint(serverIPAddress, NetworkConstants.ServerPort);
				this.Server_.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
				this.Server_.Bind(ServerIPEndpoint_);

				// Hack: Ignore ICMP messages.
				this.Server_.IOControl((IOControlCode)NetworkConstants.SIO_UDP_CONNRESET, new byte[] { 0, 0, 0, 0 }, null);

				// Initialize buffer
				this.Buffer_ = new byte[DefaultBufferSize];
				
				// Initialize Net Event queues
				this.OutboundNetEventQueue_ = new Queue<NetEvent>();
				this.InboundNetEventQueue_ = new Queue<KeyValuePair<PlayerController, NetEvent>>();

				// Initialize list of sub system delegates
				this.PassList_ = new Dictionary<ENetEventType, PassNetEvent>();

				// Create EndPoint for identifying incoming senders
				IPEndPoint endpoint = new IPEndPoint(IPAddress.Any, 0);
				this.RemoteEP_ = endpoint;
				this.Sender_ = (EndPoint)endpoint;
		}

		/// Creates entities with player controllers
		/// using the player information list.
		private void CreatePlayerEntities() {

			// Make a character creator
			CharacterCreator cc = new CharacterCreator();

			// Create player controller for each player info
			foreach (PlayerInfo item in this.PlayerInfoList_) {

				// Create controller with player info and add to list
				PlayerController playerController = new PlayerController(item);
				this.PlayerControllerList_.Add(playerController);

				// Create player entity with new controller
				Entity e = this.EntityWorld.CreateEntity();
				e.AddComponent(playerController);

				// Add components
				cc.BuildEntity(e, this.EntityWorld, item, new InitializationProperties());

				// Refresh entity
				e.Refresh();
			}

			// If all of the player entities were initialized
			// correctly, set the CharactersInitialized to true.
			this.CharactersInitialized_ = true;
		}

		/// Process all net events
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {
			try {
				// Send out the queued Net Events until there are none left
				while (OutboundNetEventQueue_.Count > 0)
					this.StartToSend(OutboundNetEventQueue_.Dequeue());

				// Processes received Net Events that have been queued up
				while (InboundNetEventQueue_.Count > 0)
					this.ProcessNetEvent(InboundNetEventQueue_.Dequeue());
			} catch(Exception exception) {
				Console.WriteLine(exception.Message);
			}
		}

		#region Networking
		#region Internal Members - Subsystems
		/// Allows outside objects to register a pass event
		internal void RegisterDelegate(ENetEventType netEventType,
			PassNetEvent passMethod) {
			this.PassList_.Add(netEventType, passMethod);
		}

		/// Allows outside objects to enqueue net events
		internal void Enqueue(NetEvent netEvent) {
			this.OutboundNetEventQueue_.Enqueue(netEvent);
		}

		/// Server's IP Endpoint
		internal IPEndPoint ServerIPEndPoint {
			get { return this.ServerIPEndpoint_; }
		}

		/// Returns the server's run time
		internal GameTime GameRunTimer {
			get { return GameTime_; }
		}

		/// Returns the system refresh interval
		internal int Interval {
			set { this.Interval_ = value; }
			get { return this.Interval_; }
		}

		/// Are all of the characters and players initialized?
		internal bool CharactersInitialized {
			get { return this.CharactersInitialized_; }
		}
		#endregion

		/// Initialize
		public override void LoadContent() {

			// Begin receiving data from clients
			this.StartToReceive();

			// Create player controllers
			this.CreatePlayerEntities();

			// Print Status
			this.PrintStatus();
		}

		#region Asynchronous Communication Methods
		/// Starts receiving incoming data from clients
		private void StartToReceive() {
			try {
				// Begin receiving datagram
				this.Server_.BeginReceiveFrom(this.Buffer_, 0, this.Buffer_.Length, SocketFlags.None,
					ref this.RemoteEP_, new AsyncCallback(OnReceive), this.Server_);
			} catch(Exception exception) {
				Console.WriteLine(exception.Message);
			}
		}

		/// Callback method used to handle newly received packets
		private void OnReceive(IAsyncResult asyncResult) {
			try {
				// End receiving temporarily to handle the current datagram
				this.Server_.EndReceiveFrom(asyncResult, ref this.Sender_);

				// Check to see if the sender's information matches any one of the player's
				foreach (PlayerController item in this.PlayerControllerList_) {

					// If there's an acceptable match, enqueue packet for processing
					if (((IPEndPoint)Sender_).Address.Equals(item.Info.ClientEndPoint.Address)) {

						// Create Net Event
						NetEvent netEvent = new NetEvent(this.Buffer_, GameTime_.ElapsedTime);

						#region Ping-Pong Handling
						// Check if the net event is a ping event
						// if it is, don't bother queuing and immediately respond
						if (netEvent.NetEventType == ENetEventType.Ping) {
							
							// Extract the ping-pong marker from the datagram
							uint marker = 0;
							netEvent.Data.ReadDynamicUInt(out marker, PingPongMarkerBitSize);

							// Create a target ip endpoint for directing the datagram to the client
							IPEndPoint target = new IPEndPoint(item.Info.ClientEndPoint.Address,
							item.Info.ClientEndPoint.Port);

							// Create a pong net event
							NetEvent pongEvent = new NetEvent(ENetEventType.Ping, 
								this.ServerIPEndpoint_, target);

							// Write the marker to the outbound datagram
							pongEvent.Data.WriteDynamicUInt(marker, PingPongMarkerBitSize);

							// Attempt to send the packet
							StartToSend(pongEvent);
						#endregion
						#region Game Datagram Handling
						} else if(netEvent.NetEventType == ENetEventType.Invalid) {
							// Drop packet
						} else {
							// Enqueue the Net Event
							Console.WriteLine(((IPEndPoint)this.Sender_).Address.ToString());
							this.InboundNetEventQueue_.Enqueue(new KeyValuePair<PlayerController,
								NetEvent>(item, netEvent));
						}
						#endregion

						// Break out of search
						break;
					}
				}

			} catch (Exception exception) {
				Console.WriteLine(exception.Message);
			}

			// Continue receiving datagrams
			// Note: This is outside of the try catch.
			// In the event that EndReceiveFrom throws an
			// exception, we still need to be able to 
			// continue receiving data from the remote host.
			this.StartToReceive();
		}

		/// Starts sending a Net Event to a client
		private void StartToSend(NetEvent netEvent) {

			// Begin sending datagram
			this.Server_.BeginSendTo(netEvent.GetData(GameTime_.ElapsedTime).Buffer, 0, netEvent.Data.Length, 
				SocketFlags.None, (EndPoint)netEvent.Target, new AsyncCallback(OnSend), netEvent.Target);
		}

		/// Callback method used to close sending
		private void OnSend(IAsyncResult asyncResult) {
			try {
				// Attempt to end send
				this.Server_.EndSend(asyncResult);
			} catch(Exception exception) {
				Console.WriteLine(exception.Message);
			}
		}
		#endregion

		/// Processes a net event with the appropriate delegate
		private void ProcessNetEvent(KeyValuePair<PlayerController, NetEvent> netEvent) {

			// Localize type
			ENetEventType type = netEvent.Value.NetEventType;

			// Iterate through to find match in list
			foreach (KeyValuePair<ENetEventType, PassNetEvent> item in this.PassList_) {
				if (item.Key == type) {
					// If match is found, call method and break out of loop
					item.Value(netEvent);
					break;
				}
			}
		}

		/// Prints the status of the server onto the screen
		private void PrintStatus() {
			Message.Info("Server System Network initiated.\nListening for datagrams from IP Address : %lite Port : %lite"
				+ "\nServer identified at IP Address : %lite",
				this.ServerIPEndpoint_.Address.ToString(), this.ServerIPEndpoint_.Port.ToString(), 
				NetworkConstants.LocalIPAddress().ToString());
		}

		#region Private Members
		/// UDP Socket instance used for the
		/// server to communicate with clients
		private Socket Server_;

		/// Server's IP Endpoint
		private IPEndPoint ServerIPEndpoint_;

		/// Endpoint used to guide packet reception
		private EndPoint RemoteEP_;

		/// Used to store the sender's information
		private EndPoint Sender_;

		/// Buffer used for storing incoming datagrams
		private byte[] Buffer_;

		/// The time required to have passed before
		/// the system can be refreshed and updated.
		private int Interval_;

		/// List of information of the
		/// players on this server instance
		private List<PlayerInfo> PlayerInfoList_;

		/// List of references to player controllers
		/// Controllers include each player's information
		private List<PlayerController> PlayerControllerList_;

		/// Outbound Net Event Queue
		private Queue<NetEvent> OutboundNetEventQueue_;

		/// Inbound Net Event Queue
		private Queue<KeyValuePair<PlayerController, NetEvent>> InboundNetEventQueue_;

		/// Delegate list for all of the sub systems
		private Dictionary<ENetEventType, PassNetEvent> PassList_;

		/// References a copy of the server's run timer
		private GameTime GameTime_;

		/// Are all of the characters and players initialized?
		private bool CharactersInitialized_;

		/// Destructor
		~ServerSystem() {

		}
		#endregion
		#endregion
	}
}
