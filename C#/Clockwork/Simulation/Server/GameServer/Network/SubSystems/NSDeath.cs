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

/// Game Server
namespace GameServer {

	/// Character Death
	public sealed class NSDeath : 
		ServerProcessingSystem {

		/// Constructor
		public NSDeath(int interval,
			ServerSystem serverSystem) :
			base(interval, serverSystem,
			ENetEventType.CharacterDeath, false) {

		}

		/// Load Content
		public override void LoadContent() {

		}

		/// 
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {

		}
	}
}
