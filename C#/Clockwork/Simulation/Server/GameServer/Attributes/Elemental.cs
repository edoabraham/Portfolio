/// Elemental.cs - Elemental Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis.Interface;
using System.Collections.Generic;
using System.Xml.Serialization;
using System.IO;

/// Game Server
namespace GameServer {

	/// Game Entity/Object Type Data
	/// Dictates the Behavior of Elements
	/// in the Game
	public class Elemental : IComponent {

		/// Default Value for Unspecified Numbers
		const float DEFAULT_VALUE = 1.0f;

		/// Decimal Place Adjuster for Inputted Numbers
		const float DECIMAL_ADJUSTER = 100.0f;

		/// Token for Dividing Values in Stream
		const char TOKEN = ',';

		/// String of Acceptable Characters in Stream
		const String VALID_CHARACTERS = "0123456789,-";

		/// Constructor
		public Elemental(EElements element = EElements.Neutral) {
			this.Element_ = element;
		}

		/// Copy Constructor
		public Elemental(Elemental source) {
			this.Element_ = source.Element;
		}

		/// Default Constructor (for Serialization)
		private Elemental() {
			this.Element_ = EElements.Neutral;
		}

		/// Returns the Value From Elemental Table
		/// of this Instance and the Target
		public float GetResult(EElements target) {
			return ElementalTable_[(int)this.Element][(int)target];
		}

		/// The Element Value of this Component
		private EElements Element_;
		public EElements Element {
			get { return this.Element_; }
			set { this.Element_ = value; }
		}

		/// [Static] Static Constructor
		static Elemental() {

			// Initialize Table
			ElementalTable_ = new List<List<float>>();

			// Initialize, Allocate, and Store Values in a Temp
			List<float> temp = new List<float>(NumOfElements_);
			for (int i = 0; i < NumOfElements_; i++)
				temp[i] = DEFAULT_VALUE;

			// Expand the Table with Temp
			for (int i = 0; i < NumOfElements_; i++)
				ElementalTable_.Add(temp);
		}

		/// Returns the Value From Elemental Table
		/// Between Two Matched Up Elements
		public static float GetResult(EElements source, EElements target) {
			return ElementalTable_[(int)source][(int)target];
		}

		/// [Static] Reads, Parses, and Stores All Values from
		/// Elemental Table File into the Elemental Table
		static bool ReadInDataTable(String fileName) {

			// Start File Read Stream
			StreamReader reader = new StreamReader(fileName);

			try {
				// String for Storing Lines of the File Stream
				String line;

				// Array of Whitespace Characters
				char[] whiteSpaces = { ' ', '\t' };

				// Vertical Index
				int i = 0;

				// Parse Each Available Line
				while ((line = reader.ReadLine()) != null) {

					// Remove White Spaces from Line
					line = line.Trim(whiteSpaces);

					// Check for Comments; Skip Line if They're Found
					if (!((line.Length >= 2) && (line[0] == '/' && line[1] == '/'))) {

						// Split the Line Up with the TOKEN
						String[] valuesStr = line.Split(TOKEN);
						int valuesStrSize = valuesStr.Length;

						// Attempt to Store Values from File
						for (int j = 0; (i < NumOfElements_) && (j < NumOfElements_); j++) {

							// If Index Value Exists, Store the Value; Otherwise Use Default
							if (j < valuesStrSize) ElementalTable_[i][j] = float.Parse(valuesStr[j]) / DECIMAL_ADJUSTER;
							else ElementalTable_[i][j] = DEFAULT_VALUE;
						}

						// Iterate Up Vertical Index
						i++;
					}
				}

			} catch (Exception e) {

				// Print Exception
				Console.WriteLine("File " + fileName + " could not be read");
				Console.WriteLine(e.Message);

			} finally {

				// Close File
				reader.Close();
			}

			return true;
		}

		/// [Static] Stores the Number of Available Elements
		private static int NumOfElements_;
		static void storeNumOfElements() {
			NumOfElements_ = Enum.GetValues(typeof(EElements)).Length;
		}
		public static int NumOfElements {
			get { return NumOfElements_; }
		}

		/// [Static] Holds the Values of Each Element
		/// Being Pitted Against Another Element
		private static List<List<float>> ElementalTable_;
	}

	/// Enumeration of Possible Elements
	public enum EElements : int {
		Neutral = 0,
		Fire,
		Water,
		Wind,
		Earth,
		Wood
	}

}
