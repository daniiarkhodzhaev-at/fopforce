#include "Display.h"


void Display::reshape(int x, int y){
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat ratio = static_cast<float>(x) / y;
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void Display::processNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
		case 27 :
            exit(0);
			break;
	}
}

void Display::processSpecialKeys(int key, int xx, int yy) {
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

void Display::display(void)
{
    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();

    gluLookAt(  radius*sin(camera_phi), radius*cos(camera_phi), camera_z,
				0,	0,  0,
				-1.0f*sin(atan(camera_z / radius))*sin(camera_phi), -1.0f	* sin(atan(camera_z / radius))*cos(camera_phi),  1.0f	* cos(atan(camera_z / radius))	);

    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0.0,0.0,0.0);
    // Red color used to draw.


    Display::drawAxises();
    Display::drawCone();
    //drawParticle();

    // Flush buffers to screen

    glFlush();
    // sawp buffers called because we are using double buffering
   glutSwapBuffers();
}


void Display::idle(void)
{
    display();
}

void Display::drawCone(){
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

void Display::drawAxises(){
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
