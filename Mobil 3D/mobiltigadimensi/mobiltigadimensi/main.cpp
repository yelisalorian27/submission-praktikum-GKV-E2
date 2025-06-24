#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <math.h>
#include <stdio.h>

// Variabel global untuk animasi
float wheelRotation = 0.0f;
float carPosition = -5.0f;
float carSpeed = 0.05f;
float cameraAngle = 0.0f;

// Rotasi kamera
float cameraX = 0.0f;
float cameraY = 5.0f;
float cameraZ = 10.0f;

void initLighting() {
    // Aktifkan lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    
    // Setup ambient light
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    
    // Setup diffuse light
    GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    
    // Setup specular light
    GLfloat specularLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    
    // Posisi light
    GLfloat lightPosition[] = {5.0f, 10.0f, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    // Material properties
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    GLfloat specularMaterial[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);
}

// Membuat kubus dengan normal vectors untuk lighting
void drawCube(float width, float height, float depth) {
    float w = width / 2.0f;
    float h = height / 2.0f;
    float d = depth / 2.0f;
    
    glBegin(GL_QUADS);
    
    // Front face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-w, -h, d);
    glVertex3f(w, -h, d);
    glVertex3f(w, h, d);
    glVertex3f(-w, h, d);
    
    // Back face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-w, -h, -d);
    glVertex3f(-w, h, -d);
    glVertex3f(w, h, -d);
    glVertex3f(w, -h, -d);
    
    // Top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-w, h, -d);
    glVertex3f(-w, h, d);
    glVertex3f(w, h, d);
    glVertex3f(w, h, -d);
    
    // Bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-w, -h, -d);
    glVertex3f(w, -h, -d);
    glVertex3f(w, -h, d);
    glVertex3f(-w, -h, d);
    
    // Right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(w, -h, -d);
    glVertex3f(w, h, -d);
    glVertex3f(w, h, d);
    glVertex3f(w, -h, d);
    
    // Left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-w, -h, -d);
    glVertex3f(-w, -h, d);
    glVertex3f(-w, h, d);
    glVertex3f(-w, h, -d);
    
    glEnd();
}

// Membuat silinder untuk roda
void drawCylinder(float radius, float height, int segments) {
    float halfHeight = height / 2.0f;
    
    // Side faces
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * M_PI * i / segments;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        
        glNormal3f(x / radius, 0.0f, z / radius);
        glVertex3f(x, -halfHeight, z);
        glVertex3f(x, halfHeight, z);
    }
    glEnd();
    
    // Top circle
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, halfHeight, 0.0f);
    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * M_PI * i / segments;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        glVertex3f(x, halfHeight, z);
    }
    glEnd();
    
    // Bottom circle
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, -halfHeight, 0.0f);
    for (int i = segments; i >= 0; i--) {
        float theta = 2.0f * M_PI * i / segments;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        glVertex3f(x, -halfHeight, z);
    }
    glEnd();
}

// Membuat roda dengan jari-jari
void drawWheel(float x, float y, float z, float rotation) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f); // Orientasi roda
    glRotatef(rotation, 1.0f, 0.0f, 0.0f); // Rotasi roda
    
    // Ban (hitam)
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCylinder(0.4f, 0.3f, 16);
    
    // Velg (abu-abu)
    glColor3f(0.6f, 0.6f, 0.6f);
    drawCylinder(0.3f, 0.32f, 16);
    
    // Jari-jari roda
    glColor3f(0.4f, 0.4f, 0.4f);
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glRotatef(i * 45.0f, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, 0.15f);
        drawCube(0.05f, 0.4f, 0.02f);
        glPopMatrix();
    }
    
    glPopMatrix();
}

// Membuat badan mobil dari rangka-rangka
void drawCarBody() {
    // Badan utama mobil (merah)
    glColor3f(0.8f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    drawCube(3.0f, 0.8f, 1.5f);
    glPopMatrix();
    
    // Kabin mobil (merah lebih gelap)
    glColor3f(0.6f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(-0.5f, 0.8f, 0.0f);
    drawCube(1.8f, 0.8f, 1.4f);
    glPopMatrix();
    
    // Kap mesin
    glColor3f(0.7f, 0.15f, 0.15f);
    glPushMatrix();
    glTranslatef(1.0f, 0.2f, 0.0f);
    drawCube(1.0f, 0.4f, 1.3f);
    glPopMatrix();
    
    // Kaca depan (biru muda transparan)
    glColor3f(0.4f, 0.6f, 0.8f);
    glPushMatrix();
    glTranslatef(0.3f, 1.2f, 0.0f);
    drawCube(0.8f, 0.6f, 1.2f);
    glPopMatrix();
    
    // Kaca samping kiri
    glPushMatrix();
    glTranslatef(-0.5f, 1.2f, 0.6f);
    drawCube(1.6f, 0.6f, 0.1f);
    glPopMatrix();
    
    // Kaca samping kanan
    glPushMatrix();
    glTranslatef(-0.5f, 1.2f, -0.6f);
    drawCube(1.6f, 0.6f, 0.1f);
    glPopMatrix();
    
    // Lampu depan (kuning)
    glColor3f(1.0f, 1.0f, 0.3f);
    glPushMatrix();
    glTranslatef(1.6f, 0.0f, 0.4f);
    drawCube(0.2f, 0.3f, 0.3f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.6f, 0.0f, -0.4f);
    drawCube(0.2f, 0.3f, 0.3f);
    glPopMatrix();
    
    // Lampu belakang (merah)
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(-1.6f, 0.0f, 0.4f);
    drawCube(0.2f, 0.3f, 0.3f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.6f, 0.0f, -0.4f);
    drawCube(0.2f, 0.3f, 0.3f);
    glPopMatrix();
    
    // Knalpot (abu-abu gelap)
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(-1.8f, -0.3f, -0.3f);
    drawCylinder(0.1f, 0.3f, 8);
    glPopMatrix();
}

void drawCar() {
    glPushMatrix();
    glTranslatef(carPosition, 0.5f, 0.0f);
    
    // Badan mobil
    drawCarBody();
    
    // Roda-roda
    drawWheel(-1.0f, -0.4f, 0.8f, wheelRotation);   // Depan kiri
    drawWheel(-1.0f, -0.4f, -0.8f, wheelRotation);  // Depan kanan
    drawWheel(1.0f, -0.4f, 0.8f, wheelRotation);    // Belakang kiri
    drawWheel(1.0f, -0.4f, -0.8f, wheelRotation);   // Belakang kanan
    
    glPopMatrix();
}

// Membuat jalan 3D
void drawRoad() {
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 0.0f);
    drawCube(20.0f, 0.2f, 4.0f);
    glPopMatrix();
    
    // Garis putih di jalan
    glColor3f(0.9f, 0.9f, 0.9f);
    for (float x = -10.0f; x < 10.0f; x += 2.0f) {
        glPushMatrix();
        glTranslatef(x, -0.35f, 0.0f);
        drawCube(1.0f, 0.05f, 0.1f);
        glPopMatrix();
    }
}

// Membuat lingkungan 3D
void drawEnvironment() {
    // Tanah (hijau)
    glColor3f(0.2f, 0.6f, 0.2f);
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 3.0f);
    drawCube(20.0f, 0.5f, 2.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, -3.0f);
    drawCube(20.0f, 0.5f, 2.0f);
    glPopMatrix();
    
    // Pohon-pohon (cokelat dan hijau)
    for (int i = -3; i < 4; i++) {
        // Batang pohon
        glColor3f(0.4f, 0.2f, 0.0f);
        glPushMatrix();
        glTranslatef(i * 3.0f, 0.5f, 4.0f);
        drawCube(0.2f, 2.0f, 0.2f);
        glPopMatrix();
        
        // Daun pohon
        glColor3f(0.1f, 0.8f, 0.1f);
        glPushMatrix();
        glTranslatef(i * 3.0f, 1.5f, 4.0f);
        drawCube(1.0f, 1.0f, 1.0f);
        glPopMatrix();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Setup kamera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Kamera mengikuti mobil
    gluLookAt(carPosition - 5.0f, 3.0f, 8.0f,  // Posisi kamera
              carPosition, 0.0f, 0.0f,          // Target (mobil)
              0.0f, 1.0f, 0.0f);                // Up vector
    
    // Update posisi light mengikuti mobil
    GLfloat lightPosition[] = {carPosition + 3.0f, 8.0f, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    // Gambar lingkungan
    drawEnvironment();
    drawRoad();
    
    // Gambar mobil
    drawCar();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
    
    glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
    // Rotasi roda
    wheelRotation += 5.0f;
    if (wheelRotation > 360.0f) {
        wheelRotation -= 360.0f;
    }
    
    // Pergerakan mobil
    carPosition += carSpeed;
    
    // Loop mobil
    if (carPosition > 15.0f) {
        carPosition = -15.0f;
    }
    
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 'W':
            carSpeed = fmin(carSpeed + 0.01f, 0.2f);
            break;
        case 's':
        case 'S':
            carSpeed = fmax(carSpeed - 0.01f, 0.01f);
            break;
        case 27: // ESC
            exit(0);
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mobil 3D dengan Depth dan Lighting");
    
    // Setup
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Langit biru
    initLighting();
    
    // Callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, timer, 0);
    glutKeyboardFunc(keyboard);
    
    printf("Kontrol:\n");
    printf("W - Percepat mobil\n");
    printf("S - Perlambat mobil\n");
    printf("ESC - Keluar\n");
    
    glutMainLoop();
    return 0;
}
