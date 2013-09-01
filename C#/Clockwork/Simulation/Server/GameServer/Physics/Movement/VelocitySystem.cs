/// VelocitySystem.cs - VelocitySystem Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;
using Utilities;

/// Game Server
namespace GameServer {

	/// Velocity System
	public class VelocitySystem : EntityProcessingSystem {

		/// Threshold Size for Movement (SQUARED)
		private const float Threshold = 0.12f;

		/// Dictates how much actual movement speed there is as
		/// it scales with each point of the movement speed stat
		private const float MovementSpeedScaling = GlobalData.MovementSpeedModifier;

		/// Dictates how much running speed there is as
		/// it scales with each point of the movement speed stat
		private const float RunningSpeedScaling = GlobalData.RunningSpeedModifier;

		/// Time it takes before running state expires (milliseconds)
		private const long RunningExpireTime = 500;

		/// Constructor
		public VelocitySystem() : 
			base(Aspect.All(typeof(CurrentStats), typeof(Transform), 
			typeof(Velocity)).GetOne(typeof(Controller), typeof(PlayerController))) {

		}

		/// Load Content
		public override void LoadContent() {
			this.VelocityMapper_ = new ComponentMapper<Velocity>(this.EntityWorld);
			this.TransformMapper_ = new ComponentMapper<Transform>(this.EntityWorld);
			this.CurrentStats_ = new ComponentMapper<CurrentStats>(this.EntityWorld);
			this.ControllerMapper_ = new ComponentMapper<Controller>(this.EntityWorld);
			this.PCController_ = new ComponentMapper<PlayerController>(this.EntityWorld);
		}

		/// Processes Entities with Their Velocities
		/// to Procure Possible Translation
		public override void Process(Entity e) {

			// Localize an Instance of Control
			Controller controller = (e.HasComponent<Controller>()) ? 
				this.ControllerMapper_.Get(e) : this.PCController_.Get(e);

			// Localize
			Velocity velocity = this.VelocityMapper_.Get(e);
			Transform transform = this.TransformMapper_.Get(e);

			// Check if There is Movement
			if (controller.IsMoving && 
				this.CheckForMovement(controller.TargetLocation, 
				(Vector2)transform.Position)) {

				// Localize
				CurrentStats stats = this.CurrentStats_.Get(e);

				// If it is a player controller, check the last
				// packet received time to determine whether or not
				// a controller in running state is still running.
				if (e.HasComponent<PlayerController>()) {

				}

				// Calculate direction and velocity
				// If the controller is a PlayerController, test for running state.
				// If the player is in running state, use the running speed modifier.
				transform.CalculateDirection(controller.TargetLocation);
				velocity.Value = transform.Direction * 
					(((e.HasComponent<PlayerController>()) && 
					(this.PCController_.Get(e).State == EAction.Running)) 
					? RunningSpeedScaling : MovementSpeedScaling) 
					* stats.MovementSpeed;

			} else {
				// Zero the Velocity
				velocity.Value = Vector3.Zero;

				// Change the state to idle
				this.PCController_.Get(e).State = EAction.Idle;
			}
		}

		#region Component Mappers
		/// Component Maps for Velocity
		/// and Transform Components
		private ComponentMapper<Velocity> VelocityMapper_;
		private ComponentMapper<Transform> TransformMapper_;
		private ComponentMapper<CurrentStats> CurrentStats_;
		private ComponentMapper<Controller> ControllerMapper_;
		private ComponentMapper<PlayerController> PCController_;
		#endregion

		/// Checks if the Displacement Between Two 
		/// Vectors is Large Enough to Procure Movement
		private bool CheckForMovement(Vector2 source, Vector2 target) {
			Vector2 displacement = source - target;
			return (displacement.SquaredLength > Threshold);
		}
	}
}
