#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <glut.h>
#include <gl.h>
#include <glu.h>

#include "Leaf.h"
#include "Value.h"
#include "Exp.h"

//#include "glm/glm.hpp"

#define pi 3.14152

using namespace std;

/******** Global Variables ********/
double angle_x = 0;
double angle_y = -45;
double angle_z = 0;

vector<Leaf*>* trace_pointer;
bool isOrtho = false;// view in orthogonal mode
bool isCM = false;// view trace of center of mass
int num;// number of leaves
int view = 1;// view fall in real-time
int rt = 0;// rendering time
int step = 3;// rendering time steps

/******** Global Functions ********/
void display();
void keyboard(unsigned char key, int x, int y);
void menu(int value);
void timer(int value);

void init_display(bool ortho);
void lab_config();

int main(int argc, char** argv)
{
	// Experiment 01: variable(length)
	Value* V1 = new Value();
	V1->set_length(0.1f);// leaf is 10cm wide
	Exp E1(V1);
	trace_pointer = E1.get_trace();
	num = E1.get_size();

	//V1->set_height(10.0f);
	//V1->set_friction(20.0f, 0.3f);
	//V1->set_density(1.0f);// viscous liquid
	//V1->set_density(0.05f);// air
	
	// graphical interface
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(900, 100);
	glutCreateWindow("Final Simulator Ver01");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	//glutTimerFunc(1, timer, 1);

	timer(0);

	glutCreateMenu(menu);
	glutAddMenuEntry("View Trace", 1);
	glutAddMenuEntry("View Real-time", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

	return 0;
}

void display()
{
	init_display(isOrtho);

	glPushMatrix();
	glRotated(angle_x, 1.0f, 0.0f, 0.0f);
	glRotated(angle_y, 0.0f, 1.0f, 0.0f);
	glRotated(angle_z, 0.0f, 0.0f, 1.0f);

	glPushMatrix();
	glTranslated(0.0f, -50.0f, 0.0f);
	lab_config();

	if (view == 1)
	{
		for (int i = 0; i < num; i++)
		{
			if (isCM)
				trace_pointer->at(i)->draw_center_of_mass();
			else
				trace_pointer->at(i)->draw_leaf();
		}
	}
	else
	{
		if (isCM)
			trace_pointer->at(rt)->draw_center_of_mass();
		else
			trace_pointer->at(rt)->draw_leaf();
	}

	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		angle_x += 45;
		break;
	case 's':
		angle_y += 45;
		break;
	case 'd':
		angle_z += 45;
		break;
	case 'q':
		angle_x -= 45;
		break;
	case 'w':
		angle_y -= 45;
		break;
	case 'e':
		angle_z -= 45;
		break;
	case 'o':
		if (isOrtho)
			isOrtho = false;
		else
			isOrtho = true;
		break;
	case 'c':
		if (isCM)
			isCM = false;
		else
			isCM = true;
		break;
	default:
		break;
	}

	rt = 0;
	glutPostRedisplay();
}

void menu(int value)
{
	view = value;
	rt = 0;
	glutPostRedisplay();
}

void timer(int value)
{
	if (rt < num - step)
		rt += step;
	glutPostRedisplay();
	glutTimerFunc(1, timer, 0);// 1ms
}