/// Polygon.cs - Polygon Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using System.Linq;
using System.Collections.Generic;
using Utilities;

/// Game Server
namespace GameServer {

	/// Polygon
	public class Polygon {

		/// Constructor
		/// Param 1: Intended center of the polygon (whether it is initially true or not)
		/// Param 2: List of points representing the shape; can be offset
		/// Note: the actual center of the points will be calculated and the points
		/// will be translated so that their center matches that of the intended center
		public Polygon(Vector2 centerOffset, List<Vector2> points) {

			// Check if points actually exist
			System.Diagnostics.Debug.Assert(points.Any());

			// Assign Values
			CenterOffset_ = centerOffset;
			Points_ = points;

			// Adjust Center
			CenterPolygon();
		}

		/// Copy Constructor
		public Polygon(Polygon polygon) {
			CenterOffset_ = polygon.CenterOffset;
			Points_ = polygon.Points;
		}

		/// Center Offset
		/// Move Polygon by changing the center's value
		private Vector2 CenterOffset_;
		public Vector2 CenterOffset {
			set {
				// Assign new center
				CenterOffset_ = value;

				// Shift Polygon
				CenterPolygon();
			}
			get { return CenterOffset_; }
		}

		/// List of Points representing the Polygon
		private List<Vector2> Points_;
		public List<Vector2> Points {
			get { return Points_; }
		}

		/// Edges of the Polygon
		private List<Vector2> Edges_;
		public List<Vector2> Edges {
			get { return Edges_; }
		}

		/// Rotate the Polygon by a certain Angle
		/// Method instead of accessors for clarity
		public void Rotate(float angle) {
			// Any() assumes that there is at least
			// one point for the center/offset
			System.Diagnostics.Debug.Assert(Points_.Any());

			// Rotate all points
			for (int i = 0, j = Points_.Count; i < j; i++)
				Points_[i] = RotatePoint(CenterOffset_, Points_[i], angle);

			// Rebuild Edges
			BuildEdges();
		}

		/// Calculates and Checks for the
		/// Collision of a Circle and a Polygon
		/// Param 1: Moving Polygon
		/// Param 2: Circle
		/// Param 3: Velocity of the Polygon
		/// Description: 
		///		Find the distance between the two center points
		///		Calculate the point whose distance is closest to the center of the circle.
		///		Check if that point fall
		public static CollisionResult CircleCollision(Polygon a, Circle b, Vector2 velocity) {

			// Create Collision Result
			CollisionResult result = new CollisionResult();

			// Localize the Center of the Polygon
			System.Diagnostics.Debug.Assert(a.Points.Any());
			Vector2 centerBoxA = a.CenterOffset;

			// Create another Polygon for the Polygon after
			// it has been translated by the velocity
			Polygon c = new Polygon(a.CenterOffset + velocity, a.Points);
			Vector2 centerBoxC = c.CenterOffset;

			// Initialize max to Negative Infinity, find the difference of the
			// two center points, and localize the normalized difference
			float maxA = float.NegativeInfinity, maxC = float.NegativeInfinity;
			Vector2 centerPointDistanceA = new Vector2(b.CenterOffset - centerBoxA);
			Vector2 centerPointDistanceNormalizedA = centerPointDistanceA.Normalized;
			Vector2 centerPointDistanceC = new Vector2(b.CenterOffset - centerBoxC);
			Vector2 centerPointDistanceNormalizedC = centerPointDistanceC.Normalized;

			// Find the Max
			for (int i = 0, j = a.Points.Count; i < j; i++) {

				// Calculate projection of the vector length between the point and its center
				// against the the vector between the circle and polygon centers
				float projectionA = (a.Points[i] - centerBoxA).DotProduct(centerPointDistanceNormalizedA);
				float projectionC = (c.Points[i] - centerBoxC).DotProduct(centerPointDistanceNormalizedC);

				// Compare project to find which point is closest to the circle's center
				if (maxA < projectionA) maxA = projectionA;
				if (maxC < projectionC) maxC = projectionC;
			}

			// Check if the polygon projection intersects with the circle projection
			// If it doesn't, there is no collision; else there is a collision
			float cpdLengthA = centerPointDistanceA.Length;
			float cpdLengthC = centerPointDistanceA.Length;
			result.Intersect = (((cpdLengthA - maxA - b.Radius) > 0) && (cpdLengthA > 0)) ? false : true;
			result.WillIntersect = (((cpdLengthC - maxC - b.Radius) > 0) && (cpdLengthC > 0)) ? false : true;

			// The minimum translation vector that can
			// be used to push the Circle and Polygon apart
			if (result.WillIntersect) {
				result.MinimumTranslationVector = centerPointDistanceNormalizedC * 
					Math.Abs(cpdLengthC - maxC - b.Radius);
			}

			return result;
		}
		public CollisionResult CircleCollision(Circle b, Vector2 velocity) {
			return CircleCollision(this, b, velocity);
		}

		/// Calculates and Checks for the
		/// Collision of two Polygons
		/// Param 1: Moving Polygon
		/// Param 2: Polygon
		/// Param 3: Velocity of the first Polygon
		/// Description:
		///		
		public static CollisionResult PolygonCollision(Polygon a, Polygon b, Vector2 velocity) {

			// Create new CollisionResult
			CollisionResult result = new CollisionResult();
			result.Intersect = true;
			result.WillIntersect = true;

			int edgeCountA = a.Edges.Count;
			int edgeCountB = a.Edges.Count;
			float minIntervalDistance = float.PositiveInfinity;
			Vector2 translationAxis = new Vector2();
			Vector2 edge;

			// Loop through all the edges of both Polygons
			for (int i = 0, j = (edgeCountA + edgeCountB); i < j; i++) {

				edge = (i < edgeCountA) ? a.Edges[i] : b.Edges[i];

				// 1. Find if the Polygons are currently intersecting

				// Find the axis perpendicular to the current edge
				Vector2 axis = new Vector2(-edge.Y, edge.X);
				axis.Normalize();

				// Find the projection of the Polygon on the current axis
				float minA = 0, minB = 0, maxA = 0, maxB = 0;
				ProjectPolygon(axis, a, ref minA, ref maxA);
				ProjectPolygon(axis, b, ref minB, ref maxB);

				// Check if the Polygon projections are currently intersecting
				if (IntervalDistance(minA, maxA, minB, maxB) > 0)
					result.Intersect = false;

				// 2. Find if the Polygons will intersect with the current velocity

				// Project the velocity on the current axis
				float velocityProjection = axis.DotProduct(velocity);

				// get the project of the first Polygon during movement
				if (velocityProjection < 0)
					minA += velocityProjection;
				else
					maxA += velocityProjection;

				// Check if the Polygon projections are currently intersecting
				float intervalDistance = IntervalDistance(minA, maxA, minB, maxB);
				if (intervalDistance > 0)
					result.WillIntersect = false;

				// If there are no intersections at all, break out of loop
				if(!result.Intersect && !result.WillIntersect)
					break;

				// Check if the current interval distance is the minimum one.
				// If so, store the interval distance and the current distance.
				// This will be used to calculate the minimum translation vector.
				intervalDistance = Math.Abs(intervalDistance);
				if (intervalDistance < minIntervalDistance) {
					minIntervalDistance = intervalDistance;
					translationAxis = axis;

					if ((a.CenterOffset - b.CenterOffset).DotProduct(translationAxis) < 0)
						translationAxis = -translationAxis;
				}
			}

			// The minimum translation vector that can
			// be used to push the Polygons apart
			if (result.WillIntersect)
				result.MinimumTranslationVector = 
					translationAxis * minIntervalDistance;

			return result;
		}
		public CollisionResult PolygonCollision(Polygon b, Vector2 velocity) {
			return PolygonCollision(this, b, velocity);
		}

		#region Private Methods
		/// Centers the Polygon so that the actual center 
		/// of the points matches the User intended center
		private void CenterPolygon() {

			// Used for calculating the actual center
			// and storing the difference
			Vector2 actualCenter = Vector2.Zero;

			// Sum the Points
			int j = Points_.Count;
			for (int i = 0; i < j; i++) {
				actualCenter += Points_[i];
			}

			// Divide the sum of the points by the number of
			// points to get the actual center
			actualCenter /= j;

			// Find the difference of the intended center
			// and the actual center
			System.Diagnostics.Debug.Assert(j > 0);
			actualCenter -= CenterOffset_;

			// Shift all Points with the difference
			for (int i = 0; i < j; i++) {
				Points_[i] -= actualCenter;
			}

			// Rebuild Edges
			BuildEdges();
		}

		/// Builds Edges for Polygon to Polygon Collision
		private void BuildEdges() {

			// Localize
			Vector2 p1;
			Vector2 p2;
			int size = Points_.Count;

			// Size for Optimization
			Edges_ = new List<Vector2>(size);

			// Calculate Edges by subtracting the current
			// point with the previous point
			for (int i = 0; i < size; i++) {
				p1 = Points_[i];
				if ((i + 1) >= size) {
					p2 = Points_[0];
				} else {
					p2 = Points_[i + 1];
				}
				Edges_[i] = p2 - p1;
			}
		}

		/// Rotates a point about another point
		/// Param 1: a is the point b is rotating about
		/// Param 2: b is the point being rotated
		/// Param 3: Angle of rotation
		private Vector2 RotatePoint(Vector2 a, Vector2 b, float angle) {
			// Calculate difference of two points
			b -= a;
			// Calculate the rotation about an origin and add center point back to offset
			return new Vector2((b.X * (float)Math.Cos(angle)) - (b.Y * (float)Math.Sin(angle)) + a.X,
				(b.X * (float)Math.Sin(angle)) + (b.Y * (float)Math.Cos(angle)) + a.X);
		}

		/// Calculate the projection of a Polygon on an axis
		/// and return it as a [min, max] interval
		public static void ProjectPolygon(Vector2 axis, Polygon polygon,
			ref float min, ref float max) { 

			System.Diagnostics.Debug.Assert(polygon.Points.Any());
			float dotProduct = axis.DotProduct(polygon.Points[0]);
			min = dotProduct;
			max = dotProduct;
			for (int i = 0, j = polygon.Points.Count; i < j; i++) {
				dotProduct = polygon.Points[i].DotProduct(axis);
				if (dotProduct < min)
					min = dotProduct;
				else if (dotProduct > max)
					max = dotProduct;
			}
		}

		/// Calculate the distance between [minA, maxA] and [minB, maxB]
		/// The distance will be negative if the intervals overlap
		public static float IntervalDistance(float minA, float maxA, float minB, float maxB) {
			if (minA < minB)
				return minB - maxA;
			else
				return minA - maxB;
		}

		#endregion
	}
}
