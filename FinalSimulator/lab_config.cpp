/*
	Laboratory space configuration function
*/

#include <glut.h>
#include <gl.h>
#include <glu.h>

void lab_config()
{
	glColor3f(0.3, 0.3, 0.3);
	// the Origin
	glBegin(GL_POINTS);
	glVertex3d(0, 0, 0);
	glEnd();

	// xy-plane
	glColor3f(0.5, 0.5, 0.5);
	//glColor3f(0.3, 0.2, 0.2);
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
	glColor3f(0.2, 0.2, 0.2);
	//glColor3f(0.3, 0.3, 0.1);
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
	glColor3f(0.1, 0.1, 0.1);
	//glColor3f(0.2, 0.2, 0.3);
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

	//glColor3f(1, 1, 1);
	glColor3f(0.8, 0.2, 0.2);
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