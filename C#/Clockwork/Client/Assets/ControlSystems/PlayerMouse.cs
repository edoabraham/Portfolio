/// PlayerMouse.cs - Player Mouse Behavior
/// Written By Jesse Z. Zhong
#region Assemblies
using UnityEngine;
using System.Collections;

using Artemis;
using Artemis.Interface;
#endregion

/// Details the behavior for a third
/// person spherical interpolating camera.
public sealed class PlayerMouse : IComponent {

	/// Targeted Point
	private Vector3 TargetedPoint_;
	public Vector3 TargetedPoint {
		get { return TargetedPoint_; }
	}

	/// Mouse Actions
	private bool MouseAction0_;
	public bool MouseAction0 {
		get { return MouseAction0_; }
	}

	/// Ray Hit Data
	private RaycastHit hit;

	/// Start Initialization
	public PlayerMouse() {
		// Initialize Target
		this.TargetedPoint_ = new Vector3();
	}

	/// Updates Mouse Processes
	public void Update() {

		if (Input.GetMouseButton(0)) {

			// Or Try This Code
			// Create Ray From Point on the Screen
			Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

			// Create Ray from the Mouse (Infinity by Default)
			if (Physics.Raycast(ray, out hit)) {
				this.TargetedPoint_ = hit.point;
			}

			// Check if Mouse Actions are Active
			this.MouseAction0_ = true;
		}
	}
}