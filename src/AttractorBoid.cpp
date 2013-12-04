#include "AttractorBoid.h"

const float avoid = .2f;
const float velMatch = 0.1f;
const float center = 0.1f;
const float minDistance = 0.4f;
const float maxSteer = .3f;
const float vDistance = 1.0f;

AttractorBoid::AttractorBoid(Vector3f position, Vector3f velocity, float pull) : GenericBoid(position, velocity){
	pos = position;
	vel = velocity;
	AttractorBoid::pull = pull;
	isDraw = true;
}

Vector3f AttractorBoid::evalF(vector<AttractorBoid*>& nf, vector<AttractorBoid*>& at){
	return (0,0,0);
}

void AttractorBoid::toggleDraw()
{
	isDraw = !isDraw;
}

void AttractorBoid::draw()
{
	GLfloat attractorColor[] = {-pull, pull, 0.0f, 0.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, attractorColor);
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	if(isDraw){
		glutSolidSphere(0.075f,10.0f,10.0f);
	}
	glPopMatrix();
}
