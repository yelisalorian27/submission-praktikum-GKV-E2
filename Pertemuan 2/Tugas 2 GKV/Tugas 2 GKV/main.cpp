#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <math.h>
#include <stdio.h>

// Variabel global untuk animasi
float wheelRotation = 0.0f;
float carPosition = -1.0f;  // Mulai dari kiri layar
float carSpeed = 0.02f;

// Fungsi untuk membuat lingkaran
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

// Fungsi untuk membuat roda
void drawWheel(float x, float y, float size, float rotation) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    
    // Ban luar (hitam)
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0.0f, 0.0f, size, 32);
    
    // Velg (abu-abu)
    glColor3f(0.6f, 0.6f, 0.6f);
    drawCircle(0.0f, 0.0f, size * 0.7f, 32);
    
    // Jari-jari (rotasi)
    glPushMatrix();
    glRotatef(rotation, 0.0f, 0.0f, 1.0f);
    glColor3f(0.3f, 0.3f, 0.3f);
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glRotatef(i * 45.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2f(-size * 0.1f, -size * 0.6f);
        glVertex2f(size * 0.1f, -size * 0.6f);
        glVertex2f(size * 0.1f, size * 0.6f);
        glVertex2f(-size * 0.1f, size * 0.6f);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
    
    glPopMatrix();
}

// Fungsi untuk membuat asap knalpot
void drawSmoke(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    
    // Asap dengan opacity menurun
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glColor4f(0.7f, 0.7f, 0.7f, 0.7f);
    drawCircle(0.0f, 0.0f, 0.05f, 16);
    
    glColor4f(0.7f, 0.7f, 0.7f, 0.5f);
    drawCircle(-0.08f, 0.0f, 0.07f, 16);
    
    glColor4f(0.7f, 0.7f, 0.7f, 0.3f);
    drawCircle(-0.18f, 0.0f, 0.09f, 16);
    
    glDisable(GL_BLEND);
    
    glPopMatrix();
}

void drawCar() {
    // Badan utama mobil
    glPushMatrix();
    glTranslatef(carPosition, 0.0f, 0.0f);
    
    // Badan mobil (merah)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6f, -0.1f);
    glVertex2f(0.6f, -0.1f);
    glVertex2f(0.6f, 0.1f);
    glVertex2f(0.4f, 0.1f);
    glVertex2f(0.2f, 0.3f);
    glVertex2f(-0.2f, 0.3f);
    glVertex2f(-0.4f, 0.1f);
    glVertex2f(-0.6f, 0.1f);
    glEnd();
    
    // Kaca depan (biru muda)
    glColor3f(0.6f, 0.8f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.15f, 0.1f);
    glVertex2f(0.15f, 0.1f);
    glVertex2f(0.1f, 0.25f);
    glVertex2f(-0.1f, 0.25f);
    glEnd();
    
    // Kaca samping (biru muda)
    glColor3f(0.6f, 0.8f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.17f, 0.1f);
    glVertex2f(0.36f, 0.1f);
    glVertex2f(0.18f, 0.25f);
    glVertex2f(0.12f, 0.25f);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2f(-0.17f, 0.1f);
    glVertex2f(-0.36f, 0.1f);
    glVertex2f(-0.18f, 0.25f);
    glVertex2f(-0.12f, 0.25f);
    glEnd();
    
    // Lampu depan (kuning)
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.55f, -0.05f);
    glVertex2f(0.6f, -0.05f);
    glVertex2f(0.6f, 0.05f);
    glVertex2f(0.55f, 0.05f);
    glEnd();
    
    // Lampu belakang (merah)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.55f, -0.05f);
    glVertex2f(-0.6f, -0.05f);
    glVertex2f(-0.6f, 0.05f);
    glVertex2f(-0.55f, 0.05f);
    glEnd();
    
    // Knalpot (abu-abu)
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6f, -0.08f);
    glVertex2f(-0.65f, -0.08f);
    glVertex2f(-0.65f, -0.02f);
    glVertex2f(-0.6f, -0.02f);
    glEnd();
    
    // Roda
    drawWheel(-0.4f, -0.1f, 0.15f, wheelRotation);
    drawWheel(0.4f, -0.1f, 0.15f, wheelRotation);
    
    // Asap knalpot
    drawSmoke(-0.65f, -0.05f);
    
    glPopMatrix();
}

void drawRoad() {
    // Jalan (abu-abu)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.3f);
    glVertex2f(1.0f, -0.3f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
    
    // Garis putih di jalan (statis)
    glColor3f(1.0f, 1.0f, 1.0f);
    for (float x = -0.9f; x < 1.0f; x += 0.4f) {
        glBegin(GL_QUADS);
        glVertex2f(x, -0.6f);
        glVertex2f(x + 0.2f, -0.6f);
        glVertex2f(x + 0.2f, -0.65f);
        glVertex2f(x, -0.65f);
        glEnd();
    }
}

void drawSky() {
    // Langit (biru muda)
    glColor3f(0.6f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.3f);
    glVertex2f(1.0f, -0.3f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
}

void drawSun() {
    glPushMatrix();
    glTranslatef(0.7f, 0.7f, 0.0f);
    
    // Matahari (kuning)
    glColor3f(1.0f, 0.8f, 0.0f);
    drawCircle(0.0f, 0.0f, 0.15f, 32);
    
    // Sinar matahari
    glBegin(GL_LINES);
    for (int i = 0; i < 8; i++) {
        float angle = i * 45.0f * 3.14159f / 180.0f;
        float x = 0.2f * cosf(angle);
        float y = 0.2f * sinf(angle);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(x, y);
    }
    glEnd();
    
    glPopMatrix();
}

void drawCloud(float x, float y, float size) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(size, size, 1.0f);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(0.0f, 0.0f, 0.1f, 32);
    drawCircle(0.1f, 0.0f, 0.08f, 32);
    drawCircle(-0.1f, 0.0f, 0.08f, 32);
    drawCircle(0.05f, 0.08f, 0.08f, 32);
    drawCircle(-0.05f, 0.08f, 0.08f, 32);
    
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Menggambar latar belakang (tetap)
    drawSky();
    drawRoad();
    drawSun();
    
    // Menggambar awan (tetap)
    drawCloud(-0.5f, 0.6f, 1.0f);
    drawCloud(0.0f, 0.7f, 0.8f);
    drawCloud(0.4f, 0.5f, 1.2f);
    
    // Menggambar mobil (bergerak)
    drawCar();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (w <= h)
        gluOrtho2D(-1.0, 1.0, -1.0 * (GLfloat)h / (GLfloat)w, 1.0 * (GLfloat)h / (GLfloat)w);
    else
        gluOrtho2D(-1.0 * (GLfloat)w / (GLfloat)h, 1.0 * (GLfloat)w / (GLfloat)h, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value) {
    // Rotasi roda
    wheelRotation += 10.0f;
    if (wheelRotation > 360.0f) {
        wheelRotation -= 360.0f;
    }
    
    // Pergerakan mobil
    carPosition += carSpeed;
    
    // Mobil bergerak dari kiri ke kanan, lalu kembali ke kiri untuk mengulang
    if (carPosition > 1.5f) {  // Keluar dari layar sebelah kanan
        carPosition = -1.5f;   // Kembali ke posisi awal di sebelah kiri
    }
    
    glutPostRedisplay();
    glutTimerFunc(50, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mobil 2D dengan OpenGL & GLUT - Looping");
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(50, timer, 0);
    
    glutMainLoop();
    return 0;
}
