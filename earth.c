#include "stdafx.h"
#include <GL/glut.h>
#include <math.h>
//#include <stdio.h>
#include <string.h>


void idleFunc();
void displayFunc();
void reshapeFunc(GLsizei width, GLsizei height);
void keyboardFunc(unsigned char, int, int);
void mouseFunc(int button, int state, int x, int y);
void initialize();


#define INC_VAL     1.0f



GLsizei g_width = 1280;
GLsizei g_height = 1024;

static GLboolean g_rotate = GL_TRUE;

static GLint page = 1;

GLenum g_fillmode = GL_FILL;

GLfloat g_light0_pos[4] = { 2.0f, 1.2f, 4.0f, 1.0f };

GLfloat g_light1_ambient[] = { .2f, .2f, .2f, 1.0f };
GLfloat g_light1_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat g_light1_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat g_light1_pos[4] = { -2.0f, 0.0f, -4.0f, 1.0f };


GLboolean g_clip1 = GL_FALSE;
GLboolean g_clip2 = GL_FALSE;
GLboolean g_clip3 = GL_FALSE;



GLdouble eqn1[4] = { 1.0, 0.0, 0.0, 0.0 };
GLdouble eqn2[4] = { 0.0, 1.0, 0.0, 0.0 };
GLdouble eqn3[4] = { 0.0, 0.0, 1.0, 0.0 };


GLfloat g_angle_y = 32.0f;
GLfloat g_inc = 0.0f;
GLfloat g_eye_y = 0;

GLfloat g_clip_x = 0.0f;
GLfloat g_clip_y = 0.0f;
GLfloat g_clip_z = 0.0f;

//PRABHUDEV SIR FUNCTION
void print(float x, float y, float z, char *textstring)
{
	//set the position of the text in the window using the x, y and z coordinates
	glRasterPos3f(x, y, z);
	//get the length of the string to display
	int len = (int)strlen(textstring);

	//loop to display character by character
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, textstring[i]);
	}
}



void first_page()
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.9, 0.9, 0.0);

	print(-1.0, 1.0, 0.0, "NIE INSTITUTE OF TECHNOLOGY, MYSORE");

	glColor3f(0.1, 0.9, 0.9);
	print(-2.45, 1.0, 0, "___________________________________________________________________________________________________");

	glColor3f(0.9, 0.0, 0.9);
	print(-0.7, 0.6, 0, "COMPUTER GRAPHICS MINI PROJECT");
	glColor3f(0.9, 0.9, 0.9);
	print(-0.8, 0.8, 0, "Department Of Computer Science and Engineering");

	glColor3f(0.7, 0.1, 0.1);
	print(-0.3, 0.4, 0.0, "'Layers Of Earth'");
	glColor3f(0.4, 0.5, 0.3);
	print(-1.8, -0.8, 0, "PROJECT ASSOCIATES");

	print(-1.9, -0.8, 0, "_______________________");
	glColor3f(0.6, 0.9, 0.7);
	print(-1.8, -1.0, 0, "NISARGA                     4NN11CS022");
	print(-1.8, -1.2, 0, "APEKSHA                     4NN11CS003");

	glColor3f(0.0, 0.0, 1.0);
	print(1.2, -1.2, 0, "PRESS 2 TO CONTINUE");

}

void second_page()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.4, 0.8, 0.6);
	print(-0.3, 1, 0, "INSTRUCTIONS");

	glColor3f(1, 1.0, 1.0);
	print(-2.45, 1, 0, "_______________________________________________________________________________________________________");
	glColor3f(0.7, 0.4, 0.5);
	print(-1.5, 0.8, 0, "->  '4' - cut along x=0 halfplane");
	print(-1.5, 0.6, 0, "->  '5' - cut along y=0 halfplane");
	print(-1.5, 0.4, 0, "->  '6' - cut along z=0 halfplane");
	print(-1.5, 0.2, 0, "->  'x', 'y', 'z' - reverse the corresponding half plane");
	print(-1.5, 0.0, 0, "->  '-', '=' - rotate about y-axis");
	print(-1.5, -0.2, 0, "->  (L / R) mouse buttons - rotate about y-axis");
	print(-1.5, -0.4, 0, "->  '[' ,  ']' - rotate viewpoint about x-axis");
	print(-1.5, -0.6, 0, "->  'f' -  fill/wireframe drawmode");
	glColor3f(0.2, 0.4, 0.7);
	print(1.2, -1.0, 0, "PRESS 3 TO IMPLEMENT");

}





void initialize()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	glFrontFace(GL_CCW);

	glPolygonMode(GL_FRONT_AND_BACK, g_fillmode);
	glEnable(GL_LIGHTING);

	glLightModeli(GL_FRONT, GL_TRUE);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, g_light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, g_light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, g_light1_specular);
	glEnable(GL_LIGHT1);
	printf("----------------------------------------------------\n");
	printf("Sphere Dissection sample in OpenGL\n");
	printf("----------------------------------------------------\n");
	printf("'1' - cut along x=0 halfplane\n");
	printf("'2' - cut along y=0 halfplane\n");
	printf("'3' - cut along z=0 halfplane\n");

	printf("'x', 'y', 'z' - reverse the corresponding half plane\n");
	printf("\n");
	printf("'-', '=' - rotate about y-axis\n");
	printf("(L/R) mouse buttons - rotate about y-axis\n");
	printf("'[', ']' - rotate viewpoint about x-axis\n");
	printf("'f' -  fill/wireframe drawmode\n");
	printf("----------------------------------------------------\n");
	printf("\n");
}


void reshapeFunc(GLsizei w, GLsizei h)
{

	g_width = w; g_height = h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 300.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(0.0f, 3.5f * sin(g_eye_y), 3.5f * cos(g_eye_y),
		0.0f, 0.0f, 0.0f,
		0.0f, (cos(g_eye_y) < 0 ? -1.0f : 1.0f), 0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, g_light0_pos);
	glLightfv(GL_LIGHT1, GL_POSITION, g_light1_pos);
}

void keyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '2': page = 2;
		break;
	case '3': page = 3;
		break;
	case 'f':
		g_fillmode = (g_fillmode == GL_FILL ? GL_LINE : GL_FILL);
		glPolygonMode(GL_FRONT_AND_BACK, g_fillmode);
		break;

	case '4':
		g_clip1 = !g_clip1;
		break;

	case '5':
		g_clip2 = !g_clip2;
		break;
	case '6':
		g_clip3 = !g_clip3;
		break;




	case '-':
		g_angle_y -= INC_VAL * 4.0f;
		break;
	case '=':
		g_angle_y += INC_VAL * 4.0f;
		break;

	case '[':
		g_eye_y -= .1f;
		break;
	case ']':
		g_eye_y += .1f;
		break;


	case 'x':
		eqn1[0] *= -1;
		break;
	case 'y':
		eqn2[1] *= -1;
		break;
	case 'z':
		eqn3[2] *= -1;
		break;
	case 'q':
		exit(0);
		break;

	}
	reshapeFunc(g_width, g_height);
	glutPostRedisplay();


}

void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{

		if (state == GLUT_DOWN)
			g_inc -= INC_VAL;
		else
			g_inc += INC_VAL;
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{



		if (state == GLUT_DOWN)
			g_inc += INC_VAL;
		else
			g_inc -= INC_VAL;
	}
	else
		g_inc = 0.0f;

	glutPostRedisplay();
}


void idleFunc()
{

	glutPostRedisplay();
}


void displayFunc()
{
	if (page == 1)
	{
		glClearColor(1,1,1,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                       //1st screen
		first_page();
		glFlush();
		glutSwapBuffers();
	}
	else if (page == 2)
	{
		glClearColor(1,1,1,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                            //2nd screen
		second_page();
		glFlush();
		glutSwapBuffers();
	}

	else if (page == 3)
	{


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		glPushMatrix();
		glRotatef(g_angle_y += g_inc, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
		glTranslatef(g_clip_x, 0.0f, 0.0f);
		glClipPlane(GL_CLIP_PLANE0, eqn1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, g_clip_y, 0.0f);
		glClipPlane(GL_CLIP_PLANE1, eqn2);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, 0.0f, g_clip_z);
		glClipPlane(GL_CLIP_PLANE2, eqn3);
		glPopMatrix();


		if (g_clip1)
			glEnable(GL_CLIP_PLANE0);
		else

			glDisable(GL_CLIP_PLANE0);

		if (g_clip2)
			glEnable(GL_CLIP_PLANE1);
		else
			glDisable(GL_CLIP_PLANE1);

		if (g_clip3)
			glEnable(GL_CLIP_PLANE2);
		else
			glDisable(GL_CLIP_PLANE2);



		glColor3f(1.0f, 1.0f, 1.0f);
		glutSolidSphere(.23, 16, 16);
		glColor3f(0.0f, 0.0f, 1.0f);
		print(0, 0, 0, "InnerCore");
		glColor3f(0.0f, 1.0f, 0.0f);
		print(0, 0.2, 0, "5200 km");
		glColor3f(0.0f, 1.0f, 1.0f);
		print(0, -0.2, 0, "4300deg C");



		glColor3f(1.0f, .8f, .2f);
		glutSolidSphere(.65, 16, 16);
		glColor3f(0.0f, 0.0f, 1.0f);
		print(0.0, 0.3, -0.4, "OuterCore");
		glColor3f(0.0f, 1.0f, 0.0f);
		print(0, 0.65, 0, "2900 km");
		glColor3f(0.0f, 1.0f, 1.0f);
		print(0, -0.6, -0.2, "3700deg C");

		glColor3f(1.0f, .1f, .1f);
		glutSolidSphere(1.2, 16, 16);
		glColor3f(0.0f, 0.0f, 1.0f);
		print(0, -0.9, 0.0, "MANTLE");
		glColor3f(0.0f, 1.0f, 1.0f);
		print(0, 0.6, -1.0, "1000deg C");


		glColor3f(0.5f, 0.5f, 0.5f);
		glutSolidSphere(1.3, 16, 16);
		glColor3f(0.0f, 0.0f, 1.0f);
		print(1.9, 1.9, -1.0, "CRUST");
		glColor3f(0.0f, 1.0f, 0.0f);
		print(0.0, 1.2, 0.0, "30 km");

		glPopMatrix();
		glFlush();
		glutSwapBuffers();
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	//glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(g_width, g_height);

	glutInitWindowPosition(1, 1);

	glutCreateWindow("Clipping Planes in OpenGL");

	glutIdleFunc(g_rotate ? idleFunc : NULL);

	initialize();

	glutDisplayFunc(displayFunc);
	glutKeyboardFunc(keyboardFunc);

	glutMouseFunc(mouseFunc);

	glutReshapeFunc(reshapeFunc);
	glutMainLoop();

	return 0;
}

#include "stdafx.h"
#include <GL/glut.h>
#include <math.h>
//#include <stdio.h>
#include <string.h>


void idleFunc();
void displayFunc();
void reshapeFunc(GLsizei width, GLsizei height);
void keyboardFunc(unsigned char, int, int);
void mouseFunc(int button, int state, int x, int y);
void initialize();


#define INC_VAL     1.0f



GLsizei g_width = 1280;
GLsizei g_height = 1024;

static GLboolean g_rotate = GL_TRUE;

static GLint page = 1;

GLenum g_fillmode = GL_FILL;

GLfloat g_light0_pos[4] = { 2.0f, 1.2f, 4.0f, 1.0f };

GLfloat g_light1_ambient[] = { .2f, .2f, .2f, 1.0f };
GLfloat g_light1_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat g_light1_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat g_light1_pos[4] = { -2.0f, 0.0f, -4.0f, 1.0f };


GLboolean g_clip1 = GL_FALSE;
GLboolean g_clip2 = GL_FALSE;
GLboolean g_clip3 = GL_FALSE;



GLdouble eqn1[4] = { 1.0, 0.0, 0.0, 0.0 };
GLdouble eqn2[4] = { 0.0, 1.0, 0.0, 0.0 };
GLdouble eqn3[4] = { 0.0, 0.0, 1.0, 0.0 };


GLfloat g_angle_y = 32.0f;
GLfloat g_inc = 0.0f;
GLfloat g_eye_y = 0;

GLfloat g_clip_x = 0.0f;
GLfloat g_clip_y = 0.0f;
GLfloat g_clip_z = 0.0f;

//PRABHUDEV SIR FUNCTION
void print(float x, float y, float z, char *textstring)
{
	//set the position of the text in the window using the x, y and z coordinates
	glRasterPos3f(x, y, z);
	//get the length of the string to display
	int len = (int)strlen(textstring);

	//loop to display character by character
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, textstring[i]);
	}
}



void first_page()
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.9, 0.9, 0.0);

	print(-1.0, 1.0, 0.0, "NIE INSTITUTE OF TECHNOLOGY, MYSORE");

	glColor3f(0.1, 0.9, 0.9);
	print(-2.45, 1.0, 0, "___________________________________________________________________________________________________");

	glColor3f(0.9, 0.0, 0.9);
	print(-0.7, 0.6, 0, "COMPUTER GRAPHICS MINI PROJECT");
	glColor3f(0.9, 0.9, 0.9);
	print(-0.8, 0.8, 0, "Department Of Computer Science and Engineering");

	glColor3f(0.7, 0.1, 0.1);
	print(-0.3, 0.4, 0.0, "'Layers Of Earth'");
	glColor3f(0.4, 0.5, 0.3);
	print(-1.8, -0.8, 0, "PROJECT ASSOCIATES");

	print(-1.9, -0.8, 0, "_______________________");
	glColor3f(0.6, 0.9, 0.7);
	print(-1.8, -1.0, 0, "NISARGA                     4NN11CS022");
	print(-1.8, -1.2, 0, "APEKSHA                     4NN11CS003");

	glColor3f(0.0, 0.0, 1.0);
	print(1.2, -1.2, 0, "PRESS 2 TO CONTINUE");

}

void second_page()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.4, 0.8, 0.6);
	print(-0.3, 1, 0, "INSTRUCTIONS");

	glColor3f(1, 1.0, 1.0);
	print(-2.45, 1, 0, "_______________________________________________________________________________________________________");
	glColor3f(0.7, 0.4, 0.5);
	print(-1.5, 0.8, 0, "->  '4' - cut along x=0 halfplane");
	print(-1.5, 0.6, 0, "->  '5' - cut along y=0 halfplane");
	print(-1.5, 0.4, 0, "->  '6' - cut along z=0 halfplane");
	print(-1.5, 0.2, 0, "->  'x', 'y', 'z' - reverse the corresponding half plane");
	print(-1.5, 0.0, 0, "->  '-', '=' - rotate about y-axis");
	print(-1.5, -0.2, 0, "->  (L / R) mouse buttons - rotate about y-axis");
	print(-1.5, -0.4, 0, "->  '[' ,  ']' - rotate viewpoint about x-axis");
	print(-1.5, -0.6, 0, "->  'f' -  fill/wireframe drawmode");
	glColor3f(0.2, 0.4, 0.7);
	print(1.2, -1.0, 0, "PRESS 3 TO IMPLEMENT");

}





void initialize()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	glFrontFace(GL_CCW);

	glPolygonMode(GL_FRONT_AND_BACK, g_fillmode);
	glEnable(GL_LIGHTING);

	glLightModeli(GL_FRONT, GL_TRUE);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, g_light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, g_light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, g_light1_specular);
	glEnable(GL_LIGHT1);
	printf("----------------------------------------------------\n");
	printf("Sphere Dissection sample in OpenGL\n");
	printf("----------------------------------------------------\n");
	printf("'1' - cut along x=0 halfplane\n");
	printf("'2' - cut along y=0 halfplane\n");
	printf("'3' - cut along z=0 halfplane\n");

	printf("'x', 'y', 'z' - reverse the corresponding half plane\n");
	printf("\n");
	printf("'-', '=' - rotate about y-axis\n");
	printf("(L/R) mouse buttons - rotate about y-axis\n");
	printf("'[', ']' - rotate viewpoint about x-axis\n");
	printf("'f' -  fill/wireframe drawmode\n");
	printf("----------------------------------------------------\n");
	printf("\n");
}


void reshapeFunc(GLsizei w, GLsizei h)
{

	g_width = w; g_height = h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 300.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(0.0f, 3.5f * sin(g_eye_y), 3.5f * cos(g_eye_y),
		0.0f, 0.0f, 0.0f,
		0.0f, (cos(g_eye_y) < 0 ? -1.0f : 1.0f), 0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, g_light0_pos);
	glLightfv(GL_LIGHT1, GL_POSITION, g_light1_pos);
}

void keyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '2': page = 2;
		break;
	case '3': page = 3;
		break;
	case 'f':
		g_fillmode = (g_fillmode == GL_FILL ? GL_LINE : GL_FILL);
		glPolygonMode(GL_FRONT_AND_BACK, g_fillmode);
		break;

	case '4':
		g_clip1 = !g_clip1;
		break;

	case '5':
		g_clip2 = !g_clip2;
		break;
	case '6':
		g_clip3 = !g_clip3;
		break;




	case '-':
		g_angle_y -= INC_VAL * 4.0f;
		break;
	case '=':
		g_angle_y += INC_VAL * 4.0f;
		break;

	case '[':
		g_eye_y -= .1f;
		break;
	case ']':
		g_eye_y += .1f;
		break;


	case 'x':
		eqn1[0] *= -1;
		break;
	case 'y':
		eqn2[1] *= -1;
		break;
	case 'z':
		eqn3[2] *= -1;
		break;
	case 'q':
		exit(0);
		break;

	}
	reshapeFunc(g_width, g_height);
	glutPostRedisplay();


}

void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{

		if (state == GLUT_DOWN)
			g_inc -= INC_VAL;
		else
			g_inc += INC_VAL;
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{



		if (state == GLUT_DOWN)
			g_inc += INC_VAL;
		else
			g_inc -= INC_VAL;
	}
	else
		g_inc = 0.0f;

	glutPostRedisplay();
}


void idleFunc()
{

	glutPostRedisplay();
}


void displayFunc()
{
	if (page == 1)
	{
		glClearColor(1,1,1,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                       //1st screen
		first_page();
		glFlush();
		glutSwapBuffers();
	}
	else if (page == 2)
	{
		glClearColor(1,1,1,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                            //2nd screen
		second_page();
		glFlush();
		glutSwapBuffers();
	}

	else if (page == 3)
	{


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		glPushMatrix();
		glRotatef(g_angle_y += g_inc, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
		glTranslatef(g_clip_x, 0.0f, 0.0f);
		glClipPlane(GL_CLIP_PLANE0, eqn1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, g_clip_y, 0.0f);
		glClipPlane(GL_CLIP_PLANE1, eqn2);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, 0.0f, g_clip_z);
		glClipPlane(GL_CLIP_PLANE2, eqn3);
		glPopMatrix();


		if (g_clip1)
			glEnable(GL_CLIP_PLANE0);
		else

			glDisable(GL_CLIP_PLANE0);

		if (g_clip2)
			glEnable(GL_CLIP_PLANE1);
		else
			glDisable(GL_CLIP_PLANE1);

		if (g_clip3)
			glEnable(GL_CLIP_PLANE2);
		else
			glDisable(GL_CLIP_PLANE2);



		glColor3f(1.0f, 1.0f, 1.0f);
		glutSolidSphere(.23, 16, 16);
		glColor3f(0.0f, 0.0f, 1.0f);
		print(0, 0, 0, "InnerCore");
		glColor3f(0.0f, 1.0f, 0.0f);
		print(0, 0.2, 0, "5200 km");
		glColor3f(0.0f, 1.0f, 1.0f);
		print(0, -0.2, 0, "4300deg C");



		glColor3f(1.0f, .8f, .2f);
		glutSolidSphere(.65, 16, 16);
		glColor3f(0.0f, 0.0f, 1.0f);
		print(0.0, 0.3, -0.4, "OuterCore");
		glColor3f(0.0f, 1.0f, 0.0f);
		print(0, 0.65, 0, "2900 km");
		glColor3f(0.0f, 1.0f, 1.0f);
		print(0, -0.6, -0.2, "3700deg C");

		glColor3f(1.0f, .1f, .1f);
		glutSolidSphere(1.2, 16, 16);
		glColor3f(0.0f, 0.0f, 1.0f);
		print(0, -0.9, 0.0, "MANTLE");
		glColor3f(0.0f, 1.0f, 1.0f);
		print(0, 0.6, -1.0, "1000deg C");


		glColor3f(0.5f, 0.5f, 0.5f);
		glutSolidSphere(1.3, 16, 16);
		glColor3f(0.0f, 0.0f, 1.0f);
		print(1.9, 1.9, -1.0, "CRUST");
		glColor3f(0.0f, 1.0f, 0.0f);
		print(0.0, 1.2, 0.0, "30 km");

		glPopMatrix();
		glFlush();
		glutSwapBuffers();
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	//glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(g_width, g_height);

	glutInitWindowPosition(1, 1);

	glutCreateWindow("Clipping Planes in OpenGL");

	glutIdleFunc(g_rotate ? idleFunc : NULL);

	initialize();

	glutDisplayFunc(displayFunc);
	glutKeyboardFunc(keyboardFunc);

	glutMouseFunc(mouseFunc);

	glutReshapeFunc(reshapeFunc);
	glutMainLoop();

	return 0;
}

