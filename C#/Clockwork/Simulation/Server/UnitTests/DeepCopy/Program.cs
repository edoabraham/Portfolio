/// Program.cs - Program Main Entry
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Deep Copy
namespace DeepCopy {
	
	/// Main Class
	public static class Program {

		/// Main Method
		static void Main(string[] args) {

			// Create byte list
			List<byte> byteArray = new List<byte>();
			for(byte i = 0; i < 6; i++)
				byteArray.Add(i);

			// Create copy class
			CopiedClass cc0 = new CopiedClass(12.5f, new HiddenObject(6, 9), byteArray);

			// Print the original
			cc0.Print();
			Console.WriteLine();

			// Create a copy and print
			CopiedClass cc1 = new CopiedClass(cc0);

			// Print the copy
			cc1.Print();
			Console.WriteLine("\n"); 

			// Change copy values
			cc1.Z = 98;
			cc1.HiddenObject = new HiddenObject(7, 18);
			for (int i = 0, j = cc1.ByteArray.Count; i < j; i++)
				cc1.ByteArray[i] += 3;

			// Print the original and copy
			cc0.Print();
			Console.WriteLine();
			cc1.Print();
			Console.WriteLine(); 

			// Pause system
			Console.ReadLine();
		}
	}
}
