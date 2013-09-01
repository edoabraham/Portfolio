/// NSCMessage.cs - NSCMessage Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using System.Linq;
using System.Collections.Generic;

using Artemis;
using Artemis.Utils;
using Artemis.System;
using NetworkEvents;
using Utilities;
#endregion

/// Game Server
namespace GameServer {

	/// Message System
	/// Handles messages received from players via client
	/// and broadcasts the messages to other players.
	/// Also allows messages from other external sources.
	public sealed class NSCMessage : ServerProcessingSystem {

		/// In Packet Structure
		/// 0 Message Type
		/// 1 Message

		/// Out Packet Structure
		/// 0 Message Type
		/// 1 Message Sender
		/// 2 Message

		#region Data Type Settings
		/// Length of the message type data region
		private static readonly int MessageTypeBitLength = 
			NetworkConstants.MessageTypeBitLength;

		/// Defines how well a message can be compressed
		private const int CompressionStep = 
			NetworkConstants.CompressionStep;
		#endregion

		/// Constructor
		public NSCMessage(int interval,
			ServerSystem serverSystem) :
			base(interval, serverSystem,
			ENetEventType.Message, true) {

		}

		/// Load Content
		public override void LoadContent() {
			this.PCMapper_ = new ComponentMapper<PlayerController>(this.EntityWorld);
		}

		/// Process all messages from players and broadcasting them to other players
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {

			// Grab bag of entities that have Player Controllers
			Bag<Entity> PCEntities = this.EntityWorld.ComponentManager.GetEntities<PlayerController>();
			while (this.InNetEventList_.Count > 0) {
				KeyValuePair<PlayerController, NetEvent> inNetEvent = this.InNetEventList_.Dequeue();
				
				// Pull the message type out of the datagram
				uint type = 0;
				inNetEvent.Value.Data.ReadDynamicUInt(out type, MessageTypeBitLength);
				NetworkConstants.EMessageType messageType = (NetworkConstants.EMessageType)type;

				// Pull the message out of the datagram
				string message = "";
				inNetEvent.Value.Data.ReadString(out message, CompressionStep);

				// Output message
				this.OutputMessage(inNetEvent.Key.Info.Name, (NetworkConstants.EMessageType)type, message);

				// Decide where/how to send the message
				// NOTE: There was a choice whether to do this or have a
				// single loop that would iterate through all of the
				// entities and test each time with a separate method.
				// After some thought, I decided that it was a little bit
				// to expensive to do it that way even though it would
				// look better in terms of code.
				switch (messageType) {
					#region All Message
					case NetworkConstants.EMessageType.All: {
							
							// Iterate through all players and enqueue 
							// message Net Events for all of them to receive
							foreach (Entity item in PCEntities) {

								// Localize
								PlayerController PCController = PCMapper_.Get(item);

								// Create and enqueue the message
								this.SendMessage(PCController, messageType, 
									inNetEvent.Key.Info.Name, message);
							}
						}
						break;
					#endregion
					#region Team Message
					case NetworkConstants.EMessageType.Team: {
							
							// Find the team id of the player who sent the message
							byte teamID = inNetEvent.Key.Info.TeamID;

							// Iterate through all players and queue 
							// message Net Events for some of them to receive
							foreach (Entity item in PCEntities) {

								// Localize
								PlayerController PCController = this.PCMapper_.Get(item);

								// Check if team id's match
								if (PCController.Info.TeamID == teamID) {

									// Create and enqueue the message
									this.SendMessage(PCController, messageType,
										inNetEvent.Key.Info.Name, message);
								}
							}
							
						}
						break;
					#endregion
					#region Default
					default:
						// Do nothing
						break;
					#endregion
				}
			}
		}

		/// Method used to create and enqueue a message Net Event
		private void SendMessage(PlayerController playerController, 
			NetworkConstants.EMessageType type, string sender, string message) {

			// Create a new Net Event
			NetEvent outNetEvent = this.CreateNetEvent(playerController);

			// Write the message type
			outNetEvent.Data.WriteDynamicUInt((uint)type, MessageTypeBitLength);

			// Write the sender's name
			outNetEvent.Data.WriteString(sender, CompressionStep);

			// Write the message to the Net Event
			outNetEvent.Data.WriteString(message, CompressionStep);

			// Enqueue the Net Event
			this.EnqueueOutNetEvent(outNetEvent);
		}

		/// Prints and outputs the message to the console and to log
		private void OutputMessage(string name, NetworkConstants.EMessageType type, string message) {

			// Output to the console
			Message.Info("[" + type.ToString() + "] " + name + " : " + message);

			// Output to log file
		}

		#region Component Mapper
		private ComponentMapper<PlayerController> PCMapper_;
		#endregion
	}
}
