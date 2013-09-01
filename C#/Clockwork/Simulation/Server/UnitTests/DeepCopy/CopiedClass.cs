/// CopiedClass.cs - CopiedClass Class Implementation
/// Written By Jesse Z. Zhong

#define EQUAL_APPROACH

/// The Mode
#if EQUAL_APPROACH
#define D_EQUAL_APPROACH
#endif

using System;
using System.Collections.Generic;

/// Deep Copy
namespace DeepCopy {

	/// Copied Class
	/// This project was created to see,
	/// exhaustively, what happens when
	/// an object is created using a copy 
	/// constructor. Are there references?
	public class CopiedClass {

		/// Constructor
		public CopiedClass() {
			this.Z_ = 0;
			this.HiddenObject_ = new HiddenObject();
			this.ByteArray_ = new List<byte>();
		}

		/// Init-Constructor
		public CopiedClass(float z, HiddenObject hiddenObject, List<byte> byteArray) {
			this.Z_ = z;
#if D_EQUAL_APPROACH
			this.HiddenObject_ = hiddenObject;
			this.ByteArray_ = byteArray;
#else
			this.HiddenObject_ = new HiddenObject(hiddenObject);
			foreach (byte item in byteArray)
				this.ByteArray_.Add(item);
#endif
		}

		/// Copy-Constructor
		public CopiedClass(CopiedClass copiedClass) {
			this.Z_ = copiedClass.Z;
#if D_EQUAL_APPROACH
			this.HiddenObject_ = copiedClass.HiddenObject;
			this.ByteArray_ = copiedClass.ByteArray;
#else
			this.HiddenObject_ = new HiddenObject(copiedClass.HiddenObject);
			foreach (byte item in copiedClass.ByteArray)
				this.ByteArray_.Add(item);
#endif
		}

		/// Values
		private float Z_;
		public float Z {
			get { return this.Z_; }
			set { this.Z_ = value; }
		}

		private HiddenObject HiddenObject_;
		public HiddenObject HiddenObject {
			get { return this.HiddenObject_; }
			set { this.HiddenObject_ = value; }
		}

		private List<byte> ByteArray_;
		public List<byte> ByteArray {
			get { return this.ByteArray_; }
			set { this.ByteArray_ = value; }
		}

		/// Output object contents to standard output
		public void Print() {
			Console.WriteLine("Z = " + this.Z_);
			this.HiddenObject_.Print();
			Console.Write("ByteArray = { ");
			foreach (byte item in this.ByteArray_)
				Console.Write(item.ToString() + " ");
			Console.WriteLine("}");
		}
	}

	/// An object meant to be nested in another.
	public class HiddenObject {

		/// Constructor
		public HiddenObject() {
			this.X_ = 0;
			this.Y_ = 0;
		}

		/// Init-Constructor
		public HiddenObject(int x, int y) {
			this.X_ = x;
			this.Y_ = y;
		}

		/// Copy Constructor
		public HiddenObject(HiddenObject hiddenObject) {
			this.X_ = hiddenObject.X;
			this.Y_ = hiddenObject.Y;
		}

		/// Output object contents to standard output
		public void Print() {
			Console.WriteLine("X = " + this.X_ + " Y = " + this.Y_);
		}

		/// Values
		private int X_;
		public int X {
			get { return this.X_; }
			set { this.X_ = value; }
		}

		private int Y_;
		public int Y {
			get { return this.Y_; }
			set { this.Y_ = value; }
		}
	}
}
