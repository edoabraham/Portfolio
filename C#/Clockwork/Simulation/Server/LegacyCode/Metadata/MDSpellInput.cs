/// MDSpellInput.cs - MDSpellInput Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

using NetworkEvents;

/// Game Server
namespace NetworkEvents {

	/// Spell Input Information from the Player
	public class MDSpellInput : IMetaData<MDSpellInput> {

		/// Floating point bit length resolution
		private const int FloatResolution = 16;

		/// The Range for Floating Point Numbers
		private const float MaxFloatValue = 327.67f;
		private const float MinFloatValue = -MaxFloatValue;

		/// Number of Spell Flags
		private const int NUM_OF_SPELLS = 8;

		/// Constructor
		public MDSpellInput(Vector2 spellTarget, uint spellFlags) {
			SpellTarget_ = spellTarget;
			SpellFlags_ = spellFlags;
		}

		/// The Vector Location of a Spell the Player wants to cast
		private Vector2 SpellTarget_;
		public Vector2 SpellTarget {
			get { return SpellTarget_; }
			set { SpellTarget_ = value; }
		}

		/// Flag for the status of each Spell; 
		/// Is the Player casting any of them?
		private uint SpellFlags_;
		public uint SpellFlags {
			get { return SpellFlags_; }
			set { SpellFlags_ = value; }
		}

		/// Write a Client Input Net Event
		public NetEvent Write(NetEvent netEvent) {
			netEvent = WriteVector2(netEvent);
			netEvent.Data.WriteDynamicUInt(SpellFlags_, NUM_OF_SPELLS);
			return netEvent;
		}

		/// Reads a Client Input Net Event
		public MDSpellInput Read(NetEvent netEvent) {
			ReadVector2(netEvent);
			netEvent.Data.ReadDynamicUInt(out SpellFlags_, NUM_OF_SPELLS);
			return this;
		}

		#region Private
		/// Writes a Vector
		private NetEvent WriteVector2(NetEvent netEvent) {
			netEvent.Data.WriteCustomResolutionSingle(SpellTarget_.X,
				MinFloatValue, MaxFloatValue, FloatResolution);
			netEvent.Data.WriteCustomResolutionSingle(SpellTarget_.Y,
				MinFloatValue, MaxFloatValue, FloatResolution);
			return netEvent;
		}

		/// Reads a Vector
		private void ReadVector2(NetEvent netEvent) {
			netEvent.Data.ReadCustomResolutionSingle(out SpellTarget_.X, 
				MinFloatValue, MaxFloatValue, FloatResolution);
			netEvent.Data.ReadCustomResolutionSingle(out SpellTarget_.Y, 
				MinFloatValue, MaxFloatValue, FloatResolution);
		}
		#endregion
	}
}
