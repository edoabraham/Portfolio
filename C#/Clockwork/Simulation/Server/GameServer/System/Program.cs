/// Program.cs - Program Entry and Game Loop
/// Authored by Jesse Z. Zhong (Takuto)

using System;
using System.Collections.Generic;

using NetworkEvents;

/// Game Server
namespace GameServer {

	/// Program Entry Point
	/// DO NOT Change Anything Here
	public static class Program {

		/// Run Arguments
		/// 0 - Instance ID
		/// 1 - IP Address
		/// 2 - Port
		/// 3 - Backlog
		public static void Main(string[] args) {

			/// Create instance of the game.
			GameServer ClockworkGameServer = new GameServer(0, 
				NetworkConstants.LocalIPAddress());

			/// Run Server
			if (ClockworkGameServer != null)
				ClockworkGameServer.Run();
		}
	}
}
