/*
	Leaf Class
	 _____
	|     |
	|     |
	|     |width
	|     |
	|_____|
	 length

	Need:
	image import, aspect ratio calculation, relative area calculation, initial direction
*/
#pragma once

#include <iostream>
#include <vector>
#include <glut.h>
#include <gl.h>
#include <glu.h>

#include "vec3.h"

//#include "glm/glm.hpp"

using namespace std;

class Leaf{
public:
	// constructor
	Leaf(double len, double posX = 0, double posY = 0, double posZ = 0, double angT = 0)
	{
		l = len;
		x = posX;
		y = posY;
		z = posZ;
		theta = angT;

		// aspect ratio considered
		w = 0.1 / len;

		import_texture();
	}

	// import texture and vertices
	void import_texture()
	{
		// set points
		point.push_back(vec3(0, 0, 0));// fake
		point.push_back(vec3(-1.0, -7.3, 0));
		point.push_back(vec3(2.0, -5.6, 0));
		point.push_back(vec3(2.8, -4.8, 0));
		point.push_back(vec3(2.6, -3.6, 0));
		point.push_back(vec3(3.6, -4.1, 0));
		point.push_back(vec3(6.1, -3.8, 0));
		point.push_back(vec3(5.7, -3.3, 0));
		point.push_back(vec3(5.9, -2.7, 0));
		point.push_back(vec3(5.8, -1.9, 0));
		point.push_back(vec3(6.5, -1.8, 0));
		point.push_back(vec3(5.9, -1.3, 0));
		point.push_back(vec3(5.9, -0.8, 0));
		point.push_back(vec3(6.5, -0.6, 0));
		point.push_back(vec3(5.7, 0.0, 0));
		point.push_back(vec3(5.8, 0.4, 0));
		point.push_back(vec3(6.8, 1.6, 0));
		point.push_back(vec3(5.9, 3.0, 0));
		point.push_back(vec3(5.2, 3.2, 0));
		point.push_back(vec3(5.0, 3.8, 0));
		point.push_back(vec3(3.6, 3.6, 0));
		point.push_back(vec3(3.1, 4.0, 0));
		point.push_back(vec3(2.3, 3.3, 0));
		point.push_back(vec3(1.9, 2.8, 0));
		point.push_back(vec3(2.0, 1.7, 0));
		point.push_back(vec3(1.5, 1.3, 0));
		point.push_back(vec3(0.8, 1.2, 0));
		point.push_back(vec3(0.2, 1.7, 0));
		point.push_back(vec3(0.0, 4.8, 0));
		point.push_back(vec3(-0.4, 7.0, 0));
		point.push_back(vec3(-0.9, 7.3, 0));
		point.push_back(vec3(-1.1, 6.9, 0));
		point.push_back(vec3(-1.4, 6.7, 0));
		point.push_back(vec3(-0.9, 6.4, 0));
		point.push_back(vec3(-0.3, 4.7, 0));
		point.push_back(vec3(-0.2, 2.4, 0));
		point.push_back(vec3(-0.1, 1.5, 0));
		point.push_back(vec3(-0.6, 1.3, 0));
		point.push_back(vec3(-1.6, 1.6, 0));
		point.push_back(vec3(-2.6, 2.7, 0));
		point.push_back(vec3(-2.4, 3.5, 0));
		point.push_back(vec3(-4.0, 4.7, 0));
		point.push_back(vec3(-4.2, 3.7, 0));
		point.push_back(vec3(-5.2, 3.9, 0));
		point.push_back(vec3(-5.9, 3.4, 0));
		point.push_back(vec3(-6.1, 2.9, 0));
		point.push_back(vec3(-6.9, 2.7, 0));
		point.push_back(vec3(-7.1, 2.2, 0));
		point.push_back(vec3(-5.8, 1.0, 0));
		point.push_back(vec3(-6.3, 0.6, 0));
		point.push_back(vec3(-6.8, -1.8, 0));
		point.push_back(vec3(-6.6, -2.8, 0));
		point.push_back(vec3(-3.9, -3.4, 0));
		point.push_back(vec3(-3.7, -3.9, 0));
		point.push_back(vec3(-3.8, -4.8, 0));
		point.push_back(vec3(-2.8, -4.9, 0));
		point.push_back(vec3(-2.5, -5.5, 0));
		point.push_back(vec3(0.0, 6.0, 0));
		point.push_back(vec3(0.0, -6.0, 0));
		point.push_back(vec3(-7.0, 0.0, 0));
		point.push_back(vec3(5.0, 0.0, 0));
		point.push_back(vec3(0.0, 0.0, 0));

		// aligned vertices
		vertex.push_back(vec3(1, 2, 56));
		vertex.push_back(vec3(2, 3, 56));
		vertex.push_back(vec3(3, 4, 56));
		vertex.push_back(vec3(6, 7, 5));
		vertex.push_back(vec3(7, 4, 5));
		vertex.push_back(vec3(7, 8, 4));
		vertex.push_back(vec3(9, 10, 11));
		vertex.push_back(vec3(9, 11, 4));
		vertex.push_back(vec3(11, 12, 4));
		vertex.push_back(vec3(12, 13, 14));
		vertex.push_back(vec3(12, 14, 4));
		vertex.push_back(vec3(4, 14, 56));
		vertex.push_back(vec3(14, 55, 56));
		vertex.push_back(vec3(53, 54, 55));
		vertex.push_back(vec3(14, 53, 55));
		vertex.push_back(vec3(53, 14, 52));
		vertex.push_back(vec3(14, 26, 52));
		vertex.push_back(vec3(14, 25, 26));
		vertex.push_back(vec3(14, 15, 25));
		vertex.push_back(vec3(15, 24, 25));
		vertex.push_back(vec3(15, 16, 24));
		vertex.push_back(vec3(16, 17, 18));
		vertex.push_back(vec3(16, 18, 24));
		vertex.push_back(vec3(18, 19, 20));
		vertex.push_back(vec3(18, 20, 24));
		vertex.push_back(vec3(20, 21, 24));
		vertex.push_back(vec3(21, 22, 24));
		vertex.push_back(vec3(22, 23, 24));
		vertex.push_back(vec3(26, 27, 36));
		vertex.push_back(vec3(27, 35, 36));
		vertex.push_back(vec3(27, 28, 35));
		vertex.push_back(vec3(35, 28, 34));
		vertex.push_back(vec3(28, 33, 34));
		vertex.push_back(vec3(28, 29, 33));
		vertex.push_back(vec3(29, 30, 31));
		vertex.push_back(vec3(29, 31, 33));
		vertex.push_back(vec3(33, 31, 32));
		vertex.push_back(vec3(26, 36, 37));
		vertex.push_back(vec3(26, 37, 52));
		vertex.push_back(vec3(52, 36, 37));
		vertex.push_back(vec3(52, 37, 38));
		vertex.push_back(vec3(39, 40, 42));
		vertex.push_back(vec3(40, 41, 42));
		vertex.push_back(vec3(39, 42, 52));
		vertex.push_back(vec3(52, 42, 45));
		vertex.push_back(vec3(42, 43, 45));
		vertex.push_back(vec3(43, 44, 45));
		vertex.push_back(vec3(52, 45, 48));
		vertex.push_back(vec3(48, 45, 46));
		vertex.push_back(vec3(46, 47, 48));
		vertex.push_back(vec3(52, 48, 49));
		vertex.push_back(vec3(52, 49, 50));
		vertex.push_back(vec3(52, 50, 51));
		vertex.push_back(vec3(38, 39, 52));
		vertex.push_back(vec3(4, 8, 9));
	}

	// draw a single leaf
	void draw_leaf()
	{
		glPushMatrix();
		glTranslated(x, y, z);
		glRotated(theta, 0, 0, 1);
		glScaled(10 * l, 1, 10 * w);
		//glScaled(10, 10, 10);

		// front face
		glColor3f(0.576471, 0.858824, 0.439216);// Color Green Yellow 
		glBegin(GL_QUADS);
		// Rectangle
		glVertex3f(-0.5f, 0, -0.5f);// Top Right Of The Quad (Top)
		glVertex3f(-0.5f, 0, 0.5f);// Top Left Of The Quad (Top)
		glVertex3f(0.5f, 0, 0.5f);// Bottom Left Of The Quad (Top)
		glVertex3f(0.5f, 0, -0.5f);// Bottom Right Of The Quad (Top)
		glEnd();

		// back face
		glColor3f(0.276471, 0.558824, 0.139216);// Color darker Green Yellow 
		glBegin(GL_QUADS);
		// Rectangle
		glVertex3f(0.5f, 0.00001f, -0.5f);// Bottom Right Of The Quad (Top)
		glVertex3f(0.5f, 0.00001f, 0.5f);// Bottom Left Of The Quad (Top)
		glVertex3f(-0.5f, 0.00001f, 0.5f);// Top Left Of The Quad (Top)
		glVertex3f(-0.5f, 0.00001f, -0.5f);// Top Right Of The Quad (Top)
		glEnd();
		glPopMatrix();
	}

	void draw_leaf2()
	{
		glPushMatrix();
		glTranslated(x, y, z);
		glRotated(theta, 0, 0, 1);
		glScaled(1 * l, 1, 1 * w);

		// front face
		glColor3f(0.576471, 0.858824, 0.439216);// Color Green Yellow 
		for (int i = 0; i < vertex.size(); i++)
		{
			glBegin(GL_TRIANGLES);
			glVertex3f(point[vertex[i].x].z, point[vertex[i].x].x, point[vertex[i].x].y);
			glVertex3f(point[vertex[i].y].z, point[vertex[i].y].x, point[vertex[i].y].y);
			glVertex3f(point[vertex[i].z].z, point[vertex[i].z].x, point[vertex[i].z].y);
			glEnd();
		}

		// back face
		glColor3f(0.276471, 0.558824, 0.139216);// Color darker Green Yellow 
		for (int i = 0; i < vertex.size(); i++)
		{
			glBegin(GL_TRIANGLES);
			glVertex3f(point[vertex[i].z].z, point[vertex[i].z].x + 0.01f, point[vertex[i].z].y);
			glVertex3f(point[vertex[i].y].z, point[vertex[i].y].x + 0.01f, point[vertex[i].y].y);
			glVertex3f(point[vertex[i].x].z, point[vertex[i].x].x + 0.01f, point[vertex[i].x].y);
			glEnd();
		}

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
	double l;// length
	double w = 1.0f;// width

	// angle w.r.t. the xy-plane
	double theta;

	vector<vec3> point;
	vector<vec3> vertex;
};