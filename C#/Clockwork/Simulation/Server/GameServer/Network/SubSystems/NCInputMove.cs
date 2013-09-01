/// NCInputMove.cs - NCInputMove Class Implementation
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

/// Game Server
namespace GameServer {

	/// Input Move System
	/// This system is in charge of translating a player's
	/// datagram for input and setting their controller
	/// to allow their character on the server to move.
	public sealed class NCInputMove : 
		ServerProcessingSystem {

		/// Packet Structure (In Only)
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
			ServerSystem serverSystem) :
			base(interval, serverSystem,
			ENetEventType.MoveInput, true) {

		}

		/// Load Content
		public override void LoadContent() {
			
		}

		/// Register the input to the respective player controller
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {
			
			// Iterate through the whole queue and process player inputs.
			while (this.InNetEventList_.Count > 0) {
				KeyValuePair<PlayerController, NetEvent> inNetEvent = this.InNetEventList_.Dequeue();

				// Pull movement target position
				float xPosition = 0.0f;
				inNetEvent.Value.Data.ReadCustomResolutionSingle(out xPosition,
					MinFloatValue, MaxFloatValue, FloatResolution);
				float yPosition = 0.0f;
				inNetEvent.Value.Data.ReadCustomResolutionSingle(out yPosition,
					MinFloatValue, MaxFloatValue, FloatResolution);

				// Set the new movement target position
				inNetEvent.Key.TargetLocation = new Vector2(xPosition, yPosition);

				// Pull and store the running flag only if the state is running or idle
				if ((inNetEvent.Key.State == EAction.Running) || 
					(inNetEvent.Key.State == EAction.Idle)) {
						bool isRunning = false;
						inNetEvent.Value.Data.ReadBool(out isRunning);
					inNetEvent.Key.State = (isRunning) ? EAction.Running : EAction.Idle;
				}

				// Register the time the packet was received and processed.
				inNetEvent.Key.LastMoveCommandTime = this.ServerSystem_.GameRunTimer.ElapsedTime;
			}
		}
	}
}
