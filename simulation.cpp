#include "simulation.hpp"

// Simulate step of each voxel
Voxel Voxel::getNext(bool fact) {
	Voxel result;
	result.humid = humid && !transit;
	result.cloud = cloud || transit;
	result.transit = !transit && humid && fact;
	return result;
}

// Simulate grid
Grid Grid::getNext() {
	Grid result(sizeX, sizeY, sizeZ);
	return result;
}

// Run whole simulation
void Simulation::simulate() {
	return;
}

int main() {
	return 0;
}