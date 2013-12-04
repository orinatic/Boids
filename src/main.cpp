#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "extra.h"
#include "camera.h"
#include "FlockBoid.h"
#include "Mesh.h"



using namespace std;

float maxSpeed;
float viewDistance;
int numFlockers;
char* fileIn;
Mesh* pattern;
vector<FlockBoid*> flockers;
vector<AttractorBoid*> attractors;

namespace
{
	
	void initSystem(int argc, char * argv[])
	{
		for(int argNum = 1; argNum < argc; ++argNum){
			string arg = argv[argNum];
			if(arg == "-input"){
				fileIn = argv[argNum+1];
				argNum++;
			}
		}
		viewDistance = 2.5f;
		numFlockers = 150;
		pattern = new Mesh();
		pattern->load(fileIn, numFlockers, viewDistance);
		maxSpeed = 1.0f;
		// seed the random number generator with the current time
		srand( time( NULL ) );
		flockers = vector<FlockBoid*>();
		attractors = vector<AttractorBoid*>();
		//flockers.push_back(new FlockBoid(Vector3f(0,0,0), Vector3f(.1,.1,.1)));
		//flockers.push_back(new FlockBoid(Vector3f(1,1,1), Vector3f(-.1,-.1,.1)));	
		float posStart = 2.0f;
		float velStart = 0.2f;
		float attractorPull = 2.0f;
		cout << "number of vertices" << pattern->vertices.size() << endl;
		for(int i = 0; i < pattern->vertices.size(); i++){
			attractors.push_back(new AttractorBoid(pattern->vertices[i], Vector3f(0,0,0), attractorPull));
		}
		for(int i = 0; i < numFlockers; i++){
				flockers.push_back(new FlockBoid(
											  Vector3f(posStart*2*rand()/RAND_MAX-posStart, posStart*2*rand()/RAND_MAX-posStart, posStart*2*rand()/RAND_MAX-posStart),
											  Vector3f(velStart*2*rand()/RAND_MAX-velStart, velStart*2*rand()/RAND_MAX-velStart, velStart*2*rand()/RAND_MAX-velStart),viewDistance));
		}
		/*	attractors.push_back(new AttractorBoid(Vector3f(-1,1,1),Vector3f(0,0,0),  attractorPull));
		attractors.push_back(new AttractorBoid(Vector3f(-1,-1,1),Vector3f(0,0,0),  attractorPull));
		attractors.push_back(new AttractorBoid(Vector3f(-1, 0,-1),Vector3f(0,0,0),  attractorPull));
		attractors.push_back(new AttractorBoid(Vector3f(1,0,0),Vector3f(0,0,0),  attractorPull));
		attractors.push_back(new AttractorBoid(Vector3f(0,0,0),Vector3f(0,0,0),  attractorPull));*/
	}

	void stepSystem()
	{
	  for(int i = 0; i < flockers.size(); i++){
		  Vector3f acc = flockers[i]->evalF(flockers, attractors);
		  if(acc.abs() !=0){
			  // cout << "number is " << i << " and acc is ";
			  // acc.print();
			  // cout << "vel is ";
			  //flockers[i]->getVel().print();
			  //cout << "pos is ";
			  //flockers[i]->getPos().print();
		  }
		  Vector3f newPos = flockers[i]->getPos() + flockers[i]->getVel()*0.1f;
		  float SIZE = 10.0f;
		  Vector3f newVel = (flockers[i]->getVel() + acc);
		  for(int i = 0; i < 3; i++){
		    if(newPos[i] > SIZE / 2)
		      newVel[i] = -abs(newVel[i]);
		    if(newPos[i] < -SIZE / 2)
		      newVel[i] = abs(newVel[i]);
		  }
		  if(newVel.abs() > maxSpeed)
			  newVel = newVel*maxSpeed/newVel.abs();
		  flockers[i]->setPos(newPos);
		  flockers[i]->setVel(newVel);
	  }
   
  }

  // Draw the current particle positions
  void drawSystem()
  {
    
    // Base material colors (they don't change)
    GLfloat particleColor[] = {0.4f, 0.7f, 1.0f, 1.0f};
    GLfloat floorColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, particleColor);
    
	for(int i = 0; i < flockers.size(); i++){
		flockers[i]->draw();
	}
	
	for(int i = 0; i <attractors.size(); i++){
		attractors[i]->draw();
	}
  }
    //----------------------------------------------------------------
    
        
    // This is the camera
    Camera camera;

    // These are state variables for the UI
    bool g_mousePressed = false;

    // Declarations of functions whose implementations occur later.
    void arcballRotation(int endX, int endY);
    void keyboardFunc( unsigned char key, int x, int y);
    void specialFunc( int key, int x, int y );
    void mouseFunc(int button, int state, int x, int y);
    void motionFunc(int x, int y);
    void reshapeFunc(int w, int h);
    void drawScene(void);
    void initRendering();

    // This function is called whenever a "Normal" key press is
    // received.
    void keyboardFunc( unsigned char key, int x, int y )
    {
        switch ( key )
        {
        case 27: // Escape key
            exit(0);
            break;
        case ' ':
        {
            Matrix4f eye = Matrix4f::identity();
            camera.SetRotation( eye );
            camera.SetCenter( Vector3f::ZERO );
            break;
        }
		
		case 'a':
			for(int i = 0; i<attractors.size(); i++){
				attractors[i]->toggleDraw();
			}
			break;
		/*
		case '2':
			system = new PendulumSystem(2);
			break;
		case '3':
			system = new PendulumSystem(4);
			break;
		case '4':
			clothSystem = new ClothSystem(8);
			system = clothSystem;
			break;
		case 'w':
			clothSystem->wireframe = !clothSystem->wireframe;
			break;
		case 's':
			clothSystem->moving = !clothSystem->moving;
			break;
		case 'd':
			if(uF)
				clothSystem->userForce = Vector3f();
			else
				clothSystem->userForce = Vector3f(0.0f, 0.0f, 50.0f);
			uF = !uF;
		*/		
        default:
            cout << "Unhandled key press " << key << "." << endl;        
        }

        glutPostRedisplay();
    }

    // This function is called whenever a "Special" key press is
    // received.  Right now, it's handling the arrow keys.
    void specialFunc( int key, int x, int y )
    {
        switch ( key )
        {

        }
        //glutPostRedisplay();
    }

    //  Called when mouse button is pressed.
    void mouseFunc(int button, int state, int x, int y)
    {
        if (state == GLUT_DOWN)
        {
            g_mousePressed = true;
            
            switch (button)
            {
            case GLUT_LEFT_BUTTON:
                camera.MouseClick(Camera::LEFT, x, y);
                break;
            case GLUT_MIDDLE_BUTTON:
                camera.MouseClick(Camera::MIDDLE, x, y);
                break;
            case GLUT_RIGHT_BUTTON:
                camera.MouseClick(Camera::RIGHT, x,y);
            default:
                break;
            }                       
        }
        else
        {
            camera.MouseRelease(x,y);
            g_mousePressed = false;
        }
        glutPostRedisplay();
    }

    // Called when mouse is moved while button pressed.
    void motionFunc(int x, int y)
    {
        camera.MouseDrag(x,y);        
    
        glutPostRedisplay();
    }

    // Called when the window is resized
    // w, h - width and height of the window in pixels.
    void reshapeFunc(int w, int h)
    {
        camera.SetDimensions(w,h);

        camera.SetViewport(0,0,w,h);
        camera.ApplyViewport();

        // Set up a perspective view, with square aspect ratio
        glMatrixMode(GL_PROJECTION);

        camera.SetPerspective(50);
        glLoadMatrixf( camera.projectionMatrix() );
    }

    // Initialize OpenGL's rendering modes
    void initRendering()
    {
        glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on
        glEnable(GL_LIGHTING);     // Enable lighting calculations
        glEnable(GL_LIGHT0);       // Turn on light #0.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
        glEnable(GL_NORMALIZE);

        // Setup polygon drawing
        glShadeModel(GL_SMOOTH);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

        // Clear to black
        glClearColor(0,0,0,1);
    }

    // This function is responsible for displaying the object.
    void drawScene(void)
    {
        // Clear the rendering window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode( GL_MODELVIEW );  
        glLoadIdentity();              

        // Light color (RGBA)
        GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0};
        GLfloat Lt0pos[] = {3.0,3.0,5.0,1.0};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
        glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);

        glLoadMatrixf( camera.viewMatrix() );

        // THIS IS WHERE THE DRAW CODE GOES.

        drawSystem();

        // This draws the coordinate axes when you're rotating, to
        // keep yourself oriented.
        if( g_mousePressed )
        {
            glPushMatrix();
            Vector3f eye = camera.GetCenter();
            glTranslatef( eye[0], eye[1], eye[2] );

            // Save current state of OpenGL
            glPushAttrib(GL_ALL_ATTRIB_BITS);

            // This is to draw the axes when the mouse button is down
            glDisable(GL_LIGHTING);
            glLineWidth(3);
            glPushMatrix();
            glScaled(5.0,5.0,5.0);
            glBegin(GL_LINES);
            glColor4f(1,0.5,0.5,1); glVertex3f(0,0,0); glVertex3f(1,0,0);
            glColor4f(0.5,1,0.5,1); glVertex3f(0,0,0); glVertex3f(0,1,0);
            glColor4f(0.5,0.5,1,1); glVertex3f(0,0,0); glVertex3f(0,0,1);

            glColor4f(0.5,0.5,0.5,1);
            glVertex3f(0,0,0); glVertex3f(-1,0,0);
            glVertex3f(0,0,0); glVertex3f(0,-1,0);
            glVertex3f(0,0,0); glVertex3f(0,0,-1);

            glEnd();
            glPopMatrix();

            glPopAttrib();
            glPopMatrix();
        }
                 
        // Dump the image to the screen.
        glutSwapBuffers();
    }

    void timerFunc(int t)
    {
        stepSystem();

        glutPostRedisplay();

        glutTimerFunc(t, &timerFunc, t);
    }

    

    
    
}

char* getFile(const char *fileName) {
	char* text;
    
	if (fileName != NULL) {
        FILE *file = fopen(fileName, "rt");
        
		if (file != NULL) {
            fseek(file, 0, SEEK_END);
            int count = ftell(file);
            rewind(file);
            
			if (count > 0) {
				text = (char*)malloc(sizeof(char) * (count + 1));
				count = fread(text, sizeof(char), count, file);
				text[count] = '\0';
			}
			fclose(file);
		}
	}
	return text;
}

GLuint loadShader(string vert, string frag) {
  const char* fragData = getFile(frag.c_str());
  const char* vertData = getFile(vert.c_str());

  cout << "Vert:\n" << vertData << endl;
  cout << "Frag:\n" << fragData << endl;

  GLuint vertexShader, fragmentShader, program;
  GLint compiled;
  program = glCreateProgramObjectARB();
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSourceARB(vertexShader, 1, &vertData, NULL);
  glCompileShaderARB(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
  if(!compiled) {
    GLint blen = 0;	
    GLsizei slen = 0;
    
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &blen);
    if (blen > 1) {
      GLchar* compiler_log = (GLchar*)malloc(blen);
      glGetInfoLogARB(vertexShader, blen, &slen, compiler_log);
      cout << "compiler_log:\n" << compiler_log << endl;
      free(compiler_log);
    }
  }


  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSourceARB(fragmentShader, 1, &fragData, NULL);
  glCompileShaderARB(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
  if(!compiled) {
    GLint blen = 0;	
    GLsizei slen = 0;
    
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &blen);
    if (blen > 1) {
      GLchar* compiler_log = (GLchar*)malloc(blen);
      glGetInfoLogARB(fragmentShader, blen, &slen, compiler_log);
      cout << "compiler_log:\n" << compiler_log << endl;
      free(compiler_log);
    }
  }

  program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  GLint linked;
  glGetProgramiv(program, GL_LINK_STATUS, &linked);
  if (!linked) {
    GLint blen = 0;	
    GLsizei slen = 0;
    
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &blen);
    if (blen > 1) {
      GLchar* compiler_log = (GLchar*)malloc(blen);
      glGetInfoLogARB(program, blen, &slen, compiler_log);
      cout << "compiler_log:\n" << compiler_log << endl;
      free(compiler_log);
    }
  } 
  
  glUseProgramObjectARB(program);
  return program;
}

// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char* argv[] )
{
    glutInit( &argc, argv );
    // We're going to animate it, so double buffer 
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

    // Initial parameters for window position and size
    glutInitWindowPosition( 60, 60 );
    glutInitWindowSize( 600, 600 );
    
    camera.SetDimensions( 600, 600 );

    camera.SetDistance( 10 );
    camera.SetCenter( Vector3f::ZERO );
    
    glutCreateWindow("Autoshapes");
    glewInit();
    // Initialize OpenGL parameters.
    initRendering();

    GLuint program = loadShader("boid.vert", "boid.frag");
	
    // Setup particle system
    initSystem(argc,argv);

    // Set up callback functions for key presses
    glutKeyboardFunc(keyboardFunc); // Handles "normal" ascii symbols
    glutSpecialFunc(specialFunc);   // Handles "special" keyboard keys

    // Set up callback functions for mouse
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);

    // Set up the callback function for resizing windows
    glutReshapeFunc( reshapeFunc );

    // Call this whenever window needs redrawing
    glutDisplayFunc( drawScene );

    // Trigger timerFunc every 20 msec
    glutTimerFunc(20, timerFunc, 20);

        
    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop();

    return 0;	// This line is never reached.
}
