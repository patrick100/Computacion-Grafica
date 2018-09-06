#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;



void drawLineIncremental(float x1,float y1,float x2,float y2) {
   
   float x,y;
   float a;
   //int valor;

   glBegin(GL_POINTS);
        
       //hallamos la pendiente       
       a = (y2-y1)/(x2-x1);
       
       for(float x=x1; x<=x2;){
         
          //y = a + b(y1+a*0.01;

          y = (y1+ a*(x-x1));
          cout<<"X "<< x << "Y "<< y <<endl;
          glVertex2f(x,y);

          x+=0.01;
       }

       /* 
       for(float i = 0; i <= 100; ){
          glVertex2f(i,i);
          i+=0.01;
       }*/

   glEnd();
}


void display()
{
    glClear( GL_COLOR_BUFFER_BIT );

    //glMatrixMode( GL_PROJECTION );
    //glLoadIdentity();
    //double ar = glutGet( GLUT_WINDOW_WIDTH ) / (double)glutGet( GLUT_WINDOW_HEIGHT );
    //glOrtho( -2 * ar, 2 * ar, -2, 2, -1, 1);

    //glMatrixMode( GL_MODELVIEW );
    //glLoadIdentity();

    glColor3ub( 255, 255, 0 );


    drawLineIncremental(0,0,0.8,0.5);
    glutSwapBuffers();
}

int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition(0, 0);
    glutCreateWindow( "DRAW LINE INCREMENTAL" );
    glutDisplayFunc( display );
    glutMainLoop();
    return 0;
}











