#ifndef REPULSORBOIDS_H
#define REPULSORBOIDS_H

#include "GenericBoids.h"

class RepulsorBoids: public GenericBoids
{
 public:
	
	/**Implementation will be tricky. The paramters will
	 * likely vary based on individual shape needed
	 **/
	vector<vector3f> evalF(vector<Vector3f> nearFlockmates, const RepulsorBoids& repulsors)
	
	void draw();
};
#endif
