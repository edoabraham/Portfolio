/// ClientSystem.cs - ClientSystem Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;

using Artemis;
using Artemis.System;
using NetworkEvents;
using Utilities;
#endregion

/// Game Client
namespace GameClient {

	/// Delegate type in charge of passing net events to sub systems
	public delegate void PassNetEvent(NetEvent netEvent);

	/// Client System
	public sealed class ClientSystem : 
		IntervalEntitySystem {
		#region Constants
		/// Default size of the buffer
		private const int DefaultBufferSize = 
			NetworkConstants.DefaultBufferSize;

		/// The bit resolution for the ping-pong marker
		private const int PingPongMarkerBitSize = 
			NetworkConstants.PingPongMarkerBitSize;
		#endregion

		/// Constructor
		public ClientSystem(int interval, GameTime gameTime,
			IPAddress serverIPAddress) : base(interval) {
				try {
					// Initialize members
					this.Interval_ = interval;
					this.GameTime_ = gameTime;

					// Setup network endpoints
					this.ServerIPEP_ = (new IPEndPoint(serverIPAddress, NetworkConstants.ServerPort));
					this.ServerEP_ = (EndPoint)ServerIPEP_;
					this.Client_ = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
					this.Client_.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
					this.ClientIPEP_ = new IPEndPoint(NetworkConstants.LocalIPAddress(), NetworkConstants.ClientPort);
					this.Client_.Bind(this.ClientIPEP_);
					this.Buffer_ = new byte[DefaultBufferSize];

					// Ping Pong and Time Variables
					this.PingQueue_ = new Queue<KeyValuePair<uint, long>>();
					this.PingPongMarker_ = 0;
					this.Ping_ = 0;
					this.TimeDifference_ = 0;
					this.NumOfTimeSamples_ = 0;

					// Initialize Net Event queues
					this.OutboundNetEventQueue_ = new Queue<NetEvent>();
					this.InboundNetEventQueue_ = new Queue<NetEvent>();

					// Initialize list of sub system delegates
					this.PassList_ = new Dictionary<ENetEventType, PassNetEvent>();

				} catch(Exception exception) {
					Console.WriteLine(exception.Message);
				}
		}

		/// Process all net events
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {
			try {
				// Send a ping packet out.
				this.SendPing();

				// Send out the queued Net Events until there are none left
				while (OutboundNetEventQueue_.Count > 0)
					this.StartToSend(OutboundNetEventQueue_.Dequeue());

				// Processes received Net Events that have been queued up
				while (InboundNetEventQueue_.Count > 0)
					this.ProcessNetEvent(InboundNetEventQueue_.Dequeue());
			} catch (Exception exception) {
				System.Diagnostics.Debug.WriteLine(exception.Message);
			}
		}

		/// Writes and sends a ping datagram
		public void SendPing() {
			try {
				// Create a new Net Event
				NetEvent netEvent = new NetEvent(ENetEventType.Ping,
					this.Client_.LocalEndPoint as IPEndPoint, this.ServerIPEP_);

				// Write the marker
				netEvent.Data.WriteDynamicUInt(this.PingPongMarker_, PingPongMarkerBitSize);

				// Enqueue outgoing ping data
				this.PingQueue_.Enqueue(new KeyValuePair<uint, long>(PingPongMarker_,
					(long)GameTime_.ElapsedTime));

				// Iterate ping pong marker assigner up
				this.PingPongMarker_++;

				// Attempt to send the datagram
				this.StartToSend(netEvent);

			} catch (Exception exception) {
				Console.WriteLine(exception.Message);
			}
		}

		#region Networking
		#region Internal Members - Subsystems
		/// Returns the IP Endpoint of the client
		internal IPEndPoint ClientIPEP {
			get { return this.ClientIPEP_; }
		}

		/// Returns the IP Endpoint of the server
		internal IPEndPoint ServerIPEP {
			get { return this.ServerIPEP_; }
		}

		/// Allows outside objects to register a pass event
		internal void RegisterDelegate(ENetEventType netEventType,
			PassNetEvent passMethod) {
				this.PassList_.Add(netEventType, passMethod);
		}

		/// Allows outside objects to enqueue net events
		internal void Enqueue(NetEvent netEvent) {
			OutboundNetEventQueue_.Enqueue(netEvent);
		}

		/// Processes a net event with the appropriate delegate
		private void ProcessNetEvent(NetEvent netEvent) {

			// Localize type
			ENetEventType type = netEvent.NetEventType;

			// Iterate through to find match in list
			foreach (KeyValuePair<ENetEventType, PassNetEvent> item in this.PassList_) {

				if (item.Key == type) {

					// If match is found, call method and break out of loop
					item.Value(netEvent);
					break;
				}
			}
		}

		/// Returns the system refresh interval
		internal int Interval {
			set { Interval_ = value; }
			get { return Interval_; }
		}
		#endregion

		/// Initialize
		public override void LoadContent() {

			// Begin receiving data from clients
			this.StartToReceive();

			// Print Status
			this.PrintStatus();
		}

		#region Asynchronous Communication Methods
		/// Starts receiving incoming data from the server
		private void StartToReceive() {
			try {
				/// Begin receiving datagram
				this.Client_.BeginReceiveFrom(Buffer_, 0, Buffer_.Length,
					SocketFlags.None, ref this.ServerEP_, new AsyncCallback(OnReceive), null);
			} catch (Exception exception) {
				Console.WriteLine(exception.Message);
			}
		}

		/// Callback method used to handle newly received packets
		private void OnReceive(IAsyncResult asyncResult) {
			try {
				// Create EndPoint for identifying incoming senders
				IPEndPoint ipSender = new IPEndPoint(IPAddress.Any, 0);
				EndPoint sender = (EndPoint)ipSender;

				// Stop reception for the time being
				this.Client_.EndReceiveFrom(asyncResult, ref sender);

				// Create Net Event
				NetEvent netEvent = new NetEvent(this.Buffer_, this.GameTime_.ElapsedTime);

				#region Ping-Pong Handling
				// Check for ping
				if (netEvent.NetEventType == ENetEventType.Ping) {
					
					// Extract the marker
					uint marker = 0;
					netEvent.Data.ReadDynamicUInt(out marker, PingPongMarkerBitSize);

					// Only take the most recent, else ignore/discard
					if (PingQueue_.Peek().Key <= marker) {

						// Make sure the one in the queue
						// matches the one that has arrived
						for (int i = 0, j = PingQueue_.Count; i < j; i++) {

							// Dequeue and compare
							KeyValuePair<uint, long> pingInfo = PingQueue_.Dequeue();
							if (pingInfo.Key == marker) {
								
								// Perform ping and time sync calculations

								// Ping calculation
								this.Ping_ = (pingInfo.Value - netEvent.TimeReceived) / 2;

								// Time difference calculation
								this.CalculateTimeDifference(netEvent.TimeReceived,
									netEvent.TimeSent, ETimeDiffType.Average);

								// Break out of loop
								break;
							}
						}
					}
				#endregion
				#region Game Datagram Handling
				} else if(netEvent.NetEventType == ENetEventType.Invalid) {
					// Drop packet
				} else {
					// Enqueue the Net Event
					this.InboundNetEventQueue_.Enqueue(netEvent);
				}
				#endregion

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

		/// Starts sending a Net Event to the server
		private void StartToSend(NetEvent netEvent) {
			try {
				// Begin sending datagram
				this.Client_.BeginSendTo(netEvent.GetData(GameTime_.ElapsedTime).Buffer, 0,
					netEvent.Data.Length, SocketFlags.None, this.ServerEP_, new AsyncCallback(OnSend), null);
			} catch (Exception exception) {
				Console.WriteLine(exception.Message);
			}
		}

		/// Callback method used to close sending
		private void OnSend(IAsyncResult asyncResult) {
			try {
				// Attempt to end send
				this.Client_.EndSend(asyncResult);
			} catch (Exception exception) {
				Console.WriteLine(exception.Message);
			}
		}
		#endregion

		/// Prints the status of the server onto the screen
		private void PrintStatus() {
			Message.Info("Client System Network initiated.\nCommunicating with IP Address : %lite Port : %lite",
				this.ServerIPEP_.Address.ToString(), this.ServerIPEP_.Port.ToString());
		}

		#region Metering
		/// Returns the IP Address the client system is using.
		public IPAddress ClientIP {
			get { return this.ServerIPEP_.Address; }
		}

		/// Number of packets received
		/// that are waiting to be handled.
		public int ReceivedUnhandledPackets {
			get { return this.InboundNetEventQueue_.Count; }
		}

		/// Number of packets pending
		/// that are waiting to be sent.
		public int PendingUnsentPacket {
			get { return this.OutboundNetEventQueue_.Count; }
		}

		/// Returns the ping.
		public long Ping {
			get { return this.Ping_; }
		}

		/// Returns the real adjusted time of the game
		public long RealGameTime {
			get { return GameTime_.ElapsedTime + TimeDifference_; }
		}
		#endregion
		
		#region Private Members
		/// IPEndpoint for the Server
		private IPEndPoint ServerIPEP_;
		private EndPoint ServerEP_;

		/// UDP Socket instance used for the
		/// client to communicate with the server
		private IPEndPoint ClientIPEP_;
		private Socket Client_;

		/// Buffer used for storing incoming datagrams
		private byte[] Buffer_;

		/// The time required to have passed before
		/// the system can be refreshed and updated.
		private int Interval_;

		/// Outbound Net Event Queue
		private Queue<NetEvent> OutboundNetEventQueue_;

		/// Inbound Net Event Queue
		private Queue<NetEvent> InboundNetEventQueue_;

		/// Delegate list for all of the sub systems
		private Dictionary<ENetEventType, PassNetEvent> PassList_;

		/// References a copy of the server's run timer
		private GameTime GameTime_;

		/// The time difference between the server and client
		private long TimeDifference_;

		/// Queue used for storing the times and the 
		/// markers of the ping packets that were sent out
		/// Used for matching up with the returning pong packets
		private Queue<KeyValuePair<uint, long>> PingQueue_;

		/// Value used to assign the number of a ping packet
		/// Used to match up ping packets with their pong packets
		private uint PingPongMarker_;

		/// Stores the current ping value
		private long Ping_;

		/// Time difference calculation type
		private enum ETimeDiffType {
			Single,
			Average,
		}

		/// Calculates the time difference depending on settings
		private int NumOfTimeSamples_;
		private void CalculateTimeDifference(long timeReceived,
			long timeSent, ETimeDiffType timeDiffType) {
			switch (timeDiffType) {
				case ETimeDiffType.Single: {
						this.TimeDifference_ = timeSent - timeReceived + Ping_;
					}
					break;
				case ETimeDiffType.Average: {
						// Calculate unique "moving average" using weighted averages
						if (NumOfTimeSamples_ > 0)
							this.TimeDifference_ = (long)((((float)NumOfTimeSamples_ / (float)(NumOfTimeSamples_ + 1)) * this.TimeDifference_)
								+ ((float)(timeSent - timeReceived + this.Ping_) / (NumOfTimeSamples_ + 1)));
						else
							this.TimeDifference_ = timeSent - timeReceived + this.Ping_;

						// Iterate up the number of samples
						NumOfTimeSamples_++;
					}
					break;
				default:
					// Do nothing
					break;
			}
		}

		/// Destructor
		~ClientSystem() {

		}
		#endregion
		#endregion
	}
}
