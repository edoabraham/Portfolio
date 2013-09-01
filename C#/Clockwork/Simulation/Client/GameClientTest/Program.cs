/// Program.cs - Program Class Implementation.
/// Written by Jesse Z. Zhong

using System;
using System.Collections.Generic;

using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;

using GameClient;
using NetworkEvents;

/// Program Entry Point
public class Program {

	/// Run arguments are purely for debugging purposes.
	/// Note: Incorporate flags for developer mode.
	static void Main(string[] args) {

		/// Temporal
		/// Note: In the actual implementation the
		/// GameClient module will be run inside of
		/// the Hub system. For now we'll run the
		/// game simulation here for easy of testing.
		GameClient.GameClient ClockworkGameClient = new GameClient.GameClient(GetIP());

		ThreadStart ts = new ThreadStart(() => {

			/// Run Client
			if (ClockworkGameClient != null)
				ClockworkGameClient.Run(true);
		});
		Thread thread = new Thread(ts);
		thread.Start();

		ClockworkGameClient.LoadingSystem.RequestInfo();
	}
		
	/// Prompts user for an IP Address. 
	/// If left blank, the IP Address is the local host.
	private static IPAddress GetIP() {

		try {
			while (true) {
				Console.Write("Server IP: ");
				string input = Console.ReadLine();
				if (input == "") {
					IPAddress local;
					Console.WriteLine((local = NetworkConstants.LocalIPAddress()).ToString());
					return local;
				}
				IPAddress myIP = IPAddress.Parse(input);
				return myIP;
			}
		} catch (Exception exception) {
			System.Diagnostics.Debug.WriteLine(exception.Message);
			return null;
		}
	}
}

