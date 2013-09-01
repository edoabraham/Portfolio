/// Spell.cs - Spell Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Linq;
using System.Collections.Generic;

using Artemis;
using Artemis.Interface;

/// Game Server
namespace GameServer {

	/// Spell Component
	public class Spell {

		/// The number of milliseconds of charge time
		/// required to increase a spell by one charge.
		private const int MillisecondsToCharge = GlobalData.SpellMillisecondsToCharge;

		/// Enumerates the target types:
		/// All means the same effect affects everyone in contact the same way.
		/// Allies means it only has an effect on allies.
		/// Enemies means it only has an effect on enemies.
		/// Divided means it affects allies and enemies in two different ways.
		/// Self means the spell only affects the character casting.
		public enum ETargetType : byte {
			All,
			Allies,
			Divided,
			Enemies,
			Self
		}

		/// Delegate used for initializing a spell
		public delegate void SpellInit(Spell spell);

		/// Delegate for running the spell's logic
		public delegate void SpellProc(Spell spell, Entity character);
		private SpellProc ProcSpell;
		public void Procure(Entity character) {

			if (this.ProcSpell != null)
				this.ProcSpell(this, character);
		}

		/// Constructor
		public Spell(
			SpellInit initSpell,
 			SpellProc procSpell) {
				this.CastTime_ = 0.0f;
				this.CoolDown_ = 0.0f;
				this.HasCharge_ = false;
				this.ChargeDuration_ = 0;
				this.ChargeBaseScale_ = 0.0f;
				this.ChargeModifierScale_ = 0.0f;
				this.SelfStats_ = new Statistics();
				this.ProcSpell = procSpell;
				if (initSpell != null)
					initSpell(this);
		}

		/// Name of a spell
		private string Name_;
		public string Name {
			get { return this.Name_; }
			set { this.Name_ = value; }
		}

		/// Time it takes for a spell to take effect
		private float CastTime_;
		public float CastTime {
			get { return this.CastTime_; }
			set { this.CastTime_ = value; }
		}

		/// Time it takes to use spell again
		private float CoolDown_;
		public float CoolDown {
			get { return this.CoolDown_; }
			set { this.CoolDown_ = value; }
		}

		/// Indicates the minimum range that the spell can be cast at.
		private float MinRange_;
		private float MinRange {
			get { return this.MinRange_; }
			set {
				// The min range cannot be negative
				System.Diagnostics.Debug.Assert(value >= 0);
				this.MinRange_ = value;
			}
		}

		/// Dictates the maximum range that the spell can be cast at.
		private float MaxRange_;
		public float MaxRange {
			get { return this.MaxRange_; }
			set { 
				// The max range cannot be negative
				System.Diagnostics.Debug.Assert(value >= 0);
				this.MaxRange_ = value; 
			}
		}

		/// Influences how the spell will affect the player casting
		/// This can be used for stamina, health, and mana depletion. 
		/// It can also be used for self healing or regeneration.
		private Statistics SelfStats_;
		public Statistics SelfStats {
			get { return this.SelfStats_; }
			set { this.SelfStats_ = value; }
		}

		/// Decides who the spell has an effect for.
		/// All means the same effect affects everyone in contact the same way.
		/// Allies means it only has an effect on allies.
		/// Enemies means it only has an effect on enemies.
		/// Divided means it affects allies and enemies in two different ways.
		/// Self means the spell only affects the character casting.
		private ETargetType Target_;
		public ETargetType Target {
			get { return this.Target_; }
			set { 
				this.Target_ = value;
				this.SetTarget(this.Target_);
			}
		}

		/// Returns whether or not this spell has a charge phase.
		private bool HasCharge_;
		public bool HasCharge {
			get { return this.HasCharge_; }
		}

		/// Sets or returns the charge duration of the spell.
		/// If the duration is not zero, set HasDuration to true.
		private long ChargeDuration_;
		public long ChargeDuration {
			get { return this.ChargeDuration_; }
			set {
				// Check if this is a charge spell
				this.HasCharge_ = (value == 0) ? false : true;
				this.ChargeDuration_ = value;
			}
		}

		/// Sets or returns the ratio at which the base spell
		/// stats are increased for each charge that a player has.
		private float ChargeBaseScale_;
		public float ChargeBaseScale {
			get { return this.ChargeBaseScale_; }
			set { this.ChargeBaseScale_ = value; }
		}

		/// Sets or returns the ratio at which the modifier spell
		/// stats are increased for each charge that a player has.
		private float ChargeModifierScale_;
		public float ChargeModifierScale {
			get { return this.ChargeModifierScale_; }
			set { this.ChargeModifierScale_ = value; }
		}

		/// List of DataSets
		private List<DataSet> StatSets_;
		private void SetTarget(ETargetType type) {
			switch (type) {
				case ETargetType.All:
					// Set up one element in StatSets_ for all
					this.StatSets_ = new List<DataSet>(1);
					break;
				case ETargetType.Allies:
					// Sets up a single element in StatSets_ for allies
					this.StatSets_ = new List<DataSet>(1);
					break;
				case ETargetType.Divided:
					// Sets up two elements, one for allies and one for enemies
					this.StatSets_ = new List<DataSet>(2);
					break;
				case ETargetType.Enemies:
					// Sets up one element for enemies only
					this.StatSets_ = new List<DataSet>(1);
					break;
				case ETargetType.Self:
					// Does not initialize StatSets_
					break;
				default:
					break;
			}
		}

		/// Returns the data set that will affect allies
		/// Set can also be edited
		public DataSet Ally {
			get {
				// Check uninitialized StatSets_
				if (this.StatSets_ == null)
					throw new Exception("StatSets_ is not initialized.");

				// Determine what set to return
				switch (this.Target_) {
					case ETargetType.All:
						// Returns the the only element as it applies to all
						if (!this.StatSets_.Any() || (this.StatSets_.Count != 1))
							return this.StatSets_[0];
						break;
					case ETargetType.Allies:
						// Returns the only element as allies
						if (!this.StatSets_.Any() || (this.StatSets_.Count != 1))
							return this.StatSets_[0];
						break;
					case ETargetType.Divided:
						// Returns the first element as it applies to allies
						if (!this.StatSets_.Any() || (this.StatSets_.Count != 2))
							return this.StatSets_[0];
						break;
					case ETargetType.Enemies:
						// Throws an exception as this should not be possible
						throw new Exception("A Target of ETargetType.Enemies cannot have ally stats. Illegal access.");
					case ETargetType.Self:
						// Throws an exception as this should not be possible
						throw new Exception("A Target of ETargetType.Self cannot have ally stats. Illegal access.");
					default:
						// Throws an exception
						throw new Exception("Could not return DataSet as the Target is an unknown value.");
				}

				// Close all return paths
				return new DataSet();
			}

			set {
				// Check uninitialized StatSets_
				if (this.StatSets_ == null)
					throw new Exception("StatSets_ is not initialized.");

				// Determine what set to return
				switch (this.Target_) {
					case ETargetType.All:
						// Edits the the only element as it applies to all
						if (!this.StatSets_.Any() || (this.StatSets_.Count != 1))
							this.StatSets_[0] = value;
						break;
					case ETargetType.Allies:
						// Edits the only element as allies
						if (!this.StatSets_.Any() || (this.StatSets_.Count != 1))
							this.StatSets_[0] = value;
						break;
					case ETargetType.Divided:
						// Edits the first element as it applies to allies
						if (!this.StatSets_.Any() || (this.StatSets_.Count != 2))
							this.StatSets_[0] = value;
						break;
					case ETargetType.Enemies:
						// Throws an exception as this should not be possible
						throw new Exception("A Target of ETargetType.Enemies cannot have ally stats. Illegal access.");
					case ETargetType.Self:
						// Throws an exception as this should not be possible
						throw new Exception("A Target of ETargetType.Self cannot have ally stats. Illegal access.");
					default:
						// Throws an exception
						throw new Exception("Could not return DataSet as the Target is an unknown value.");
				}
			}
		}

		/// Returns the data set that will affect enemies
		/// Set can also be edited
		public DataSet Enemy {
			get {
				// Check uninitialized StatSets_
				if (this.StatSets_ == null)
					throw new Exception("StatSets_ is not initialized.");

				// Determine what set to return
				switch (this.Target_) {
					case ETargetType.All:
						// Returns the the only element as it applies to all
						if (!this.StatSets_.Any() || (this.StatSets_.Count != 1))
							return this.StatSets_[0];
						break;
					case ETargetType.Allies:
						// Throws an exception as this should not be possible
						throw new Exception("A Target of ETargetType.Allies cannot have enemy stats. Illegal access.");
					case ETargetType.Divided:
						// Returns the second element as it applies to enemies
						if (!this.StatSets_.Any() || (this.StatSets_.Count != 2))
							return this.StatSets_[1];
						break;
					case ETargetType.Enemies:
						// Returns the only element as enemies
						if (!this.StatSets_.Any() || (this.StatSets_.Count != 1))
							return this.StatSets_[0];
						break;
					case ETargetType.Self:
						// Throws an exception as this should not be possible
						throw new Exception("A Target of ETargetType.Self cannot have ally stats. Illegal access.");
					default:
						// Throws an exception
						throw new Exception("Could not return DataSet as the Target is an unknown value.");
				}

				// Close all return paths
				return new DataSet();
			}

			set {
				// Check uninitialized StatSets_
				if (this.StatSets_ == null)
					throw new Exception("StatSets_ is not initialized.");

				// Determine what set to return
				switch (this.Target_) {
					case ETargetType.All:
						// Returns the the only element as it applies to all
						if (!this.StatSets_.Any() || (this.StatSets_.Count != 1))
							this.StatSets_[0] = value;
						break;
					case ETargetType.Allies:
						// Throws an exception as this should not be possible
						throw new Exception("A Target of ETargetType.Allies cannot have enemy stats. Illegal access.");
					case ETargetType.Divided:
						// Returns the second element as it applies to enemies
						if (!this.StatSets_.Any() || (this.StatSets_.Count != 2))
							this.StatSets_[1] = value;
						break;
					case ETargetType.Enemies:
						// Returns the only element as enemies
						if (!this.StatSets_.Any() || (this.StatSets_.Count != 1))
							this.StatSets_[0] = value;
						break;
					case ETargetType.Self:
						// Throws an exception as this should not be possible
						throw new Exception("A Target of ETargetType.Self cannot have ally stats. Illegal access.");
					default:
						// Throws an exception
						throw new Exception("Could not return DataSet as the Target is an unknown value.");
				}
			}
		}

		/// Structure for storing a set of base and scaling stats for spells.
		public struct DataSet {
			public Statistics BaseStats;
			public Statistics ScaleStats;
		}
	}
}
