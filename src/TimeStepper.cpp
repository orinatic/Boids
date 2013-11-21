#include "TimeStepper.h"

///TODO: implement Explicit Euler time integrator here
void ForwardEuler::takeStep(ParticleSystem* particleSystem, float stepSize)
{
	vector<Vector3f> X = particleSystem->getState();
	vector<Vector3f> f = particleSystem->evalF(X);
	vector<Vector3f> nX;
	for(int i = 0; i < X.size(); i++) {
		nX.push_back(X[i] + stepSize * f[i]);
	}
	particleSystem->setState(nX);
}

///TODO: implement Trapzoidal rule here
void Trapzoidal::takeStep(ParticleSystem* particleSystem, float stepSize)
{
	vector<Vector3f> X = particleSystem->getState();
	vector<Vector3f> f = particleSystem->evalF(X);
	vector<Vector3f> nX;
	for(int i = 0; i < X.size(); i++) {
		nX.push_back(X[i] + stepSize * f[i]);
	}
	vector<Vector3f> fp = particleSystem->evalF(nX);
	nX.clear();
	for(int i = 0; i < X.size(); i++) {
		nX.push_back(X[i] + stepSize / 2 * (f[i] + fp[i]));
	}
	particleSystem->setState(nX);
}
