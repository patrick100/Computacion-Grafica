#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;



void drawLineMiddlePoint(float x1,float y1,float x2,float y2) {
   
   float dx, dy, incE, incNE, d, x,y;

   dx = x2 - x1;
   dy = y2 - y1;

   d = 2* dy-dx; /* Valor inicial de d */

   incE = 2*dy; /* Incremento de E*/
   incNE = 2*(dy-dx); /* Incremento de NE*/

   x = x1;
   y = x1;

   glBegin(GL_POINTS);

   glVertex2f(x,y);

   while( x < x2){

      if(d <= 0){
        /*Escoger E*/
        d = d + incE;
        x = x+0.01;
      }else{
        /*Escoger NE*/
        d = d + incNE;
        x = x + 0.01;
        y = y + 0.01;
      }
      glVertex2f(x,y);

   }

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


    drawLineMiddlePoint(0,0,0.8,0.5);
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











