/// Vector3.cs - Vector3 Struct Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;
using System.Xml.Serialization;

/// Utilities
namespace Utilities {
	/// Vector 3D
	public struct Vector3 {

		/// Components
		public float X;
		public float Y;
		public float Z;

		/// Individual Component Hybrid Constructor
		public Vector3(float x, float y = 0, float z = 0) {
			X = x;
			Y = y;
			Z = z;
		}

		/// Copy Constructor
		public Vector3(Vector3 vector) {
			this.X = vector.X;
			this.Y = vector.Y;
			this.Z = vector.Z;
		}

		/// Vector2 Constructor
		public Vector3(Vector2 vector, float z = 0) {
			this.X = vector.X;
			this.Y = vector.Y;
			Z = z;
		}

		/// Addition
		public static Vector3 operator +(Vector3 a, Vector3 b) {
			return new Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
		}

		/// Negate
		public static Vector3 operator -(Vector3 a) {
			return new Vector3(-a.X, -a.Y, -a.Z);
		}

		/// Subtraction
		public static Vector3 operator -(Vector3 a, Vector3 b) {
			return new Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
		}

		/// Multiplication
		public static Vector3 operator *(Vector3 a, float d) {
			return new Vector3(a.X * d, a.Y * d, a.Z * d);
		}
		public static Vector3 operator *(float d, Vector3 a) {
			return new Vector3(a.X * d, a.Y * d, a.Z * d);
		}

		/// Division
		public static Vector3 operator /(Vector3 a, float d) {
			return new Vector3(a.X / d, a.Y / d, a.Z / d);
		}

		/// Equals Comparison
		public static bool operator ==(Vector3 left, Vector3 right) {

			// Reference and Null Reference Test
			if (System.Object.ReferenceEquals(left, right))
				return true;

			// Single Null Reference Test
			if (((object)left == null) || ((object)right == null))
				return false;

			// Value Comparison
			return ((left.X == right.X) && (left.Y == right.Y)
				&& (left.Z == right.Z));
		}

		/// Not Equals Comparison
		public static bool operator !=(Vector3 left, Vector3 right) {
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
				return (X * X + Y * Y + Z * Z);
			}
		}

		/// Return a Normalized Vector3 of this Vector3
		/// Does Not Change the Values of this Vector3
		[XmlIgnore]
		public Vector3 Normalized {
			get {
				return Normalize(this);
			}
		}

		/// Returns the Normalization of a Passed Vector
		public static Vector3 Normalize(Vector3 a) {

			// Length of Zero Exception
			if (a.Length == 0)
				return Vector3.Zero;

			else {

				// Return Normalized Components
				float length = a.Length;
				return new Vector3(a.X / length,
					a.Y / length, a.Z / length);
			}
		}

		/// Normalizes this Vector and Returns it
		public Vector3 Normalize() {
			this = Normalize(this);
			return this;
		}

		/// Equals Override
		public override bool Equals(object obj) {

			if (obj == null)
				return false;

			if ((System.Object)obj == null)
				return false;

			return ((X == ((Vector3)obj).X) &&
				(Y == ((Vector3)obj).Y) && (Z == ((Vector3)obj).Z));
		}
		public bool Equals(Vector3 a) {

			if ((object)a == null)
				return false;

			return ((X == ((Vector3)a).X) &&
				(Y == ((Vector3)a).Y) && (Z == ((Vector3)a).Z));
		}

		/// Hash Code Override
		public override int GetHashCode() {
			return base.GetHashCode();
		}

		/// Returns a Zeroed Vector
		[XmlIgnore]
		public static Vector3 Zero {
			get { return new Vector3(0, 0, 0); }
		}

		/// Cross Product
		public static Vector3 CrossProduct(Vector3 a, Vector3 b) {
			return new Vector3(a.Y * b.Z - a.Z * b.Y,
				a.Z * b.X - a.X * b.Z, a.X * b.Y - a.Y * b.X);
		}
		public Vector3 CrossProduct(Vector3 b) {
			return CrossProduct(this, b);
		}

		/// Dot Product
		public static float DotProduct(Vector3 a, Vector3 b) {
			return (a.X * b.X + a.Y * b.Y + a.Z * b.Z);
		}
		public float DotProduct(Vector3 b) {
			return DotProduct(this, b);
		}

		/// Angle
		public static float Angle(Vector3 a, Vector3 b) {
			return (float)Math.Acos(Normalize(a).DotProduct(Normalize(b)));
		}
		public float Angle(Vector3 b) {
			return Angle(this, b);
		}
		public float Angle() {
			return Angle(this, Vector3.Zero);
		}

		/// Override the ToString Method
		public override string ToString() {
			return "X : " + X.ToString() + " Y : " + Y.ToString() + " Z : " + Z.ToString();
		}
	}
}

