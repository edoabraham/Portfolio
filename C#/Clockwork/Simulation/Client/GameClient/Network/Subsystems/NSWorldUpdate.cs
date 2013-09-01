/// NSWorldUpdate.cs - NSWoldUpdate Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using System.Linq;
using System.Collections.Generic;

using Artemis;
using Artemis.Utils;
using Artemis.System;
using NetworkEvents;
#endregion

/// Game Client
namespace GameClient {

	/// World Update
	public class NSWorldUpdate : 
		ClientProcessingSystem {

		/// Constructor
		public NSWorldUpdate(int interval,
			ClientSystem clientSystem) :
			base(interval, clientSystem,
			ENetEventType.WorldUpdate, true) {

		}

		/// Load Content
		public override void LoadContent() {

		}

		/// 
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {

		}
	}
}
