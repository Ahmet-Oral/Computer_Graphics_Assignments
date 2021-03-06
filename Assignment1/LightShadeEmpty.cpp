#include "pch.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <GL/glut.h>


/*TO DO: 
Declare 3 enum structures, namely: MaterialType, MaterialDisplayList and LightValues
Declare BRASS, RED_PLASTIC, EMERALD, SLATE in the 1st
TORUS_MATERIAL = 1, TEAPOT_MATERIAL = 2, ICO_MATERIAL = 3 in the 2nd
LIGHT_OFF, LIGHT_RED, LIGHT_WHITE, LIGHT_GREEN in the 3rd*/


GLfloat red_light[]   = { 1.0, 0.0, 0.0, 1.0 }, 
        green_light[] = { 0.0, 1.0, 0.0, 1.0 }, 
	    white_light[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat left_light_position[] =  {-1.0, 0.0, 1.0, 0.0 }, 
        right_light_position[] = { 1.0, 0.0, 1.0, 0.0 };

GLfloat brass_ambient[] = { 0.33, 0.22, 0.03, 1.0 }, 
        brass_diffuse[] = { 0.78, 0.57, 0.11, 1.0 }, 
	    brass_specular[] ={ 0.99, 0.91, 0.81, 1.0 }, 
	    brass_shininess = 27.8;

// TO DO: Declare appropriate ambient, diffuse, specular color arrays and shininess for red plastic, emerald and slate, too.
// Do not forget that typically, shininess of a red plastic is around 30, emerald 75, slate 0.6


int shade_model = GL_SMOOTH;
char *left_light, *right_light;
char *ico_material, *teapot_material, *torus_material;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glScalef(1.3, 1.3, 1.3);
	glRotatef(20.0, 1.0, 0.0, 0.0);
	
	glPushMatrix();
	glTranslatef(-0.65, 0.7, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glCallList(TORUS_MATERIAL);
	glutSolidTorus(0.275, 0.85, 10, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.75, -0.8, 0.0);
	glCallList(TEAPOT_MATERIAL);
	glutSolidTeapot(0.7);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 0.0, -1.0);
	glCallList(ICO_MATERIAL);
	glutSolidIcosahedron();
	glPopMatrix();

	glPopMatrix();
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 3000, 0, 3000);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
	glutSwapBuffers();
}

void light_select(GLenum lg, int value, char **label)
{
	glEnable(lg);
	switch (value) {
		case LIGHT_OFF:
			*label = (char*)"off";
			glDisable(lg);
			break;
		case LIGHT_RED:
			*label = (char*)"red";
			glLightfv(lg, GL_DIFFUSE, red_light);
			break;
		case LIGHT_WHITE:
			*label = (char*)"white";
			glLightfv(lg, GL_DIFFUSE, white_light);
			break;
		case LIGHT_GREEN:
			*label = (char*)"green";
			glLightfv(lg, GL_DIFFUSE, green_light);
			break;
	}
	glutPostRedisplay();
}

void left_light_select(int value)
{
	light_select(GL_LIGHT0, value, &left_light);
}

void right_light_select(int value)
{
	light_select(GL_LIGHT1, value, &right_light);
}

void material(int dlist, GLfloat * ambient, GLfloat * diffuse,	GLfloat * specular, GLfloat shininess)
{
	glNewList(dlist, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glEndList();
}

char * material_select(int object, int value)
{
	glutPostRedisplay();
	switch (value) {
		case BRASS:
			material(object, brass_ambient,	brass_diffuse, brass_specular, brass_shininess);
			return (char*)"brass";
		case RED_PLASTIC:
			//TO DO: call material function similarly
			return (char*)"red plastic";
		case EMERALD:
			//TO DO: call material function similarly
			return (char*)"emerald";
		case SLATE:
			//TO DO: call material function similarly
			return (char*)"slate";
	}
	return NULL; /* avoid bogus warning! */
}

void torus_select(int value)
{
	torus_material = material_select(TORUS_MATERIAL, value);
}

void teapot_select(int value)
{
	teapot_material = material_select(TEAPOT_MATERIAL, value);
}

void ico_select(int value)
{
	ico_material = material_select(ICO_MATERIAL, value);
}

void main_menu_select(int value)
{
	if (value == 666)
		exit(0);
	//TO DO: Call glShadeModel with appropriate parameter
	
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	int left_light_m, right_light_m, torus_m, teapot_m, ico_m;

	glutInitWindowSize(400, 400);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Week 5 Lab Task 2 Lighting");
	glutDisplayFunc(display);

	//TO DO: uncomment these parts to observe how to add menu entries
//#define LIGHT_MENU_ENTRIES() \
//    glutAddMenuEntry("Disable", LIGHT_OFF); \
//    glutAddMenuEntry("Red", LIGHT_RED); \
//    glutAddMenuEntry("White", LIGHT_WHITE); \
//    glutAddMenuEntry("Green", LIGHT_GREEN);
//#define MATERIAL_MENU_ENTRIES() \
//    glutAddMenuEntry("Brass", BRASS); \
//    glutAddMenuEntry("Red plastic", RED_PLASTIC); \
//    glutAddMenuEntry("Emerald", EMERALD); \
//    glutAddMenuEntry("Slate", SLATE);
//
//	left_light_m = glutCreateMenu(left_light_select);
//	LIGHT_MENU_ENTRIES();
//	right_light_m = glutCreateMenu(right_light_select);
//	LIGHT_MENU_ENTRIES();
//	torus_m = glutCreateMenu(torus_select);
//	MATERIAL_MENU_ENTRIES();
//	teapot_m = glutCreateMenu(teapot_select);
//	MATERIAL_MENU_ENTRIES();
//	ico_m = glutCreateMenu(ico_select);
//	MATERIAL_MENU_ENTRIES();
//
//	glutCreateMenu(main_menu_select);
//
//	glutAddMenuEntry("Smooth shading", GL_SMOOTH);
//	glutAddMenuEntry("Flat shading", GL_FLAT);
//	glutAddSubMenu("Left light", left_light_m);
//	glutAddSubMenu("Right light", right_light_m);
//	glutAddSubMenu("Torus", torus_m);
//	glutAddSubMenu("Teapot", teapot_m);
//	glutAddSubMenu("Icosahedron", ico_m);
//	glutAddMenuEntry("Quit", 666);
//	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glLightfv(GL_LIGHT0, GL_POSITION, left_light_position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightfv(GL_LIGHT1, GL_POSITION, right_light_position);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);
	left_light_select(LIGHT_RED);
	right_light_select(LIGHT_GREEN);
	torus_select(RED_PLASTIC);
	teapot_select(BRASS);
	ico_select(EMERALD);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glLineWidth(1.0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective( 50.0, 1.0, 1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 5.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.);  
	glTranslatef(0.0, 0.0, -1.0);

	glutMainLoop();
	return 0;          
}