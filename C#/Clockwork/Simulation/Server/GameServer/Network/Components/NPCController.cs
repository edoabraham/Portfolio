/// NPCController.cs - NPCController class implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

using Artemis;
using Artemis.Interface;

/// Game Server
namespace GameServer {

	/// 
	public sealed class NPCController : Controller {

		/// Max number of spells a NPC can control.
		private const int MaxSpells = GlobalData.MaxNPCTotalSpells;

		/// Constructor
		public NPCController(NPCInfo npcInfo) 
			: base() {

				this.Info_ = npcInfo;
		}

		/// NPC setup
		private NPCInfo Info_;
		public NPCInfo Info {
			get { return this.Info_; }
			set { this.Info_ = value; }
		}
	}
}
