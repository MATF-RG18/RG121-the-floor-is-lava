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
    // Position and parameters of light source
    GLfloat light_position[] = { 5, 7, 5, 0 };
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1 };
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    GLfloat light_specular[] = { 0.7, 0.7, 0.7, 1 };

    GLfloat ambient_coeffs[] = { 0.2, 0.2, 0.2, 1 };
    GLfloat diffuse_coeffs[] = { 0.3, 0.3, 0.3, 1 };
    GLfloat specular_coeffs[] = { 0.7, 0.7, 0.7, 1 };
    GLfloat shininess = 20;

    GLfloat ambient_coeffs_player[] = { 0.2, 0.2, 0.9, 1 };
    GLfloat diffuse_coeffs_player[] = { 0.5, 0.5, 0.5, 1 };
    GLfloat specular_coeffs_player[] = { 0.7, 0.7, 0.7, 1 };

    // Clearing buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Positioning the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(px+7, 10, pz+7,
              px-3, 0.5, pz-3,
              0, 1, 0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glDisable(GL_LIGHTING);
    // Floor
    glColor3f(0.55, 0.09, 0.09);
    glBegin(GL_POLYGON);
        glVertex3f(-50, 0, -50);
        glVertex3f(-50, 0, 50);
        glVertex3f(50, 0, 50);
        glVertex3f(50, 0, -50);
    glEnd();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //Drawing initial block
    glPushMatrix();
      glTranslatef(px, 2.5, pz);
      glColor3f(1, 0, 0);
      glutSolidCube(5);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(px, 2.5, pz);
      glColor3f(1, 0, 0);
      glutSolidCube(5);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_player);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_player);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs_player);

    // Drawing player on the block
    glPushMatrix();
      glColor3f(0, 0, 1);
      glTranslatef(px, py+5.5, pz);
      glutSolidSphere(0.5, 40, 40);
    glPopMatrix();

    // Swapping buffers
    glutSwapBuffers();
}
