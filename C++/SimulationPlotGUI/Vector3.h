/// Vector3.h - Vector 3D Struct Declaration
/// Written By Jesse Z. Zhong

/// 3D Vector Structure
template<typename DATA_TYPE = double>
struct Vector3 {

	// Copy Constructor
	Vector3(const Vector3<DATA_TYPE>& source) {
		X = source.X;
		Y = source.Y;
		Z = source.Y;
	}

	// Hybrid Constructor
	Vector3(DATA_TYPE x = 0, 
		DATA_TYPE y = 0, DATA_TYPE z = 0) {
		X = x;
		Y = y;
		Z = z;
	}

	DATA_TYPE X, Y, Z;
    
    // Returns a Zeroed Vector
    static Vector3 Zero() {
        return Vector3();
    }

	// Basic Operator Overloads

	// Assignment
	const Vector3& operator=(const Vector3& source) {
		X = source.X;
		Y = source.Y;
		Z = source.Z;
		return *this;
	}

	// Addition
	const Vector3& operator+(const Vector3& operand) {
		X += operand.X;
		Y += operand.Y;
		Z += operand.Z;
		return *this;
	}
    
    // Subtraction
    const Vector3& operator-(const Vector3& operand) {
        X -= operand.X;
		Y -= operand.Y;
		Z -= operand.Z;
		return *this;
    }
};