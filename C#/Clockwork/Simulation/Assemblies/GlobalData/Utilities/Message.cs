/// Message.cs - Message Class Used for Printing to Console
/// Written by Jesse Z. Zhong

using System;
using System.Text;

/// Utilities
namespace Utilities {

	/// Message Printing
	public static class Message {

		/// Time Stamp Formatting
		private const string TIMESTAMP_FORMAT = "yyyy/MM/dd mm:ss.ffff";

		/// Message Headers For Different Kinds of Text
		private const string INFO = "<Info> ";
		private const string SUCCESS = "<Success> ";
		private const string ERROR = "<Error> ";
		private const string FAIL = "<Failed> ";
		private const string WARNING = "<Warning> ";
		private const string SYSINFO = "<SysInfo> ";

		/// Colors of Different Kinds of Text
		private const Colors INFO_COLOR = Colors.White;
		private const Colors SUCCESS_COLOR = Colors.Green;
		private const Colors ERROR_COLOR = Colors.Red;
		private const Colors FAIL_COLOR = Colors.Red;
		private const Colors WARNING_COLOR = Colors.Yellow;
		private const Colors SYSINFO_COLOR = Colors.Cyan;
		private const Colors FILES_COLOR = Colors.White;
		private const Colors GENERAL_COLOR = Colors.Gray;

		/// Highlight Symbol
		private const string HIGHLIGHT_SYMBOL = "%lite";

		/// Colors
		private enum Colors {
			Black,
			White,
			Blue,
			Green,
			Cyan,
			Red,
			Magenta,
			Yellow,
			Gray
		}

		/// Main Function That Heads a Information Message and Prints with Highlighting
		public static void Info(string MessageString, params string[] HighLightedItems) {
			ColoredPrint(INFO, INFO_COLOR);
			ColoredPrint(GetTimeStamp + " ", Colors.White);
			HighlitePrint(MessageString, HighLightedItems);
		}

		/// Main Function That Heads a Success Message and Prints with Highlighting
		public static void Success(string MessageString, params string[] HighLightedItems) {
			ColoredPrint(SUCCESS, SUCCESS_COLOR);
			ColoredPrint(GetTimeStamp + " ", Colors.White);
			HighlitePrint(MessageString, HighLightedItems);
		}

		/// Main Function That Heads a Error Message and Prints with Highlighting
		public static void Error(string MessageString, params string[] HighLightedItems) {
			ColoredPrint(ERROR, ERROR_COLOR);
			ColoredPrint(GetTimeStamp + " ", Colors.White);
			HighlitePrint(MessageString, HighLightedItems);
		}

		/// Main Function That Heads a Failure Message and Prints with Highlighting
		public static void Failed(string MessageString, params string[] HighLightedItems) {
			ColoredPrint(FAIL, FAIL_COLOR);
			ColoredPrint(GetTimeStamp + " ", Colors.White);
			HighlitePrint(MessageString, HighLightedItems);
		}

		/// Main Function That Heads a Warning Message and Prints with Highlighting
		public static void Warning(string MessageString, params string[] HighLightedItems) {
			ColoredPrint(WARNING, WARNING_COLOR);
			ColoredPrint(GetTimeStamp + " ", Colors.White);
			HighlitePrint(MessageString, HighLightedItems);
		}

		/// Main Function That Heads a System Info Message and Prints with Highlighting
		public static void SysInfo(string MessageString, params string[] HighLightedItems) {
			ColoredPrint(SYSINFO, SYSINFO_COLOR);
			ColoredPrint(GetTimeStamp + " ", Colors.White);
			HighlitePrint(MessageString, HighLightedItems);
		}

		/// Splices and Prints Sections While Highlighting Files
		public static void HighlitePrint(string MessageString, params string[] HighlightedItems) {
			int ParamsIndex = 0;
			int StringIndex0 = 0;
			int StringIndex1 = 0;

			while ((StringIndex1 <= MessageString.Length) && StringIndex0 <= StringIndex1) {

				// Boolean That Checks if the File Symbol is Found
				bool SymbolFound = false;

				// Search For Any Instances Of The Symbol And Stores Position Into the Sub String's Index
				if (MessageString.IndexOf(HIGHLIGHT_SYMBOL, StringIndex0) != -1) {
					StringIndex1 = MessageString.IndexOf(HIGHLIGHT_SYMBOL, StringIndex0);
					SymbolFound = true;
				} else if (MessageString.Length > 0) {

					// If None Are Found, Pass the End of the File
					StringIndex1 = MessageString.Length;
				}

				// Prints Anything that Comes Before a Discovered 
				ColoredPrint(MessageString.Substring(StringIndex0, StringIndex1 - StringIndex0), GENERAL_COLOR);

				// Print Highlighted Param If It Exists
				if (HighlightedItems.Length > ParamsIndex && SymbolFound) ColoredPrint(HighlightedItems[ParamsIndex], FILES_COLOR);

				// Shift Past the Symbol
				StringIndex1 += HIGHLIGHT_SYMBOL.Length;
				StringIndex0 = StringIndex1;

				// Iterate ParameterIndex Up to Next Param
				ParamsIndex++;
			}

			// New Line
			Console.WriteLine("");
		}

		/// Helper Function that Prints String in a Specified Color 
		private static void ColoredPrint(string InputText, Colors SpecificColor) {

			// Find and Assign Corresponding Color
			switch (SpecificColor) {
				case Colors.Black:
					Console.ForegroundColor = ConsoleColor.Black;
					break;
				case Colors.White:
					Console.ForegroundColor = ConsoleColor.White;
					break;
				case Colors.Blue:
					Console.ForegroundColor = ConsoleColor.Blue;
					break;
				case Colors.Green:
					Console.ForegroundColor = ConsoleColor.Green;
					break;
				case Colors.Cyan:
					Console.ForegroundColor = ConsoleColor.Cyan;
					break;
				case Colors.Red:
					Console.ForegroundColor = ConsoleColor.Red;
					break;
				case Colors.Magenta:
					Console.ForegroundColor = ConsoleColor.Magenta;
					break;
				case Colors.Yellow:
					Console.ForegroundColor = ConsoleColor.Yellow;
					break;
				case Colors.Gray:
					Console.ForegroundColor = ConsoleColor.Gray;
					break;
				default:
					Console.ResetColor();
					break;
			}

			Console.Write(InputText);
			Console.ResetColor();
		}

		/// Returns Timestamp as a String
		private static string GetTimeStamp {
			get {
				return DateTime.Now.ToString(TIMESTAMP_FORMAT);
			}
		}

		/// Constructor
		static Message() {

		}
	}
}