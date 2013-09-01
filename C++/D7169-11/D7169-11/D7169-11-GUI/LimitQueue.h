// LimitQueue.h - Limit Queue template class implementation.
// Written By Jesse Z. Zhong
#ifndef __LimitQueue_H__
#define __LimitQueue_H__
#pragma region Includes
#include "stdafx.h"
#include <queue>
using namespace std;
#pragma endregion
#pragma region Constants
const int DefaultQueueLimit = 10;
#pragma endregion
#pragma region Queue Delegates
template<class T>
typedef void (*DequeMethod)(const T&);
#pragma endregion
// Extends the standard queue class to
// include a limit to the number of entries.
template<class T>
class LimitQueue : public queue<T> {
public:
	// Default Constructor
	LimitQueue() {
		this->Limit_ = DefaultQueueLimit;
		this->DequeMethod = NULL;
	}

	// Hybrid Constructor
	LimitQueue(DequeMethod method, int limit = DefaultQueueLimit) : queue<T> {
		if(limit > 0)
			this->Limit_ = limit;
		else {
			throw "LimitQueue: Limit must be a positive number.";
			this->Limit_ = DefaultQueueLimit;
		}
		this->DequeMethod_ = method;
	}

	// Destructor
	~LimitQueue() {

	}

	// Adds a new item to the queue
	// while respecting the queue limit.
	void push(const T& item) {

		// Enqueue new item into the queue.
		base.push(item);

		// Dequeue all entries that exceed the limit.
		if(this->DequeMethod_ != NULL) {
			while(this->size() > DefaultQueueLimit) {
				this->DequeMethod_(this->front());
				this->pop();
			}
		}
	}

	// Assign a deque method to the queue.
	void AssignDeque(DequeMethod method) {
		this->DequeMethod_ = method;
	}

private:
	// The largest size the queue can expand to.
	int Limit_;

	// Reference to the method for safely
	// removing elements from the queue.
	DequeMethod DequeMethod_;
};

#endif // End : __LimitQueue_H__