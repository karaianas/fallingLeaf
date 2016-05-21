/*
	Initial display set-up function
*/

#include <glut.h>
#include <gl.h>
#include <glu.h>

void init_display(bool ortho)
{
	// initialization
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	// viewport
	glViewport(-250, -250, 1300, 1300);// center and size

	if (ortho)
	{
		// orthogonal
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-100, 100, -100, 100, 1, 300.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	else
	{
		// perspective
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1, 1, -1, 1, 1, 300.0);
		//glFrustum(-1, 1, -1, 1, 1, 300.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	//gluLookAt(0, 0, 20, 0.0, 0, 0.0, 0, 1.0, 0.0);// eye, at, up
	//gluLookAt(0, 0, 200, 0.0, 0, 0.0, 0, 1.0, 0.0);// eye, at, up
	gluLookAt(0, 0, 150, 0.0, 0, 0.0, 0, 1.0, 0.0);// eye, at, up
}