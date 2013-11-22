#ifndef GENERICBOID_H
#define GENERICBOID_H

#include <vector>
#include <vecmath.h>

using namespace std;

class GenericBoid
{
 public:
	GenericBoid(int numBoids = 0);
	
	int numBoids;

	virtual vector<Vector3f> evalF(vector<Vector3f> nearFlockmates, const GenericBoid&  attractors) = 0;

	vector<vector3f> getState(){return state;};

	void setState(const vector<Vector3f> & newState){state = newState;};

	virtual void draw() = 0;
 
 protected:
	vector<Vector3f> state;
	vector<float> pulls;
};

#endif
