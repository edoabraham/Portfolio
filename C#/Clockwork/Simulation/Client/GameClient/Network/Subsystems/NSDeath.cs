/// NSDeath.cs - NSDeath Class Implementation
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

	/// Character Death
	public class NSDeath : 
		ClientProcessingSystem {

		/// Constructor
		public NSDeath(int interval,
			ClientSystem clientSystem) :
			base(interval, clientSystem,
			ENetEventType.CharacterDeath, true) {

		}

		/// Load Content
		public override void LoadContent() {

		}

		/// 
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {

		}
	}
}
