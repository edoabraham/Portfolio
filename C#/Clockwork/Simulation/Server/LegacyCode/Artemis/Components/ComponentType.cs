/// ComponentType.cs - ComponentType Class Implementation
/// Written By Jesse Z. Zhong

using System;
using ArtemisUnity;
using System.Collections.Generic;

/// Define Type BigInteger
using BigInteger = System.Int64;

/// Artemis
namespace ArtemisUnity {

	/// Component Type
	public sealed class ComponentType {

		private static BigInteger NextBit_ = 1;
		private static int NextID_ = 0;

		private BigInteger Bit_;
		private int ID_;

		public ComponentType() {
			Init();
		}

		private void Init() {
			Bit_ = NextBit_;
			NextBit_ = NextBit_ << 1;
			ID_ = NextID_++;
		}

		public BigInteger Bit {
			get { return Bit_; }
		}

		public int ID {
			get { return ID_; }
		}
	}
}
