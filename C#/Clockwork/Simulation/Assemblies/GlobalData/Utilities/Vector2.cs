/// Vector2.cs - Vector2 Struct Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;
using System.Xml.Serialization;

/// Utilities
namespace Utilities {
	/// Vector 2D
	public struct Vector2 {

		/// Components
		public float X;
		public float Y;

		/// Constructor
		public Vector2(float x, float y = 0) {
			X = x;
			Y = y;
		}

		/// Copy Constructor
		public Vector2(Vector2 vector) {
			this.X = vector.X;
			this.Y = vector.Y;
		}

		/// Explicit Conversion from Vector3 to Vector2
		public static explicit operator Vector2(Vector3 b) {
			return new Vector2(b.X, b.Y);
		}

		/// Explicit Conversion from Vector2 to Vector3
		public static explicit operator Vector3(Vector2 b) {
			return new Vector3(b.X, b.Y, 0);
		}

		/// Addition
		public static Vector2 operator +(Vector2 a, Vector2 b) {
			return new Vector2(a.X + b.X, a.Y + b.Y);
		}

		/// Negate
		public static Vector2 operator -(Vector2 a) {
			return new Vector2(-a.X, -a.Y);
		}

		/// Subtraction
		public static Vector2 operator -(Vector2 a, Vector2 b) {
			return new Vector2(a.X - b.X, a.Y - b.Y);
		}

		/// Multiplication
		public static Vector2 operator *(Vector2 a, float d) {
			return new Vector2(a.X * d, a.Y * d);
		}
		public static Vector2 operator *(float d, Vector2 a) {
			return new Vector2(a.X * d, a.Y * d);
		}

		/// Division
		public static Vector2 operator /(Vector2 a, float d) {
			return new Vector2(a.X / d, a.Y / d);
		}

		/// Equals Comparison
		public static bool operator ==(Vector2 left, Vector2 right) {

			// Reference and Null Reference Test
			if (System.Object.ReferenceEquals(left, right))
				return true;

			// Single Null Reference Test
			if (((object)left == null) || ((object)right == null))
				return false;

			// Value Comparison
			return ((left.X == right.X) && (left.Y == right.Y));
		}

		/// Not Equals Comparison
		public static bool operator !=(Vector2 left, Vector2 right) {
			return !(left == right);
		}

		/// Returns the Magnitude of the Vector
		[XmlIgnore]
		public float Length {
			get {
				return (float)Math.Sqrt(SquaredLength);
			}
		}

		/// Returns the Squared Length of the Vector
		[XmlIgnore]
		public float SquaredLength {
			get {
				return (X * X + Y * Y);
			}
		}

		/// Return a Normalized Vector2 of this Vector2
		/// Does Not Change the Values of this Vector2
		[XmlIgnore]
		public Vector2 Normalized {
			get {
				return Normalize(this);
			}
		}

		/// Returns the Normalization of a Passed Vector
		public static Vector2 Normalize(Vector2 a) {

			// Length of Zero Exception
			if (a.Length == 0)
				return Vector2.Zero;

			else {

				// Return Normalized Components
				float length = a.Length;
				return new Vector2(a.X / length,
					a.Y / length);
			}
		}

		/// Normalizes this Vector and Returns it
		public Vector2 Normalize() {
			this = Normalize(this);
			return this;
		}

		/// Equals Override
		public override bool Equals(object obj) {

			if (obj == null)
				return false;

			if ((System.Object)obj == null)
				return false;

			return ((X == ((Vector2)obj).X) &&
				(Y == ((Vector2)obj).Y));
		}
		public bool Equals(Vector2 a) {

			if ((object)a == null)
				return false;

			return ((X == ((Vector2)a).X) &&
				(Y == ((Vector2)a).Y));
		}

		/// Hash Code Override
		public override int GetHashCode() {
			return base.GetHashCode();
		}

		/// Returns a Zeroed Vector
		[XmlIgnore]
		public static Vector2 Zero {
			get { return new Vector2(0, 0); }
		}

		/// Dot Product
		public static float DotProduct(Vector2 a, Vector2 b) {
			return ((a.X * b.X) + (a.Y * b.Y));
		}
		public float DotProduct(Vector2 b) {
			return DotProduct(this, b);
		}

		/// Angle
		public static float Angle(Vector2 a, Vector2 b) {
			return (float)Math.Acos(Normalize(a).DotProduct(Normalize(b)));
		}
		public float Angle(Vector2 b) {
			return Angle(this, b);
		}
		public float Angle() {
			return Angle(this, Vector2.Zero);
		}

		/// Override the ToString Method
		public override string ToString() {
			return "X : " + X.ToString() + " Y : " + Y.ToString();
		}
	}
}



