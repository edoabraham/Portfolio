/// ParticleDataStruct.cpp - Particle Data Structure Method Implementations
/// Written By Jesse Z. Zhong

#include "stdafx.h"
#include "ParticleDataStruct.h"

#ifndef DELIMITERS
#define DELIMITERS " ,\n\0"
#endif

// Constructor
ParticleDataStruct::ParticleDataStruct() {
    Position = Vector3<double>();
    Velocity = Vector3<double>();
}

// Parses a Line of Data for a Particle
ParticleDataStruct& ParticleDataStruct::ParseLine(char* line) {

    // Store in Vector3's
    Position.X = atof(Utilities::TestForNull(strtok(line, DELIMITERS)));
    Position.Y = atof(Utilities::TestForNull(strtok(NULL, DELIMITERS)));
    Position.Z = atof(Utilities::TestForNull(strtok(NULL, DELIMITERS)));
    Velocity.X = atof(Utilities::TestForNull(strtok(NULL, DELIMITERS)));
    Velocity.Y = atof(Utilities::TestForNull(strtok(NULL, DELIMITERS)));
    Velocity.Z = atof(Utilities::TestForNull(strtok(NULL, DELIMITERS)));
    
    ParticleType = atoi(Utilities::TestForNull(strtok(NULL, DELIMITERS)));
    
	return *this;
}

void ParticleDataStruct::Max(ParticleDataStruct& currentMax, const ParticleDataStruct& particleData) {
    
    // Update Max Values
    currentMax.Position.X = (currentMax.Position.X > particleData.Position.X) ? currentMax.Position.X : particleData.Position.X;
    currentMax.Position.Y = (currentMax.Position.Y > particleData.Position.Y) ? currentMax.Position.Y : particleData.Position.Y;
    currentMax.Position.Z = (currentMax.Position.Z > particleData.Position.Z) ? currentMax.Position.Z : particleData.Position.Z;
    
    currentMax.Velocity.X = (currentMax.Velocity.X > particleData.Velocity.X) ? currentMax.Velocity.X : particleData.Velocity.X;
    currentMax.Velocity.Y = (currentMax.Velocity.Y > particleData.Velocity.Y) ? currentMax.Velocity.Y : particleData.Velocity.Y;
    currentMax.Velocity.Z = (currentMax.Velocity.Z > particleData.Velocity.Z) ? currentMax.Velocity.Z : particleData.Velocity.Z;
}

void ParticleDataStruct::Min(ParticleDataStruct& currentMin, const ParticleDataStruct& particleData) {
    
    // Update Min Values
    currentMin.Position.X = (currentMin.Position.X < particleData.Position.X) ? currentMin.Position.X : particleData.Position.X;
    currentMin.Position.Y = (currentMin.Position.Y < particleData.Position.Y) ? currentMin.Position.Y : particleData.Position.Y;
    currentMin.Position.Z = (currentMin.Position.Z < particleData.Position.Z) ? currentMin.Position.Z : particleData.Position.Z;
    
    currentMin.Velocity.X = (currentMin.Velocity.X < particleData.Velocity.X) ? currentMin.Velocity.X : particleData.Velocity.X;
    currentMin.Velocity.Y = (currentMin.Velocity.Y < particleData.Velocity.Y) ? currentMin.Velocity.Y : particleData.Velocity.Y;
    currentMin.Velocity.Z = (currentMin.Velocity.Z < particleData.Velocity.Z) ? currentMin.Velocity.Z : particleData.Velocity.Z;
}

ostream& operator<<(ostream& out, const ParticleDataStruct& particleData) {
    out << particleData.Position.X << ", "
    << particleData.Position.Y << ", "
    << particleData.Position.Z << ", "
    << particleData.Velocity.X << ", "
    << particleData.Velocity.Y << ", "
    << particleData.Velocity.Z << ", "
    << particleData.ParticleType << endl;
    return out;
}