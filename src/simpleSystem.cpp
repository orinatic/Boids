
#include "simpleSystem.h"

using namespace std;

SimpleSystem::SimpleSystem()
	: ParticleSystem(1)
{
	m_vVecState.push_back(Vector3f(1.0f, 0.0f, 0.0f));
}

vector<Vector3f> SimpleSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	for(int i = 0; i < state.size(); i++)
		f.push_back(Vector3f(-state[i].y(), state[i].x(), 0));

	return f;
}

// render the system (ie draw the particles)
void SimpleSystem::draw()
{
	Vector3f pos = m_vVecState[0];
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glutSolidSphere(0.075f,10.0f,10.0f);
	glPopMatrix();
}
