/// MDRequestKeyBindingChange.cs - MDRequestKeyBindingChange Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Network Events
namespace NetworkEvents {

	/// 
	public class MDRequestKeyBindingChange :
		IMetaData<MDRequestKeyBindingChange> {

		public MDRequestKeyBindingChange() {

		}

		/// Write
		public NetEvent Write(NetEvent netEvent) {
			return netEvent;
		}

		/// Read
		public MDRequestKeyBindingChange Read(NetEvent netEvent) {
			return this;
		}
	}
}
