/// ParticleDataStruct.h - Particle Data Structure Declaration
/// Written By Jesse Z. Zhong

#ifndef __PARTICLE_DATA_STRUCT_H__
#define __PARTICLE_DATA_STRUCT_H__

#include "stdafx.h"
#include "Vector3.h"
#include "Utilities.h"

using namespace std;

/// Data of a Given Particle
struct ParticleDataStruct {
    // Constructor
    ParticleDataStruct();

	// Spacial Data
	Vector3<double> Position;
	Vector3<double> Velocity;

	// Index of Element
	int ParticleType;

	// Parses a Line of Data for a Particle
	ParticleDataStruct& ParseLine(char* line);
    
    // Compares Two Particle Data Values and
    // Returns Particle Data of the Greatest Extremes
    static void Max(ParticleDataStruct& currentMax, const ParticleDataStruct& particleData);
    static void Min(ParticleDataStruct& currentMin, const ParticleDataStruct& particleData);
};

ostream& operator<<(ostream& out, const ParticleDataStruct& particleData);

#endif