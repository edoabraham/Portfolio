/// MDCharacterDeath.cs - MDCharacterDeath Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Network Events
namespace NetworkEvents {

	/// Informs all Players of a Character Death, whether it
	/// be another Player or a Boss, and the Name of the Killer
	public class MDCharacterDeath : IMetaData<MDCharacterDeath> {

		/// Compression Step (ASCII)
		/// TODO: Change to UTF-8 Later
		private const int CompressionStep = 7;

		/// Constructor
		/// Pass the Name of the Killer and the name
		/// of the Character that was Killed
		public MDCharacterDeath(string killer, string killed) {
			Killer_ = killer;
			Killed_ = killed;
		}

		/// Name of the Killer
		private string Killer_;
		public string Killer {
			set { Killer_ = value; }
			get { return Killer_; }
		}

		/// Name of the Character that was Killed
		private string Killed_;
		public string Killed {
			set { Killed_ = value; }
			get { return Killed_; }
		}

		/// Writes the Names of the Killer and Killed to a Net Event
		public NetEvent Write(NetEvent netEvent) {
			netEvent.Data.WriteString(Killer_, CompressionStep);
			netEvent.Data.WriteString(Killed_, CompressionStep);
			return netEvent;
		}

		/// Reads the Names of the Killer and Killed from Net Event
		public MDCharacterDeath Read(NetEvent netEvent) {
			netEvent.Data.ReadString(out Killer_, CompressionStep);
			netEvent.Data.ReadString(out Killed_, CompressionStep);
			return this;
		}
	}
}
