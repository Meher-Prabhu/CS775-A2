#include <iostream>
#include <vector>
using namespace std;

class Voxel {
	bool cloud, humid, transit; // Cloud, humid and transition variables for each voxel.

	public:
		Voxel() { cloud = humid = transit = false; }

		Voxel(bool cloud, bool humid, bool transit) {
			this->cloud = cloud;
			this->humid = humid;
			this->transit = transit;
		}

		~Voxel() {}

		bool getCloud() { return cloud; }

		void setCloud(bool value) {	cloud = value;	}

		bool getHumid() { return humid; }

		void setHumid(bool value) { humid = value; }

		bool getTransit() { return transit; }

		void setTransit(bool value) { transit = value; }

		Voxel getNext(bool fact);
};

class Grid {
	int sizeX, sizeY, sizeZ;
	vector< vector< vector<Voxel> > > voxels;

	public:
		Grid(int sx, int sy, int sz) {
			sizeX = sx;
			sizeY = sy;
			sizeZ = sz;
			voxels.resize(sx);
			for(int i = 0; i < sx; i++) {
				voxels[i].resize(sy);
				for(int j = 0; j < sy; j++) {
					voxels[i][j].resize(sz);
				}
			}
		}

		Grid(const Grid& grid) {
			this->sizeX = grid.sizeX;
			this->sizeY = grid.sizeY;
			this->sizeZ = grid.sizeZ;
			this->voxels = grid.voxels;
		}

		~Grid() {}

		int getXDimension() { return sizeX; }

		int getYDimension() { return sizeY; }

		int getZDimension() { return sizeZ; }

		int setXDimension(int sx) { sizeX = sx; }

		int setYDimension(int sy) { sizeY = sy; }

		int setZDimension(int sz) { sizeX = sz; }

		Voxel getVoxel(int x, int y, int z) { 
			if(x < sizeX && y < sizeY && z < sizeZ && x >= 0 && y >= 0 && z >= 0) return voxels[x][y][z]; 
		}

		void setVoxel(int x, int y, int z, Voxel voxel) { 
			if(x < sizeX && y < sizeY && z < sizeZ && x >= 0 && y >= 0 && z >= 0) voxels[x][y][z] = voxel; 
		}

		Grid getNext();
};

class Simulation {
	int timeSteps;
	vector<Grid> grids;

	public:
		Simulation(int time) { timeSteps = time; }

		Simulation(int time, Grid grid) { 
			timeSteps = time;
			grids.push_back(grid); 
		}

		~Simulation() {}

		Grid getGrid(int time) { return grids[time]; }

		void setGrid(int time, Grid grid) { grids[time] = grid; }

		int getTimeSteps() { return timeSteps; }

		void setTimeSteps(int time) { timeSteps = time; }

		int nSteps() { return grids.size(); }

		void simulate();
};