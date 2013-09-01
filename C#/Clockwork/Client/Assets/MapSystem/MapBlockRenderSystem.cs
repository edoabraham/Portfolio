/// MapBlockRenderSystem.cs - MapBlockRenderSystem Class Implementation
/// Written By Jesse Z. Zhong

#region System Directives
using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;
#endregion

using UnityEngine;

/// 
public class MapBlockRenderSystem : EntityProcessingSystem {

	/// Constructor
	public MapBlockRenderSystem() : 
		base(typeof(MapBlock)) {

	}
	
	/// Initialize System
	public override void LoadContent() {
		this.MapBlockMapper_ = new ComponentMapper<MapBlock>(this.EntityWorld);
	}
	
	/// 
	public override void Process(Entity e) {
		
	}
	
	#region Component Mappers
	private ComponentMapper<MapBlock> MapBlockMapper_;
	#endregion
}

