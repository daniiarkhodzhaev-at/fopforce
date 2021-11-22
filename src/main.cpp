#include <GL/freeglut.h>
#include <GL/glu.h>

#include "Display.h"
#include "RandomNumberGenerator.h"

#include <stdlib.h>

#include <vector>
#include <math.h>
#include <iostream>

void display(void);
void reshape(int x, int y);
void display_cone(void);

float camera_phi = 0.0;
float camera_z = 0.0;

float deltaAngle = 0.05f;
float deltaZ = 0.5f;

struct Coord{
    float x, y, z;
};

int N = 10000;
std::vector<Coord> particles;
std::vector<Coord> velocities;

void idle(void)
{
    display();
}

void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
		case GLUT_KEY_LEFT :
			camera_phi -= deltaAngle;
			break;
		case GLUT_KEY_RIGHT :
			camera_phi += deltaAngle;
			break;
        case GLUT_KEY_DOWN :
            camera_z -= deltaZ;
            break;
        case GLUT_KEY_UP :
            camera_z += deltaZ;
            break;
	}
}

void processNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
		case 27 :
            exit(0);
			break;
	}
}

int main (int argc, char **argv)
{
    Coord c;
    Coord v;
    RandomNumberGenerator rnd;
    particles.reserve(N);
    velocities.reserve(N);
    float c_max = 0; //0.01f;
    float v_max = 0.001f;
    for (int i = 0; i < N; ++i){
        c.x = rnd.getRandomFloat(-c_max, c_max);
        c.y = rnd.getRandomFloat(-c_max, c_max);
        c.z = rnd.getRandomFloat(-c_max, c_max);

        v.x = rnd.getRandomFloat(-v_max/2, v_max/2);
        v.y = rnd.getRandomFloat(-v_max/2, v_max/2);
        v.z = rnd.getRandomFloat(-v_max, 0);
        particles.push_back(c);
        velocities.push_back(v);
    }

    glutInit(&argc, argv);
    glutInitWindowSize(350,350);
    glutCreateWindow("Solid Sphere");


    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutIdleFunc(idle);

    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processNormalKeys);

    glutMainLoop();
    return 0;
}



void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat ratio = static_cast<float>(x) / y;
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);
    //gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,21.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void drawCone(){
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    // changing in transformation matrix.
    glRotatef(-0,1.0,0.0,0.0);
    glRotatef(-0,0.0,1.0,0.0);

    glScalef(1.0,1.0,1.0);
    // built-in (glut library) function , draw you a sphere.

    glutWireCone(1, 3, 16, 16);

    glPopMatrix();
}

void drawAxises(){
    glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glRotatef(0.0,1.0,0.0,0.0);
        glRotatef(0.0,0.0,1.0,0.0);
        glRotatef(90.0,0.0,0.0,1.0);
        glutSolidCylinder(0.02, 4.0, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glRotatef(0.0,1.0,0.0,0.0);
        glRotatef(-90.0,0.0,1.0,0.0);
        glRotatef(0.0,0.0,0.0,1.0);
        glutSolidCylinder(0.02, 4.0, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glRotatef(-90.0,1.0,0.0,0.0);
        glRotatef(0.0,0.0,1.0,0.0);
        glRotatef(0.0,0.0,0.0,1.0);
        glutSolidCylinder(0.02, 4.0, 16, 16);
    glPopMatrix();

}

void drawParticle(){
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    for (int i = 0; i < N; ++i){
        glTranslated(particles[i].x, particles[i].y, particles[i].z);
        glutWireSphere(0.04, 5, 5);
        particles[i].x += velocities[i].x;
        particles[i].y += velocities[i].y;
        particles[i].z += velocities[i].z;
    }
    glPopMatrix();
}


void display(void)
{


    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();

    gluLookAt(	   5.0f*sin(camera_phi),	5.0f*cos(camera_phi),	  camera_z,
				0,	0,  0,
				-1.0f	* sin(atan(camera_z / 5.0f))*sin(camera_phi),   -1.0f	* sin(atan(camera_z / 5.0f))*cos(camera_phi),  1.0f	* cos(atan(camera_z / 5.0f))	);

    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0.0,0.0,0.0);
    // Red color used to draw.


    drawAxises();
    drawCone();
    drawParticle();

    // Flush buffers to screen

    glFlush();
    // sawp buffers called because we are using double buffering
   glutSwapBuffers();
}
