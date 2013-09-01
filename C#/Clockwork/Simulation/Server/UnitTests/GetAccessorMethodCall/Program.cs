/// Program entry point
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

/// Get Accessors Method Call Test
namespace GetAccessorMethodCall {

	/// Program main class
	public class Program {

		/// Main Method
		static void Main(string[] args) {

			// Instance of Enclosing Class
			EnclosingClass eic = new EnclosingClass();

			// Print first
			eic.EC.Print();

			// Attempt to assign values
			eic.EC.AssignValues(3, 4);

			// Print again
			eic.EC.Print();

			// Pause program
			Console.ReadLine();
		}
	}
}
