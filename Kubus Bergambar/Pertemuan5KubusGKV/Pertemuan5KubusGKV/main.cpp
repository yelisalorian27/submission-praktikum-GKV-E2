// Nama: Yelisa Lorian
// NIM: 24060123130082
// Lab: GKV E2

#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Imageloader.h"

using namespace std;

const float BOX_SIZE = 7.0f; // Panjang tiap sisi kubus
float _angle = 0;  // Rotasi terhadap box
GLuint _textureIds[6];  // Array untuk menyimpan 6 tekstur

void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // Tekan Escape untuk EXIT
            exit(0);
    }
}

// Membuat gambar menjadi tekstur kemudian berikan ID pada tekstur
GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return textureId;
}

// Memuat enam tekstur berbeda
void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    
    const char* textureFiles[6] = {
        "/Users/yelisalorian/Downloads/Pertemuan5KubusGKV/contoh12.bmp",
        "/Users/yelisalorian/Downloads/Pertemuan5KubusGKV/contoh11.bmp",
        "/Users/yelisalorian/Downloads/Pertemuan5KubusGKV/contoh.bmp",
        "/Users/yelisalorian/Downloads/Pertemuan5KubusGKV/contoh9.bmp",
        "/Users/yelisalorian/Downloads/Pertemuan5KubusGKV/contoh8.bmp",
        "/Users/yelisalorian/Downloads/Pertemuan5KubusGKV/contoh_7.bmp",
        
    };

    for (int i = 0; i < 6; i++) {
        Image* image = loadBMP(textureFiles[i]);
        _textureIds[i] = loadTexture(image);
        delete image;
    }
}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -20.0f);

    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    
    GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat lightPos[] = {-2 * BOX_SIZE, BOX_SIZE, 4 * BOX_SIZE, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_TEXTURE_2D);
    glRotatef(_angle, 1.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Sisi depan
    glBindTexture(GL_TEXTURE_2D, _textureIds[0]);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0, 0);
    glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2, BOX_SIZE/2);
    glTexCoord2f(1, 0);
    glVertex3f(BOX_SIZE/2, -BOX_SIZE/2, BOX_SIZE/2);
    glTexCoord2f(1, 1);
    glVertex3f(BOX_SIZE/2, BOX_SIZE/2, BOX_SIZE/2);
    glTexCoord2f(0, 1);
    glVertex3f(-BOX_SIZE/2, BOX_SIZE/2, BOX_SIZE/2);
    glEnd();

    // Sisi belakang
    glBindTexture(GL_TEXTURE_2D, _textureIds[1]);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0, 0);
    glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE/2);
    glTexCoord2f(1, 0);
    glVertex3f(-BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE/2);
    glTexCoord2f(1, 1);
    glVertex3f(BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE/2);
    glTexCoord2f(0, 1);
    glVertex3f(BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE/2);
    glEnd();

    // Sisi kiri
    glBindTexture(GL_TEXTURE_2D, _textureIds[2]);
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 0);
    glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE/2);
    glTexCoord2f(1, 0);
    glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2, BOX_SIZE/2);
    glTexCoord2f(1, 1);
    glVertex3f(-BOX_SIZE/2, BOX_SIZE/2, BOX_SIZE/2);
    glTexCoord2f(0, 1);
    glVertex3f(-BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE/2);
    glEnd();
    
    // Sisi kanan
    glBindTexture(GL_TEXTURE_2D, _textureIds[3]);
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 0);
    glVertex3f(BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE/2);
    glTexCoord2f(1, 0);
    glVertex3f(BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE/2);
    glTexCoord2f(1, 1);
    glVertex3f(BOX_SIZE/2, BOX_SIZE/2, BOX_SIZE/2);
    glTexCoord2f(0, 1);
    glVertex3f(BOX_SIZE/2, -BOX_SIZE/2, BOX_SIZE/2);
    glEnd();

    // Sisi atas
    glBindTexture(GL_TEXTURE_2D, _textureIds[4]);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0, 0);
    glVertex3f(-BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE/2);
    glTexCoord2f(1, 0);
    glVertex3f(-BOX_SIZE/2, BOX_SIZE/2, BOX_SIZE/2);
    glTexCoord2f(1, 1);
    glVertex3f(BOX_SIZE/2, BOX_SIZE/2, BOX_SIZE/2);
    glTexCoord2f(0, 1);
    glVertex3f(BOX_SIZE/2, BOX_SIZE/2, -BOX_SIZE/2);
    glEnd();

    // Sisi bawah
    glBindTexture(GL_TEXTURE_2D, _textureIds[5]);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0, 0);
    glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE/2);
    glTexCoord2f(1, 0);
    glVertex3f(BOX_SIZE/2, -BOX_SIZE/2, -BOX_SIZE/2);
    glTexCoord2f(1, 1);
    glVertex3f(BOX_SIZE/2, -BOX_SIZE/2, BOX_SIZE/2);
    glTexCoord2f(0, 1);
    glVertex3f(-BOX_SIZE/2, -BOX_SIZE/2, BOX_SIZE/2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

// Panggil setiap 25ms
void update(int value) {
    _angle += 1.0f;
    if (_angle > 360) _angle -= 360;
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Tekstur Kubus Yelisa");
    initRendering();
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}
