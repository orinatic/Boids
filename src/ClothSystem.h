#ifndef CLOTHSYSTEM_H
#define CLOTHSYSTEM_H


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include "extra.h"
#include <vector>

#include "particleSystem.h"

class ClothSystem: public ParticleSystem
{
public:
	ClothSystem(int numSide);
	vector<Vector3f> evalF(vector<Vector3f> state);
	
	void draw();
	Vector3f userForce;
	bool moving;
	bool wireframe;
private:
	int side;
	vector<spring> springs;
};


#endif
