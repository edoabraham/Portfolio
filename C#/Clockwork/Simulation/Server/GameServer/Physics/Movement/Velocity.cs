/// Velocity.cs - Velocity Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis.Interface;
using System.Collections.Generic;
using System.Xml.Serialization;
using Utilities;

/// Game Server
namespace GameServer {

	/// Velocity
	public class Velocity : IComponent {

		/// Constructor
		public Velocity() {
			this.Velocity_ = new Vector3(0.0f, 0.0f, 0.0f);
		}

		/// Init-Constructor; Vector3D Source
		public Velocity(Vector3 source) {
			this.Velocity_ = source;
		}

		/// Copy Constructor
		public Velocity(Velocity source) {
			this.Velocity_ = source.Value;
		}

		/// Gets the Direction Angle of Velocity
		/// On the XY Plane
		public float Direction {
			get {
				return (float)Math.Atan(Velocity_.X / Velocity_.Y);
			}
		}

		/// Velocity Vector
		private Vector3 Velocity_;
		public Vector3 Value {
			get { return Velocity_; }
			set { Velocity_ = value; }
		}

	}
}
