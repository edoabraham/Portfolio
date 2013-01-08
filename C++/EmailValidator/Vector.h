/// Vector.h - Template Vector Class Declaration
/// Written By Jesse Z. Zhong

#pragma once

#include <iostream>
#include <sstream>
#include <string>

// Defines the Initial Capacity of All Vector Instances
#define INITIAL_CAPACITY 10

// Defines How Large of a Linear Increase
// in Capacity will Occur, when the Size Reaches
// its Max Capacity
#define CAPACITY_BOOST 10

/// Vector Class Container Implementation
template<typename DATA_TYPE>
class Vector {
public:
	// Default/Init Constructor, Creates a Zero-Size Vector that can
	// Store Non-Zero Capacity of Elements
	Vector(int initialCapacity = INITIAL_CAPACITY) {
		Size_ = 0;
		Capacity_ = initialCapacity;
		Data_ = new DATA_TYPE[Capacity_];
	}

	// Copy-Constructor
	Vector(const Vector& source) {

		// Initially, the Data Pointer is Set to Some Garbage Address,
		// which will Cause Delete Statement in the Assignment Operator
		// to Crash. So We Reset the Data Pointer to NULL to Prevent the
		// Delete Estimate in the = Assignment Operator
		Data_ = NULL;
		*this = source;
	}

	// Destructor
	~Vector() {
		delete[] Data_;
	}

	// Assignment Operator, Performs Deep Copy
	Vector& operator = (const Vector& source) {

		// Dispose the Old Memory
		delete[] Data_;

		// Declare a New Data_ with the Sources Capacity
		Data_ = new DATA_TYPE[source.GetCapacity()];

		// Allocate Data to Match the Size of Source Capacity
		this->Capacity_ = source.GetCapacity();

		// Copy All Array Elements from Source Data into This Data
		for(int i = 0, j = source.GetSize(); i < j; i++)
			Data_[i] = source[i];

		// Copy Size and Capacity
		this->Size_ = source.GetSize();
		this->Capacity_ = source.GetCapacity();

		// Return the Result
		return *this;
	}

	// Index Operator
	DATA_TYPE& operator[](int index) const {

		// Check if the index Looked Up is within Bounds
		CheckBounds(index, "operator[](int index)");

		// Pass the Element
		return Data_[index];
	}

	// Adds a New Element at the End of the Vector
	void Add(const DATA_TYPE& value) {
		
		// Add New Value at the End
		Insert(value, Size_);
	}

	// Inserts the Value into this Vector at a Specified Index
	// Moves the Tail to the Right to Accommodate the New Element
	void Insert(const DATA_TYPE& source, int index) {

		// Expand Size
		Size_++;

		// Check Bounds
		CheckBounds(index, "Insert(const DATA_TYPE& value, int index)");

		// If the Capacity is Not Large Enough then Reallocate
		if(Size_ >= Capacity_) {

			// Increase the Capacity
			Capacity_ += CAPACITY_BOOST;

			// Allocate New Larger C-Array
			DATA_TYPE* newData = new DATA_TYPE[Capacity_];

			// Copy Elements from Data to newData
			for(int i = 0; i < Size_; i++) 
				newData[i] = Data_[i];

			// Delete Old Data
			delete[] Data_;

			// Replace the Pointer to the Deleted Old Data with the Pointer newData
			Data_ = newData;
		}

		// If it's Following the Last Element then Skip Shifting
		if(index == Size_ - 1);
		else {
			// Shift Elements Forward
			for(int i = Size_; i >= index; i--)
				SwapElements(i, (i + 1));
		}
		
		// Add New Data at Index
		Data_[index] = source;
	}

	// Inserts New Element by Expanding the Size and 
	// Inserting the New Value at the End of the Array
	void PushBack(const DATA_TYPE& source) {

		// Inserting at the End
		Insert(source, Size_);
	}

	// Removes an Element at the Specified Index by Moving the Tail 
	// to the Left
	void Remove(int index) {

		// Check Bounds
		CheckBounds(index, "Remove(int index");

		// If it's the Last Element then Skip Shifting
		if(index == (Size_ - 1));
		else {
			// Shift Elements Back
			for(int i = index, j = (Size_ - 1); i < j; i++)
				SwapElements(i, (i + 1));
		}

		// Remove Last Data Point
		if((Size_ - 1) > 0) Size_--;
		else {
			std::string e = "Vector::Remove - Size is attempting to go out of legal bounds; Size cannot be negative";
			throw e;
		}

		// If the Capacity Far Exceeds the Necessary Size then Reallocate
		if(Capacity_ >= (Size_ + CAPACITY_BOOST)) {

			// Decrease the Capacity
			Capacity_ -= CAPACITY_BOOST;

			// Allocate New Smaller C-Array
			DATA_TYPE* newData = new DATA_TYPE[Capacity_];

			// Copy Elements from Data to newData
			for(int i = 0; i < Size_; i++) 
				newData[i] = Data_[i];

			// Delete Old Data
			delete[] Data_;

			// Replace the Pointer to the Deleted Old Data with the Pointer newData
			Data_ = newData;
		}
	}

	// Shrink the Size and Possibly the Capacity
	void Shrink() {

		// Remove Last Element
		Remove(Size_ - 1);
	}

	// Get-Accessors to Provide Read-Only Access to Size and Capacity
	int GetSize() const {
		return Size_;
	}
	int GetCapacity() const {
		return Capacity_;
	}

private:
	// Checks if Passed Index Falls within Bounds of the Array
	// Throw and Exception if it is Not within Bounds
	void CheckBounds(int index, char* source) const {
		if((index < 0) || (index >= Size_)) {
			std::stringstream error;
			error << "Vector::" << source << " - Index " << index << " is out of bounds (0.." << (Size_ - 1) << ")";
			string errorMessage = error.str().c_str();
			throw errorMessage;
		}
	}

	// Simple Swap Function for Swapping Two Elements
	void SwapElements(int sourceIndex, int targetIndex) {
		
		// Temporary Storage of Target Element
		DATA_TYPE temp = Data_[targetIndex];

		// Target Element Receives Source Element
		Data_[targetIndex] = Data_[sourceIndex];

		// Source Receives Target Original Element
		Data_[sourceIndex] = temp;
	}

	// Pointer Representing the Encapsulated C-Array
	DATA_TYPE* Data_;

	// Size is the Count of the Elements in the C-Array are Actually Used
	int Size_;

	// Capacity is the Total COunt of Allocated Elements in the Data C-Array
	int Capacity_;
};

template<typename DATA_TYPE>
std::ostream& operator << (std::ostream& out, const Vector<DATA_TYPE>& myVector) {

	// Bracket
	out << "{ ";

	// Write a For-Loop to Print All Vector Elements
	for(int i = 0, j = (myVector.GetSize() - 1); i < j; i++)
		out << myVector[i] << ", ";

	// Last Element and Bracket
	out << myVector[myVector.GetSize() - 1] << " }";

	return out;
}