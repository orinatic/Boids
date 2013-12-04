#ifndef GENERICBOID_H
#define GENERICBOID_H

#include "extra.h"
#include <vector>
#include <vecmath.h>
#include <iostream>

using namespace std;

class GenericBoid
{
 public:
	GenericBoid(Vector3f position, Vector3f velocity);

	Vector3f getPos(){return pos;};
	Vector3f getPos(Vector3f op);
	Vector3f getVel(){return vel;};
	float getPull(){return pull;};

	void setPos(const Vector3f newPos){pos = newPos;};
	void setVel(const Vector3f newVel){vel = newVel;};
	virtual void draw() = 0;
 
 protected:
	Vector3f pos;
	Vector3f vel;
	float pull;
};

#endif
