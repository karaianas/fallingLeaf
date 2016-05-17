/*
	Leaf Class
	 _____
	|     |
	|     |
	|     |height
	|     |
	|_____|
	 width = length

	Need:
	image import, aspect ratio calculation, relative area calculation, initial direction
*/
#pragma once

#include <iostream>
#include <vector>
#include <glut.h>
#include <gl.h>
#include <glu.h>

//#include "glm/glm.hpp"

using namespace std;

class Leaf{
public:
	// constructor
	Leaf(double len, double posX = 0, double posY = 0, double posZ = 0, double angT = 0)
	{
		w = len;
		x = posX;
		y = posY;
		z = posZ;
		theta = angT;
	}

	// draw a single leaf
	void draw_leaf()
	{
		glPushMatrix();
		glTranslated(x, y, z);
		glRotated(theta, 0, 0, 1);
		glScaled(10 * w, 1, 10 * h);
		//glScaled(10, 1, 10 * h);

		// front face
		glColor3f(0.576471, 0.858824, 0.439216);// Color Green Yellow 
		glBegin(GL_QUADS);
		// Rectangle
		glVertex3f(-0.8f, 0, -0.8f);// Top Right Of The Quad (Top)
		glVertex3f(-0.8f, 0, 0.8f);// Top Left Of The Quad (Top)
		glVertex3f(0.8f, 0, 0.8f);// Bottom Left Of The Quad (Top)
		glVertex3f(0.8f, 0, -0.8f);// Bottom Right Of The Quad (Top)
		glEnd();

		// back face
		glColor3f(0.276471, 0.558824, 0.139216);// Color darker Green Yellow 
		glBegin(GL_QUADS);
		// Rectangle
		glVertex3f(0.8f, 0.00001f, -0.8f);// Bottom Right Of The Quad (Top)
		glVertex3f(0.8f, 0.00001f, 0.8f);// Bottom Left Of The Quad (Top)
		glVertex3f(-0.8f, 0.00001f, 0.8f);// Top Left Of The Quad (Top)
		glVertex3f(-0.8f, 0.00001f, -0.8f);// Top Right Of The Quad (Top)
		glEnd();
		glPopMatrix();
	}

	// draw center of mass of the leaf
	void draw_center_of_mass()
	{
		glColor3f(0.2, 1.0, 0.5);
		glPushMatrix();
		glTranslated(x, y, z);
		glutSolidSphere(0.2, 10, 10);
		glPopMatrix();
	}

	// get position
	double get_y()
	{
		return y;
	}

	double get_x()
	{
		return x;
	}

private:
	// position
	double x;
	double y;
	double z;

	// size
	double w;// width
	double h = 1.0f;// height

	// angle w.r.t. the xy-plane
	double theta;
};