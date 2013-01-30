/// WallRadiusVsTime.h - Wall Radius vs Time Graph Class Declaration
/// Written By Jesse Z. Zhong

#ifndef __WALL_RADIUS_VS_TIME_H__
#define __WALL_RADIUS_VS_TIME_H__

#include "stdafx.h"
#include "Graph.h"
#include "RPK.h"

// Wall Radius versus Time Graph
class WallRadiusVsTimeGraph : public Graph<vector<RPKStruct> > {
public:
	// Constructor
	WallRadiusVsTimeGraph(QWidget* parent = NULL);

private:
	// Abstract Method for Interpreting Snapshot Data
	virtual void ProcessPoints(vector<RPKStruct>& RPKData);
};

#endif