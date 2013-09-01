/// Entity.cs - Entity Class Implementation
/// Written By Jesse Z. Zhong

using System;

/// Define Type BigInteger
using BigInteger = System.Int64;

/// Artemis
namespace ArtemisUnity {

	/// Entity
	public sealed class Entity {

		private int ID_;
		private long UniqueID_;
		private BigInteger TypeBits_ = 0;
		private BigInteger SystemBits_ = 0;

		private EntityWorld World_;
		private EntityManager EntityManager_;

		private bool Enabled_ = true;
		private bool RefreshingState_ = false;
		private bool DeletingState_ = false;

		/// Internal Constructor
		internal Entity(EntityWorld world, int id) {
			this.World_ = world;
			this.EntityManager_ = world.EntityManager;
			this.ID_ = id;
		}

		/// Returns the Entity's ID
		internal int ID {
			get { return ID_; }
		}

		/// Accessors for Entity's Unique ID
		public long UniqueID {
			internal set {
				// Ensure that the ID is Not Negative
				System.Diagnostics.Debug.Assert(UniqueID_ >= 0);
				UniqueID_ = value;
			}
			get { return UniqueID_; }
		}

		/// Accessors for the Type Bits
		internal BigInteger TypeBits {
			set { TypeBits_ = value; }
			get { return TypeBits_; }
		}

		/// Add the Bit Value of a Certain 
		/// Component Type to the Entity's Type Bits
		internal void AddTypeBit(BigInteger bit) {
			TypeBits_ |= bit;
		}

		/// Remove the Bit Value of a Certain
		/// Component Type from the Entity's Type Bits
		internal void RemoveTypeBit(BigInteger bit) {
			TypeBits_ &= ~bit;
		}

		/// Accessors for the Entity's Refresh State
		public bool RefreshingState {
			set { RefreshingState_ = value; }
			get { return RefreshingState_; }
		}

		/// Accessors for the Entity's Delete State
		public bool DeletingState {
			set { DeletingState_ = value; }
			get { return DeletingState_; }
		}

		/// Accessors for the Entity's System Bits
		internal BigInteger SystemBits {
			set { SystemBits_ = value; }
			get { return SystemBits_; }
		}

		/// Add the Bit Value of a Certain 
		/// Component Type to the System's Type Bits
		internal void AddSystemBit(BigInteger bit) {
			SystemBits_ |= bit;
		}

		/// Remove the Bit Value of a Certain
		/// Component Type from the System's Type Bits
		internal void RemoveSystemBit(BigInteger bit) {
			SystemBits_ &= ~bit;
		}

		/// Resets the States of the Entity
		public void Reset() {
			SystemBits_ = 0;
			TypeBits_ = 0;
			Enabled_ = true;
		}

		/// Toggle the Enable Value of the Entity
		public bool Enabled {
			set { Enabled_ = value; }
			get { return Enabled_; }
		}


		/// **
		/// COMPONENT METHODS
		/// =================================

		/// Add a Component to This Entity
		public void AddComponent(ArtemisComponent component) {
			System.Diagnostics.Debug.Assert(component != null);
			EntityManager_.AddComponent(this, component);
		}

		public void AddComponent<T>(ArtemisComponent component) where T : ArtemisComponent {
			System.Diagnostics.Debug.Assert(component != null);
			EntityManager_.AddComponent<T>(this, component);
		}

		/// Remove a Component from This Entity
		public void RemoveComponent<T>(ArtemisComponent component) where T : ArtemisComponent {
			System.Diagnostics.Debug.Assert(component != null);
			EntityManager_.RemoveComponent<T>(this, component);
		}

		public void RemoveComponent(ComponentType type) {
			System.Diagnostics.Debug.Assert(type != null);
			EntityManager_.RemoveComponent(this, type);
		}

		/// Returns Whether or Not This Entity is Still in Use
		public bool IsActive {
			get { return EntityManager_.IsActive(ID_); }
		}

		/// Return the Component Given the Component Type
		public ArtemisComponent GetComponent(ComponentType type) {
			// Check for Null References
			System.Diagnostics.Debug.Assert(type != null);
			return EntityManager_.GetComponent(this, type);
		}

		public T GetComponent<T>() where T : ArtemisComponent {
			return (T)GetComponent(ComponentTypeManager.GetTypeFor<T>());
		}

		/// Check if the Component of Passed Type Exists
		public bool HasComponent<T>() where T : ArtemisComponent {
			return (T)GetComponent(ComponentTypeManager.GetTypeFor<T>()) != null;
		}

		/// Return All the Components of This Entity
		public Bag<ArtemisComponent> Components {
			get {
				return EntityManager_.GetComponents(this);
			}
		}

		/// Refreshes All Components in This Entity
		public void Refresh() {
			if (RefreshingState_ == true)
				return;
			World_.RefreshEntity(this);
			RefreshingState_ = true;
		}

		/// Set Current Entity Up For Deletion
		public void Delete() {
			if (DeletingState_ == true)
				return;
			World_.DeleteEntity(this);
			DeletingState_ = true;
		}

		/// Sets the Group of Entities
		public String Group {
			set { World_.GroupManager.Set(value, this); }
			get { return World_.GroupManager.GetGroupOf(this); }
		}

		/// Assigns a Tag for This Entity
		public String Tag {
			set { World_.TagManager.Register(value, this); }
			get { return World_.TagManager.GetTagOfEntity(this); }
		}
	}
}
