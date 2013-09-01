/// MapSystem.cs - Map System Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

using Artemis;
using Artemis.System;

/// Game Server
namespace GameServer {

	/// Map System
	public class MapSystem : EntityProcessingSystem {

		/// Constructor
		public MapSystem(string mapDirectory)
			: base(typeof(MapCell)) {

			MapDirectory_ = mapDirectory;
		}

		/// Initialize
		public override void LoadContent() {
			MapCellMapper_ = new ComponentMapper<MapCell>(this.EntityWorld);

		}

		/// Process Entities
		public override void Process(Entity entity) {
			
		}

		#region Component Mapper
		private ComponentMapper<MapCell> MapCellMapper_;
		#endregion

		private string MapDirectory_;
		public string MapDirectory {
			get { return MapDirectory_; }
		}
	}
}
