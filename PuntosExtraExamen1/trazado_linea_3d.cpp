#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;



void drawLineIncremental(float x1,float y1,float z1,float x2,float y2,float z2) {
   
   float x,y,z;
   float a;


   glBegin(GL_POINTS);
        
       //hallamos la pendiente       
       a = (y2-y1)/(x2-x1);
       //float zx=0;
       for (z =z1; z<=z2;)
       {
       
	       for(x=x1; x<=x2;){
	         
	          //y = a + b(y1+a*0.01;

	          y = (y1+ a*(x-x1));
	          //cout<<"X "<< x << "Y "<< y <<endl;
	          glVertex3f(x,y,z);
	          x+=0.01;
	       }

	       //zx = x-y;     
	      

	       z+=0.01;
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


    drawLineIncremental(0,0,0,0.8,0.5,0.5);
    glutSwapBuffers();
}


void Move(unsigned char key, int x, int y)
{

    
    
   switch(key) {
    

    /* TRASLACION */
    //glTranslatef(x,y,z)
    case 'w' :
        cout<<"UP"<<endl;
        glTranslatef(0.0, 0.1 ,0.0);
        break;
    case 'a' : 
        cout<<"LEFT"<<endl;
        glTranslatef(-0.1, 0.0 ,0.0);
        break;
    case 's' :
        cout<<"DOWN"<<endl;
        glTranslatef(0.0, -0.1, 0);
        break;
    case 'd' :
        cout<<"RIGHT"<<endl;
        glTranslatef(0.1, 0 ,0.0);
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



int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition(0, 0);
    glutCreateWindow( "DRAW LINE INCREMENTAL" );

    glutKeyboardFunc(Move);

    glutDisplayFunc( display );
    glutMainLoop();
    return 0;
}