#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <vector>


using namespace std;


// how to compile g++ tortuga.cpp -lGL -lGLU -lglut


//almacenar la matriz de modelado
GLdouble mModel[16];


//para almacenar los puntos
int np = 0;

float px[10000];
float py[10000];
float pz[10000];
    

void graph_tortuga3d(){

GLdouble cordx[] = { 0.0, 4.0, -8.0, 0.0, 8.0,-4.0};
GLdouble cordy[] = { -6.0, 2.0, 0.0, 8.0, 0.0,-4.0};
GLdouble r[] = { 6.0, 3.0, 2.0, 2.0, 2.0, 2.0};
GLint i;
glColor3f(0,255,0);

    for (i=0;i<6;i++){
        glutWireSphere(r[i], 15.0, 15.0);
        glTranslatef(cordx[i],cordy[i],0.0);
    }
}






//Para dibujar la ruta
void displayTrace() {
    int i;
    glColor3f(255,255,255) ;
    glBegin(GL_LINE_STRIP);
    for (i = 0; i < np; i++) {
        glVertex3f(px[i],py[i],pz[i]);
    }
    glEnd();
}



//coordenadas de la tortuga 
void addPointToTrace() {

    GLdouble m[16];
    glGetDoublev (GL_MODELVIEW_MATRIX, m);

    //printf ("\nMatrix:\n");
    //for (int i = 0; i < 4; i++) {
    //    printf ("Row %i: %f \t%f \t%f \t%f \n",i+1, m[i+0],m[i+4],m[i+8],m[i+12]);
    //}

    // if is the first point
    if (np == 0) { // add the first point
        px [0] = 0;
        py [0] = 0;
        pz [0] = 0;
        np++;
    }

    px [np] = m[0] * px [0] + m[4] * py [0] + m[8] * pz [0] + m[12];
    py [np] = m[1] * px [0] + m[5] * py [0] + m[9] * pz [0] + m[13];
    pz [np] = m[2] * px [0] + m[6] * py [0] + m[10] * pz [0] + m[14];

    np++;
}





void Move(unsigned char key, int x, int y)
{

    
    
   switch(key) {
    

    /* TRASLACION */
    //glTranslatef(x,y,z)
    case 'w' :
        cout<<"UP"<<endl;
        glTranslatef(0.0, 0.1 ,0.0);
        addPointToTrace();
        break;
    case 'a' : 
        cout<<"LEFT"<<endl;
        glTranslatef(-0.1, 0.0 ,0.0);
        break;
    case 's' :
        cout<<"DOWN"<<endl;
        glTranslatef(0.0, -0.1, 0);
        addPointToTrace();
        break;
    case 'd' :
        cout<<"RIGHT"<<endl;
        glTranslatef(0.1, 0 ,0.0);
        addPointToTrace();
        break;
        
    /* ROTACION */
    //glRotatef(angle,x,y,z);
        
    case 'i' :
        cout<<"UP"<<endl;
        glRotatef(5.0, 1.0, 0.0, 0.0);
        break;
    case 'j' : 
        cout<<"LEFT"<<endl;
        glRotatef(-5.0, 0.0, 1.0, 0.0);
        break;
    case 'k' :
        cout<<"DOWN"<<endl;
        glRotatef(-5.0, 1.0, 0.0, 0.0);
        break;
    case 'l' :
        cout<<"RIGHT"<<endl;
        glRotatef(5.0, 0.0, 1.0, 0.0);
        break;    

    /* SCALE */
    //glScalef(x,y,z)    
    case '+' :
        glScalef(2,2,2);
        break;

    case '-' :
        glScalef(0.5,0.5,0.5);
        break;    


    }



    glutPostRedisplay();

}

void reshape(int width, int height) {

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 1.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


void display(void) {

    glClear( GL_COLOR_BUFFER_BIT );
    //glPushMatrix();
    //glMultMatrixd(mModel);
    

    //glColor3f(1.0,1.0,0.0);
    glColor3ub( 255, 255, 0 );
    

    graph_tortuga3d();
    glPopMatrix();
    displayTrace();
    
    glutSwapBuffers();

}





int main( int argc, char **argv )
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glGetDoublev (GL_MODELVIEW_MATRIX, mModel);
    glPopMatrix();


    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( 800, 650 );
    glutInitWindowPosition(50, 100);
    glutCreateWindow( "PINTAR CON TORTUGA" );
    

    glutReshapeFunc(reshape);

    glutKeyboardFunc(Move);
    glutDisplayFunc( display );
 

    glutMainLoop();
    return 0;
}
