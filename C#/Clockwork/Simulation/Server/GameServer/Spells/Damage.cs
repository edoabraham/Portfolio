/// Damage.cs - Damage Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Handles Damage Formulas
	public static class Damage {

		/// Constructor
		static Damage() {

		}

		/// Physical Damage Formula
		public static int Physical(int defense, int damage) {
			// Simple flat implementation
			int result = damage - defense;
			if (result > 0)
				return result;
			else
				return 1;
		}

		/// Magical Damage Formula
		public static int Magical(int defense, int damage) {
			// Simple flat implementation
			int result = damage - defense;
			if (result > 0)
				return result;
			else
				return 1;
		}
	}
}
