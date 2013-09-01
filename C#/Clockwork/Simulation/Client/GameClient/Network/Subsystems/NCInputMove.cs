/// NCInputMove.cs - NCInputMove class implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using System.Linq;
using System.Collections.Generic;

using Artemis;
using Artemis.Utils;
using Artemis.System;
using NetworkEvents;
using Utilities;
#endregion

/// Game Client
namespace GameClient {

	/// Input Move System
	/// This system is in charge of sending any
	/// requested player movement to the server.
	public sealed class NCInputMove : 
		ClientProcessingSystem {

		/// Packet Structure (Out Only)
		/// 0 Target Position X
		/// 1 Target Position Y
		/// 2 Running Flag

		#region Data Type Settings
		/// Floating point bit length resolution
		private const int FloatResolution = GlobalData.FloatResolution;

		/// The Range for Floating Point Numbers
		private const float MaxFloatValue = GlobalData.MaxFloatValue;
		private const float MinFloatValue = GlobalData.MinFloatValue;
		#endregion

		/// Constructor
		public NCInputMove(int interval,
			ClientSystem clientSystem) :
			base(interval, clientSystem,
			ENetEventType.MoveInput, false) {

				this.NewInput_ = false;
				this.IsRunning_ = false;
				this.TargetLocation_ = Vector2.Zero;
		}

		/// Load Content
		public override void LoadContent() {
			
		}

		/// Process any player requested movement and write
		/// and queue the request to be sent to the server.
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {

			// Check if there is new input
			if (this.NewInput_) {

				// Create new network event
				NetEvent netEvent = this.CreateNetEvent();
				
				// Write target location
				netEvent.Data.WriteCustomResolutionSingle(this.TargetLocation_.X, 
					MinFloatValue, MaxFloatValue, FloatResolution);
				netEvent.Data.WriteCustomResolutionSingle(this.TargetLocation_.Y,
					MinFloatValue, MaxFloatValue, FloatResolution);

				// Write the running state
				netEvent.Data.WriteBool(this.IsRunning_);

				// Set NewInput_ to false to prevent
				// processing the same input more than once
				this.NewInput_ = false;

				// Queue up net event
				this.EnqueueOutNetEvent(netEvent);
			}
		}

		/// External method used for registering
		/// an input request by the player to move.
		public void Move(Vector2 target, bool isRunning) {
			this.TargetLocation_ = target;
			this.IsRunning_ = isRunning;
			this.NewInput_ = true;
		}

		/// Registers the location that 
		/// the player would like to move to.
		private Vector2 TargetLocation_;

		/// Flag used to indicate if a player is running.
		private bool IsRunning_;

		/// Keeps track of whether or not
		/// there is new input that has
		/// not been handled and sent yet.
		private bool NewInput_;
	}
}
