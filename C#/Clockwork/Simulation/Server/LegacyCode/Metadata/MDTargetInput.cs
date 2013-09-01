/// MDTargetInput.cs - TargetInput Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

/// Network Events
namespace NetworkEvents {

	/// Client to Server Player Input
	/// Sends the next location the player would
	/// like to go to in the form of a 2D Vector
	public class MDTargetInput : IMetaData<MDTargetInput> {

		/// Floating point bit length resolution
		private const int FloatResolution = 16;

		/// The Range for Floating Point Numbers
		private const float MaxFloatValue = 327.67f;
		private const float MinFloatValue = -MaxFloatValue;

		/// Constructor
		/// Pass the vector for the new location
		public MDTargetInput(Vector2 target) {
			TargetLocation_ = target;
		}

		/// The Location that the Player would
		/// like to go to next
		private Vector2 TargetLocation_;
		public Vector2 TargetLocation {
			set { TargetLocation_ = value; }
			get { return TargetLocation_; }
		}

		/// Writes the Target Location to a Net Event's Metadata
		public NetEvent Write(NetEvent netEvent) {
			netEvent.Data.WriteCustomResolutionSingle(TargetLocation_.X, 
				MinFloatValue, MaxFloatValue, FloatResolution);
			netEvent.Data.WriteCustomResolutionSingle(TargetLocation_.Y, 
				MinFloatValue, MaxFloatValue, FloatResolution);
			return netEvent;
		}

		/// Reads the Target Location to a Net Event's Metadata
		public MDTargetInput Read(NetEvent netEvent) {
			netEvent.Data.ReadCustomResolutionSingle(out TargetLocation_.X, 
				MinFloatValue, MaxFloatValue, FloatResolution);
			netEvent.Data.ReadCustomResolutionSingle(out TargetLocation_.Y,
				MinFloatValue, MaxFloatValue, FloatResolution);
			return this;
		}
	}
}
