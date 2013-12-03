#include "FlockBoid.h"

const float m = 1.0f;
const float G = 9.8f;
const float drag = 1.0f;
const float avoid = .5f;
const float velMatch = 0.01f;
const float center = 0.001f;
const float minDistance = 0.6f;
const float maxSteer = .3f;

FlockBoid::FlockBoid(Vector3f position, Vector3f velocity) : GenericBoid(position, velocity){
	pos = position;
	vel = velocity;
	pull = 0;
}
Vector3f FlockBoid::evalF(vector<FlockBoid*>& nf, vector<AttractorBoid*>& at){
	Vector3f sectionAcc = (0,0,0);
	Vector3f totalAcc = (0,0,0);
	Vector3f diff = (0,0,0);
	//avoid nearby flockmates
	for(int i = 0; i < nf.size(); i++){
		diff = pos - nf[i]->getPos();
		if(diff.abs() < minDistance && diff.abs() > 0){
			sectionAcc += (diff)*(minDistance - diff.abs())*avoid;
		}
	}
	if((totalAcc + sectionAcc).abs() < maxSteer){
		totalAcc += sectionAcc;
	} else {
		totalAcc += sectionAcc*(maxSteer-totalAcc.abs())/sectionAcc.abs();
	}
	//match velocity
	sectionAcc = (0,0,0);
	for(int i = 0; i<nf.size(); i++){
		vel.print();
		diff = vel - nf[i]->getVel();
		if(diff.abs() != 0){
			sectionAcc += -diff*velMatch/(nf.size()-1);
		}
	}
	if((totalAcc + sectionAcc).abs() < maxSteer){
		totalAcc += sectionAcc;
	} else {
		totalAcc += sectionAcc*(maxSteer-totalAcc.abs())/sectionAcc.abs();
	}
	sectionAcc = (0,0,0);
	//match center
	for(int i = 0; i < nf.size(); i++){
		diff = pos - nf[i]->getPos();
		sectionAcc += -diff*center/(nf.size()-1);
	}
	if((totalAcc + sectionAcc).abs() < maxSteer){
		totalAcc += sectionAcc;
	} else {
		totalAcc += sectionAcc*(maxSteer-totalAcc.abs())/sectionAcc.abs();
	}
	return (totalAcc);
}

void FlockBoid::draw()
{
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glutSolidSphere(0.075f,10.0f,10.0f);
	glPopMatrix();
}
