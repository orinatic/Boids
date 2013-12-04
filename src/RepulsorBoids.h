#ifndef REPULSORBOIDS_H
#define REPULSORBOIDS_H

#include "GenericBoid.h"

class RepulsorBoids: public GenericBoid
{
 public:
	
	/**Implementation will be tricky. The paramters will
	 * likely vary based on individual shape needed
	 **/
	Vector3f evalF(vector<GenericBoid*>& nf, vector<GenericBoid*>& at);
	
	void draw()=0;
};
#endif
