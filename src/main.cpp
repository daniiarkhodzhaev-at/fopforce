#include <GL/freeglut.h>
#include <GL/glu.h>

#include "Display.h"

#include <stdlib.h>

int main (int argc, char **argv)
{
    int N = 50000;
    Display* d = new Display(N);

    glutInit(&argc, argv);
    glutInitWindowSize(550,550);
    glutCreateWindow("Modeling");


    glutDisplayFunc(Display::display);
    glutReshapeFunc(Display::reshape);

	glutSpecialFunc(Display::processSpecialKeys);
    glutKeyboardFunc(Display::processNormalKeys);

    Display::timer(0);
    glutMainLoop();
    return 0;
}

/*
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
*/

