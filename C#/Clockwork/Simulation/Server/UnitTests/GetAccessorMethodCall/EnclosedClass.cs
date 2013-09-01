/// EnclosedClass.cs - EncloseClass Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

/// Get Accessors Method Call Test
namespace GetAccessorMethodCall {

	/// The objective of this test is to see
	/// what happens when we call a method 
	/// from an object that is of "get" type.
	public class EnclosedClass {

		/// Constructor
		public EnclosedClass() {
			this.X_ = 0;
			this.Y_ = 0;
			this.Z_ = 0;
		}

		/// Internal Values
		private int X_;
		private int Y_;
		private int Z_;

		/// Changes the values of the object
		public void AssignValues(int x, int y) {

			// Assign X_ and Y_
			this.X_ = x;
			this.Y_ = y;

			// Add for Z_
			this.Z_ = x + y;
		}

		/// Prints the internal values
		public void Print() {
			Console.WriteLine("X = " + this.X_.ToString() + 
				", Y = " + this.Y_.ToString() + ", Z = " + this.Z_.ToString());
		}
	}

	/// This class has an instance of the
	/// EnclosedClass with the "get" type.
	public class EnclosingClass {

		/// Constructor
		public EnclosingClass() {
			this.EC_ = new EnclosedClass();
		}

		/// Returns the Enclosed Class
		private EnclosedClass EC_;
		public EnclosedClass EC {
			get { return this.EC_; }
		}
	}
}
