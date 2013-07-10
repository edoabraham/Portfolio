// Vector3.h - Vector 3D Struct Declaration
// Written By Jesse Z. Zhong
#pragma region Includes
#include "stdafx.h"
using namespace std;
#pragma endregion
// 3D Vector Structure
template<typename DATA_TYPE = double>
struct Vector3 {

	// Copy Constructor
	Vector3(const Vector3<DATA_TYPE>& source) {
		X = source.X;
		Y = source.Y;
		Z = source.Z;
	}

	// Hybrid Constructor
	Vector3(DATA_TYPE x = 0, 
		DATA_TYPE y = 0, DATA_TYPE z = 0) {
		X = x;
		Y = y;
		Z = z;
	}

	// The scalar components of a vector.
	DATA_TYPE X, Y, Z;
    
    // Returns a Zeroed Vector
    static Vector3 Zero() {
        return Vector3();
    }

	// Assignment operator overload.
	const Vector3& operator=(const Vector3& source) {
		X = source.X;
		Y = source.Y;
		Z = source.Z;
		return *this;
	}

	// Addition operator overload.
	const Vector3& operator+(const Vector3& operand) {
		X += operand.X;
		Y += operand.Y;
		Z += operand.Z;
		return *this;
	}
    
    // Subtraction operator overload.
    const Vector3& operator-(const Vector3& operand) {
        X -= operand.X;
		Y -= operand.Y;
		Z -= operand.Z;
		return *this;
    }
};

// Out stream operator overload for vector 3D.
template<typename T>
ostream& operator<<(ostream& out, const Vector3<T>& data) {
    out << data.X << ", " << data.Y << ", " << data.Z;
    return out;
}