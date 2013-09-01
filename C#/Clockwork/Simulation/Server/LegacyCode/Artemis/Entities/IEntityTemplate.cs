/// IEntityTemplate.cs - IEntityTemplate Class Implementation
/// Written By Jesse Z. Zhong

using System;
using ArtemisUnity;
using System.Collections.Generic;

/// Artemis
namespace ArtemisUnity {

	/// Interface for Generating Entities
	/// with Predefined Components
	public interface IEntityTemplate {

		/// Adds Components to Passed 
		/// Entity and Returns the Entity
		Entity BuildEntity(Entity e);

	}
}
