/// ParameterList.h - Parameter List Enumeration Implementation
/// Written By Jesse Z. Zhong

// Parameter Name List with Corresponding Const Values
enum ParameterList {
	CONE_ANGLE = 0,
	TEMPERATURE,
	WALL_TEMPERATURE,
	EQUILIBRIUM_RADIUS,
	DRIVER_PRESSURE,
	FREQUENCY,
	INITIAL_TIME,
	INITIAL_RADIUS,
	INITIAL_VELOCITY,

	// Last Param 
	// (Used for Count of Enum)
	LAST_PARAM = INITIAL_VELOCITY
};
