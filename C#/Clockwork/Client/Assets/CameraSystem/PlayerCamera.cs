/// PlayerCamera.cs - Player Camera Behavior
/// Written By Jesse Z. Zhong
#region Assemblies
using UnityEngine;
using System.Collections;
#endregion

/// Details the Behavior for a Third Person
/// Spherical Interpolating Camera
public class PlayerCamera : MonoBehaviour {

	/// Targeted Object for 
	/// the Camera will Follow
	public static GameObject Target;

	/// Awake Initialization
	void Awake() {
		Target = new GameObject("Camera Target");
		Target.transform.position = Vector3.zero;
	}

	public float HeightOffset = 1.6f;
	public float Distance = 5.0f;

	public float MaxDistance = 20f;
	public float MinDistance = 0.8f;

	public float xSpeed = 250.0f;
	public float ySpeed = 120.0f;

	public int yMinLimit = -80;
	public int yMaxLimit = 80;

	public int ZoomRate = 40;

	public float RotationDampening = 3.0f;
	public float ZoomDampening = 5.0f;

	private float X_ = 0.0f;
	private float Y_ = 0.0f;

	private float CurrentDistance_;
	private float DesiredDistance_;
	private float CorrectedDistance_;

	/// Initialization
	void Start() {

		// Initialize States
		Vector3 angles = transform.eulerAngles;
		X_ = angles.x;
		Y_ = angles.y;

		CurrentDistance_ = Distance;
		DesiredDistance_ = Distance;
		CorrectedDistance_ = Distance;

		// Set to Rigid so the Camera Does Not
		// Change its Rotation
		if (rigidbody)
			rigidbody.freezeRotation = true;
	}

	/// Update
	void LateUpdate() {
		// Check for Target Between Changes
		System.Diagnostics.Debug.Assert(Target != null);

		// 
		if (Input.GetMouseButton(1)) {
			X_ += Input.GetAxis("Mouse X") * xSpeed * 0.02f;
			Y_ -= Input.GetAxis("Mouse Y") * ySpeed * 0.02f;
		}

		Y_ = ClampAngle(Y_, yMinLimit, yMaxLimit);

		// Set Camera Rotation
		Quaternion rotation = Quaternion.Euler(Y_, X_, 0);

		// Calculate the Desired Distance
		DesiredDistance_ -= Input.GetAxis("ScrollWheel") * 
			Time.deltaTime * ZoomRate * Mathf.Abs(DesiredDistance_);

		DesiredDistance_ = Mathf.Clamp(DesiredDistance_, MinDistance, MaxDistance);

		CorrectedDistance_ = DesiredDistance_;

		// Calculate Desired Camera Position
		Vector3 position = Target.transform.position - (rotation * 
			Vector3.forward * DesiredDistance_ + new Vector3(0, -HeightOffset, 0));

		// Use Raycast to Test for the Correct Position
		// This will Make Sure the Positions are Synced Up Properly
		RaycastHit collisionHit;
		Vector3 trueTargetPosition = new Vector3(Target.transform.position.x, 
			Target.transform.position.y + HeightOffset, Target.transform.position.z);

		// Correct the Position with the Point the
		// Ray Intersects with the Collided Item
		bool isCorrected = false;
		if (Physics.Linecast(trueTargetPosition, position, out collisionHit)) {
			position = collisionHit.point;
			CorrectedDistance_ = Vector3.Distance(trueTargetPosition, position);
			isCorrected = true;
		}

		CurrentDistance_ = !isCorrected || CorrectedDistance_ > CurrentDistance_ ? 
			Mathf.Lerp(CurrentDistance_, CorrectedDistance_, Time.deltaTime * ZoomDampening) : 
			CorrectedDistance_;

		position = Target.transform.position - (rotation * Vector3.forward * 
			CurrentDistance_ + new Vector3(0, -HeightOffset, 0));

		// Update Camera's Position and Rotation
		transform.rotation = rotation;
		transform.position = position;
	}

	private static float ClampAngle(float angle, float min, float max) {
		if (angle < -360.0f)
			angle += 360.0f;
		if (angle > 360.0f)
			angle -= 360.0f;
		return Mathf.Clamp(angle, min, max);
	}
}
