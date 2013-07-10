/// TemperatureVsRadius.h - Temperature vs Radius Graph Class Declaration
/// Written By Jesse Z. Zhong

#ifndef __TEMPERATURE_VS_RADIUS_H__
#define __TEMPERATURE_VS_RADIUS_H__

#include "stdafx.h"
#include "Graph.h"
#include "SnapshotData.h"
#include "ProjectSettings.h"

// Temperature versus Radius Graph
class TemperatureVsRadiusGraph : public Graph<SnapshotData> {
public:
	// Constructor
	TemperatureVsRadiusGraph(QWidget* parent = NULL);

private:
	// Abstract Method for Interpreting Snapshot Data
	virtual void ProcessPoints(SnapshotData &snapshotData);
};

#endif