/// IonizationVsRadius.h - Ionization vs Radius Graph Class Declaration
/// Written By Jesse Z. Zhong

#ifndef __IONIZATION_VS_RADIUS_H__
#define __IONIZATION_VS_RADIUS_H__

#include "stdafx.h"
#include "Graph.h"
#include "SnapshotData.h"
#include "ProjectSettings.h"

using namespace std;

// Ionization versus Radius Graph
class IonizationVsRadiusGraph : public Graph<SnapshotData> {
public:
    // Constructor
    IonizationVsRadiusGraph(QWidget* parent = NULL);
    
private:
    // Abstract Method for Interpreting Snapshot Data
	virtual void ProcessPoints(SnapshotData &snapshotData);

};

#endif