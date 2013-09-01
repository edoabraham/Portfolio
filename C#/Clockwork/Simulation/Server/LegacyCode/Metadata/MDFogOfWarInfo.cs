/// MDFogOfWarInfo.cs - MDFogOfWarInfo Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Network Events
namespace NetworkEvents {

	/// 
	public class MDFogOfWarInfo : IMetaData<MDFogOfWarInfo> {


		/// Write
		public NetEvent Write(NetEvent netEvent) {
			return netEvent;
		}

		/// Read
		public MDFogOfWarInfo Read(NetEvent netEvent) {
			return this;
		}
	}
}
