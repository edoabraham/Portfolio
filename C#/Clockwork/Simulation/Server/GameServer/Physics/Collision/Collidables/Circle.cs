/// Circle.cs - Circle Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using System.Linq;
using System.Collections.Generic;
using Utilities;

/// Game Server
namespace GameServer {

	/// Circle
	public struct Circle {

		/// Constructor
		public Circle(Vector2 centerOffset, 
			float radius) {
				CenterOffset_ = centerOffset;
				Radius_ = radius;
		}

		/// Offset placement of 
		/// the circle's origin/center
		private Vector2 CenterOffset_;
		public Vector2 CenterOffset {
			set { CenterOffset_ = value; }
			get { return CenterOffset_; }
		}

		/// Radius of the Circle
		private float Radius_;
		public float Radius {
			set { Radius_ = value; }
			get { return Radius_; }
		}

		/// Calculates and Checks for
		/// the Collision of two Circles
		/// Param 1: Moving Circle
		/// Param 2: "Stationary" Circle (Circle whose velocity isn't factored in yet)
		/// Param 3: Velocity of the first Circle
		/// Return: CollisionResult
		public static CollisionResult CircleCollision(Circle a, Circle b, Vector2 velocity) {

			// Create new CollisionResult
			CollisionResult result = new CollisionResult();

			// 1. Calculate if the Circles are already intersecting

			// Calculates the difference of the two centers

			// Compare to the Sum of the Radii
			float sumOfRadii = a.Radius + b.Radius;
			float sumOfRadiiSquared = sumOfRadii * sumOfRadii;
			if ((a.CenterOffset - b.CenterOffset).SquaredLength < sumOfRadiiSquared)
				result.Intersect = true;
			else result.Intersect = false;

			// 2. Calculate if the Circles will intersect

			// Offset the first Circle as if it has moved
			a.CenterOffset += velocity;
			Vector2 difference = (a.CenterOffset - b.CenterOffset);
			if (difference.SquaredLength < sumOfRadiiSquared)
				result.WillIntersect = true;
			else result.WillIntersect = false;

			// The minimum translation vector that can
			// be used to push the Circles apart
			if (result.WillIntersect) {
				result.MinimumTranslationVector = difference.Normalized *
					Math.Abs(difference.Length - sumOfRadii);
			}

			return result;
		}
		public CollisionResult CircleCollision(Circle b, Vector2 velociy) {
			return CircleCollision(this, b, velociy);
		}

		/// Calculates and Checks for the
		/// Collision of a Circle and a Polygon
		/// Param 1: Moving Circle
		/// Param 2: Polygon
		/// Param 3: Velocity of the Circle
		/// Description: 
		///		Find the distance between the two center points
		///		Calculate the point whose distance is closest to the center of the circle.
		///		Check if that point fall
		public static CollisionResult PolygonCollision(Circle a, Polygon b, Vector2 velocity) {

			// Create Collision Result
			CollisionResult result = new CollisionResult();

			// Create a copy of the Circle that has been translated by the velocity
			Circle c = new Circle(a.CenterOffset + velocity, a.Radius);

			// Localize the Center of the Polygon
			System.Diagnostics.Debug.Assert(b.Points.Any());
			Vector2 centerBox = b.CenterOffset;

			// Initialize max to Negative Infinity, find the difference of the
			// two center points, and localize the normalized difference
			float maxA = float.NegativeInfinity, maxC = float.NegativeInfinity;
			Vector2 centerPointDistanceA = new Vector2(a.CenterOffset - centerBox);
			Vector2 centerPointDistanceNormalizedA = centerPointDistanceA.Normalized;
			Vector2 centerPointDistanceC = new Vector2(c.CenterOffset - centerBox);
			Vector2 centerPointDistanceNormalizedC = centerPointDistanceC.Normalized;

			// Find the Max
			for (int i = 0, j = b.Points.Count; i < j; i++) {

				// Calculate projection of the vector length between the point and its center
				// against the the vector between the circle and polygon centers
				float projectionA = (b.Points[i] - centerBox).DotProduct(centerPointDistanceNormalizedA);
				float projectionC = (b.Points[i] - centerBox).DotProduct(centerPointDistanceNormalizedC);

				// Compare project to find which point is closest to the circle's center
				if (maxA < projectionA) maxA = projectionA;
				if (maxC < projectionC) maxC = projectionC;
			}

			// Check if the polygon projection intersects with the circle projection
			// If it doesn't, there is no collision; else there is a collision
			float cpdLengthA = centerPointDistanceA.Length;
			float cpdLengthC = centerPointDistanceA.Length;
			result.Intersect = (((cpdLengthA - maxA - a.Radius) > 0) && (cpdLengthA > 0)) ? false : true;
			result.WillIntersect = (((cpdLengthC - maxC - c.Radius) > 0) && (cpdLengthC > 0)) ? false : true;

			// The minimum translation vector that can
			// be used to push the Circle and Polygon apart
			if (result.WillIntersect) {
				result.MinimumTranslationVector = centerPointDistanceNormalizedC *
					Math.Abs(cpdLengthC - maxC - c.Radius);
			}

			return result;
		}
		public CollisionResult PolygonCollision(Polygon b, Vector2 velocity) {
			return PolygonCollision(this, b, velocity);
		}
	}
}
