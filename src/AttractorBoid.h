#ifndef ATTRACTORBOID_H
#define ATTRACTORBOID_H

#include "RepulsorBoids.h"

class AttractorBoid: public GenericBoid
{
 public:
	
	//Implementation will ignore nearFlockmates, most likely
	Vector3f evalF(vector<GenericBoid*>& nf, vector<GenericBoid*>& at);
	
	void draw();
	
};
	
#endif
