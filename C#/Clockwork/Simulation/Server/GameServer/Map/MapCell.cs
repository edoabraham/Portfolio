/// MapCell.cs - MapCell Class Implementation
/// Written By Jesse Z. Zhong and Drew Lopreiato

using System;
using Artemis.Interface;
using System.Collections.Generic;

/// Game Server
namespace GameServer {

	/// Enumerates the regions that can 
	/// be blocked from walking over
	/// These are lines
	public enum EBoundingFlag : byte {
		HorizontalTop = 1,
		HorizontalMid = 2,
		HorizontalBot = 4,
		VerticalLeft = 8,
		VerticalMid = 16,
		VerticalRight = 32,
		DiagonalOne = 64,
		DiagonalThree = 128
	}

	/// Enumerates the terrain types
	public enum EBlockTypes : byte {
		Grass = 0,
		Brush,
		Dirt,
		Trees,
		DirtRock,
		MineralRock,
		ShallowWater,
		DeepWater
	}

	/// Map Cell
	public class MapCell : IComponent {

		/// ID Pool
		private static short IDs_ = 0;

		/// Constructor
		public MapCell(byte x = 0, 
			byte y = 0, byte terrain = 0, 
			byte boundaryFlags = 0,
			byte elevation = 128) {

			// Assign new id
			this.ID_ = IDs_;
			IDs_++;

			// Initialize other variables
			this.X_ = x;
			this.Y_ = y;
			this.Terrain_ = terrain;
			this.BoundaryFlags_ = boundaryFlags;
			this.Elevation_ = elevation;
		}

		/// Coordinates for Map Cell
		private byte X_;
		public byte X {
			set { X_ = value; }
			get { return X_; }
		}
		private byte Y_;
		public byte Y {
			set { Y_ = value; }
			get { return Y_; }
		}

		/// ID of the MapCell
		/// Helps mark the placement and
		/// identify it from others
		private short ID_;
		public short ID {
			set { ID_ = value; }
			get { return ID_; }
		}

		/// Describes the terrain type of this cell
		private byte Terrain_;
		public byte Terrain {
			get { return Terrain_; }
			set { Terrain_ = value; }
		}

		/// Represents the conjunction of individual
		/// EBoundingFlags to make a bounded area
		private byte BoundaryFlags_;
		public byte BoundaryFlags {
			set { BoundaryFlags_ = value; }
			get { return BoundaryFlags_; }
		}

		/// Represents the elevation of the map cell
		/// The default elevation is 128
		private byte Elevation_;
		public byte Elevation {
			set { Elevation_ = value; }
			get { return Elevation_; }
		}
	}
}
