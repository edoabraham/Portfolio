/// SpellAISystem.cs - SpellAISystem class implementation.
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

using Artemis;
using Artemis.Utils;
using Artemis.System;
using Artemis.Interface;

/// Game Server
namespace GameServer {

	/// In charge of updating a spell's
	/// behavior according to its AI
	public class SpellAISystem : EntityProcessingSystem {

		/// Constructor
		public SpellAISystem()
			: base(typeof(SpellAI), typeof(Controller), typeof(Transform), 
			typeof(Velocity), typeof(Statistics), typeof(Killable)) {

		}

		/// Load content
		public override void LoadContent() {
			this.SpellAIMapper_ = new ComponentMapper<SpellAI>(this.EntityWorld);
			this.ControllerMapper_ = new ComponentMapper<Controller>(this.EntityWorld);
			this.TransformMapper_ = new ComponentMapper<Transform>(this.EntityWorld);
			this.VelocityMapper_ = new ComponentMapper<Velocity>(this.EntityWorld);
			this.StatisticsMapper_ = new ComponentMapper<Statistics>(this.EntityWorld);
			this.KillableMapper_ = new ComponentMapper<Killable>(this.EntityWorld);
		}

		/// Update the behavior of the spells that have AI
		public override void Process(Entity e) {
			
			// Localize SpellAI
			SpellAI spellAI = SpellAIMapper_.Get(e);

			// Make sure the update method is not null
			if (spellAI.Update != null) {

				// Localize all other components
				Controller controller = ControllerMapper_.Get(e);
				Transform transform = TransformMapper_.Get(e);
				Velocity velocity = VelocityMapper_.Get(e);
				Statistics statistics = StatisticsMapper_.Get(e);
				Killable killable = KillableMapper_.Get(e);

				// Update components using the Update method
				spellAI.Update(controller, transform, velocity, statistics, killable);
			}
		}

		#region Component Mapper
		private ComponentMapper<SpellAI> SpellAIMapper_;
		private ComponentMapper<Controller> ControllerMapper_;
		private ComponentMapper<Transform> TransformMapper_;
		private ComponentMapper<Velocity> VelocityMapper_;
		private ComponentMapper<Statistics> StatisticsMapper_;
		private ComponentMapper<Killable> KillableMapper_;
		#endregion
	}
}
