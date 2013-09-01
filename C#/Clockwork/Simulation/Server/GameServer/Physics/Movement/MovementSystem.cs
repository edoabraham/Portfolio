/// MovementSystem.cs - MovementSystem Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;
using Utilities;

/// Game Server
namespace GameServer {

	/// Movement System
	/// Dictates the behavior of movement in the game.
	public sealed class MovementSystem : EntityProcessingSystem {

		/// Inherited Constructor
		public MovementSystem() :
			base(Aspect.All(typeof(Transform), typeof(Velocity))) {
			
		}

		/// Load Content
		public override void LoadContent() {
			this.BlinkMapper_ = new ComponentMapper<Blink>(this.EntityWorld);
			this.VelocityMapper_ = new ComponentMapper<Velocity>(this.EntityWorld);
			this.TransformMapper_ = new ComponentMapper<Transform>(this.EntityWorld);
		}

		/// Processes Entities with Their Velocities
		/// to Procure Possible Translation
		public override void Process(Entity e) {

			// Localize
			Transform transform = this.TransformMapper_.Get(e);

			// Check if there is a Blink Component
			if (e.HasComponent<Blink>()) {

				// Localize
				Blink blink = this.BlinkMapper_.Get(e);

				// Check if it is Active; Delete if not active
				if (blink.Finished)
					e.RemoveComponent<Blink>();
				else {

					// Perform Translation
					transform.Position += blink.Velocity;

					// Set the Direction of the Transform Component
					transform.Direction = new Vector3(blink.Direction, 
						transform.Direction.Y, transform.Direction.Y);
				}

			} else {

				// Localize
				Velocity velocity = this.VelocityMapper_.Get(e);

				// Perform Translation
				transform.Position += velocity.Value;

				// Set the Direction of the Transform Component
				transform.Direction = new Vector3(velocity.Direction,
						transform.Direction.Y, transform.Direction.Y);
			}
		}

		#region Component Mappers
		/// Component Maps for Velocity
		/// and Transform Components
		private ComponentMapper<Blink> BlinkMapper_;
		private ComponentMapper<Velocity> VelocityMapper_;
		private ComponentMapper<Transform> TransformMapper_;
		#endregion
	}
}
