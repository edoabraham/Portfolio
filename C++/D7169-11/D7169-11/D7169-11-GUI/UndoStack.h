// UndoStack.h - Undo Stack template class implementation.
// Written By Jesse Z. Zhong
#ifndef __UndoStack_H__
#define __UndoStack_H__
#pragma region Includes
#include "stdafx.h"
#include <list>
using namespace std;
#pragma endregion
// Object for storing the state
// of a plot data at a certain time.
template<class T>
class UndoState {
public:
	// Constructor
	UndoState(T* owner = NULL) {
		this->Owner_ = owner;
		if(this->Owner_)
			this->State_ = *owner;
	}

	// Restores the an object to its original state.
	virtual void Restore() {
		if(this->Owner_)
			(*this->Owner_) = this->State_;
	}

	// Returns the owner of the state.
	T* GetOwner() const {
		return this->Owner_;
	}

private:
	// The object that owns the state.
	T* Owner_;

	// The previous state of the object.
	T State_;
};

// Container used to store undo commands.
template<class T>
class UndoStack {
public:
#pragma region Instance
	// Init-Constructor
	UndoStack(bool hasLimit = false, 
		int limit = DefaultLimit) {
			this->HasLimit_ = limit;
			this->Limit_ = limit;
			this->Stack_ = list<UndoState<T>>();
	}

	// Destructor
	~UndoStack() {
		
	}

	// Adds a new item to the top of the stack.
	void Push(T* item) {

		// Insert the item at the front of the list.
		this->Stack_.push_front(UndoState<T>(item));

		// Check if a limit is enforced.
		if(this->HasLimit_) {

			// Remove all items that exceed the limit.
			while(this->Stack_.size() > this->Limit_)
				this->Stack_.pop_back();
		}
	}

	// Removes and returns the top of the stack.
	UndoState<T> Pop() {

		// Check if the list is empty.
		if(this->Stack_.empty())
			return UndoState<T>();

		// Localizes the front of the list.
		UndoState<T> front = this->Stack_.front();

		// Remove the item from the front.
		this->Stack_.pop_front();

		// Return the front item.
		return front;
	}

	// Removes all items that match the item passed.
	void RemoveAll(const T* item) {

		// Remove all items with the compare method.
		this->Stack_.remove_if([&](const UndoState<T>& element) {
			return item == element.GetOwner();
		});
	}

#pragma endregion
#pragma region Accessors
	// Indicates whether or not a maximum number
	// of elements is enforced in this instance.
	void SetHasLimit(bool hasLimit) { this->HasLimit_ = hasLimit; }
	bool GetHasLimit() const { return this->HasLimit_; }

	// Maximum number of items that can be stored.
	void SetLimit(int limit) { if(limit > 0) this->Limit_ = limit; }
	bool GetLimit() const { return this->Limit_; }
#pragma endregion
private:
	// Container used to store the stack.
	list<UndoState<T>> Stack_;

	// Maximum number of items that can be stored.
	static const int DefaultLimit = 10;
	int Limit_;

	// Indicates whether or not a maximum number
	// of elements is enforced in this instance.
	bool HasLimit_;
};

#endif // End : __UndoStack_H__