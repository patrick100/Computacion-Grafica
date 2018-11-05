//#include <stdarg.h>w
#include <GL/glut.h>

#include "Vector_tools.h"
#include "Camara.h"

#include "primitivas.h"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool command = false; /* command mode */
char strCommand[256];

static Camara *MiCamara;
static int spot_move = 0;
static int old_x, old_y;

void display(void) {
    float At[3];
    float Direction[3];
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    MiCamara->SetGLCamera();
    
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    drawSphereTurtle();
    glPopMatrix();
    
    glutSwapBuffers();
}

void parseCommand(char* strCommandParse) {
    char *strToken0;
    char *strToken1;
    double val;
    strToken0 = strtok(strCommandParse, " ");
    while ((strToken1 = strtok(NULL, " ")) != NULL) {
        val = atof(strToken1);
        if (!strcmp("fd", strToken0)) { // FORWARD
            glTranslatef(0.0, 0.0, val);
        } else if (!strcmp("bk", strToken0)) { // BACK
            glTranslatef(0.0, 0.0, -val);
        } else if (!strcmp("rt", strToken0)) { // RIGHT
            glRotatef(-val, 0., 1., 0.);
        } else if (!strcmp("lt", strToken0)) { // LEFT
            glRotatef(val, 0., 1., 0.);
        } else if (!strcmp("up", strToken0)) { // UP
            glRotatef(val, 1., 0., 0.);
        } else if (!strcmp("dn", strToken0)) { // DOWN
            glRotatef(-val, 1., 0., 0.);
        }
        strToken0 = strtok(NULL, " ");
        display();
    }
    // EXIT COMMAND MODE
    if (strToken0 != NULL && strncmp(strToken0, "exit", 4) == 0) {
        command = false;
        // HOME
    } else if (strToken0 != NULL && !strcmp("home", strToken0)) {
        glLoadIdentity();
    }
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    MiCamara->SetGLAspectRatioCamera();
}

void MouseMotion(int x, int y) {
    old_y = y;
    old_x = x;
}

void Zoom(int x, int y) {

    float zoom;

    zoom = (float) ((y - old_y) * DEGREE_TO_RAD);
    old_y = y;

    switch (MiCamara->camMovimiento) {

        case CAM_EXAMINAR:
            if (MiCamara->camAperture + zoom > (5 * DEGREE_TO_RAD) && MiCamara->camAperture + zoom < 175 * DEGREE_TO_RAD)
                MiCamara->camAperture = MiCamara->camAperture + zoom;
            break;

    }

    glutPostRedisplay();
}

void Examinar(int x, int y) {

    float rot_x, rot_y;

    rot_y = (float) (old_y - y);
    rot_x = (float) (x - old_x);
    MiCamara->Rotar_Latitud( rot_y * DEGREE_TO_RAD);
    MiCamara->Rotar_Longitud(rot_x * DEGREE_TO_RAD);

    old_y = y;
    old_x = x;

    glutPostRedisplay();

}



/*
void Mouse_Spot_Abrir_Cerrar(int x, int y) {

    float step;

    step = (float) (y - old_y);
    old_y = y;

    if (LOCAL_MyLights[current_light]->spotCutOff + step < 90 && LOCAL_MyLights[current_light]->spotCutOff + step > 0)
        LOCAL_MyLights[current_light]->spotCutOff += step;

    LOCAL_MyLights[current_light]->needsUpdate = TRUE;
    glutPostRedisplay();
}
void Mouse_Spot(int x, int y) {
    float rot_x, rot_y;

    rot_y = (float) (old_y - y);
    rot_x = (float) (x - old_x);

    Rotar_Spot_Latitud(LOCAL_MyLights[current_light], rot_y * DEGREE_TO_RAD);
    Rotar_Spot_Longitud(LOCAL_MyLights[current_light], rot_x * DEGREE_TO_RAD);

    old_y = y;
    old_x = x;

    glutPostRedisplay();
}*/

void Andar(int x, int y) {

    float rotacion_x, avance_y;

    avance_y = (float) (y - old_y) / 10;
    rotacion_x = (float) (old_x - x) * DEGREE_TO_RAD / 5;
    MiCamara->YawCamera(rotacion_x);
    MiCamara->AvanceFreeCamera(avance_y);

    old_y = y;
    old_x = x;

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {

    old_x = x;
    old_y = y;

    switch (button) {

        case GLUT_LEFT_BUTTON:

            switch (MiCamara->camMovimiento) {

                case CAM_EXAMINAR:
                    if (state == GLUT_DOWN)
                        glutMotionFunc(Zoom);
                    if (state == GLUT_UP) {
                        glutPassiveMotionFunc(Examinar);
                        glutMotionFunc(NULL);
                    }
                    break;

                case CAM_PASEAR:
                    if (state == GLUT_DOWN)
                        glutMotionFunc(Andar);
                    if (state == GLUT_UP)
                        glutMotionFunc(NULL);
                    break;
            }

        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                //glutMotionFunc(scale);
                break;

        default:
            break;

    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (command) {
        if (key == 13) {
            strcat(strCommand, " ");
            if (strlen(strCommand) == 1) command = false;
            parseCommand(strCommand);
            strcpy(strCommand, "");
        } else {
            char strKey[2] = " ";
            strKey[0] = key;
            printf(strKey);
            strcat(strCommand, strKey);
        }
    } else { // not in command mode
        switch (key) {
            case 'h':
                printf("help\n\n");
                printf("c - Toggle culling\n");
                printf("q/escape - Quit\n\n");
                break;
            case 'c':
                if (glIsEnabled(GL_CULL_FACE))
                    glDisable(GL_CULL_FACE);
                else
                    glEnable(GL_CULL_FACE);
                break;
            case '1':
                glRotatef(1.0, 1., 0., 0.);
                break;
            case '2':
                glRotatef(1.0, 0., 1., 0.);
                break;
            case 'i':
                command = true;
                break;
            case 'q':
            case 27:
                delete MiCamara;
                exit(0);
                break;
        }
    }
    glutPostRedisplay();
}

static void SpecialKey(int key, int x, int y) {
    switch (key) {


            



        
        case GLUT_KEY_F1:
            glutPassiveMotionFunc(MouseMotion);
            MiCamara->camMovimiento = CAM_STOP;
            printf("%s\n","SE PRESIONO F1" );
            break;
        case GLUT_KEY_F2:
            glutPassiveMotionFunc(Examinar);
            MiCamara->camMovimiento = CAM_EXAMINAR;
            printf("%s\n","SE PRESIONO F2" );
            break;
        case GLUT_KEY_F3:
            glutPassiveMotionFunc(MouseMotion);
            MiCamara->camMovimiento = CAM_PASEAR;
            MiCamara->camAtY = 0;
            MiCamara->camViewY = 0;
            MiCamara->SetDependentParametersCamera();
            printf("%s\n","SE PRESIONO F3" );
            break;
        
       

        
        case GLUT_KEY_PAGE_UP:
            //AvanceFreeCamera( MiCamara, 0.5f );
            if (MiCamara->camAperture < 175 * DEGREE_TO_RAD)
                MiCamara->camAperture = MiCamara->camAperture + 2.5f * DEGREE_TO_RAD;
            break;

        case GLUT_KEY_PAGE_DOWN:
            //AvanceFreeCamera( MiCamara, -0.5f );
            if (MiCamara->camAperture > 5 * DEGREE_TO_RAD)
                MiCamara->camAperture = MiCamara->camAperture - 2.5f * DEGREE_TO_RAD;
            break;

        case GLUT_KEY_UP:
            MiCamara->Rotar_Latitud( 2.5f * DEGREE_TO_RAD);
            //PitchCamera( MiCamara, 3.0f * DEGREE_TO_RAD );
            break;

        case GLUT_KEY_DOWN:
            MiCamara->Rotar_Latitud( -2.5f * DEGREE_TO_RAD);
            //PitchCamera( MiCamara, -3.0f * DEGREE_TO_RAD );
            break;

        case GLUT_KEY_LEFT:
            MiCamara->Rotar_Longitud( -2.5f * DEGREE_TO_RAD);
            //YawCamera( MiCamara, 3.0f * DEGREE_TO_RAD );
            break;

        case GLUT_KEY_RIGHT:
            MiCamara->Rotar_Longitud(2.5f * DEGREE_TO_RAD);
            //YawCamera( MiCamara, -3.0f * DEGREE_TO_RAD );
            break;
        

        case GLUT_KEY_F4: //Reset Camera
            MiCamara->camAtX = 0;
            MiCamara->camAtY = 0;
            MiCamara->camAtZ = 0;
            MiCamara->camViewX = 0;
            MiCamara->camViewY = 1;
            MiCamara->camViewZ = -3;
            MiCamara->SetDependentParametersCamera();
            printf("%s\n","SE PRESIONO F4 (HOME)" );
            break;
        default:
            printf("key %d %c X %d Y %d\n", key, key, x, y);
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    // Colocamos la cámara en (0,1,-3) mirando hacia (0,0,0)
    MiCamara = new Camara(0.0f, 1.0f, -3.0f);

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("tortuga");
    //glEnable(GL_COLOR_MATERIAL);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKey);

    //Ratón
    glutMouseFunc(mouse); //Pulsado de Botones
    glutMotionFunc(NULL); //Movimiento con Botones pulsados
    glutPassiveMotionFunc(MouseMotion); //Movimientos sin Botones pulsados

    glutMainLoop();
    return 0;
}