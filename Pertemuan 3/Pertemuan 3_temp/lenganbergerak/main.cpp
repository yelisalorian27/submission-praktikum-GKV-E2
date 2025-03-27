#include <GLUT/glut.h>
#include <cstdlib>

static int shoulder = 0, elbow = 0;
static int palm = 0;
static int fingers = 0;
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void drawFinger()
{
    glPushMatrix();
    glScalef(0.2, 0.2, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // Shoulder
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // Elbow
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // Palm
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)palm, 0.0, 0.0, 1.0);
    glPushMatrix();
    glScalef(1.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    
    float fingerSpacing = 0.25;
    for (int i = 0; i < 5; ++i)
    {
        glPushMatrix();
        // Posisi jari di telapak tangan (disusun sejajar sumbu Y)
        glTranslatef(0.5, 0.5 - i * fingerSpacing, 0.0); // Jarak antar jari
        glRotatef((GLfloat)fingers, 0.0, 1.0, 0.0);      // Gerakan tekuk ke depan
        glTranslatef(0.0, 0.0, 0.5);                     // Maju ke depan (sumbu Z)
        drawFinger();
        glPopMatrix();
    }

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -8.0);  // Kamera agak mundur supaya kelihatan
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
        shoulder = (shoulder + 5) % 360;
        break;
    case 'S':
        shoulder = (shoulder - 5) % 360;
        break;
    case 'e':
        elbow = (elbow + 5) % 360;
        break;
    case 'E':
        elbow = (elbow - 5) % 360;
        break;
    case 'p':
        palm = (palm + 5) % 360;
        break;
    case 'P':
        palm = (palm - 5) % 360;
        break;
    case 'j':
        if (fingers < 45) fingers += 5;
        break;
    case 'J':
        if (fingers > -10) fingers -= 5;
        break;
    case 27: // ESC
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tangan");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}


//      s / S Putar bahu
//      e / E Putar siku
//      p / P Putar telapak
//      j Tekuk jari ke depan
//      J Luruskan jari
