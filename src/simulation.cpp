#include "simulation.hpp"
// #include <stdlib.h>

// Simulate step of each voxel
Voxel Voxel::getNext(bool fact) {
	Voxel result;
	double rnd = ((double) rand() / (RAND_MAX));
	result.humid = humid && !transit;
	result.transit = !transit && humid && fact;
	if(cloud) {
		result.cloud = cloud && (rnd > pExt);
		result.humid = humid || (rnd < pHum);
		result.transit = transit || (rnd < pAct);
	}
	else result.cloud = (cloud || transit);
	return result;
}

// Simulate grid
Grid Grid::getNext() {
	Grid result(sizeX, sizeY, sizeZ, velocity);
	for(int i = 0; i < sizeX; i++) {
		for(int j = 0; j < sizeY; j++) {
			for(int k = 0; k < sizeZ; k++) {
				// cout<<"Cell #"<<i<<","<<j<<","<<k<<endl;
				bool fact;
				if(i+1 < sizeX)	fact = voxels[i+1][j][k].getTransit(); 
				if(j+1 < sizeY) fact = fact || voxels[i][j+1][k].getTransit();
				if(k+1 < sizeZ) fact = fact || voxels[i][j][k+1].getTransit();
				if(i > 0) fact = fact || voxels[i-1][j][k].getTransit();
				if(j > 0) fact = fact || voxels[i][j-1][k].getTransit();
				if(k > 0) fact = fact || voxels[i][j][k-1].getTransit();
				if(i > 1) fact = fact || voxels[i-2][j][k].getTransit();
				if(i+2 < sizeX) fact = fact || voxels[i+2][j][k].getTransit();
				if(j > 1) fact = fact || voxels[i][j-2][k].getTransit();
				if(j+2 < sizeY) fact = fact || voxels[i][j+2][k].getTransit(); 
				if(k > 1) fact = fact || voxels[i][j][k-2].getTransit();
				// cout<<fact<<endl;
				Voxel nextVoxel = voxels[i][j][k].getNext(fact);
				// if(i > velocity) nextVoxel = voxels[i-velocity][j][k];
				// else nextVoxel = Voxel();
				result.voxels[i][j][k] = nextVoxel;

			}
		}
	}
	return result;
}

// Run whole simulation
void Simulation::simulate() {
	for (int i = 0; i < timeSteps; i++) {
		// cout<<"Iteration #"<<i+1<<endl;
		Grid nextGrid = grids[i].getNext();
		grids.push_back(nextGrid);
	}
	return;
}

// int main() {
// 	Grid grid(20,20,20,0);
// 	Simulation sim(10, grid);
// 	sim.simulate();
// 	Grid finGrid = sim.getGrid(10);
// 	for(int i = 0; i < 20; i++) {
// 		for(int j = 0; j < 20; j++) {
// 			cout<<grid.getVoxel(i, j, 0).getCloud()<<" ";
// 		}
// 		cout<<endl;
// 	}
// 	cout<<"Final"<<endl;
// 	for(int i = 0; i < 20; i++) {
// 		for(int j = 0; j < 20; j++) {
// 			cout<<finGrid.getVoxel(i, j, 0).getCloud()<<" ";
// 		}
// 		cout<<endl;
// 	}
// 	return 0;
// }