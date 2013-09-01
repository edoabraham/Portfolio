/// Transform.cs - Transform Class Implementation
/// Written By Jesse Z. Zhong

#region System Directives
using System;
using Artemis.Interface;
using System.Collections.Generic;
using System.Xml.Serialization;
using Utilities;
#endregion

/// Game Server
namespace GameServer {

	/// Different Character Size Flags
	public enum CharacterSize : int {
		Small,
		Medium,
		Large
	}

	/// Transform Component
	public class Transform : IComponent {

		/// Size Radius Values
		private const float SmallRadius = 0.6f;
		private const float MediumRadius = 0.8f;
		private const float LargeRadius = 1.0f;

		/// Default Constructor (for Serialization)
		private Transform() {
			this.Position_ = Vector3.Zero;
			this.HasCircle_ = false;
			this.HasPolygon_ = false;
			this.DirectCircle_ = false;
		}

		/// Init-Constructor; Vector3 Source
		public Transform(Vector3 source) {
			this.Position_ = source;
			this.HasCircle_ = false;
			this.HasPolygon_ = false;
			this.DirectCircle_ = false;
		}

		/// Init-Constructor; Transform Source
		public Transform(Transform source) {
			this.Position_ = source.Position;
			this.HasCircle_ = source.HasCircle;
			this.HasPolygon_ = source.HasPolygon;
			this.DirectCircle_ = source.DirectCircle;
			this.DirectionAngle_ = source.DirectionAngle;
		}

		/// Character Transform Constructor
		public Transform(Vector3 source, CharacterSize size) {
			this.Position_ = source;
			this.CircleZone_.CenterOffset = (Vector2)source;
			this.SetSize(size);
			this.HasCircle_ = true;
			this.HasPolygon_ = false;
			this.DirectCircle_ = true;
			this.DirectionAngle_ = 0;
		}

		/// Circle and Polygon
		public Transform(Vector3 source, Circle circleZone,
			Polygon polygonZone) {
			this.Position_ = source;
			this.CircleTemplate_ = circleZone;
			this.PolygonTemplate_ = polygonZone;
			this.HasCircle_ = true;
			this.HasPolygon_ = true;
			this.DirectCircle_ = false;
		}

		/// Circle Only
		public Transform(Vector3 source, Circle circleZone) {
			this.Position_ = source;
			this.CircleTemplate_ = circleZone;
			this.HasCircle_ = true;
			this.HasPolygon_ = false;
			this.DirectCircle_ = false;
		}

		/// Polygon Only
		public Transform(Vector3 source, Polygon polygonZone) {
			this.Position_ = source;
			this.PolygonTemplate_ = polygonZone;
			this.HasCircle_ = false;
			this.HasPolygon_ = true;
			this.DirectCircle_ = false;
		}

		/// Translate the Position Given a Vector3 Displacement
		public void Offset(Vector3 displacement) {
			Position_ += displacement;
			Update();
		}

		/// Translate the Position Given the
		/// Floating Point Type Components
		public void Offset(float x) {
			this.Offset(x, 0, 0);
		}
		public void Offset(float x, float y) {
			this.Offset(x, y, 0);
		}
		public void Offset(float x, float y, float z) {
			this.Position_ += new Vector3(x, y, z);
			Update();
		}

		/// Rotates the Components Direction
		/// X => Yaw, Y => Pitch, Z => Roll
		public void Rotate(Vector3 angles) {
			Direction_ += angles;
			Update();
		}

		/// Rotates the Components Direction
		/// X => Yaw, Y => Pitch, Z => Roll
		public void Rotate(float yaw) {
			Rotate(yaw, this.Direction_.Y, this.Direction_.Z);
		}
		public void Rotate(float yaw, float pitch) {
			Rotate(yaw, pitch, this.Direction_.Z);
		}
		public void Rotate(float yaw, float pitch, float roll) {
			this.Rotate(new Vector3(yaw, pitch, roll));
		}

		/// Position Vector
		protected Vector3 Position_;
		public Vector3 Position {
			get { return Position_; }
			set { 
				Position_ = value;
				Update();
			}
		}

		/// Rotation Vector or Direction Vector;
		/// X => Yaw, Y => Pitch, Z => Roll
		protected Vector3 Direction_;
		public Vector3 Direction {
			set { this.Direction_ = value; }
			get { return this.Direction_; }
		}

		/// Calculates Facing Direction
		/// Angle on the X, Y Plane
		public void CalculateDirection(Vector2 target) {
			if ((Vector2)this.Position_ != target) {
				// Calculate direction vector
				Vector2 direction = target - (Vector2)this.Position_;
				direction.Normalize();
				Direction_ = (Vector3)direction;

				// Calculate angle
				if ((direction.Y == 0.0f) && (direction.X == 0.0f))
					DirectionAngle_ = 0.0f;
				DirectionAngle_ = (float)Math.Atan2(direction.Y, direction.X);
			}
		}
		private float DirectionAngle_;
		public float DirectionAngle {
			get { return this.DirectionAngle_; }
		}

		#region Collision
		#region Spell Notes
		/// Spell Transform
		/// Spell collision zones have a more elaborate setup
		/// compared to that of characters. Each contains a 
		/// Circle and Polygon shape that can be used to free
		/// form a collision area.
		/// This should be more than enough to create fairly
		/// accurate and low cost spell areas.
		/// Example Collision Areas:
		///		Cast Circle - Circle Area, no Polygon
		///		Cone - Circle + Triangle Polygon
		///		Projectile - Long, narrow Pentagon Polygon, no Circle
		///		
		/// As for the fields and Accessors, there will be a private
		/// copy of two different Circles and two different Polygons.
		/// One copy will represent the unchanged template of the shape.
		/// This includes the offset, which is important for creating
		/// interesting spells and spell hit zones. The second will be
		/// the first one with the position and angle taken into account.
		#endregion
		/// Sets the Radius of the Collision
		/// Zone depending on the chosen Size
		private void SetSize(CharacterSize size) {
			switch (size) {
				case CharacterSize.Small:
					CircleZone_.Radius = SmallRadius;
					break;
				case CharacterSize.Medium:
					CircleZone_.Radius = MediumRadius;
					break;
				case CharacterSize.Large:
					CircleZone_.Radius = LargeRadius;
					break;
				default:
					// Default on Medium Size
					CircleZone_.Radius = MediumRadius;
					break;
			}
		}

		/// Update Collision Zone
		private void Update() {

			// Circle Update
			if (HasCircle_) {
				/// Check if Character or not
				if (DirectCircle_) {
					CircleZone_.CenterOffset = (Vector2)Position_;
				} else {
					CircleZone_ = new Circle(CircleTemplate_.CenterOffset +
						(Vector2)Position_, CircleTemplate_.Radius);
				}
			}

			// Polygon Update
			if (HasPolygon_) {
				PolygonZone_ = new Polygon(PolygonTemplate_.CenterOffset + 
					(Vector2)Position_, PolygonTemplate_.Points);
				PolygonZone_.Rotate(Direction_.Y);
			}
		}

		/// Circle Zone
		private Circle CircleTemplate_;
		private Circle CircleZone_;
		public Circle CircleZone {
			get { return this.CircleZone_; }
		}

		/// Polygon Zone
		private Polygon PolygonTemplate_;
		private Polygon PolygonZone_;
		public Polygon PolygonZone {
			get { return this.PolygonZone_; }
		}

		/// Flags
		private bool DirectCircle_;
		private bool HasCircle_;
		private bool HasPolygon_;
		public bool DirectCircle {
			get { return DirectCircle_; }
		}
		public bool HasCircle {
			get { return HasCircle_; }
		}
		public bool HasPolygon {
			get { return HasPolygon_; }
		}
		#endregion
	}
}


