/// MDConfirmKeyBindingChanges.cs - MDConfirmKeyBindingChanges Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Network Events
namespace NetworkEvents {

	/// Sends a True or False Confirmation informing
	/// a specific Client that the Key Binding Changes
	/// requested were made and that it is alright to 
	/// make the same changes client side.
	public class MDConfirmKeyBindingChanges :
		IMetaData<MDConfirmKeyBindingChanges> {

		/// Constructor
		public MDConfirmKeyBindingChanges() {

		}

		/// Write
		public NetEvent Write(NetEvent netEvent) {
			return netEvent;
		}

		/// Read
		public MDConfirmKeyBindingChanges Read(NetEvent netEvent) {
			return this;
		}
	}
}
