/// Controller.cs - Controller Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis.Interface;
using System.Collections.Generic;
using Utilities;

/// Game Server
namespace GameServer {

	/// Controller
	/// General character controller
	/// Used for controlling a character's movement
	/// and actions, as well as other states
	public class Controller : IComponent {

		/// ID pool for controllers to
		/// select game id's from
		protected static byte IDPool = 0;

		/// Constructor
		public Controller() {
			this.IsMoving_ = false;
			this.ID_ = IDPool++;
			this.TargetLocation = Vector2.Zero;
		}

		private byte ID_;
		public byte ID {
			get { return this.ID_; }
		}

		/// Desired destination of an entity
		private Vector2 TargetLocation_;
		public Vector2 TargetLocation {
			set { this.TargetLocation_ = value; }
			get { return this.TargetLocation_; }
		}

		/// Movement Flag
		private bool IsMoving_;
		public bool IsMoving {
			set { this.IsMoving_ = value; }
			get { return this.IsMoving_; }
		}
	}
}
