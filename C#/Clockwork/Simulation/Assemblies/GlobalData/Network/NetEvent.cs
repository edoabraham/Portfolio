/// NetEvent.cs - NetEvent Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

using System.Net;

/// Network Events
namespace NetworkEvents {

	/// Net Event Class
	public class NetEvent {

		/// Datagram Header
		/// | 0 ~ 7 | 8 ~ 15 | 16 ~ 23 | 24 ~ 31 |
		/// | Type  |         Time Stamp         |

		#region Data Type Settings
		/// The byte length of the Net Event Type
		public const int NetEventTypeByteLength = 1;
		public const int NetEventTypeBitLength = 
			NetEventTypeByteLength * 8;

		/// The byte length of the elapsed game time
		public const int GameTimeByteLength = 3;
		public const int GameTimeBitLength = 
			GameTimeByteLength * 8;

		/// The minimum size of a datagram 
		/// (size of the custom header extension)
		public const int MinimumPacketLength = 
			NetEventTypeByteLength + GameTimeByteLength;
		#endregion

		/// Send Constructor
		/// Use this constructor to create packets to send
		public NetEvent(ENetEventType netEventType, 
			IPEndPoint sender, IPEndPoint target) {

				this.NetEventType_ = netEventType;
				this.Sender_ = sender;
				this.Target_ = target;

				// Initialize buffer data
				this.Data_ = new BinaryPacket();

				// Add the Net Event ID
				this.Data_.WriteDynamicUInt((uint)netEventType, NetEventTypeBitLength);

				// Reserve space for time
				this.Data_.WriteDynamicUInt(0, GameTimeBitLength);

				// Not really important to sending
				this.TimeSent_ = 0;
				this.TimeReceived_ = 0;
		}

		/// Event Type
		public ENetEventType NetEventType {
			get { return this.NetEventType_; }
		}

		/// Sender's IP EndPoint
		public IPEndPoint Sender {
			get { return this.Sender_; }
			set { this.Sender_ = value; }
		}

		/// Target's IP EndPoint
		public IPEndPoint Target {
			get { return this.Target_; }
			set { this.Target_ = value; }
		}

		/// Sender's IP Address
		public IPAddress SenderIPAddress {
			get { return this.Sender_.Address; }
			set { this.Sender_.Address = value; }
		}

		/// Target's IP Address
		public IPAddress TargetIPAddress {
			get { return this.Target_.Address; }
			set { this.Target_.Address = value; }
		}

		/// Sender's Port
		public int SenderPort {
			get { return this.Sender_.Port; }
			set { this.Sender_.Port = value; }
		}

		/// Target's Port
		public int TargetPort {
			get { return this.Target_.Port; }
			set { this.Target_.Port = value; }
		}

		/// The buffer data
		public BinaryPacket Data {
			get { return Data_; }
		}

		/// Returns data (custom header extension
		/// + payload) with the adjusted time
		public BinaryPacket GetData(long time) {
			
			// Adjust for the correct time
			// returning the data packet
			if (Data_ != null) {
				System.Diagnostics.Debug.Assert((Data_.Buffer != null)
					&& (Data_.Buffer.Length >= (NetEventTypeByteLength +
					GameTimeByteLength)));

				/// Overwrite the time stamp to have the current time
				try {
					// + 1 for the continuation bit
					this.Data_.Overwrite((uint)time, 
						GameTimeBitLength, NetEventTypeBitLength + 1);

				} catch(Exception exception) {
					Console.WriteLine(exception.Message);
				}
			}
			return this.Data_;
		}

		/// Receive Constructor
		/// Use this constructor to store received packets
		public NetEvent(byte[] buffer, long arrivedTime) {
			this.Data_ = new BinaryPacket(buffer);
			this.TimeReceived_ = arrivedTime;
			this.ParseBuffer();
		}

		/// Records the time that the datagram was sent
		public long TimeSent {
			get { return TimeSent_; }
		}

		/// Records the time that the datagram arrived
		public long TimeReceived {
			get { return TimeReceived_; }
		}

		#region Private Members
		/// Parses a buffer for relevant information
		private void ParseBuffer() {
			if (this.Data_.Length >= MinimumPacketLength) {
				uint uintVal = 0;

				// Read for Net Event Type first and store
				this.Data_.ReadDynamicUInt(out uintVal, NetEventTypeBitLength);
				this.NetEventType_ = (ENetEventType)uintVal;

				// Read for the game time next
				this.Data_.ReadDynamicUInt(out uintVal, GameTimeBitLength);
				this.TimeSent_ = uintVal;
				
				#region Don't wanna see it
			} else {

				// Initialize with dummy info
				this.NetEventType_ = ENetEventType.Invalid;
				this.Target_ = new IPEndPoint(IPAddress.Any, 0);
				this.Sender_ = new IPEndPoint(IPAddress.Any, 0);
				#endregion
			}
		}

		/// Prints the buffer to the console
		private void PrintBuffer() {
			foreach (byte item in Data_.Buffer)
				Console.Write(item.ToString() + " ");
			Console.WriteLine();
		}

		/// Writes an N-Bit Unsigned Integer into the Buffer
		private byte[] ConvertToByte(uint value, int bytes) {

			if ((bytes > 1) && (bytes <= 4)) {

				// Shift bits over
				value <<= 32 - (8 * bytes);

				// Create buffer
				byte[] buffer = new byte[bytes];

				// Unsigned int used for comparing bits
				uint bitComparer = (uint)1 << 31;

				// Iterate through bytes
				int bitIndex = 0, bitLength = 8;
				for (int bufferIndex = 0, bufferLenth = buffer.Length;
					bufferIndex < bufferLenth; bufferIndex++) {

					// Byte with a bit in it
					// Used for writing a bit to a byte
					byte bitWriter = (byte)1 << 7;

					// Iterate through bits
					// and store into the byte
					while (bitIndex < bitLength) {

						// Compare to see if bit exists
						// Write bite to the buffer if it does
						if ((value & bitComparer) == bitComparer)
							buffer[bufferIndex] |= bitWriter;

						// Shift the bit in the bit writer
						// and the bit comparer to the right
						bitComparer >>= 1;
						bitWriter >>= 1;

						// Increment index up
						bitIndex++;
					}

					// Update bit length
					bitLength += 8;
				}

				return buffer;
			} else {
				throw new Exception("Invalid number of bytes; Uint has a maximum of 4" + 
					"bytes; at least a size of one byte must be specified.");
			}
		}

		/// Converts a byte array to a unsigned integer
		private uint ConvertToUint(byte[] value) {
			uint result = 0;
			if ((value == null) || (value.Length > 4))
				throw new Exception("The byte array cannot be empty or exceed a length of 4 bytes.");

			uint bitWriter = 1;

			for (int bufferIndex = value.Length - 1;
				bufferIndex >= 0; bufferIndex--) {

				byte bitComparer = 1;

				for (int bitIndex = 7; bitIndex >= 0; bitIndex--) {


					if ((value[bufferIndex] & bitComparer) == bitComparer)
						result |= bitWriter;

					// 
					bitComparer <<= 1;
					bitWriter <<= 1;
				}
			}
			return result;
		}

		private IPEndPoint Sender_;
		private IPEndPoint Target_;
		private ENetEventType NetEventType_;
		private BinaryPacket Data_;
		private long TimeSent_;
		private long TimeReceived_;
		#endregion
	}
}
