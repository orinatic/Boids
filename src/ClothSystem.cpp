#include "ClothSystem.h"

const float m = 10.0f;
const float G = -9.8f;
const float kDrag = 10.1f;
const float restLength = 1.0f;
const float kStructural = 810.75f;
const float kShear = 810.75f;
const float kFlex = 810.75f;

ClothSystem::ClothSystem(int numSide) : ParticleSystem(numSide * numSide)
{
	userForce = Vector3f();
	moving = false;
	wireframe = false;
	side = numSide;
	for(int row = 0; row < numSide; row++) {
		for(int col = 0; col < numSide; col++) {
			m_vVecState.push_back(Vector3f(restLength * (col - numSide / 2), 
										   -restLength * (row - numSide / 2), 0.0f));
			m_vVecState.push_back(Vector3f());
	
			int i = row * numSide + col;
			if(col + 1 < numSide)
				springs.push_back(spring(i, i + 1, kStructural, restLength));
			if(row + 1 < numSide)
				springs.push_back(spring(i, i + numSide, kStructural, restLength));

			if(row > 0 && col + 1 < numSide)
				springs.push_back(spring(i, i + 1 - numSide, kShear, restLength * sqrt(2), false));
			if(row + 1 < numSide && col + 1 < numSide)
				springs.push_back(spring(i, i + 1 + numSide, kShear, restLength * sqrt(2), false));
			
			if(col + 2 < numSide)
				springs.push_back(spring(i, i + 2, kFlex, 2 * restLength, false));
			if(row + 2 < numSide)
				springs.push_back(spring(i, i + 2 * numSide, kFlex, 2 * restLength, false));
			
		}
	}
}

float t = 0.00;

// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> ClothSystem::evalF(vector<Vector3f> state)
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

		// Calculate User Force
		fT += userForce / m;

		if(i == 0 || i == side - 1) {
			if(moving) {
				fT = Vector3f(0.0f, 0.0f, 1 * cos(t));
				t += M_PI / 1000;
			} else {
				fT = Vector3f();
				oVel = Vector3f();
			}
		}

		f.push_back(oVel);
		f.push_back(fT);
	}

	return f;
}

void ClothSystem::draw()
{
	if(wireframe) {
		for (int i = 0; i < m_numParticles; i++) {
			Vector3f pos = m_vVecState[2 * i];
			glPushMatrix();
			glTranslatef(pos[0], pos[1], pos[2]);
			glutSolidSphere(0.075f,10.0f,10.0f);
			glPopMatrix();
		}
		
		for (int i = 0; i < springs.size(); i++) {
			spring s = springs[i];
			if(!s.display)
				continue;
			
			Vector3f a = m_vVecState[2 * s.a];
			Vector3f b = m_vVecState[2 * s.b];
			Vector3f d = b - a;
			
			glPushMatrix();
			glTranslatef(a[0], a[1], a[2]);
			Vector3f z = d.normalized();
			Vector3f y = Vector3f::cross(z, -Vector3f::FORWARD).normalized();
			Vector3f x = Vector3f::cross(y, z).normalized();
			Matrix4f r = Matrix4f(Vector4f(x, 0.0f),
								  Vector4f(y, 0.0f),
								  Vector4f(z, 0.0f),
								  Vector4f(0.0f,0.0f,0.0f,1.0f), true);
			glMultMatrix(r);
			glMultMatrix(Matrix4f::scaling(0.05f, 0.05f, d.abs()));
			glMultMatrix(Matrix4f::translation(0.0f, 0.0f, 0.5f));
			glutSolidCube(1.0f);
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
	} else {
		glBegin(GL_TRIANGLES);
		for(int row = 0; row < side - 1; row++) {
			for(int col = 0; col < side - 1; col++) {
				int i = row * side + col;
				Vector3f p00 = m_vVecState[2 * i];
				Vector3f p01 = m_vVecState[2 * (i + 1)];
				Vector3f p10 = m_vVecState[2 * (i + side)];
				Vector3f p11 = m_vVecState[2 * (i + side + 1)];
				Vector3f pXX = (p00 + p01 + p10 + p11) / 4;

				Vector3f triangles[][3] = {
					{p10, pXX, p00},
					{p00, pXX, p01},
					{p01, pXX, p11},
					{p11, pXX, p10},
				};
				for(int x = 0; x < 4; x++) {
					Vector3f a = triangles[x][0];
					Vector3f b = triangles[x][1];
					Vector3f c = triangles[x][2];
				
					glNormal(-Vector3f::cross(b - a, b - c).normalized());
					glVertex(a);
					glVertex(b);
					glVertex(c);
				}
			}
		}
		glEnd();	
	}
}

