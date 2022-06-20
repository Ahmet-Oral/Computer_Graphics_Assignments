#include<windows.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

//Ahmet Oral - 180709008
//Introduction to Computer Graphics - Midterm Assignment
///////////////////////////////////////////////////////////////
//-----------------------------------------------------------
//For all planets, rotation speed around the sun is realistic.
//-----------------------------------------------------------
//Scale is also realistic for all planets.
//---------------------------------------------------------- -
//Distance from the sun is not realistic because if it would be 
//...realistic even jupiter wouldn't be bigger than 1 pixel so I
//...reduced the distance in realistic ratio.
//-----------------------------------------------------------
//Program is interactive with the user.You can zoom in, out and 
//... change the angle you look with 'Up and Down Arrow' keys.
//... If user press Escape Key program closes.
//-----------------------------------------------------------
//You can changle the light by clicking right mouse button and
//...selecting the light you want.There are 4 light options:
//...Disable lightning - Red light - Green Light - White Light 
//... and a reset option to take all changes back.
//-----------------------------------------------------------
//Sadly I couldn't manage to add a texture feature.I run into lots
//of issues and errors I couldn't fix no matter what I do :/
///////////////////////////////////////////////////////////////



using namespace std;
float eyeX = 0.0f;
float eyeY = 2.0f;
float eyeZ = 2.0f;
char* light;

//Used in the rings of saturn
double angular = 2 * 3.14 / 50;

//Coordinates of the light source
GLfloat qPos[] = { 0,0,0,0.1 };

//Light values we can select at change lights menu.
enum LightValues {
    LIGHT_OFF,
    LIGHT_RED,
    LIGHT_WHITE,
    LIGHT_GREEN,
    RESET,
};

//Red green white lights and ambient color used in change lights menu
GLfloat red_light[] = { 1.0, 0.0, 0.0, 1.0 },
green_light[] = { 0.0, 1.0, 0.0, 1.0 },
white_light[] = { 1.0, 1.0, 1.0, 1.0 },
ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };


//Changing Lights menu: there are 4 options so a switch case is used.Light can be changed to red, green or white.
//... Also light can be disabled completely.Lastly there is an option to reset all changes.
void light_select(int value, char** label)
{
    glEnable(GL_LIGHT7);
    switch (value) {

        //If light turned off.
    case LIGHT_OFF:
        *label = (char*)"off";
        //Disable lights.
        glDisable(GL_LIGHT7);
        glDisable(GL_LIGHT0);
        break;

        //If we change light color we add light values we defined before.
    case LIGHT_RED:
        *label = (char*)"red";
        glEnable(GL_LIGHT0);
        //Use red light
        glLightfv(GL_LIGHT7, GL_DIFFUSE, red_light);
        break;
    case LIGHT_WHITE:
        *label = (char*)"white";
        glEnable(GL_LIGHT0);
        //Use white light
        glLightfv(GL_LIGHT7, GL_DIFFUSE, white_light);
        break;
    case LIGHT_GREEN:
        *label = (char*)"green";
        glEnable(GL_LIGHT0);
        //Use green light
        glLightfv(GL_LIGHT7, GL_DIFFUSE, green_light);
        break;
    //If user wants to reset the changes.
    case RESET:
        *label = (char*)"Reset";
        glDisable(GL_LIGHT7);
        glDisable(GL_LIGHT0);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT7);
        //Use the default light.
        glLightfv(GL_LIGHT7, GL_DIFFUSE, ambientColor);
        break;
    }
    glutPostRedisplay();
}

//Changle lights menu
void lights_select(int value)
{
    light_select(value, &light);
}

void main_menu_select(int value)
{
    if (value == 666)
        exit(0);
    glShadeModel(GLU_SMOOTH);
    glutPostRedisplay();
}




//Closing the program when user press Escape key.
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
    case 27: //Escape key
        exit(0);
    }
}

//Initializes 3D rendering.
void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING); //Enable lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1
    glEnable(GL_NORMALIZE); //Automatically normalize normals

}

//Called when the window is resized.
void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

//------------------------------------------------
float _angle = 0.0f;
void update(int value);

//Draw Planets --------------------------
void drawSun() {
    //sun
    glColor3f(255, 255, 0.0);        //Colour of the sun
    glutSolidSphere(0.75, 200, 200); //Sizes of the sun


}   

float MercuryAngle, MercurySpeed = 4.7f;
void drawMercury() {
    //mercury
        
    //Orbit
    glColor3f(1, 1, 1);
    glutWireTorus(1.14, 0, 100, 1);//Orbit distance

    glPushMatrix();
    glRotatef(MercuryAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(1.14, .1, 0.0); //distance height depth

    glColor3f(.88, .88, .88);
    glutSolidSphere(0.048, 100, 100);//size
    glPopMatrix();
}

float VenusAngle, VenusSpeed = 3.5f;
void drawVenus() {
    //Venus

        //Orbit
    glColor3f(1, 1, 1);
    glutWireTorus(2.16, 0, 100, 1);

    glPushMatrix();
    glRotatef(VenusAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(2.16, 0.1, 0.0); //distance

    glColor3f(.96, .82, .6);
    glutSolidSphere(0.125, 100, 100); //size
    glPopMatrix();
}

//Moons rotates 12 times around the earth while earth rotates 1 time around the sun.
float EarthAngle, angleMoon , MoonSpeed = 27.0f, EarthSpeed = 2.9f;
void drawEarth() {
    glColor3f(1, 1, 1);
    glutWireTorus(3, .0, 100, 1);
    glPushMatrix();
    glRotatef(EarthAngle, 0.0, 1.0, 0.0);
    glTranslatef(3, 0.1, 0.0); //distance
    glColor3f(.27, .68, .93);
    glScalef(0.23, 0.23, 0.23);
    glutSolidSphere(0.6, 50, 50);//size of earth
    glPushMatrix();

    glRotatef(angleMoon, 0.0, 0.1, 0.05);
    glTranslatef(1.3, 0.0, 0.0); //distance
    glColor3f(1.0, 1.0, 1.0);
    
    glutSolidSphere(0.1, 100, 100);//size of moon
    glPopMatrix();//for moon
    glPopMatrix();//for earth
}

float MarsAngle, MarsSpeed = 2.4f;
void drawMars() {
    //mars

    //Orbit
    glColor3f(1, 1, 1);
    glutWireTorus(4.5, 0, 100, 1);

    glPushMatrix();
    glRotatef(MarsAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(4.5, 0.1, 0.0); //distance

    glColor3f(.99, .33, .3);
    glutSolidSphere(.067, 100, 100);//size
    glPopMatrix();
}

float JupiterAngle, JupiterSpeed = 1.3f;
void drawJupiter() {
    //Jupiter

    //Orbit
    glColor3f(1, 1, 1);
    glutWireTorus(10.4, 0, 100, 1);

    glPushMatrix();
    glRotatef(JupiterAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(10.4, 0.1, 0.0); //distance

    glColor3f(.67, .59, .53);
    glutSolidSphere(1.42, 100, 100);//size
    glPopMatrix();
}

float SaturnAngle, SaturnSpeed = 0.960f;
void drawSaturn() {
    //Saturn

    //Orbit
    glColor3f(1, 1, 1);
    glutWireTorus(16, 0, 100, 1);

    glPushMatrix();
    glRotatef(SaturnAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(16, 0.1, 0.0); //distance

    glColor3f(.75, .62, .43);
    glutSolidSphere(1.20, 100, 100);//size
    glPushMatrix();

    glRotatef(45, 1.0, 0.0, 0.0);
    glPointSize(3);
    glColor3f(5.0, 3.0, 1.0);
    glScalef(1.2, 1.2, 1.2);
    glBegin(GL_POINTS);
    double ang1 = 0.0;
    int i = 0;
    for (i = 0; i < 50; i++)
    {
        glVertex2d(cos(ang1), sin(ang1));
        ang1 += angular;
    }
    glEnd();

    glPointSize(2);
    glPopMatrix();//ring 
    glPopMatrix(); //saturn
}

float UranusAngle, UranusSpeed = 0.68f;
void drawUranus() {
    //Uranus

    //Orbit
    glColor3f(1, 1, 1);
    glutWireTorus(25, 0, 100, 1);

    glPushMatrix();
    glRotatef(UranusAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(25, 0.1, 0.0); //distance

    glColor3f(.5, .62, .8);
    glutSolidSphere(.51, 100, 100);//size
    glPopMatrix();
}

float NeptuneAngle, NeptuneSpeed = 0.543f;
void drawNeptune() {
    //Neptune

    //Orbit
    glColor3f(1, 1, 1);
    glutWireTorus(40, 0, 100, 1);

    glPushMatrix();
    glRotatef(NeptuneAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(40, 0.1, 0.0); //distance

    glColor3f(.22, .32, .82);
    glutSolidSphere(.49, 100, 100);//size
    glPopMatrix();
}

//------------------------------------------------

//Draws the 3D scene
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Where light source is.
    glLightfv(GL_LIGHT7, GL_POSITION, qPos);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(7.0f, eyeY, eyeZ,
        0.0f, 0.0f, -7.0f,            //Change the position of the camera
        0.0f, 2.0f, 3.0f);


    glTranslatef(0.0f, 0.6f, -7.5f);

    //Add ambient light
    GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f }; //Color (0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    glColor3f(1.0f, 1.0f, 0.0f);

    // rotate the whole scene by 20 degree
    glRotatef(40, 1.0f, .5f, -0.35f);


    //------------Call Draw Functions-------------
    drawSun();
    drawMercury();
    drawVenus();
    drawEarth();
    drawMars();
    drawJupiter();
    drawSaturn();
    drawUranus();
    drawNeptune();


    glutSwapBuffers();
}
//--------------Draw Ends----------------------


//Up and Down arrow keys zoom or out the model.
void keyboardSpecial(int key, int xx, int yy)
{
    switch (key) {
    case GLUT_KEY_UP:
        eyeY -= 1.0f;
        eyeZ -= 1.0f;
        break;
    case GLUT_KEY_DOWN:
        eyeY += 1.0f;
        eyeZ += 1.0f;
        break;
    }
}



//Update all planets and moon
void update(int value) {

    angleMoon += MoonSpeed;
    if (angleMoon > 360) {
        angleMoon -= 360;
    }

    MercuryAngle += MercurySpeed;
    if (MercuryAngle > 360.0f)
        MercuryAngle -= 360.0f;

    VenusAngle += VenusSpeed;
    if (VenusAngle > 360.0f)
        VenusAngle -= 360.0f;

    EarthAngle += EarthSpeed;
    if (EarthAngle > 360.0f)
        EarthAngle -= 360.0f;

    MarsAngle += MarsSpeed;
    if (MarsAngle > 360.0f)
        MarsAngle -= 360.0f;

    JupiterAngle += JupiterSpeed;
    if (JupiterAngle > 360.0f)
        JupiterAngle -= 360.0f;

    SaturnAngle += SaturnSpeed;
    if (SaturnAngle > 360.0f)
        SaturnAngle -= 360.0f;

    UranusAngle += UranusSpeed;
    if (UranusAngle > 360.0f)
        UranusAngle -= 360.0f;

    NeptuneAngle += NeptuneSpeed;
    if (NeptuneAngle > 360.0f)
        NeptuneSpeed -= 360.0f;

   

    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

//-----------------------------------------------------

int main(int argc, char** argv) {


    int light_menu;

    //Contents of the 'Change Light' menu.
#define LIGHT_MENU_ENTRIES() \
    glutAddMenuEntry("Disable", LIGHT_OFF); \
    glutAddMenuEntry("Red", LIGHT_RED); \
    glutAddMenuEntry("White", LIGHT_WHITE); \
    glutAddMenuEntry("Green", LIGHT_GREEN); \
    glutAddMenuEntry("Reset", RESET);


    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1050, 650);

    //Create the window
    glutCreateWindow("Solar System");
    initRendering();

    //Set handler functions
    glutDisplayFunc(drawScene);


    //Defining Change Light menu and adding contents in it.
    light_menu = glutCreateMenu(lights_select);
    LIGHT_MENU_ENTRIES();

    glutCreateMenu(main_menu_select);
    //Menu and submenu entries
    glutAddSubMenu("Change light", light_menu);
    glutAddMenuEntry("Quit", 666);
    //Right mouse click opens the menu
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    //Zoom in and Out
    glutSpecialFunc(keyboardSpecial);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);

    glutTimerFunc(1, update, 0); //Add a timer

    glutMainLoop();
    return 0;
}