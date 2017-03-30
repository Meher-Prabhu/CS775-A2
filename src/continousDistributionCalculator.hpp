#include <iostream>
#include <vector>
#include <math.h>
#include "simulation.hpp"
using namespace std;

class ContinousGrid {
	int sizeX,sizeY,sizeZ,sizeT;
	double effectiveRadius;
	vector<vector<vector<vector<double> > > > voxels;
	double distance(double x1,double y1,double z1,double x2,double y2,double z2){
		return sqrt(pow((x2-x1),2) + pow((y2-y1),2) + pow((z2-z1),2)) ;
	}

public:
	ContinousGrid(int x, int y, int z, int t){
		sizeX = x;
		sizeY = y;
		sizeZ = z;
		sizeT = t;
		voxels.resize(sizeX);
		for(int i = 0; i < sizeX ; i++) {
			voxels[i].resize(sizeY );
			for(int j = 0; j < sizeY; j++) {
				voxels[i][j].resize(sizeZ);
				for(int k = 0; k < sizeZ ; k++){
					voxels[i][j][k].resize(sizeT);
				}
			}
		}
	}

	~ContinousGrid(){}

	int getSizeX(){ return sizeX;}
	int getSizeY(){ return sizeY;}
	int getSizeZ(){ return sizeZ;}
	int getSizeT(){ return sizeT;}
	int getEffectiveRadius(){ return effectiveRadius;}

	void setSizeX(int size){sizeX = size;}
	void setSizeY(int size){sizeY = size;}
	void setSizeZ(int size){sizeZ = size;}
	void setSizeT(int size){sizeT = size;}
	void setEffectiveRadius(double value){effectiveRadius = value;}

	double getVoxelValue(int x,int y,int z,int t){ return voxels[x][y][z][t];}
	void setVoxelValue(int x,int y,int z,int t,double value){ voxels[x][y][z][t] = value;}

	double getDensityAtPoint(double x,double y,double z,double t);
};

class ContinousDistributionCalculator {
	int vecSizeX,vecSizeY,vecSizeZ,vecSizeT;
	int smoothSizeX,smoothSizeY,smoothSizeZ,smoothSizeT;
	vector< vector< vector< vector<double> > > > smoothingWeight;
public:
	ContinousDistributionCalculator(){

		smoothSizeX = 2;
		smoothSizeY = 2;
		smoothSizeZ = 2;
		smoothSizeT = 1;
		vecSizeX = 3;
		vecSizeY = 3;
		vecSizeZ = 3;
		vecSizeT = 2;
		smoothingWeight.resize(smoothSizeX+1);
		for(int i = 0; i < smoothSizeX+1; i++) {
			smoothingWeight[i].resize(smoothSizeY+1);
			for(int j = 0; j < smoothSizeY+1; j++) {
				smoothingWeight[i][j].resize(smoothSizeZ+1);
				for(int k = 0; k < smoothSizeZ+1; k++){
					smoothingWeight[i][j][k].resize(smoothSizeT+1);
				}
			}
		}
	}
	ContinousDistributionCalculator(int x,int y,int z, int t){
		smoothSizeX = x;
		smoothSizeY = y;
		smoothSizeZ = z;
		smoothSizeT = t;
		vecSizeX = x+1;
		vecSizeY = y+1;
		vecSizeZ = z+1;
		vecSizeT = t+1;
		smoothingWeight.resize(smoothSizeX+1);
		for(int i = 0; i < smoothSizeX+1; i++) {
			smoothingWeight[i].resize(smoothSizeY+1);
			for(int j = 0; j < smoothSizeY+1; j++) {
				smoothingWeight[i][j].resize(smoothSizeZ+1);
				for(int k = 0; k < smoothSizeZ+1; k++){
					smoothingWeight[i][j][k].resize(smoothSizeT+1);
				}
			}
		}
	}
	ContinousDistributionCalculator(int x,int y,int z, int t,vector< vector< vector< vector<double> > > > weights){
		smoothSizeX = x;
		smoothSizeY = y;
		smoothSizeZ = z;
		smoothSizeT = t;
		vecSizeX = x+1;
		vecSizeY = y+1;
		vecSizeZ = z+1;
		vecSizeT = t+1;
		smoothingWeight = weights;
	}

	~ContinousDistributionCalculator(){}

	int getSmoothSizeX(){ return smoothSizeX;}
	int getSmoothSizeY(){ return smoothSizeY;}
	int getSmoothSizeZ(){ return smoothSizeZ;}
	int getSmoothSizeT(){ return smoothSizeT;}

	void setSmoothSizeX(int size){smoothSizeX = size;}
	void setSmoothSizeY(int size){smoothSizeY = size;}
	void setSmoothSizeZ(int size){smoothSizeZ = size;}
	void setSmoothSizeT(int size){smoothSizeT = size;}

	double getSmoothingWeight(int x,int y,int z,int t){
		if(x < smoothSizeX && y < smoothSizeY && z < smoothSizeZ && t < smoothSizeT && x >= 0 && y >= 0 && z >= 0 && t >= 0) return smoothingWeight[x][y][z][t];
		else return smoothingWeight[0][0][0][0];
	}

	void setSmoothingWeight(int x,int y,int z,int t,double value){
		if(x < smoothSizeX && y < smoothSizeY && z < smoothSizeZ && t < smoothSizeT && x >= 0 && y >= 0 && z >= 0 && t >= 0) smoothingWeight[x][y][z][t] = value;	
	}

	ContinousGrid discreetToContinous(Simulation sim);


};