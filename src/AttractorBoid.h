#ifndef ATTRACTORBOID_H
#define ATTRACTORBOID_H

#include "GenericBoid.h"

class AttractorBoid: public GenericBoid
{
 public:
	AttractorBoid(Vector3f position, Vector3f velocity, float pull);

	//Implementation will ignore nearFlockmates, most likely
	Vector3f evalF(vector<AttractorBoid*>& nf, vector<AttractorBoid*>& at);
	
	void draw();
	
};
	
#endif
