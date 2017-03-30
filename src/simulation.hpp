#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

class Voxel {
	bool cloud, humid, transit; // Cloud, humid and transition variables for each voxel.
	float pExt, pHum, pAct;

	public:
		Voxel() { 
			// cout<<"Here"<<endl;
			cloud = false;
			double rnd1 = ((double) rand() / (RAND_MAX));
			double rnd2 = ((double) rand() / (RAND_MAX));
			// cout<<rnd1<<" "<<rnd2<<endl;
			humid = (rnd1 > 0.5) ? true:false;
			transit = (rnd2 > 0.5) ? true:false;
			// cout<<humid<<" "<<transit<<endl;
			pExt = pHum = pAct = 0.5; 
		}

		Voxel(bool cloud, bool humid, bool transit, float pExt, float pHum, float pAct) {
			this->cloud = cloud;
			this->humid = humid;
			this->transit = transit;
			this->pExt = pExt;
			this->pHum = pHum;
			this->pAct = pAct;
		}

		~Voxel() {}

		bool getCloud() { return cloud; }

		void setCloud(bool value) {	cloud = value;	}

		bool getHumid() { return humid; }

		void setHumid(bool value) { humid = value; }

		bool getTransit() { return transit; }

		void setTransit(bool value) { transit = value; }

		float getPExt() { return pExt; }

		void setPExt(float value) { pExt = value; }

		float getPHum() { return pHum; }

		void setPHum(float value) { pHum = value; }

		float getPAct() { return pAct; }

		void setPAct(float value) { pAct = value; }

		Voxel getNext(bool fact);
};

class Grid {
	int sizeX, sizeY, sizeZ;
	vector< vector< vector<Voxel> > > voxels;
	float velocity;

	public:
		Grid(int sx, int sy, int sz, int vel) {
			sizeX = sx;
			sizeY = sy;
			sizeZ = sz;
			voxels.resize(sx);
			for(int i = 0; i < sx; i++) {
				voxels[i].resize(sy);
				for(int j = 0; j < sy; j++) {
					voxels[i][j].resize(sz);
					// for(int k = 0; k < sz; k++) {
					// 	voxels[i][j][k] = Voxel();
					// }
				}
			}
			velocity = vel;
			for(int i = 0; i < 20; i++) {
				for(int j = 0; j < 20; j++) {
					// cout<<voxels[i][j][0].getHumid()<<" ";
				}
				// cout<<endl;
			}
		}

		Grid(const Grid& grid) {
			this->sizeX = grid.sizeX;
			this->sizeY = grid.sizeY;
			this->sizeZ = grid.sizeZ;
			this->velocity = grid.velocity;
			this->voxels = grid.voxels;
		}

		~Grid() {}

		int getXDimension() { return sizeX; }

		int getYDimension() { return sizeY; }

		int getZDimension() { return sizeZ; }

		void setXDimension(int sx) { sizeX = sx; }

		void setYDimension(int sy) { sizeY = sy; }

		void setZDimension(int sz) { sizeX = sz; }

		Voxel getVoxel(int x, int y, int z) { 
			if(x < sizeX && y < sizeY && z < sizeZ && x >= 0 && y >= 0 && z >= 0) return voxels[x][y][z];
			else return voxels[0][0][0];
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
			cout<<grids.size()<<endl; 
		}

		~Simulation() {}

		Grid getGrid(int time) { return grids[time]; }

		void setGrid(int time, Grid grid) { grids[time] = grid; }

		int getXDimension() { if(grids.size() > 0 )return grids[0].getXDimension(); else return 0; }

		int getYDimension() { if(grids.size() > 0 )return grids[0].getYDimension(); else return 0; }

		int getZDimension() { if(grids.size() > 0 )return grids[0].getZDimension(); else return 0; }

		int getTimeSteps() { return timeSteps; }

		void setTimeSteps(int time) { timeSteps = time; }

		int nSteps() { return grids.size(); }

		void simulate();
};