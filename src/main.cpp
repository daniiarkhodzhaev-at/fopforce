#include <GL/freeglut.h>
#include <GL/glu.h>

#include <Display.h>
#include <RandomNumberGenerator.h>

#include <stdlib.h>

#include <vector>

void display(void);
void reshape(int x, int y);
void display_cone(void);

struct Coord{
    float x, y, z;
};

int N = 10000;
std::vector<Coord> particles;
std::vector<Coord> velocities;




int main (int argc, char **argv)
{

    /*
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

        v.x = rnd.getRandomFloat(-v_max*10, v_max*10);
        v.y = rnd.getRandomFloat(-v_max*10, v_max*10);
        v.z = rnd.getRandomFloat(-v_max, 0);
        particles.push_back(c);
        velocities.push_back(v);
    }
    */

    glutInit(&argc, argv);
    glutInitWindowSize(350,350);
    glutCreateWindow("Solid Sphere");


    glutDisplayFunc(Display::display);
    glutReshapeFunc(Display::reshape);

    glutSpecialFunc(Display::processSpecialKeys);
    glutKeyboardFunc(Display::processNormalKeys);

    Display::init();
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

