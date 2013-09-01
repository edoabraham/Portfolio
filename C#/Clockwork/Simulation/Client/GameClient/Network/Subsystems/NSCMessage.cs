/// NSCMessage.cs - NSCMessage Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using System.Linq;
using System.Collections.Generic;
using System.IO;

using Artemis;
using Artemis.Utils;
using Artemis.System;
using NetworkEvents;
#endregion

/// Game Client
namespace GameClient {

	/// Message System
	public sealed class NSCMessage : ClientProcessingSystem {

		/// Out Packet Structure
		/// 0 Message Type
		/// 1 Message Sender
		/// 2 Message

		/// Out Packet Structure
		/// 0 Message Type
		/// 1 Message

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
			ClientSystem clientSystem, 
			Stream outStream = null) :
			base(interval, clientSystem,
			ENetEventType.Message, true) {
				this.OutStream_ = outStream;
				this.MessageString_ = "";
				this.NewMessage_ = false;
		}

		/// Load Content
		public override void LoadContent() {

		}

		/// Writes a message to the out stream.
		public void SendMessage(NetworkConstants.EMessageType messageType,
			string message) {

			// Create a new Net Event
			NetEvent netEvent = this.CreateNetEvent();

			// Write the message type
			netEvent.Data.WriteDynamicUInt((uint)messageType, MessageTypeBitLength);

			// Write the message
			netEvent.Data.WriteString(message, CompressionStep);

			// Enqueue net event to be sent
			this.EnqueueOutNetEvent(netEvent);
		}

		/// Process received messages to be sent over stream.
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {
			try {
				while (this.InNetEventList_.Count > 0) {
					NetEvent netEvent = this.InNetEventList_.Dequeue();

					// Output the received message
					this.OutputMessage(netEvent);
				}

			} catch (Exception exception) {
				Console.WriteLine(exception.Message);
			}
		}

		/// Stores a received message into the in stream.
		private void OutputMessage(NetEvent netEvent) {

			try {
				// Pull the message type
				uint type = 0;
				netEvent.Data.ReadDynamicUInt(out type, MessageTypeBitLength);
				NetworkConstants.EMessageType messageType = (NetworkConstants.EMessageType)type;

				// Pull the sender's name
				string name = "";
				netEvent.Data.ReadString(out name, CompressionStep);

				// Pull the message
				string message = "";
				netEvent.Data.ReadString(out message, CompressionStep);

				// Convert the message to a byte buffer
				string line = this.FormatMessage(messageType, name, message);
				byte[] buffer = ToBytes(line);

				// Store message into out stream
				if(this.OutStream_ != null)
					this.OutStream_.Write(buffer, 0, buffer.Length);

				// Store message into the message string
				this.MessageString_ += line;
				this.NewMessage_ = true;

			} catch (Exception exception) {
				Console.WriteLine(exception.Message);
			}
		}

		/// Formats an output message
		private string FormatMessage(NetworkConstants.EMessageType type,
			string senderName, string message) {

				string line = "[" + type.ToString() + "]" + senderName + " : " + message;
				return line;
		}

		/// Converts a string to a byte array
		private const int SizeOfChar_ = sizeof(char);
		public static byte[] ToBytes(string source) {
			byte[] bytes = new byte[source.Length * SizeOfChar_];
			System.Buffer.BlockCopy(source.ToCharArray(), 0, bytes, 0, bytes.Length);
			return bytes;
		}

		/// Converts a byte array into a string
		public static string ToString(byte[] source) {
			char[] chars = new char[(int)(source.Length / SizeOfChar_)];
			System.Buffer.BlockCopy(source, 0, chars, 0, source.Length);
			return new string(chars);
		}

		/// Stream that is in charge of
		/// sending received messages to the UI
		private Stream OutStream_;
		public void SetOutStream(Stream stream) {
			this.OutStream_ = stream;
		}

		/// String used to stored received messages.
		/// Clears the string when the get is called.
		private string MessageString_;
		public string MessageString {
			get {
				string messageString = this.MessageString_;
				this.MessageString_ = "";
				this.NewMessage_ = false;
				return messageString;
			}
		}

		/// Keeps track if there are any new messages.
		private bool NewMessage_;
		public bool NewMessage {
			get { return this.NewMessage_; }
		}
	}
}
