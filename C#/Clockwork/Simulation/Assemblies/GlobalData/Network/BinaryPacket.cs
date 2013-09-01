/// BinaryPacket.cs - BinaryPacket Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Network Events
namespace NetworkEvents {

	/// Binary Packet
	public class BinaryPacket {

		/// Bit Length of an Event ID
		const int EVENT_ID_LENGTH = 6;

		/// Constructor
		public BinaryPacket() {
			Buffer_ = new List<byte>();
		}

		private List<byte> Buffer_;
		private int BitIndex_ = 0;
		private int MaxBitIndex_ = 0;

		/// Sets the Buffer with 
		public BinaryPacket(byte[] buffer) {
			this.Buffer_ = new List<byte>(buffer);
		}

		/// Gets or Sets the Bit Index
		public int BitIndex {
			get { return BitIndex_; }
			set {
				if ((value < 0) || ((value + 7) / 8) > Buffer_.Count)
					throw new ArgumentOutOfRangeException("Unable to set the bit index outside of the buffer size.");
				BitIndex_ = value;
			}
		}

		/// Gets or Sets the Max Bit Index
		public int MaxBitIndex {
			get { return MaxBitIndex_; }
			set {
				if (value < 0 || (value + 7) / 8 > Buffer_.Count) 
					throw new ArgumentOutOfRangeException("Unable to set the bit index outside of the buffer size.");
				BitIndex_ = value;
			}
		}

		/// Get the Header Size for the Length in Bytes
		/// The Size is Default to Unsigned Integer (32 Bit)
		public int HeaderSize {
			get { return sizeof(uint); }
		}

		/// Gets the Header Size for the Length in Bits
		/// The Size is Default to Unsigned Integer (32 Bit)
		public int HeaderSizeInBits {
			get { return (sizeof(uint) * 8); }
		}

		/// Returns the Buffer Length in Bytes
		public int Length {
			get { return Buffer_.Count; }
		}

		/// Returns the Buffer as an Array of Bytes
		public byte[] Buffer {
			get { return Buffer_.ToArray(); }
		}

		/// Returns a String of 0s and 1s Representing the Bits
		/// in the Buffer; Good for Debugging; Places a Space
		/// Between Nibbles and Two Spaces Between Bytes
		public string Trace() {
			string s = string.Empty;
			for (int copyBits = 0; copyBits < (Buffer_.Count * 8); copyBits++) {
				s += ((Buffer_[copyBits / 8] >> (7 - (copyBits % 8))) & 0x1) == 0 ? "0" : "1";
				if (((copyBits + 1) % 4) == 0 && copyBits != 0) {
					s += " ";
					if (((copyBits + 1) % 8) == 0)
						s += " ";
				}
			}
			return s;
		}

		/// Expands the Buffer Size Appending Bytes So 
		/// that the Functions don't Overflow; Records 
		/// the Furthest Write in the MaxBitIndex
		private void ExpandBuffer(int bits) {
			if (bits < 1) 
				throw new ArgumentOutOfRangeException("bits must be greater than 0");
			while (((BitIndex_ + bits + 7) / 8) > Buffer_.Count) 
				Buffer_.Add(new byte());
			MaxBitIndex_ = Math.Max(MaxBitIndex_, BitIndex_ + bits);
		}

		/// Rounds the BitIndex Up to a Byte
		public void RoundUpToByte() {
			BitIndex_ = (BitIndex_ + 7) / 8 * 8;
		}

		/// Reads the Length Stored in the Header
		/// BeginPacket and EndPacket should have been Called
		/// to Make this; Note: It's Expected 4 Bytes are in 
		/// the Buffer Before this is Called
		public void ReadLength() {
			int oldBitIndex = BitIndex_;
			BitIndex_ = 0;
			MaxBitIndex_ = 0;
			uint length;
			if (ReadUInt32(out length))
				MaxBitIndex_ = (int)length;
			BitIndex_ = oldBitIndex;
		}

		/// 
		/// WRITE METHODS
		/// 

		/// Writes a Begin Packet Header of 32 Bits.
		public void BeginPacket() {
			WriteUInt32(0);
		}

		/// Writes the MaxBits of the Packet to the 
		/// Beginning of the Packet
		public void EndPacket() {
			int oldBitIndex = BitIndex_;
			BitIndex_ = 0;
			WriteUInt32((uint)MaxBitIndex_);
			BitIndex_ = oldBitIndex;
		}

		/// Overwrites a byte at a certain index
		public void Overwrite(uint value, int bits, int index) {
			
			// Save the original bit index
			int bitIndex = BitIndex_;

			// Set new index
			BitIndex_ = index;

			// Start writing
			WriteDynamicUInt(value, bits);

			// Change the bit index back
			BitIndex_ = bitIndex;
		}

		/// Writes an Event ID
		public void WriteEventID(uint value) {
			WriteDynamicUInt(value, EVENT_ID_LENGTH);
		}

		/// Writes a Single Bit Either 0 or 1 into the Buffer
		public void WriteBool(bool value) {
			// Push Back 1 Bit
			ExpandBuffer(1);
			if (value) Buffer_[BitIndex_ / 8] |= (byte)(1 << (7 - BitIndex_ % 8));
			BitIndex_++;
		}

		/// Writes an 8 Bit Unsigned Byte into the Buffer
		public void WriteByte(byte value) {
			// Push Back a Whole Byte
			ExpandBuffer(8);
			int offset = BitIndex_ % 8;
			Buffer_[BitIndex_ / 8] |= (byte)(value << (8 - offset));
			if (offset != 0)
				Buffer_[(BitIndex_ / 8) + 1] |= (byte)(value << (8 - offset));
			BitIndex_ += 8;
		}

		/// Writes an 8 Bit Signed Byte into the Buffer
		public void WriteSByte(sbyte value) {
			ExpandBuffer(8);
			int offset = BitIndex_ % 8;
			Buffer_[(BitIndex_ / 8)] |= (byte) (value >> offset);
			if(offset != 0)
				Buffer_[(BitIndex_ / 8) + 1] |= (byte) (value << (8 - offset));
			BitIndex_ += 8;
		}

		/// Writes a 16 Bit Unsigned Short into the Buffer
		public void WriteUint16(ushort value) {
			ExpandBuffer(16);
			int offset = BitIndex_ % 8;
			Buffer_[BitIndex_ / 8] |= (byte) (value >> (8 + offset));
			Buffer_[(BitIndex_ / 8) + 1] |= (byte)(value >> offset);
			if (offset != 0)
				Buffer_[(BitIndex_ / 8) + 2] |= (byte)(value << (8 - offset));
			BitIndex_ += 16;
		}

		/// Writes a 32 Bit Unsigned Integer into the Buffer
		public void WriteUInt32(uint value) {
			ExpandBuffer(32);
			int offset = BitIndex_ % 8;
			Buffer_[BitIndex_ / 8] |= (byte) (value >> (24 + offset));
			Buffer_[(BitIndex_ / 8) + 1] |= (byte) (value >> (16 + offset));
			Buffer_[(BitIndex_ / 8) + 2] |= (byte) (value >> (8 + offset));
			Buffer_[(BitIndex_ / 8) + 3] |= (byte) (value >> offset);
			if (offset != 0)
				Buffer_[(BitIndex_ / 8) + 4] |= (byte) (value << (8 - offset));
			BitIndex_ += 32;
		}

		/// Writes a 32 Bit Signed Integer into the Buffer
		public void WriteInt32(int value) {
			ExpandBuffer(32);
			int offset = BitIndex_ % 8;
			Buffer_[BitIndex_ / 8] |= (byte) (value >> (24 + offset));
			Buffer_[(BitIndex_ / 8) + 1] |= (byte) (value >> (16 + offset));
			Buffer_[(BitIndex_ / 8) + 2] |= (byte) (value >> (8 + offset));
			Buffer_[(BitIndex_ / 8) + 3] |= (byte) (value >> offset);
			if (offset != 0)
				Buffer_[(BitIndex_ / 8) + 4] |= (byte) (value << (8 - offset));
			BitIndex_ += 32;
		}

		/// Writes an N-Bit Unsigned Integer into the Buffer
		public void WriteUInt(uint value, int bits) {
			if ((bits < 1) || (bits > 32))
				throw new ArgumentOutOfRangeException("bits must be in the range (0, 32]");
			if ((bits != 32) && (value > ((0x1 << bits) - 1)))
				throw new ArgumentOutOfRangeException("value does not fit into " + bits.ToString() + " bits.");

			ExpandBuffer(bits);
			value <<= (32 - bits);
			int offset = BitIndex_ % 8;
			Buffer_[BitIndex_ / 8] |= (byte) (value >> (24 + offset));
			if ((offset + bits) > 8) {
				Buffer_[(BitIndex_ / 8) + 1] |= (byte) (value >> (16 + offset));
				if ((offset + bits) > 16) {
					Buffer_[(BitIndex_ / 8) + 2] |= (byte) (value >> (8 + offset));
					if ((offset + bits) > 24) {
						Buffer_[(BitIndex_ / 8) + 3] |= (byte) (value >> offset);
						if ((offset + bits) > 32) {
							Buffer_[(BitIndex_ / 8) + 4] |= (byte) (value << (8 - offset));
						}
					}
				}
			}
			BitIndex_ += bits;

		}

		/// Writes an N-Bit Signed Integer into the Buffer
		public void WriteInt(int value, int bits) {
			if ((bits < 1) || (bits > 32)) 
				throw new ArgumentOutOfRangeException("bits must be in the range (0, 32]");
			if (((bits != 32) && (value < -(0x1 << (bits - 1))) || (value >= (0x1 << (bits - 1))))) 
				throw new ArgumentOutOfRangeException("Value does not fit into " + bits.ToString() + " bits");

			ExpandBuffer(bits);
			value <<= (32 - bits);
			uint uvalue = (uint)value;

			int offset = BitIndex_ % 8;
			Buffer_[BitIndex_ / 8] |= (byte) (uvalue >> (24 + offset));
			if ((offset + bits) > 8) {
				Buffer_[(BitIndex_ / 8) + 1] |= (byte) (uvalue >> (16 + offset));
				if ((offset + bits) > 16) {
					Buffer_[(BitIndex_ / 8) + 2] |= (byte) (uvalue >> (8 + offset));
					if ((offset + bits) > 24) {
						Buffer_[(BitIndex_ / 8) + 3] |= (byte) (uvalue >> offset);
						if ((offset + bits) > 32) {
							Buffer_[(BitIndex_ / 8) + 4] |= (byte) (uvalue << (8 - offset));
						}
					}
				}
			}
			BitIndex_ += bits;
		}

		/// Writes a 32 Bit Single into the Buffer
		public void WriteSingle(float value) {
			WriteUInt32(BitConverter.ToUInt32(BitConverter.GetBytes(value), 0));
		}

		/// Writes a 64 Bit Double into the Buffer
		public void WriteDouble(double value) {
			byte[] bytes = BitConverter.GetBytes(value);
			WriteUInt32(BitConverter.ToUInt32(bytes, 0));
			WriteUInt32(BitConverter.ToUInt32(bytes, 4));
		}

		/// Writes an Integer Using a Variable Width Encoding
		/// of Bits; Choose a Bit Value that Represents the 
		/// Number of Bits to Hold the Average Value
		public void WriteDynamicUInt(uint value, int bits) {
			if ((bits < 1) || (bits > 32)) 
				throw new ArgumentOutOfRangeException("bits must be in the range (0, 32]");
			int shift = bits;
			// Stop when our value can fit inside
			for (; (shift < 32) && (value >= (0x1 << shift)); shift += bits)
				WriteBool(true); // Write a 1 for a continuation bit signifying one more interval is needed
			if (shift < 32)
				WriteBool(false);    // Write a 0 for a continuation bit signifying the end
			WriteUInt(value, shift >= 32 ? 32 : shift);
		}

		/// Default 4 Bits
		public void WriteDynamicUInt(uint value) {
			WriteDynamicUInt(value, 4);
		}

		/// Creates a Value for the Ratio: value / (2 ^ bitResolution)
		/// in Relationship to value / (max - min); This Allows
		/// a Floating Point to have a Resolution
		public void WriteCustomResolutionSingle(float value, float min, float max, int bitResolution) {
			if ((bitResolution < 1) || (bitResolution > 31)) 
				throw new ArgumentOutOfRangeException("bitResolution must be in the range (0, 32)");
			if (min > max) 
				throw new ArgumentOutOfRangeException("min argument must be less than the max argument");
			if ((value < min) || (value > max)) 
				throw new ArgumentOutOfRangeException("The value must be on the interval [min, max]");

			uint uValue;
			if ((min < 0) && (max > 0))
				uValue = value == 0 ? 0 : (uint) Math.Round((value - min) 
					/ (max - min) * (float) ((0x1 << bitResolution) - 2)) + 1;
			else 
				uValue = (uint)Math.Round((value - min) / (max - min) * (float)((0x1 << bitResolution) - 1));

			WriteUInt(uValue, bitResolution);
		}

		/// Creates a Value for the Ratio: value / (2 ^ bitResolution - 1)
		/// in Relationship to value / (max - min); This Allows
		/// a Floating Point to have a Resolution
		public void WriteCustomResolutionDouble(double value, double min, float max, int bitResolution) {
			if ((bitResolution < 1) || (bitResolution > 31)) 
				throw new ArgumentOutOfRangeException("bitResolution must be in the range (0, 32)");
			if (min > max) 
				throw new ArgumentOutOfRangeException("min argument must be less than the max argument");
			if ((value < min) || (value > max)) 
				throw new ArgumentOutOfRangeException("The value must be on the interval [min, max]");

			uint uValue;
			if ((min < 0) && (max > 0))
				uValue = value == 0 ? 0 : (uint)Math.Round((value - min) 
					/ (max - min) * (double)((0x1 << bitResolution) - 2)) + 1;
			else
				uValue = (uint)Math.Round((value - min) 
					/ (max - min) * (double)((0x1 << bitResolution) - 1));
			WriteUInt(uValue, bitResolution);
		}

		/// Writes the Length of the String Using WriteDynamicUnsignedInteger
		/// and then Writes a Boolean, True for Unicode, False for ASCII;
		/// ASCII Uses a Compression Step Using Either 6 or 7 Bits Per Character
		public void WriteString(string value, int bits) {
			if ((bits < 1) || (bits > 31)) 
				throw new ArgumentOutOfRangeException("bits must be in the range (0, 32)");
			uint size = (uint)value.Length;
			WriteDynamicUInt(size, bits);
			for (int i = 0; i < size; i++) {
				WriteDynamicUInt((uint)value[i], bits);
			}
		}

		/// Defaults to 4 arrayBits
		public void WriteString(string value) {
			WriteString(value, 4);
		}

		/// Appends a Binary Packet to the Buffer
		public void WriteBinaryPacket(BinaryPacket value) {
			int oldBitIndex = value.BitIndex_;
			value.BitIndex_ = 0;
			int valueMaxBitIndex = value.MaxBitIndex;
			WriteDynamicUInt((uint)valueMaxBitIndex);
			for (uint copyBytes = 0; copyBytes < valueMaxBitIndex / 8; ++copyBytes) {
				byte valueByte;
				value.ReadByte(out valueByte);
				WriteByte(valueByte);
			}
			for (uint copyBits = 0; copyBits < valueMaxBitIndex % 8; ++copyBits) {
				bool valueBit;
				value.ReadBool(out valueBit);
				WriteBool(valueBit);
			}
			BitIndex_ += valueMaxBitIndex;
			value.BitIndex_ = oldBitIndex;
		}

		/// 
		/// READ METHODS
		/// 

		/// Reads an Event ID
		public bool ReadEventID(out uint value) {
			return ReadDynamicUInt(out value, EVENT_ID_LENGTH);
		}

		/// Read One Bit from the Buffer
		public bool ReadBool(out bool value) {
			value = false;
			if ((BitIndex_ + 1 + 7) / 8 > Buffer_.Count)
				return false;
			value = ((Buffer_[BitIndex_ / 8] >> (7 - BitIndex_ % 8)) & 0x1) == 1;
			BitIndex_++;
			return true;
		}

		/// Reads an 8 Bit Unsigned Byte from the Buffer
		public bool ReadByte(out byte value) {
			value = 0;
			if ((BitIndex_ + 8 + 7) / 8 > Buffer_.Count)
				return false;
			int offset = BitIndex_ % 8;
			value |= (byte) (Buffer_[BitIndex_ / 8] << offset);
			if (offset != 0)
				value |= (byte) (Buffer_[BitIndex_ / 8 + 1] >> 8 - offset);
			BitIndex_ += 8;
			return true;
		}

		/// Reads an 8 Bit Signed Byte from the Buffer
		public bool ReadSByte(out sbyte value) {
			value = 0;
			if ((BitIndex_ + 8 + 7) / 8 > Buffer_.Count)
				return false;
			int offset = BitIndex_ % 8;
			value |= (sbyte) (Buffer_[BitIndex_ / 8] << offset);
			if (offset != 0) 
				value |= (sbyte) (Buffer_[BitIndex_ / 8 + 1] >> 8 - offset);
			BitIndex_ += 8;
			return true;
		}

		/// Reads a 16 Bit Unsigned Short from the Buffer
		public bool ReadUInt16(out ushort value) {
			value = 0;
			if ((BitIndex_ + 16 + 7) / 8 > Buffer_.Count)
				return false;
			int offset = BitIndex_ % 8;
			value |= (ushort) (Buffer_[BitIndex_ / 8] << 8 + offset);
			value |= (ushort) (Buffer_[BitIndex_ / 8 + 1] << offset);
			if (offset != 0)
				value |= (ushort) (Buffer_[BitIndex_ / 8 + 2] >> 8 - offset);
			BitIndex_ += 16;
			return true;
		}

		/// Reads a 16 Bit Signed Short from the Buffer
		public bool ReadInt16(out short value) {
			value = 0;
			if ((BitIndex_ + 16 + 7) / 8 > Buffer_.Count) {
				return false;
			}
			int offset = BitIndex_ % 8;
			value |= (short)(Buffer_[BitIndex_ / 8] << 8 + offset);
			value |= (short)(Buffer_[BitIndex_ / 8 + 1] << offset);
			if (offset != 0) {
				value |= (short)(Buffer_[BitIndex_ / 8 + 2] >> 8 - offset);
			}
			BitIndex_ += 16;
			return true;
		}

		/// Reads a 32 Bit Unsigned Integer from the Buffer
		public bool ReadUInt32(out uint value) {
			value = 0;
			if ((BitIndex_ + 32 + 7) / 8 > Buffer_.Count) {
				return false;
			}
			int offset = BitIndex_ % 8;
			value |= (uint)(Buffer_[BitIndex_ / 8] << 24 + offset);
			value |= (uint)(Buffer_[(BitIndex_ / 8) + 1] << (16 + offset));
			value |= (uint)(Buffer_[(BitIndex_ / 8) + 2] << (8 + offset));
			value |= (uint)(Buffer_[(BitIndex_ / 8) + 3] << offset);
			if (offset != 0) {
				value |= (uint)(Buffer_[(BitIndex_ / 8) + 4] >> (8 - offset));
			}
			BitIndex_ += 32;
			return true;
		}

		/// Reads a 32 Bit Signed Integer from the Buffer
		public bool ReadInt32(out int value) {
			value = 0;
			if ((BitIndex_ + 32 + 7) / 8 > Buffer_.Count) {
				return false;
			}
			int offset = BitIndex_ % 8;
			value |= (int)(Buffer_[BitIndex_ / 8] << 24 + offset);
			value |= (int)(Buffer_[(BitIndex_ / 8) + 1] << (16 + offset));
			value |= (int)(Buffer_[(BitIndex_ / 8) + 2] << (8 + offset));
			value |= (int)(Buffer_[(BitIndex_ / 8) + 3] << offset);
			if (offset != 0) {
				value |= (int)(Buffer_[(BitIndex_ / 8) + 4] >> (8 - offset));
			}
			BitIndex_ += 32;
			return true;
		}

		/// Reads an N-Bit Custom Unsigned Integer from the Buffer
		public bool ReadUInt(out uint value, int bits) {
			if ((bits < 1) || (bits > 32)) 
				throw new ArgumentOutOfRangeException("bits must be in the range (0, 32]");

			value = 0;
			if (((BitIndex_ + bits + 7) / 8) > Buffer_.Count) {
				return false;
			}
			int offset = BitIndex_ % 8;
			value = (uint) Buffer_[BitIndex_ / 8] << (24 + offset);
			if ((offset + bits) > 8) {
				value |= (uint) Buffer_[(BitIndex_ / 8) + 1] << (16 + offset);
				if ((offset + bits) > 16) {
					value |= (uint) Buffer_[(BitIndex_ / 8) + 2] << (8 + offset);
					if ((offset + bits) > 24) {
						value |= (uint) Buffer_[(BitIndex_ / 8) + 3] << offset;
						if ((offset + bits) > 32) {
							value |= (uint) Buffer_[(BitIndex_ / 8) + 4] >> (8 - offset);
						}
					}
				}
			}
			value >>= (32 - bits);
			BitIndex_ += bits;
			return true;
		}

		/// Reads an N-Bit Custom Signed Integer from the Buffer
		public bool ReadInt(out int value, int bits) {
			if ((bits < 1) || (bits > 32)) 
				throw new ArgumentOutOfRangeException("bits must be in the range (0, 32]");

			value = 0;
			if (((BitIndex_ + bits + 7) / 8) > Buffer_.Count) {
				return false;
			}
			int offset = BitIndex_ % 8;
			value = Buffer_[BitIndex_ / 8] << 24 + offset;
			if ((offset + bits) > 8) {
				value |= Buffer_[(BitIndex_ / 8) + 1] << (16 + offset);
				if ((offset + bits) > 16) {
					value |= Buffer_[(BitIndex_ / 8) + 2] << (8 + offset);
					if ((offset + bits) > 24) {
						value |= Buffer_[(BitIndex_ / 8) + 3] << offset;
						if ((offset + bits) > 32) {
							value |= Buffer_[(BitIndex_ / 8) + 4] >> (8 - offset);
						}
					}
				}
			}
			value >>= (32 - bits);
			BitIndex_ += bits;
			return true;
		}

		/// Reads a 64 Bit Double from the Buffer
		public bool ReadDouble(out double value) {
			value = 0;
			if ((BitIndex_ + 64 + 7) / 8 > Buffer_.Count) {
				return false;
			}
			byte[] bytes = new byte[8];
			uint uValue1;
			if (!ReadUInt32(out uValue1)) return false;
			byte[] first4bytes = BitConverter.GetBytes(uValue1);
			uint uValue2;
			if (!ReadUInt32(out uValue2)) return false;
			byte[] last4bytes = BitConverter.GetBytes(uValue2);
			for (uint copyBytes = 0; copyBytes < 4; ++copyBytes) {
				bytes[copyBytes] = first4bytes[copyBytes];
			}
			for (uint copyBytes = 4; copyBytes < 8; ++copyBytes) {
				bytes[copyBytes] = last4bytes[copyBytes - 4];
			}
			value = BitConverter.ToDouble(bytes, 0);
			return true;
		}

		/// Reads a Dynamic Unsigned Integer
		public bool ReadDynamicUInt(out uint value, int bits) {
			if (bits < 1 || bits > 32) 
				throw new ArgumentOutOfRangeException("bits must be in the range (0, 32]");
			value = 0;
			int valueBitCount = bits;
			bool continuationBitValue = true;
			do {
				if (!ReadBool(out continuationBitValue)) return false;
				if (continuationBitValue) valueBitCount += bits;
			}
			while (continuationBitValue && valueBitCount < 32);
			return ReadUInt(out value, valueBitCount >= 32 ? 32 : valueBitCount);
		}

		/// Default 4 Bits
		public bool ReadDynamicUInt(out uint value) {
			return ReadDynamicUInt(out value, 4);
		}

		/// Reads a Dynamic Unsigned Integer
		public bool ReadDynamicInt(out int value, int bits) {
			if ((bits < 1) || (bits > 32)) 
				throw new ArgumentOutOfRangeException("bits must be in the range (0, 32]");
			value = 0;
			int valueBitCount = bits;
			bool continuationBitValue = true;
			do {
				if (!ReadBool(out continuationBitValue)) return false;
				if (continuationBitValue) valueBitCount += bits;
			}
			while (continuationBitValue && valueBitCount < 32);
			return ReadInt(out value, valueBitCount >= 32 ? 32 : valueBitCount);
		}

		/// Default 4 Bits
		public bool ReadDynamicSignedInteger(out int value) {
			return ReadDynamicInt(out value, 4);
		}

		/// Reads a Custom Resolution Single
		public bool ReadCustomResolutionSingle(out float value, float min, float max, int bitResolution) {
			if ((bitResolution < 1) || (bitResolution > 31)) 
				throw new ArgumentOutOfRangeException("bitResolution must be in the range (0, 32)");
			if (min > max) throw new ArgumentOutOfRangeException("min argument must be less than the max argument");
			value = 0;
			uint uValue;
			if (!ReadUInt(out uValue, bitResolution)) return false;
			if (min < 0 && max > 0) {
				value = uValue == 0 ? 0 : (uValue - 1) / (float)((0x1 << bitResolution) - 2) * (max - min) + min;
			} else {
				value = uValue / (float)((0x1 << bitResolution) - 1) * (max - min) + min;
			}
			return true;
		}

		/// Reads a Custom Resolution Double
		public bool ReadCustomResolutionDouble(out double value, double min, double max, int bitResolution) {
			if ((bitResolution < 1) || (bitResolution > 31)) 
				throw new ArgumentOutOfRangeException("bitResolution must be in the range (0, 32)");
			if (min > max) 
				throw new ArgumentOutOfRangeException("min argument must be less than the max argument");
			value = 0;
			uint uValue;
			if (!ReadUInt(out uValue, bitResolution)) return false;
			if (min < 0 && max > 0) {
				value = uValue == 0 ? 0 : (uValue - 1) / (double)((0x1 << bitResolution) - 2) * (max - min) + min;
			} else {
				value = uValue / (double)((0x1 << bitResolution) - 1) * (max - min) + min;
			}
			return true;
		}

		/// Reads a String
		public bool ReadString(out string value, int bits) {
			if (bits < 1 || bits > 31) 
				throw new ArgumentOutOfRangeException("bits must be in the range (0, 32)");
			value = string.Empty;
			uint size;
			if (!ReadDynamicUInt(out size, bits)) return false;
			for (int i = 0; i < size; i++) {
				uint symbol = 0;
				if(!ReadDynamicUInt(out symbol, bits))
					return false;
				value += (char)symbol;
			}
			return true;
		}

		/// Defaults 4 Bits
		public bool ReadString(out string value) {
			return ReadString(out value, 4);
		}

		/// Reads a Binary Packet that 
		/// has been Written to the Buffer
		public bool ReadBinaryPacket(out BinaryPacket value) {
			value = new BinaryPacket();
			uint valueMaxBitIndex;
			if (!ReadDynamicUInt(out valueMaxBitIndex)) return false;
			for (uint copyBytes = 0; copyBytes < valueMaxBitIndex / 8; ++copyBytes) {
				byte valueByte;
				if (!ReadByte(out valueByte)) return false;
				value.WriteByte(valueByte);
			}
			for (uint copyBits = 0; copyBits < valueMaxBitIndex % 8; ++copyBits) {
				bool valueBit;
				if (!ReadBool(out valueBit)) return false;
				value.WriteBool(valueBit);
			}
			BitIndex_ += (int)valueMaxBitIndex;
			value.BitIndex_ = 0;
			return true;
		}
	}
}
