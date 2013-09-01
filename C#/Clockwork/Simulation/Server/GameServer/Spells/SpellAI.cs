/// SpellAI.cs - Spell AI class implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;

using Artemis;
using Artemis.Interface;

/// Game Server
namespace GameServer {

	/// This delegate is the outline of all Spell AI update methods.
	/// A defined instance of this method will be assigned by the SpellSystem
	/// when the spell is created. It will be used to dictate the behavior
	/// of the spell until its death.
	public delegate void SpellUpdate(Controller controller, Transform transform, 
	Velocity velocity, Statistics statistics, Killable killable);

	/// Controls the logic of a spell
	public class SpellAI : IComponent {

		/// Constructor
		public SpellAI(uint ownderID, uint spellID) {
			this.OwnerID_ = ownderID;
			this.SpellID_ = spellID;
		}

		/// Returns the id of the owner of the spell
		private uint OwnerID_;
		public uint OwnerID {
			get { return this.OwnerID_; }
		}

		/// Returns the id of the spell the
		/// entity  is supposed to be a part of
		private uint SpellID_;
		public uint SpellID {
			get { return this.SpellID_; }
		}

		/// AI Update method
		public SpellUpdate Update;
	}
}
