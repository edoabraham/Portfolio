/// SystemsInitializer.cs - SystemsInitializer Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using System.Collections.Generic;
using Artemis;
using Artemis.System;
using GameClient;
#endregion

using PlayerInfo = GameClient.NSCWorldLoad.PlayerInfo;
using NPCInfo = GameClient.NSCWorldLoad.NPCInfo;

/// In charge of instantiating game objects
public class SystemsInitializer : EntitySystem {

	/// Constructor
	public SystemsInitializer(NSCWorldLoad worldLoad) : base() {
		this.WorldLoad_ = worldLoad;
		this.RequestedInfo_ = false;
	}

	/// Initialize
	public override void LoadContent() {
		
	}

	/// 
	protected override void ProcessEntities(IDictionary<int, Entity> entities) {
		#region Request Game Info from the Server
		if (this.RequestedInfo_) {
			this.WorldLoad_.RequestInfo();
			this.RequestedInfo_ = false;
		}
		#endregion

		// Process info that is received and begin 
		// loading the appropriate assets and creating entities.
		if (this.WorldLoad_.InfoReceived) {

			// Localize
			var playerInfoList = this.WorldLoad_.PlayerInfoList;
			var npcInfoList = this.WorldLoad_.NPCInfoList;
		}
	}

	/// 
	private bool RequestedInfo_;
	public bool RequestedInfo {
		get { return this.InfoRecieved_; }
		set { this.InfoRecieved_ = value; }
	}

	/// Reference to the network system in
	/// charge of retrieving loading information.
	private NSCWorldLoad WorldLoad_;
}
