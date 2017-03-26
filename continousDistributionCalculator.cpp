#include "continousDistributionCalculator.hpp"
using namespace std;

double ContinousGrid::getDensityAtPoint(double x,double y,double z,double t){
	int minT = floor(t);
	int maxT = ceil(t);
	double minX = floor(x - effectiveRadius) - 0.5;
	double maxX = floor(x + effectiveRadius) + 0.5;
	double minY = floor(y - effectiveRadius) - 0.5;
	double maxY = floor(y + effectiveRadius) + 0.5;
	double minZ = floor(z - effectiveRadius) - 0.5;
	double maxZ = floor(z + effectiveRadius) + 0.5;
	double densityValue1 = 0;
	double densityValue2 = 0;
	MetaBall metaball(effectiveRadius);
	for(int i = 0; i <= maxX - minX; i++){
		double currX = minX + i;
		for(int j = 0; j <= maxY - minY; j++){
			double currY = minY + j;
			for(int k = 0; k <= maxZ - minZ; k++){
				double currZ = minZ + k;
				densityValue1 += (voxels[floor(currX)][floor(currY)][floor(currZ)][minT]) * 
								(metaball.getFunctionValue(distance(currX,currY,currZ,x,y,z)));
				densityValue2 += (voxels[floor(currX)][floor(currY)][floor(currZ)][maxT]) * 
								(metaball.getFunctionValue(distance(currX,currY,currZ,x,y,z)));
			}
		}
	}
	if(minT!=maxT)
		return (t - minT)*densityValue2 + (maxT - t)*densityValue1;
	else
		return densityValue1;
}

ContinousGrid continousDistributionCalculator::discreetToContinous(Simulation sim){
	ContinousGrid grid(sim.getXDimension(),sim.getYDimension(),sim.getZDimension(),sim.getTimeSteps());
	for(int i = 0;i < sim.getXDimension();i++){
		for(int j = 0;j < sim.getYDimension();j++){
			for(int k = 0;k < sim.getZDimension();k++){
				for(int t = 0;t< sim.getTimeSteps();t++){
					double value = 0;
					for(int ni = -smoothSizeX; ni < 2*smoothSizeX + 1; ni++){
						if(ni + i >= 0 && ni + i <= sim.getXDimension()-1){
							for(int nj = -smoothSizeY; nj < 2*smoothSizeY + 1; nj++){
								if(nj + j >= 0 && nj + j <= sim.getYDimension()-1){
									for(int nk = -smoothSizeZ; nk < 2*smoothSizeZ + 1; nk++){
										if(nk + k >= 0 && nk + k <= sim.getZDimension()-1){
											for(int nt = -smoothSizeT; nt < 2*smoothSizeT + 1; nt++){
												if(nt + t >= 0 && nt + t <= sim.getTimeSteps()-1){
													if(sim.getGrid(nt + t).getVoxel(ni + i,nj + j,nk + k))
														value += smoothingWeight[ni][nj][nk][nt];
												}
											}
										}
									}
								}
							}
						}
					}
					grid.setVoxelValue(i,j,k,t,(value)/((2*smoothSizeX + 1)*(2*smoothSizeY + 1)*(2*smoothSizeZ + 1)*(2*smoothSizeT + 1)))
				}
			}
		}
	}

}