#ifndef ATTRACTORBOIDS_H
#define ATTRACTORBOIDS_H

#include "RepulsorBoids.h"

class AttractorBoids: public GenericBoids
{
 public:
	
	//Implementation will ignore nearFlockmates, most likely
	vector<vector3f> evalF(vector<Vector3f> nearFlockmates, const RepulsorBoids& repulsors)
	
	void draw();
	
};
	
#endif
