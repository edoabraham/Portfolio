/// NetworkConstants.cs - NetworkConstants Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Linq;
using System.Linq.Expressions;
using System.Text;

using System.Net;
using System.Net.Sockets;

/// Network Events
namespace NetworkEvents {

	/// Constants that are shared 
	/// between client and server.
	public static class NetworkConstants {

		/// Server and Client port numbers
		public const int ServerPort = 8800;
		public const int ClientPort = 8400;

		/// Magic Number
		public const int SIO_UDP_CONNRESET = -1744830452;

		/// Default buffer size
		/// Note: Do not exceed 1024,
		/// as performance will be seriously affected
		public const int DefaultBufferSize = 1024;

		/// The bit resolution for the ping-pong marker
		public const int PingPongMarkerBitSize = 23;

		#region Message
		/// Message Type
		/// Decides what type of message is being sent
		public enum EMessageType : uint {
			All,
			Team,
			Whisper
		}

		/// Length of the message type
		public static readonly int MessageTypeBitLength = EnumBitLength(typeof(EMessageType));

		/// Defines how well a message can be compressed
		/// This number must also take into account the
		/// encoding type of the characters being sent.
		public const int CompressionStep = 16;
		#endregion

		#region World
		#region Loading
		/// Enumerates the loading phase of a client
		public enum ELoadPhase {
			Info = 0,
			Progress,
			Completion
		}

		/// Length of the load phase type
		public static readonly int LoadPhaseBitLength = EnumBitLength(typeof(ELoadPhase));

		/// The bit length of the progress percent number
		public const int MaxProgressBitLength = 7;
		#endregion

		/// Max bit length for a player ID
		public const int PlayerIDBitLength = 4;

		/// Max bit length of characters (ECharacter)
		public static readonly int CharacterIDBitLength = EnumBitLength(typeof(ECharacter));

		/// Max bit length of spells (ESpell)
		public static readonly int SpellIDBitLength = EnumBitLength(typeof(ESpell));

		/// Max bit length of items (EItem)
		public static readonly int ItemIDBitLength = EnumBitLength(typeof(EItem));

		/// Max bit length of map (EMap)
		public static readonly int MapIDBitLength = EnumBitLength(typeof(EMap));
		
		
		#endregion

		/// Finds the optimal bit size for 
		/// storing enum values of a certain enum type
		private static int EnumBitLength(Type enumType) {
			int result = (int)Math.Ceiling(Math.Log((double)Enum.GetNames(enumType).Length, 2));
			return (result > 0) ? result : 1;
		}

		/// Finds the optimal bit size for storing
		/// values that have an expected max value
		private static int BitLength(int maxValue) {
			int result = (int)Math.Ceiling(Math.Log((double)maxValue, 2));
			return (result > 0) ? result : 1;
		}

		/// Returns the Local Host Address
		public static IPAddress LocalIPAddress() {
			IPAddress localIP = IPAddress.Any;
			IPHostEntry host = Dns.GetHostEntry(Dns.GetHostName());
			foreach (IPAddress item in host.AddressList) {
				if (item.AddressFamily == AddressFamily.InterNetwork) {
					localIP = item;
					break;
				}
			}
			return localIP;
		}
	}
}
