/// CollisionSystem.cs - CollisionSystem Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis;
using Artemis.System;
using System.Collections.Generic;
using Utilities;

/// Game Server
namespace GameServer {

	/// Handles Collision checking and the Results of a Collision
	/// This includes collisions between two different characters
	/// or between characters and spells.
	public class CollisionSystem : EntitySystem {

		/// Constructor
		public CollisionSystem() : base(typeof(Transform)) {
			
		}

		/// Load Content
		public override void LoadContent() {
			TransformMapper_ = new ComponentMapper<Transform>(EntityWorld);
			VelocityMapper_ = new ComponentMapper<Velocity>(EntityWorld);
			MapCellMapper_ = new ComponentMapper<MapCell>(EntityWorld);
			SpellAIMapper_ = new ComponentMapper<SpellAI>(EntityWorld);
		}

		/// Process the Entities
		protected override void ProcessEntities(IDictionary<int, Entity> entities) {

			foreach (Entity e1 in entities.Values) {
				foreach (Entity e2 in entities.Values) {

					// Make sure the entities are not the same
					if (e1 != e2)
						Process(e1, e2);
				}
			}
		}

		/// Check and handle collision for two entities,
		/// given that they have Transform Components
		private void Process(Entity e1, Entity e2) {

			// **
			// CHARACTER COLLISION
			// ********************
			// Characters require all information since in most cases intersection of two characters is not permitted.
			// In order to prevent this, Intersect, WillIntersect, and MinimumTranslationVector are all needed.
			if ((e1.Group == EntityGroupName.Characters) && (e2.Group == EntityGroupName.Characters)) {

				// Localize
				Transform transform1 = TransformMapper_.Get(e1);
				Transform transform2 = TransformMapper_.Get(e2);
				Velocity velocity = VelocityMapper_.Get(e1);

				// Check for impending collisions
				CollisionResult result = transform1.CircleZone.
					CircleCollision(transform2.CircleZone, (Vector2)velocity.Value);

				// Adjust Velocity if the characters are about to collide so 
				// that the two characters collide by never intersect one another.
				if(result.WillIntersect)
					velocity.Value -= (Vector3)result.MinimumTranslationVector;
			}

			// **
			// SPELL COLLISION
			// ****************
			// Spells only need to test for actual intersection. As long as there's contact, then
			// there is enough collision information to carry out spell effects.
			// Projectiles may need another exception to improve accuracy (usage of WillIntersect)
			// Spell to Character Collision testing; Only test for Spell to Character since
			// both tests are equivalent and performing them twice will have double results
			if ((e1.Group == EntityGroupName.Spells) && (e2.Group == EntityGroupName.Characters)) {

				// Localize
				Transform transform1 = TransformMapper_.Get(e1);
				Transform transform2 = TransformMapper_.Get(e2);
				Velocity velocity = VelocityMapper_.Get(e1);
				CollisionResult result = new CollisionResult();

				// Check for collisions
				if (transform1.HasCircle)
					result = transform1.CircleZone.CircleCollision(transform2.CircleZone,
						(Vector2)velocity.Value);
			}
		}

		#region Component Mapper
		private ComponentMapper<Transform> TransformMapper_;
		private ComponentMapper<Velocity> VelocityMapper_;
		private ComponentMapper<MapCell> MapCellMapper_;
		private ComponentMapper<SpellAI> SpellAIMapper_;
		#endregion
	}
}
