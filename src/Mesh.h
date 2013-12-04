#ifndef MESH_H
#define MESH_H

#include <vector>
#include <vecmath.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "extra.h"

class Tuple3u
{
 public:
  Tuple3u() {};
  Tuple3u(unsigned a, unsigned b, unsigned c) {
    elements[0] = a;
    elements[1] = b;
    elements[2] = c;
  }
	unsigned& operator [] (int i)
	{
		return elements[i];
	}
 private:
	unsigned elements[3];
};

struct Mesh
{
	std::vector< Vector3f > vertices;

	std::vector< Tuple3u > faces;

	void load(const char *filename, const int numBoids, const float vDistance);
};

#endif
