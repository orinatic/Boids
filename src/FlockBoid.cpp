#include "FlockBoid.h"

const float avoid = .2f;
const float velMatch = 0.15f;
const float center = 0.15f;
const float pullConstant = 0.1f;
const float minDistance = 0.4f;
const float maxSteer = .05f;
const float vDistance = 1.0f;

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
		diff = pos - nf[i]->getPos(pos);
		if(diff.abs() < minDistance && diff.abs() > 0){
		  sectionAcc += (diff)*(minDistance - diff.abs())*avoid;
		}
		//cout << "steer acceleration is " << sectionAcc.abs() << endl;
	}
	if((totalAcc + sectionAcc).abs() < maxSteer){
		totalAcc += sectionAcc;
	} else {
		totalAcc += sectionAcc*(maxSteer-totalAcc.abs())/sectionAcc.abs();
	}
	//match velocity
	sectionAcc = (0,0,0);
	for(int i = 0; i<nf.size(); i++){
		//vel.print();
		diff = vel - nf[i]->getVel();
		if(diff.abs() != 0 && (pos-nf[i]->getPos()).abs() < vDistance){
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
		diff = pos - nf[i]->getPos(pos);		
		if(diff.abs() < vDistance){
			sectionAcc += -diff*center/(nf.size()-1);
		}
	}
	if((totalAcc + sectionAcc).abs() < maxSteer){
		totalAcc += sectionAcc;
	} else {
		totalAcc += sectionAcc*(maxSteer-totalAcc.abs())/sectionAcc.abs();
	}
	sectionAcc = (0, 0, 0);
	//Steer toward attractors
	for(int i = 0; i < at.size(); i++){
		diff = pos - at[i]->getPos();
		if(diff.abs() < 2*vDistance){
			//cout << " pull = " <<at[i]->getPull()<< endl;
			//cout << " sectionAcc = ";
			sectionAcc += -diff.normalized()*at[i]->getPull()*pullConstant;
			//sectionAcc.print();
			//cout << " diff = ";
			//diff.normalized().print();
			//cout << " pull constant = "<< pullConstant << endl;
		}
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
