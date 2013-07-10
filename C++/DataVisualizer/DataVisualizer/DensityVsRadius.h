/// DensityVsRadius.h - Density vs Radius Graph Class Declaration
/// Written By Jesse Z. Zhong
#ifndef __DENSITY_VS_RADIUS_H__
#define __DENSITY_VS_RADIUS_H__

#include "stdafx.h"
#include "Graph.h"
#include "SnapshotData.h"
#include "ProjectSettings.h"

class DensityVsRadiusGraph : public Graph<SnapshotData> {
public:
	// Constructor
	DensityVsRadiusGraph(QWidget* parent = NULL);

private:
	// Abstract Method for Interpreting Snapshot Data
	virtual void ProcessPoints(SnapshotData &snapshotData);
};

#endif