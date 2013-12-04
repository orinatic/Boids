#include "GenericBoid.h"
GenericBoid::GenericBoid(Vector3f position, Vector3f velocity){
	pos = position;
	vel = velocity;
}

Vector3f GenericBoid::getPos(Vector3f op) {
	float SIZE = 10;
	Vector3f p = Vector3f();
	for(int c = 0; c < 3; c++) {
		float md = 2 * SIZE;
		for(int i = -1; i <= 1; i++) {
			float dist = abs(op[c] - (pos[c] + i * SIZE));
			if(dist < md) {
				md = dist;
				p[c] = pos[c] + i * SIZE;
			}
		}
	}
	return p;
}
