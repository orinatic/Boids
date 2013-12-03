#ifndef FLOCKBOID_H
#define FLOCKBOID_H

#include "AttractorBoid.h"

class FlockBoid: public GenericBoid
{
 public:
	FlockBoid(Vector3f position, Vector3f velocity);

	Vector3f evalF(vector<FlockBoid*>& nf, vector<AttractorBoid*>& at);

	void draw();
};

#endif
