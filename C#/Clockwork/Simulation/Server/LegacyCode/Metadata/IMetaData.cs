/// IMetaData.cs - IMetaData Interface Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Network Events
namespace NetworkEvents {

	/// Interface for creating Net Events with
	/// Read and Write capabilities
	public interface IMetaData<T> {

		NetEvent Write(NetEvent netEvent);
		T Read(NetEvent netEvent);

	}
}
