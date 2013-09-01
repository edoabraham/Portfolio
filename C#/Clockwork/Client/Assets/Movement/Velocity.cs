/// Velocity.cs - Velocity Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using Artemis;
using Artemis.Interface;
using System.Collections.Generic;
using UnityEngine;
#endregion

/// Physics Components
/// Simple Velocity Implementation
public class Velocity : IComponent {

	/// Constructor
	public Velocity() {
		this.Velocity_ = new Vector3(0.0f, 0.0f, 0.0f);
	}

	/// Init-Constructor; Vector3D Source
	public Velocity(Vector3 source) {
		this.Velocity_ = source;
	}

	/// Init-Constructor; Vector2D Source
	public Velocity(Vector2 source) {
		this.Velocity_ = new Vector3(source.x, source.y, 0.0f);
	}
	public Velocity(Vector2 source, float z) {
		this.Velocity_ = new Vector3(source.x, source.y, z);
	}

	/// Gets the Direction Angle of Velocity
	/// On the XY Plane
	public float Direction {
		get {
			return (float)Math.Atan(Velocity_.x / Velocity_.y);
		}
	}

	/// Velocity Vector
	private Vector3 Velocity_;
	public Vector3 Value {
		get { return Velocity_; }
		set { Velocity_ = value; }
	}
}

