/// Serializer.cs - Serializer Class Implementation.
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;
using System.IO;

/// Utilities
namespace Utilities {

	/// Class that includes methods that
	/// are in charge of serializing and
	/// deserializing files of different formats.
	public static class Serializer {

		/// Serializes object to XML
		public static void ToXML<T>(T o, string fileName) {
			XmlSerializer serializer = new XmlSerializer(typeof(T));
			using (TextWriter textWriter = new StreamWriter(fileName)) {
				serializer.Serialize(textWriter, o);
			}
		}

		/// Deserializes XML to object
		public static T FromXML<T>(string fileName) where T : new() {
			XmlSerializer deserializer = new XmlSerializer(typeof(T));
			T o = new T();
			try {
				using (TextReader textReader = new StreamReader(fileName)) {
					o = (T)deserializer.Deserialize(textReader);
				}
			} catch (Exception ex) {
				Message.Error(ex.Message);
			}
			return o;
		}
	}
}