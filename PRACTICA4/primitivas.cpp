#include <GL/glut.h>
#include "Vector_tools.h"
#include "primitivas.h"

void Draw_Parallel(float *At) {
    double radius, angle;
    float vectorX, vectorZ, vectorX1, vectorZ1;
    int lightingFlag;

    lightingFlag = glIsEnabled(GL_LIGHTING);
    if (lightingFlag) glDisable(GL_LIGHTING);

    radius = sqrt(At[0] * At[0] + At[2] * At[2]);
    vectorZ1 = radius;
    vectorX1 = 0.0;
    glBegin(GL_LINE_STRIP);
    for (angle = 0.0f; angle <= (2.0f * 3.14159); angle += 0.01f) {
        vectorX = radius * (float) sin((double) angle);
        vectorZ = radius * (float) cos((double) angle);
        glVertex3d(vectorX1, At[1], vectorZ1);
        vectorZ1 = vectorZ;
        vectorX1 = vectorX;
    }
    glEnd();
}

void Draw_Meridian(float *At) {
    double radius, alfa, beta;
    float vectorX, vectorY, vectorZ, vectorX1, vectorY1, vectorZ1;
    int lightingFlag;

    lightingFlag = glIsEnabled(GL_LIGHTING);
    if (lightingFlag) glDisable(GL_LIGHTING);

    radius = sqrt(pow(At[0], 2) + pow(At[1], 2) + pow(At[2], 2));
    alfa = atan2(At[2], At[0]);
    vectorX1 = radius * (float) cos((double) alfa);
    vectorY1 = 0;
    vectorZ1 = radius * (float) sin((double) alfa);
    glBegin(GL_LINE_STRIP);
    for (beta = 0.0f; beta <= (2.0f * 3.14159); beta += 0.01f) {
        vectorX = radius * (float) cos((double) beta)*(float) cos((double) alfa);
        vectorY = radius * (float) sin((double) beta);
        vectorZ = radius * (float) cos((double) beta)*(float) sin((double) alfa);
        glVertex3d(vectorX1, vectorY1, vectorZ1);
        vectorX1 = vectorX;
        vectorY1 = vectorY;
        vectorZ1 = vectorZ;
    }
    glEnd();
}

void Draw_Vector(float *At, float *Direction) {
    int ierr;
    float mod;
    float alpha, beta;
    float length = .2f;
    float vectorX, vectorY, vectorZ;
    int lightingFlag;

    lightingFlag = glIsEnabled(GL_LIGHTING);
    if (lightingFlag) glDisable(GL_LIGHTING);

    mod = sqrt(pow(Direction[0], 2) + pow(Direction[1], 2) + pow(Direction[2], 2));
    alpha = atan2(Direction[0], Direction[2]);
    beta = asin(Direction[1] / mod);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(At[0], At[1], At[2]);
    glVertex3f(At[0] + Direction[0] * length, At[1] + Direction[1] * length, At[2] + Direction[2] * length);
    glEnd();

    VectorNormalize(&ierr, &Direction[0], &Direction[1], &Direction[2]);
    vectorX = At[0] + Direction[0]*(length - 0.05);
    vectorY = At[1] + Direction[1]*(length - 0.05);
    vectorZ = At[2] + Direction[2]*(length - 0.05);
    glTranslatef(vectorX, vectorY, vectorZ);
    glRotatef(beta *RAD_TO_DEGREE, sin(alpha - PI_VALUE / 2.0), 0.0f, cos(alpha - PI_VALUE / 2.0));
    glRotatef(alpha*RAD_TO_DEGREE, 0.0f, 1.0f, 0.0f);
    glutSolidCone(0.02, 0.1, 28, 28);
}

void Draw_Sphere_Spot(float *At, float *Direction) {
    int lightingFlag;
    float mod;
    float alpha, beta, alfa;
    float length = .2f;
    double radius, angle;
    float vectorX, vectorY, vectorZ, vectorX1, vectorY1, vectorZ1;

    lightingFlag = glIsEnabled(GL_LIGHTING);
    if (lightingFlag) glDisable(GL_LIGHTING);

    mod = sqrt(pow(Direction[0], 2) + pow(Direction[1], 2) + pow(Direction[2], 2));
    alpha = atan2(Direction[0], Direction[2]);
    beta = asin(Direction[1] / mod);

    glLoadIdentity();
    radius = sqrt(pow(Direction[0] * length, 2) + pow(Direction[2] * length, 2));
    vectorX1 = At[0];
    vectorZ1 = At[2] + radius;
    glBegin(GL_LINE_STRIP);
    for (angle = 0.0f; angle <= (2.0f * 3.14159); angle += 0.01f) {
        vectorX = At[0] + radius * (float) sin((double) angle);
        vectorZ = At[2] + radius * (float) cos((double) angle);
        glVertex3d(vectorX1, At[1] + Direction[1] * length, vectorZ1);
        vectorZ1 = vectorZ;
        vectorX1 = vectorX;
    }
    glEnd();

    radius = sqrt(pow(Direction[0] * length, 2) + pow(Direction[1] * length, 2) + pow(Direction[2] * length, 2));
    alfa = atan(Direction[2] / Direction[0]);
    vectorX1 = At[0] + radius * (float) cos((double) alfa);
    vectorY1 = At[1];
    vectorZ1 = At[2] + radius * (float) sin((double) alfa);
    glBegin(GL_LINE_STRIP);
    for (beta = 0.0f; beta <= (2.0f * 3.14159); beta += 0.01f) {
        vectorX = At[0] + radius * (float) cos((double) beta)*(float) cos((double) alfa);
        vectorY = At[1] + radius * (float) sin((double) beta);
        vectorZ = At[2] + radius * (float) cos((double) beta)*(float) sin((double) alfa);
        glVertex3d(vectorX1, vectorY1, vectorZ1);
        vectorX1 = vectorX;
        vectorY1 = vectorY;
        vectorZ1 = vectorZ;
    }
    glEnd();

}

void DrawAxis(void) {
    int lightingFlag;

    lightingFlag = glIsEnabled(GL_LIGHTING);
    if (lightingFlag) glDisable(GL_LIGHTING);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();
    //Flechas
    //Eje X
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glutSolidCone(0.02, 0.1, 28, 28);
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    glTranslatef(-1.0, 0.0, 0.0);
    //Eje Y
    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(0.0, 1.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.02, 0.1, 28, 28);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -1.0, 0.0);
    //Eje Z	
    glColor3f(0.0f, 0.0f, 1.0f);
    glTranslatef(0.0, 0.0, 1.0);
    glutSolidCone(0.02, 0.1, 28, 28);
    glTranslatef(0.0, 0.0, -1.0);

    if (lightingFlag) glEnable(GL_LIGHTING);
}

void drawSphereTurtle() {

    int slices = 40;
    int stacks = 40;

    glPushMatrix();
    glScalef(1.0f, .3f, 1.0f);
    glutSolidSphere(1.0, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.7f, 0.0f, .7f);
    glutSolidSphere(.3, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.7f, 0.0f, .7f);
    glutSolidSphere(.3, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.7f, 0.0f, -.7f);
    glutSolidSphere(.3, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.7f, 0.0f, -.7f);
    glutSolidSphere(.3, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0f, .6f, 1.0f);
    glTranslatef(0.0f, 0.0f, -1.2f);
    glutSolidSphere(.4, slices, stacks);
    glPopMatrix();
}