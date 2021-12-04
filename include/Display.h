#include <GL/freeglut.h>
#include <GL/glu.h>

#include <math.h>
#include <iostream>

class Display{
private:
    inline static float FPS = 60;

    inline static float camera_phi = 0.0f;
    inline static float camera_z = 0.0f;

    inline static float deltaAngle = 0.05f;
    inline static float deltaZ = 0.05f;

    inline static float radius = 5.0f;

public:

    static void reshape(int x, int y);

    static void processNormalKeys(unsigned char key, int x, int y);
    static void processSpecialKeys(int key, int xx, int yy);

    static void timer(int);
    static void display(void);

    static void drawCone();
    static void drawAxises();
    static void drawParticle();
};
