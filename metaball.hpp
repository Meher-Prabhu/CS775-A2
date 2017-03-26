#include <math.h>

class MetaBall{
	double effectiveRadius;

public:
	MetaBall(double radius){
		effectiveRadius = radius;
	}
	~MetaBall();
	
	double getEffectiveRadius(){ return effectiveRadius;}
	void setEffectiveRadius(double radius){effectiveRadius = radius;}
	double getNormalizationConstant(){ return (748.0/405.0)*M_PI*effectiveRadius; }
	double getFunctionValue(double radius){
		double a = radius/effectiveRadius;
		if(radius<=effectiveRadius)
			return (-(4.0/9.0)*pow(a,6) + (17.0/9.0)*pow(a,4) - (22.0/9.0)*pow(a,2) + 1.0)/getNormalizationConstant;
		else
			return 0.0;
	}
}