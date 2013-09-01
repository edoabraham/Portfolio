/// Statistics.cs - Statistics Class Implementation
/// Written By Jesse Z. Zhong

using System;
using Artemis.Interface;
using System.Collections.Generic;
using System.Xml.Serialization;
using System.ComponentModel;

/// Gamer Server
namespace GameServer {

	/// Game Entity/Object Type Data
	/// Collection of Statistics for Characters

	/// Base Stats for a Character that are only influenced
	/// by leveling up or equipping items in the game.
	/// NOTE: Recalculations should only happen when
	/// items are added or swapped, or a level up occurred.
	
	public class Statistics : Artemis.Interface.IComponent {

		/// Constructor
		public Statistics() {
			this.HealthPoints_ = 0;
			this.HealthRegen_ = 0;
			this.ManaPoints_ = 0;
			this.ManaRegen_ = 0;
			this.StaminaPoints_ = 0;
			this.StaminaRegen_ = 0;
			this.PhysicalDamage_ = 0;
			this.MagicalDamage_ = 0;
			this.PhysicalDefense_ = 0;
			this.MagicalDefense_ = 0;
			this.MovementSpeed_ = 0;
			this.AttackSpeed_ = 0;
			this.CastRate_ = 0;
			this.CoolDownRate_ = 0;
			this.CriticalRate_ = 0;
			this.SightRange_ = 0;
		}

		/// Copy Constructor
		public Statistics(Statistics stats) {
			this.HealthPoints_ = stats.Health;
			this.HealthRegen_ = stats.HealthRegen;
			this.ManaPoints_ = stats.Mana;
			this.ManaRegen_ = stats.ManaRegen;
			this.StaminaPoints_ = stats.Stamina;
			this.StaminaRegen_ = stats.StaminaRegen;
			this.PhysicalDamage_ = stats.PhysicalDamage;
			this.MagicalDamage_ = stats.MagicalDamage;
			this.PhysicalDefense_ = stats.PhysicalDefense;
			this.MagicalDefense_ = stats.MagicalDefense;
			this.MovementSpeed_ = stats.MovementSpeed;
			this.AttackSpeed_ = stats.AttackSpeed;
			this.CastRate_ = stats.CastRate;
			this.CoolDownRate_ = stats.CoolDownRate;
			this.CriticalRate_ = stats.CastRate;
			this.SightRange_ = stats.SightRange;
		}

		/// Health Points
		[DisplayName("Health")]
		public int Health {
			get { return this.HealthPoints_; }
			set { this.HealthPoints_ = value; }
		}

		/// Health Regen Points
		[DisplayName("Health Regen")]
		public int HealthRegen {
			get { return this.HealthRegen_; }
			set { this.HealthRegen_ = value; }
		}

		/// Mana Points
		[DisplayName("Mana")]
		public int Mana {
			get { return this.ManaPoints_; }
			set { this.ManaPoints_ = value; }
		}

		/// Mana Regen Points
		[DisplayName("Mana Regen")]
		public int ManaRegen {
			get { return this.ManaRegen_; }
			set { this.ManaRegen_ = value; }
		}

		/// Stamina Points
		[DisplayName("Stamina")]
		public int Stamina {
			get { return this.StaminaPoints_; }
			set { this.StaminaPoints_ = value; }
		}

		/// Stamina Regen Points
		[DisplayName("Stamina Regen")]
		public int StaminaRegen {
			get { return this.StaminaRegen_; }
			set { this.StaminaRegen_ = value; }
		}

		/// Physical Damage
		[DisplayName("Physical Damage")]
		public int PhysicalDamage {
			get { return this.PhysicalDamage_; }
			set { this.PhysicalDamage_ = value; }
		}

		/// Magical Damage
		[DisplayName("Magical Damage")]
		public int MagicalDamage {
			get { return this.MagicalDamage_; }
			set { this.MagicalDamage_ = value; }
		}

		/// Physical Defense
		[DisplayName("Physical Defense")]
		public int PhysicalDefense {
			get { return this.PhysicalDefense_; }
			set { this.PhysicalDefense_ = value; }
		}

		/// Magical Defense
		[DisplayName("Magical Defense")]
		public int MagicalDefense {
			get { return this.MagicalDefense_; }
			set { this.MagicalDefense_ = value; }
		}

		/// Movement Speed
		/// The higher the value, the faster
		/// a character can move
		[DisplayName("Movement Speed")]
		public int MovementSpeed {
			get { return this.MovementSpeed_; }
			set { this.MovementSpeed_ = value; }
		}

		/// Attack Speed
		/// The higher the value, the faster
		/// physical attack actions are
		/// Also influences recovery time
		[DisplayName("Attack Speed")]
		public int AttackSpeed {
			get { return this.AttackSpeed_; }
			set { this.AttackSpeed_ = value; }
		}

		/// Cast Time Rate
		/// The higher the value, the quicker
		/// magic spell cast animations are
		[DisplayName("Cast Rate")]
		public int CastRate {
			get { return CastRate_; }
			set { CastRate_ = value; }
		}

		/// Cool Down Rate
		/// The higher the value is, the shorter
		/// the amount of time that is required
		/// to be able to cast magic again
		[DisplayName("Cool Down Rate")]
		public float CoolDownRate {
			get { return this.CoolDownRate_; }
			set { this.CoolDownRate_ = 0; }
		}

		/// Critical Rate
		[DisplayName("Critical Rate")]
		public float CriticalRate {
			get { return this.CriticalRate_; }
			set { this.CriticalRate_ = value; }
		}

		/// Sight Range
		[DisplayName("Vision/Sight Range")]
		public float SightRange {
			get { return this.SightRange_; }
			set { this.SightRange_ = value; }
		}

		#region Private
		private int HealthPoints_;
		private int HealthRegen_;
		private int ManaPoints_;
		private int ManaRegen_;
		private int StaminaPoints_;
		private int StaminaRegen_;
		private int PhysicalDamage_;
		private int MagicalDamage_;
		private int PhysicalDefense_;
		private int MagicalDefense_;
		private int MovementSpeed_;
		private int AttackSpeed_;
		private int CastRate_;
		private float CoolDownRate_;
		private float CriticalRate_;
		private float SightRange_;
		#endregion
	}

	/// Current Stats mainly used to keep track of 
	/// remaining Health, Mana, or Stamina left.
	/// Contains Stat Buffs and Debuffs.
	/// NOTE: Recalculations should only happen when
	/// damage is taken or Mana or Stamina are used.
	public class CurrentStats : Statistics {

		/// Constructor
		public CurrentStats()
			: base() {

		}

		/// Copy Constructor
		public CurrentStats(CurrentStats currStats)
			: base(currStats) {

		}
	}
}
