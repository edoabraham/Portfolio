/// ComponentTypeManager.cs - ComponentTypeManager Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Define Type BigInteger
using BigInteger = System.Int64;

/// Artemis
namespace ArtemisUnity {

	/// Static Class with Methods 
	/// for Managing Component Types
	public static class ComponentTypeManager {

		/// Dictionary of All Component Types
		private static Dictionary<Type, ComponentType> ComponentTypes_ = new Dictionary<Type, ComponentType>();

		/// Return the Component Type of a Component
		public static ComponentType GetTypeFor<T>() where T : ArtemisComponent {

			// Declare Intermediate Type
			ComponentType type = null;
			Type readType = typeof(T);

			// If the Component Type Does Not Already Exist in the 
			// Dictionary, Add the Type as a New Entry
			if (!ComponentTypes_.TryGetValue(readType, out type)) {
				type = new ComponentType();
				ComponentTypes_.Add(readType, type);
			}

			// Return the Type
			return type;
		}

		/// Tests if a Component Type is in Fact 
		/// an Actual Type in the System; If Not, then Add the Type
		public static ComponentType GetTypeFor(Type componentType) {

			// Assertion Check for Null Reference
			System.Diagnostics.Debug.Assert(componentType != null);

			// Declare Intermediate Type
			ComponentType type = null;

			// If the Component Type Does Not Already Exist in the 
			// Dictionary, Add the Type as a New Entry
			if (!ComponentTypes_.TryGetValue(componentType, out type)) {
				type = new ComponentType();
				ComponentTypes_.Add(componentType, type);
			}

			// Return the Type
			return type;
		}

		/// Return the Bit Value of a Component
		public static BigInteger GetBit<T>() where T : ArtemisComponent {
			return GetTypeFor<T>().Bit;
		}

		/// Return the ID of a Component
		public static int GetID<T>() where T : ArtemisComponent {
			return GetTypeFor<T>().ID;
		}
	}
}
