#include <GLUT/glut.h>
#include <math.h>

float rotationX = 0.0f;
float rotationY = 0.0f;
float rotationZ = 0.0f;

// Warna-warna untuk kubus
typedef struct {
    float r, g, b;
} Color;

Color colors[] = {
    {1.0f, 0.0f, 0.0f}, // Merah
    {0.0f, 1.0f, 0.0f}, // Hijau
    {0.0f, 0.0f, 1.0f}, // Biru
    {1.0f, 1.0f, 0.0f}, // Kuning
    {1.0f, 0.0f, 1.0f}, // Magenta
    {0.0f, 1.0f, 1.0f}, // Cyan
    {1.0f, 0.5f, 0.0f}, // Oranye
    {0.5f, 0.0f, 0.5f}  // Ungu
};

// Fungsi untuk menggambar kubus dengan GL_QUADS
void drawCubeWithQuads(float x, float y, float z, Color color) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(color.r, color.g, color.b);
    
    glBegin(GL_QUADS);
    // Depan
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    
    // Belakang
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    
    // Atas
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    
    // Bawah
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    
    // Kiri
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    
    // Kanan
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    
    glEnd();
    glPopMatrix();
}

// Fungsi untuk menggambar kubus dengan GL_QUAD_STRIP
void drawCubeWithQuadStrip(float x, float y, float z, Color color) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(color.r, color.g, color.b);
    
    // Sisi depan dan belakang dengan GL_QUAD_STRIP
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
    
    // Sisi atas dan bawah dengan GL_QUAD_STRIP
    glBegin(GL_QUAD_STRIP);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
    
    glPopMatrix();
}

// Fungsi untuk menggambar kubus dengan GL_TRIANGLE_STRIP
void drawCubeWithTriangleStrip(float x, float y, float z, Color color) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(color.r, color.g, color.b);
    
    // Sisi depan dengan GL_TRIANGLE_STRIP
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glEnd();
    
    // Sisi atas dengan GL_TRIANGLE_STRIP
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glEnd();
    
    // Sisi belakang dengan GL_TRIANGLE_STRIP
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
    
    // Sisi bawah dengan GL_TRIANGLE_STRIP
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glEnd();
    
    // Sisi kiri dengan GL_TRIANGLE_STRIP
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glEnd();
    
    // Sisi kanan dengan GL_TRIANGLE_STRIP
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glEnd();
    
    glPopMatrix();
}

// Fungsi untuk menggambar kubus dengan GL_TRIANGLE_FAN
void drawCubeWithTriangleFan(float x, float y, float z, Color color) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(color.r, color.g, color.b);
    
    // Depan dengan GL_TRIANGLE_FAN
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 1.0); // Pusat
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glEnd();
    
    // Belakang dengan GL_TRIANGLE_FAN
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, -1.0); // Pusat
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
    
    // Atas, bawah, kiri, kanan dengan GL_TRIANGLE_FAN
    // Atas
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 1.0, 0); // Pusat
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
    
    // Bawah
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, -1.0, 0); // Pusat
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
    
    glPopMatrix();
}

// Fungsi untuk menggambar kerangka kubus dengan GL_LINE_LOOP dan GL_LINE_STRIP
void drawCubeWireframe(float x, float y, float z, Color color) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(color.r, color.g, color.b);
    
    // Depan dengan GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glEnd();
    
    // Belakang dengan GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glEnd();
    
    // Tepi penghubung dengan GL_LINE_STRIP
    glBegin(GL_LINE_STRIP);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
    
    glPopMatrix();
}

// Fungsi untuk menggambar menara kubus
void drawCubeTower() {
    // Kubus dasar (paling bawah) dengan GL_QUADS
    drawCubeWithQuads(0.0, 0.0, 0.0, colors[0]);
    
    // Kubus kedua dengan GL_QUAD_STRIP
    drawCubeWithQuadStrip(0.0, 2.5, 0.0, colors[1]);
    
    // Kubus ketiga dengan GL_TRIANGLE_STRIP
    drawCubeWithTriangleStrip(0.0, 5.0, 0.0, colors[2]);
    
    // Kubus keempat dengan GL_TRIANGLE_FAN
    drawCubeWithTriangleFan(0.0, 7.5, 0.0, colors[3]);
    
    // Kubus kelima (wireframe) dengan GL_LINE_LOOP dan GL_LINE_STRIP
    drawCubeWireframe(0.0, 10.0, 0.0, colors[4]);
    
    // Kubus ekstra dengan kombinasi berbeda
    drawCubeWithQuads(2.5, 1.25, 0.0, colors[5]);
    drawCubeWithTriangleFan(-2.5, 1.25, 0.0, colors[6]);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Posisi kamera
    gluLookAt(15.0, 10.0, 15.0,  // Posisi kamera
              0.0, 5.0, 0.0,     // Target pandangan
              0.0, 1.0, 0.0);    // Vektor atas
    
    // Rotasi objek
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);
    
    // Gambar menara kubus
    drawCubeTower();
    
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width/(float)height, 0.1, 100.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'x':
            rotationX += 5.0f;
            break;
        case 'X':
            rotationX -= 5.0f;
            break;
        case 'y':
            rotationY += 5.0f;
            break;
        case 'Y':
            rotationY -= 5.0f;
            break;
        case 'z':
            rotationZ += 5.0f;
            break;
        case 'Z':
            rotationZ -= 5.0f;
            break;
        case 27: // ESC
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Kubus Bertingkat Kreatif dengan Primitif OpenGL");
    
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}
