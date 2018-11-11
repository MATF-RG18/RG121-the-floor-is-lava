#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

static int window_width = 600, window_height = 600;
// Player position
static float px = 5, py = 0, pz = 5;

// Declaring callback functions
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

int main(int argc, char **argv)
{
    // Initializing GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    // Creating window
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    // Registering callback functions
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    // Initializing OpenGL
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    // Entering main loop
    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}

static void on_reshape(int width, int height)
{
    // Setting viewport
    glViewport(0, 0, width, height);

    // Saving window width and height
    window_width = width;
    window_height = height;

    // Setting projection parameters
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 1000);
}

static void on_display(void)
{
    // Clearing buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Positioning the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(px+7, 10, pz+7,
              px-3, 0.5, pz-3,
              0, 1, 0);

    // Floor
    glColor3f(0.55, 0.09, 0.09);
    glBegin(GL_POLYGON);
        glVertex3f(-50, 0, -50);
        glVertex3f(-50, 0, 50);
        glVertex3f(50, 0, 50);
        glVertex3f(50, 0, -50);
    glEnd();

    //Drawing initial block
    glPushMatrix();
      glTranslatef(px, 2.5, pz);
      glColor3f(0.2, 0.2, 0.2);
      glutSolidCube(5);
    glPopMatrix();

    // Drawing player on the block
    glPushMatrix();
      glColor3f(0, 0, 1);
      glTranslatef(px, py+5.5, pz);
      glutSolidSphere(0.5, 40, 40);
    glPopMatrix();

    // Swapping buffers
    glutSwapBuffers();
}
