/// CollisionResult.cs - CollisionResult Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;
using Utilities;

/// Game Server
namespace GameServer {

	/// Structure that stores the results of Collision Methods
	public struct CollisionResult {

		// Are the Transforms going to intersect forward in time?
		public bool WillIntersect;

		// Are the Transforms currently intersecting?
		public bool Intersect;

		// The translation needed to push the first Transform from the second
		public Vector2 MinimumTranslationVector;
	}
}
