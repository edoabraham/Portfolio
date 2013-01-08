// Collision Detection Written by Jesse
// Assumes most polygons are rectangular

#include <math.h>
#include <stdio.h>

// Structures
/**********************************************************************************/
struct object {
	char* name;
	// Stats go here

	// Collision Details
	int weight;
	int dimensions[4];
	int cntrX, cntrY;
};

static struct object [1024]; // Store Object Data


// Function Prototypes
/**********************************************************************************/



// Rectangular Object Centers
void cntrObject (object* var) {
	// Finds center of edges
	float topLine = abs(var->dimensions[0] - var->dimensions[1]);
	float rightLine = abs(var->dimensions[1] - var->dimensions[2]);
	float bottomLine = abs(var->dimensions[2] - var->dimensions[3]);
	float leftLine = abs(var->dimensions[3] - var->dimensions[4]);

	// Check if truly rectangle
	if(topLine == bottomLine && rightLine == leftLine) {
		var->cntrX = topLine;
		var->cntrY = rightLine;
	} else {
		// Failure returns error message.
		printf("Object %s is not a rectangle. \n", var->name);
	}
}

// Collision Functions
/**********************************************************************************/

// Attacks are objects


// Types of Collisions and Functions
void collideResult () {


}

// Character runs into Monster
bool crashCollide () {

}

bool bounceCollide () {

}

// Ice contact
bool slideCollide () {}