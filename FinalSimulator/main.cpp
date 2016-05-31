#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <ctime>

#include <glut.h>
#include <gl.h>
#include <glu.h>
#include <glaux.h>

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
vector<Leaf*>* trace_pointer2;
vector<Leaf*>* trace_pointer3;

bool isOrtho = false;// view in orthogonal mode
bool isCM = false;// view trace of center of mass

int num = 0;// number of leaves
int num2 = 0;
int num3 = 0;

int view = 1;// view fall in real-time

int rt = 0;// rendering time
int rt2 = 0;
int rt3 = 0;

int step = 4;// rendering time steps

bool red = false;
bool green = true;
bool blue = false;

/******** Global Functions ********/
void display();
void keyboard(unsigned char key, int x, int y);
void menu(int value);
void timer(int value);

void init_display(bool ortho);
void lab_config();
bool console();

AUX_RGBImageRec * LoadBMP(char *szFilename);
int LoadGLTextures();

int main(int argc, char** argv)
{
	// start experiment
	clock_t begin = clock();

	Value* V1 = new Value();
	V1->set_position(50, 100, 0);//50, 100, 20
	//V1->set_length(1.0);
	//V1->set_density(0.05);
	//V1->set_friction(2, 0.2);
	Exp E1(V1);
	trace_pointer = E1.get_trace();
	num = E1.get_size();

	Value* V2 = new Value();
	V2->set_position(20, 100, 30);
	V2->set_length(0.5);
	Exp E2(V2);
	trace_pointer2 = E2.get_trace();
	num2 = E2.get_size();

	Value* V3 = new Value();
	V3->set_position(50, 100, -20);
	//V3->set_friction(15.0, 0.15);
	//V3->set_length(1.0);
	V3->set_length(0.05);
	Exp E3(V3);
	trace_pointer3 = E3.get_trace();
	num3 = E3.get_size();

	clock_t end = clock();

	double precomputation_time = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Precomputation time: " << precomputation_time << "s[CPU clock]" << endl;

	// graphical interface
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(900, 100);
	glutCreateWindow("Final Simulator Ver03");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	timer(0);

	glutCreateMenu(menu);
	glutAddMenuEntry("View Trace", 1);
	glutAddMenuEntry("View Real-time", 2);
	glutAddMenuEntry("View Still", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

	return 0;
}

void display()
{
	// initialization
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(1, 1, 1, 1);// white background

	init_display(isOrtho);

	glPushMatrix();
	glRotated(angle_x, 1.0f, 0.0f, 0.0f);
	glRotated(angle_y, 0.0f, 1.0f, 0.0f);
	glRotated(angle_z, 0.0f, 0.0f, 1.0f);

	glPushMatrix();
	glTranslated(0.0f, -50.0f, 0.0f);

	lab_config();

	// view trace
	if (view == 1)
	{
		// green ---------------------------------------------------------------------------
		if (green)
		{
			for (int i = 0; i < num; i += 1)
			{
				if (isCM)
				{
					//glPushMatrix();
					//glRotated(0.1 * i, 0, 1, 0);
					trace_pointer->at(i)->draw_center_of_mass(isOrtho, 2);
					//glPopMatrix();
				}
				else
				{
					//glPushMatrix();
					//glRotated(0.1 * i, 0, 1, 0);
					trace_pointer->at(i)->draw_leaf();
					//glPopMatrix();
				}
			}
		}

		// red ---------------------------------------------------------------------------
		if (red)
		{
			for (int i = 0; i < num2; i += 1)
			{
				if (isCM)
				{
					glPushMatrix();
					glRotated(0.1 * i, 0, 1, 0);
					trace_pointer2->at(i)->draw_center_of_mass(isOrtho, 1);
					glPopMatrix();
				}
				else
				{
					glPushMatrix();
					glRotated(0.1 * i, 0, 1, 0);
					trace_pointer2->at(i)->draw_leaf();
					glPopMatrix();
				}
			}
		}

		// blue ---------------------------------------------------------------------------
		if (blue)
		{
			for (int i = 0; i < num3; i += 1)
			{
				if (isCM)
				{
					//glPushMatrix();
					//glRotated(0.1 * i, 0, 1, 0);
					trace_pointer3->at(i)->draw_center_of_mass(isOrtho, 3);
					//glPopMatrix();
				}
				else
				{
					//glPushMatrix();
					//glRotated(0.1 * i, 0, 1, 0);
					trace_pointer3->at(i)->draw_leaf();
					//glPopMatrix();
				}
			}
		}

	}
	// view real-time
	else if (view == 2)
	{
		// green ---------------------------------------------------------------------------
		if (green)
		{
			if (isCM)
				trace_pointer->at(rt)->draw_center_of_mass(isOrtho, 2);
			else
			{
				//glPushMatrix();
				//glRotated(0.1 * rt, 0, 1, 0);
				trace_pointer->at(rt)->draw_leaf3(2);
				//trace_pointer->at(rt)->draw_leaf4();
				//glPopMatrix();
			}
		}

		// red ---------------------------------------------------------------------------
		if (red)
		{
			if (isCM)
				trace_pointer2->at(rt2)->draw_center_of_mass(isOrtho, 1);
			else
			{
				glPushMatrix();
				glRotated(0.1 * rt2, 0, 1, 0);
				trace_pointer2->at(rt2)->draw_leaf3(1);
				glPopMatrix();
			}
		}

		// blue ---------------------------------------------------------------------------
		if (blue)
		{
			if (isCM)
				trace_pointer3->at(rt3)->draw_center_of_mass(isOrtho, 3);
			else
			{
				//glPushMatrix();
				//glRotated(0.1 * rt2, 0, 1, 0);
				trace_pointer3->at(rt3)->draw_leaf3(3);
				//glPopMatrix();
			}
		}

	}
	// view still
	else
	{
		// green ---------------------------------------------------------------------------
		if (green)
		{
			// show both CM and object
			if (isCM)
			{
				// CM
				for (int i = 0; i < num; i++)
				{
					//glPushMatrix();
					//glRotated(0.1 * i, 0, 1, 0);
					trace_pointer->at(i)->draw_center_of_mass(isOrtho, 2);
					//glPopMatrix();
				}
				// object
				for (int i = 0; i < num; i += 190)
				{
					//glPushMatrix();
					//glRotated(0.1 * i, 0, 1, 0);
					trace_pointer->at(i)->draw_leaf3(2);
					//trace_pointer->at(i)->draw_leaf4();
					//glPopMatrix();
				}
			}
			else
			{
				for (int i = 0; i < num; i += 190)
				{
					//glPushMatrix();
					//glRotated(0.1 * i, 0, 1, 0);
					trace_pointer->at(i)->draw_leaf3(2);
					//trace_pointer->at(i)->draw_leaf4();
					//glPopMatrix();
				}
			}
		}

		// red ---------------------------------------------------------------------------
		if (red)
		{
			if (isCM)
			{
				// CM
				for (int i = 0; i < num2; i++)
				{
					glPushMatrix();
					glRotated(0.1 * i, 0, 1, 0);
					trace_pointer2->at(i)->draw_center_of_mass(isOrtho, 1);
					glPopMatrix();
				}
				// object
				for (int i = 0; i < num2; i += 100)
				{
					glPushMatrix();
					glRotated(0.1 * i, 0, 1, 0);
					trace_pointer2->at(i)->draw_leaf3(1);
					glPopMatrix();
				}
			}
			else
			{
				for (int i = 0; i < num2; i += 100)
				{
					glPushMatrix();
					glRotated(0.1 * i, 0, 1, 0);
					trace_pointer2->at(i)->draw_leaf3(1);
					glPopMatrix();
				}
			}
		}

		// blue ---------------------------------------------------------------------------
		if (blue)
		{
			if (isCM)
			{
				// CM
				for (int i = 0; i < num3; i++)
				{
					//glPushMatrix();
					//glRotated(0.1 * i, 0, 1, 0);
					trace_pointer3->at(i)->draw_center_of_mass(isOrtho, 3);
					//glPopMatrix();
				}
				// object
				for (int i = 0; i < num3; i += 100)
				{
					//glPushMatrix();
					//glRotated(0.1 * i, 0, 1, 0);
					trace_pointer3->at(i)->draw_leaf3(3);
					//glPopMatrix();
				}
			}
			else
			{
				for (int i = 0; i < num3; i += 100)
				{
					//glPushMatrix();
					//glRotated(0.1 * i, 0, 1, 0);
					trace_pointer3->at(i)->draw_leaf3(3);
					//glPopMatrix();
				}
			}
		}
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
		angle_x += 30;
		break;
	case 's':
		angle_y += 45;
		break;
	case 'd':
		angle_z += 30;
		break;
	case 'q':
		angle_x -= 30;
		break;
	case 'w':
		angle_y -= 45;
		break;
	case 'e':
		angle_z -= 30;
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
		break;
	// render multiple objects
	case 'l':
		if (red)
			red = false;
		else
			red = true;
		break;
	case 'j':
		if (green)
			green = false;
		else
			green = true;
		break;
	case 'k':
		if (blue)
			blue = false;
		else
			blue = true;
		break;
	default:
		break;
	}

	rt = 0;
	rt2 = 0;
	rt3 = 0;
	glutPostRedisplay();
}

void menu(int value)
{
	view = value;
	rt = 0;
	rt2 = 0;
	rt3 = 0;
	glutPostRedisplay();
}

void timer(int value)
{
	if (rt < num - step)
		rt += step;

	if (rt2 < num2 - step)
		rt2 += step;

	if (rt3 < num3 - step)
		rt3 += step;

	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);// 10ms
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
	rt2 = 0;
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
			printf("[3] Set Density\nOption: ");
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