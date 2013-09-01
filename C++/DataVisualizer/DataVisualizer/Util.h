// Util.h - Util Class Declaration.
// Written By Jesse Z. Zhong
#ifndef __Util_h__
#define __Util_h__
#include "stdafx.h"

using namespace std;

// List of useful functions.
namespace Util {

	// Golden Ratio
	const double PHI = 1.6180339887;

	// Pi
	const double PI = 3.14159265359;

	// Prints a message in debug mode.
	static inline void Print(string message) {
#ifdef _DEBUG
		cout << message << endl;
#endif
	}

	// Check if a point's x component is within bounds.
	inline bool CheckBoundariesX(const QPoint& point, const QRect& rectangle) {

		// Localize data.
		int width = rectangle.width();
		int pointX = point.x();
		int rectX = rectangle.x();

		// Create an instance of a bound test result.
		return (width < 0) ? ((pointX < rectX) && (pointX >= width)) 
			: ((pointX >= rectX) && (pointX <= width));
	}

	// Check if a point's y component is within bounds.
	inline bool CheckBoundariesY(const QPoint& point, const QRect& rectangle) {

		// Localize data.
		int height = rectangle.height();
		int pointY = point.y();
		int rectY = rectangle.y();

		// Create an instance of a bound test result.
		return (height < 0) ? ((pointY < rectY) && (pointY >= height)) 
			: ((pointY >= rectY) && (pointY <= height));
	}

	// Method used to check if a point is within a certain rectangle's area.
	inline bool CheckBoundaries(const QPoint& point, const QRect& rectangle) {
		return CheckBoundariesX(point, rectangle) && CheckBoundariesY(point, rectangle);
	}

	// Method used to check if a point is within a certain rectangle's area
	// and correct it if it exceeds any of the boundaries of the rectangle.
	inline QPoint& CheckPoint(const QPoint& point, const QRect& rectangle) {

		// Create a copy of the point.
		QPoint* newPoint = new QPoint(point);

		// Check along the x axis.
		if(point.x() < rectangle.x())
			newPoint->setX(rectangle.x());
		else {
			int upperBound = 0;
			if(point.x() > (upperBound = (rectangle.x() + rectangle.width())))
				newPoint->setX(upperBound);
		}

		// Check along the y axis.
		if(point.y() < rectangle.y())
			newPoint->setY(rectangle.y());
		else {
			int upperBound = 0;
			if(point.y() > (upperBound = (rectangle.y() + rectangle.height())))
				newPoint->setY(upperBound);
		}

		// Return the copy.
		return *newPoint;
	}
}

#endif // End: Util