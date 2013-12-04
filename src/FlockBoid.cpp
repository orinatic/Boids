#include "FlockBoid.h"

const float avoid = .2f;
const float velMatch = 0.15f;
const float center = 0.15f;
const float pullConstant = 0.05f;
const float minDistance = 0.70f;
const float maxSteer = .05f;
float vDistance;;
Vector3f avoidDir;
Vector3f matchVDir;
Vector3f centerDir;
Vector3f attractorDir;

FlockBoid::FlockBoid(Vector3f position, Vector3f velocity, float view) : GenericBoid(position, velocity){
	pos = position;
	vel = velocity;
	pull = 0;
	vDistance = view;
	isForceDraw = false;
}

void FlockBoid::toggleForceDraw()
{
	isForceDraw = !isForceDraw;
}

Vector3f FlockBoid::evalF(vector<FlockBoid*>& nf, vector<AttractorBoid*>& at){
	Vector3f sectionAcc = (0,0,0);
	Vector3f totalAcc = (0,0,0);
	Vector3f diff = (0,0,0);
	int n = 1;
	//avoid nearby flockmates
	for(int i = 0; i < nf.size(); i++){
		diff = pos - nf[i]->getPos(pos);
		if(diff.abs() < minDistance && diff.abs() > 0){
		  sectionAcc += (diff)*(minDistance - diff.abs())*avoid;
		}
		//cout << "steer acceleration is " << sectionAcc.abs() << endl;
	}
	avoidDir = sectionAcc.normalized() / 10.0f;
	
	if((totalAcc + sectionAcc).abs() < maxSteer||sectionAcc.abs()<0.001){
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
			sectionAcc += -diff*velMatch;
			n++;
		}
	}
	sectionAcc = sectionAcc/n;
	matchVDir = sectionAcc.normalized() / 10.0f;
	if((totalAcc + sectionAcc).abs() < maxSteer||sectionAcc.abs()<0.001){
		totalAcc += sectionAcc;
	} else {
		totalAcc += sectionAcc*(maxSteer-totalAcc.abs())/sectionAcc.abs();
	}
	sectionAcc = (0,0,0);
	n = 1;
	//match center
	for(int i = 0; i < nf.size(); i++){
		diff = pos - nf[i]->getPos(pos);		
		if(diff.abs() < vDistance){
			sectionAcc += -diff*center;
			n++;
		}
	}
	sectionAcc = sectionAcc/n;
	centerDir = sectionAcc.normalized() / 10.0f;
	if((totalAcc + sectionAcc).abs() < maxSteer||sectionAcc.abs() < 0.001){
		totalAcc += sectionAcc;
	} else {
		totalAcc += sectionAcc*(maxSteer-totalAcc.abs())/sectionAcc.abs();
	}
	sectionAcc = (0, 0, 0);
	n = 1;
	//Steer toward attractors
	for(int i = 0; i < at.size(); i++){
		diff = pos - at[i]->getPos();
		if(diff.abs() < vDistance){
			//cout << " pull = " <<at[i]->getPull()<< endl;
			//cout << " sectionAcc = ";
			sectionAcc += -diff*at[i]->getPull()*pullConstant;
			//sectionAcc.print();
			//cout << " diff = ";
			//diff.normalized().print();
			//cout << " pull constant = "<< pullConstant << endl;
		}
	}
	sectionAcc = sectionAcc/n;
	attractorDir = sectionAcc.normalized() / 10.0f; 
	if((totalAcc + sectionAcc).abs() < maxSteer||sectionAcc.abs() < 0.001){
		totalAcc += sectionAcc;
	} else {
		totalAcc += sectionAcc*(maxSteer-totalAcc.abs())/sectionAcc.abs();
	}

	return (totalAcc);
}

void FlockBoid::draw()
{
	GLfloat flockColor[] = {0.0f, 1.0f, 1.0f, 0.0f};
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

	if(isForceDraw) {
	  glPushMatrix();
	  
	  // Save current state of OpenGL
	  glPushAttrib(GL_ALL_ATTRIB_BITS);

	  // This is to draw the axes when the mouse button is down
	  glDisable(GL_LIGHTING);
	  glLineWidth(3);
	  glPushMatrix();
	  glScaled(5.0,5.0,5.0);
	  glBegin(GL_LINES);

	  glColor4f(1,0.5,0.5,1); glVertex3f(0,0,0); glVertex3f(avoidDir[0],avoidDir[1],avoidDir[2]);
	  glColor4f(0.5,1,0.5,1); glVertex3f(0,0,0); glVertex3f(matchVDir[0], matchVDir[1], matchVDir[2]);
	  glColor4f(0.5,0.5,1,1); glVertex3f(0,0,0); glVertex3f(centerDir[0], centerDir[1], centerDir[2]);
	  glColor4f(0.5,1,1,1); glVertex3f(0,0,0); glVertex3f(attractorDir[0], attractorDir[1], attractorDir[2]);
	  
	  
	  glEnd();
	  glPopMatrix();
	  
	  glPopAttrib();
	  glPopMatrix();
	  
	}
	glPopMatrix();
}
