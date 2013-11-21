
#include "pendulumSystem.h"

const float m = 10.0f;
const float G = -9.8f;
const float kDrag = 10.1f;
const float restLength = 1.0f;
const float kSpring = 810.75f;

PendulumSystem::PendulumSystem(int numParticles):ParticleSystem(numParticles)
{
	m_numParticles = numParticles;

	// fill in code for initializing the state based on the number of particles
	for (int i = 0; i < m_numParticles; i++) {
		m_vVecState.push_back(Vector3f(restLength * i, 0.0f, 0.0f));
		m_vVecState.push_back(Vector3f());
		if(i > 0)
			springs.push_back(spring(i - 1, i, kSpring, restLength));
	}
}


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> PendulumSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	for(int i = 0; i < m_numParticles; i++) {
		Vector3f oPos = state[2 * i];
		Vector3f oVel = state[2 * i + 1];

		Vector3f fT = Vector3f();

		// Calculate Gravity
		Vector3f fG = Vector3f(0.0f, m * G, 0.0f);
		fT += fG / m;

		// Calculate Spring
		Vector3f fS = Vector3f();

		for(int j = 0; j < springs.size(); j++) {
			spring s = springs[j];
			Vector3f d = Vector3f(s.l, 0.0f, 0.0f);
			if(s.a == i)
				d = oPos - state[2 * s.b];
			if(s.b == i)
				d = oPos - state[2 * s.a];
			fS += -s.k * (d.abs() - s.l) * d.normalized();
		}

		fT += fS / m;

		// Calculate Drag
		Vector3f fD = -kDrag * oVel;

		fT += fD / m;

		if(i == 0)
			fT = Vector3f();

		f.push_back(oVel);
		f.push_back(fT);
	}

	return f;
}

// render the system (ie draw the particles)
void PendulumSystem::draw()
{
	for (int i = 0; i < m_numParticles; i++) {
		Vector3f pos = m_vVecState[2 * i];
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2]);
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
	}

	glBegin(GL_LINES);
	for(int i = 0; i < springs.size(); i++) {
		Vector3f a = m_vVecState[2 * springs[i].a];
		Vector3f b = m_vVecState[2 * springs[i].b];
		glVertex3f(a[0], a[1], a[2]);
		glVertex3f(b[0], b[1], b[2]);
	}
	glEnd();
}
