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

void GenericBoid::draw()
{
	GLfloat flockColor[] = {0.0f, 0.5f, 0.5f, 0.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, flockColor);
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	Vector3f voff = vel.normalized() * 0.025f;
	for(int i = 0; i < 10; i++) {
	  float d = (1.0f - i * 0.1f);
	  glColor4f(vel[0] + 0.5f, vel[1] + 0.5f, vel[2] + 0.5f, d);
	  glTranslatef(-voff[0], -voff[1], -voff[2]);
	  glutSolidSphere(0.075f - i * 0.005f,10.0f,10.0f);
	}
	glPopMatrix();
}
