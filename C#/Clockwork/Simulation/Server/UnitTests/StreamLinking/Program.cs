using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

/// Success
public class Program {
	static void Main(string[] args) {

		ExternalStream es = new ExternalStream(Console.OpenStandardOutput());
		while (true) {
			es.Write(Console.ReadLine());
		}
	}
}

