//ALPHA BLENDING AND ANTIALIASING
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <GL\freeglut.h>
#include <math.h>


GLfloat light0_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
//TO DO: Create the diffuse component of light 0 similar to ambient. Use 0 for RGB components and 1 for alpha

//TO DO: Create the diffuse component of light 1 similar to above. Make it yellow and use 1 for alpha
//TO DO: Declare the position of light 1 similarly.Use 1 in all 3 directions and 0 for the 4th 

//TO DO: Create the diffuse component of light 2 similar to above. Make it turqoise and use 1 for alpha
//TO DO: Declare the position of light 2 similarly.Use -1 in all 3 directions and 0 for the 4th 

GLfloat angle1 = 0.0, angle2 = 0.0;

void write(GLfloat x, GLfloat y, char *text) //This function outputs the characters we see on the screen
{
	char *p;

	glPushMatrix();
	glTranslatef(x, y, 0);
	for (p = text; *p; p++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	glPopMatrix();
}

void display(void)
{
	static GLfloat amb[] = 	{ 0.4, 0.4, 0.4, 0.5 };
	static GLfloat dif[] =	{ 1.0, 1.0, 1.0, 0.6 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//NOTICE THAT LIGHT 1 IS AFFECTING THE FIRST ICOSA
	glEnable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	
	//TO DO: Assign amb and dif arrays to the material using glMaterialfv function. Use only the front side for both ambient and diffuse
	//You will find the same usage somewhere below!!!
	

	glPushMatrix();
	glTranslatef(-0.3, -0.3, 0.0);
	
	//TO DO: rotate first icosa by angle1 in 1.0 x and 0.5 y directions
	
	glCallList(1);        /* render ico display list */
	glPopMatrix();

	glClear(GL_DEPTH_BUFFER_BIT);
	
	//NOTICE THAT LIGHT 2 IS AFFECTING THE SECOND ICOSA
	glEnable(GL_LIGHT2);
	glDisable(GL_LIGHT1);
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

	glPushMatrix();
	glTranslatef(0.3, 0.3, 0.0);
	//TO DO: rotate second icosa by angle2 in 1.0 x and 0.5 z directions
	glCallList(1);        /* render ico display list */
	glPopMatrix();

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 1500, 0, 1500);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	write(100, 225, (char*) "THIS IS ANTIALIASED.");
	
	//Until now, line smoothing was enabled. TO DO: Now disable OpenGL line smoothing
	
	glDisable(GL_BLEND);
	
	write(100, 40, (char*)"THIS TEXT IS NOT.");
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
	glMatrixMode(GL_MODELVIEW);

	glutSwapBuffers();
}

void idle(void)
{
	//TO DO: give an appropriate increase for both angles, angle1 and angle2, so that they rotate. E.g. angle1 +=.....
	
	glutPostRedisplay();
}

void visible(int vis)
{
	if (vis == GLUT_VISIBLE)
		glutIdleFunc(idle);
	else
		glutIdleFunc(NULL);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Week5LAB_Task1_AA_AlphaBlend");
	glutDisplayFunc(display);
	glutVisibilityFunc(visible);

	glNewList(1, GL_COMPILE);  /* create ico display list */
	glutSolidIcosahedron();
	glEndList();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);

	//TO DO: Uncomment the below lines
	/*glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);*/
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2.0);

	glMatrixMode(GL_PROJECTION);
	gluPerspective( 50.0, 1.0,1.0, 10.0); //fov, aspect ratio, near, far
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.);  //eye, center, up
	glTranslatef(0.0, 0.6, -1.0);

	glutMainLoop();
	return 0; 
}


