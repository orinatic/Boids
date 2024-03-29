#ifndef EXTRA_H
#define EXTRA_H

#ifdef WIN32
#include <windows.h>
#endif

#if __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#ifndef M_PI
#define M_PI  3.14159265358979323846
#endif

#include <vecmath.h>

struct spring {
	int a;
	int b;
	float k;
	float l;
	bool display;
    spring(int a, int b, float k, float l) : 
	a(a), b(b), k(k), l(l), display(true) {};
    spring(int a, int b, float k, float l, bool d) : 
	a(a), b(b), k(k), l(l), display(d) {};
};

// Inline functions to help with drawing
inline void glVertex( const Vector3f& a )
{
    glVertex3fv(a);
}

inline void glNormal( const Vector3f& a ) 
{
    glNormal3fv(a);
}

inline void glLoadMatrix( const Matrix4f& m )
{
    glLoadMatrixf( m );
}

inline void glMultMatrix( const Matrix4f& m )
{
    glMultMatrixf( m );
}

#endif
