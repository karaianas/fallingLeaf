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
int num = 0;// number of leaves
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
bool console();

int main(int argc, char** argv)
{
	// start experiment
	Value* V1 = new Value();
	Exp E1(V1);
	trace_pointer = E1.get_trace();
	num = E1.get_size();

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
	case 'x':
		console();
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

bool console()
{
	int opt1 = 0;
	printf("\nStart Experiment\n");
	printf("[1] Default Experiment\n");
	printf("[2] New Experiment\nOption: ");
	scanf("%d", &opt1);
	
	if ((opt1 != 2) && (opt1 != 1))
		return false;

	// initialize global variables
	angle_x = 0; angle_y = -45; angle_z = 0;
	isOrtho = false; isCM = false;
	num = 0;
	view = 1;
	rt = 0;
	step = 3;

	Value* V1 = new Value();

	// [2] New Experiment
	if (opt1 == 2)
	{
		bool setting = true;
		int opt2 = 0;

		// set variables
		while (setting)
		{
			printf("\n[0] End Setting\n");
			printf("[1] Set Length\n");
			printf("[2] Set Drag Coefficients\n");
			printf("[3] Set Density\n");
			printf("[4] Aspect Ratio length\nOption: ");
			scanf("%d", &opt2);

			switch (opt2)
			{
			case 0:
				setting = false;
				break;
			case 1:
				double len;
				printf("Enter length in meters: ");
				scanf("%lf", &len);
				V1->set_length(len);
				break;
			case 2:
				double c_ver, c_hor;
				printf("Enter vertical coeff <= 50: ");
				scanf("%lf", &c_ver);
				printf("Enter horizontal coeff <= 1: ");
				scanf("%lf", &c_hor);
				V1->set_friction(c_ver, c_hor);
				break;
			case 3:
				double den;
				printf("Enter density: ");
				scanf("%lf", &den);
				V1->set_density(den);
				break;
			case 4:
				double as_len;
				printf("Enter length: ");
				scanf("%lf", &as_len);
				V1->set_aspect_ratio(as_len);
				break;
			default:
				return false;
			}
		}
	}

	// start experiment
	Exp* E1 = new Exp(V1);
	trace_pointer = E1->get_trace();
	num = E1->get_size();
	
	return true;
}