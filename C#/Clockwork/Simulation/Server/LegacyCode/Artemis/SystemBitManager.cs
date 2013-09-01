/// SystemBitManager.cs - SystemBitManager Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Define Type BigInteger
using BigInteger = System.Int64;

/// Artemis
namespace ArtemisUnity {

	/// System Bit Manager
	internal static class SystemBitManager {

		private static int POS = 0;
		private static Dictionary<EntitySystem, BigInteger> SystemBits_ = new Dictionary<EntitySystem, BigInteger>();

		public static BigInteger GetBitFor(EntitySystem es) {
			BigInteger bit;
			bool hasBit = SystemBits_.TryGetValue(es, out bit);
			if (!hasBit) {

				bit = 1 << POS;

				POS++;
				SystemBits_.Add(es, bit);
			}

			return bit;
		}

	}
}
