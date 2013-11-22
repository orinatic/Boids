#ifndef FLOCKBOIDS_H
#define FLOCKBOIDS_H

#include "AttractorBoids.h"

class FlockBoids: public GenericBoids
{
 public:
	FlockBoids(int numBoids);

	vector<Vector3f> evalF(vector<Vector3f> nearFlockmates, const AttractorBoids attractors);

	void draw();
};

#endif
