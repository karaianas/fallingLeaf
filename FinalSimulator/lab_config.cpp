/*
Laboratory space configuration function
*/

#include <glut.h>
#include <gl.h>
#include <glu.h>

void lab_config()
{
	// 100 * 100 * 100 config
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);

	glColor3f(0.9, 0.9, 0.9);

	// the Origin
	glBegin(GL_POINTS);
	glVertex3d(0, 0, 0);
	glEnd();

	// xy-plane
	for (int i = 0; i <= 100; i += 5)
	{
		glBegin(GL_LINES);
		glVertex3f(-50, 0 + i, -50);
		glVertex3f(50, 0 + i, -50);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(-50 + i, 100, -50);
		glVertex3f(-50 + i, 0, -50);
		glEnd();
	}

	// yz-plane
	for (int i = 0; i <= 100; i += 5)
	{
		glBegin(GL_LINES);
		glVertex3f(-50, 0 + i, 50);
		glVertex3f(-50, 0 + i, -50);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(-50, 100, -50 + i);
		glVertex3f(-50, 0, -50 + i);
		glEnd();
	}
	
	// zx-plane
	for (int i = 0; i <= 100; i += 5)
	{
		if (i == 50)
			i += 5;

		glBegin(GL_LINES);
		glVertex3f(-50 + i, 0, 50);
		glVertex3f(-50 + i, 0, -50);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(-50, 0, -50 + i);
		glVertex3f(50, 0, -50 + i);
		glEnd();
	}

	glColor3f(1, 0, 0);
	
	// y-axis
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 100, 0);
	glEnd();
	
	// x-axis
	glBegin(GL_LINES);
	glVertex3d(-50, 0.1, 0);
	glVertex3d(50, 0.1, 0);
	glEnd();

	// z-axis
	glBegin(GL_LINES);
	glVertex3d(0, 0.1, -50);
	glVertex3d(0, 0.1, 50);
	glEnd();
}