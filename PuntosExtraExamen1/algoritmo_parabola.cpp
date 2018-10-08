#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;



void parabola(float x1,float y1,float x2,float y2) {
   
   float x,y;

   glBegin(GL_POINTS);

       for(x=x1; x<=x2;){
         
        
          //Calculamos el lado positivo
          y= pow(x,2);
          
          glVertex2f(x,y);

          //Calculamos el lado negativo   
          glVertex2f(x*-1,y);
          x+=0.01;
       } 

   glEnd();
}


void display()
{
    glClear( GL_COLOR_BUFFER_BIT );

    glColor3ub( 255, 255, 0 );


    parabola(0,0,0.9,0.9);
    glutSwapBuffers();
}





int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition(0, 0);
    glutCreateWindow( "DRAW PARABOLA" );
    
    glutDisplayFunc( display );
    glutMainLoop();
    return 0;
}