#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;


void graph_poligon( unsigned int sides, float radio )
{
    if( sides < 3 ) return;

    const float PI = 3.14159;
    const float step = ( 2 * PI ) / static_cast< float >( sides );

    //const float step =0.1;

    cout<<"STEP IS: "<< step<<endl;

    //glBegin( GL_LINE_LOOP );
    glBegin( GL_LINES );
    /*
    for( unsigned int i = 0; i < sides; ++i )
    {
        cout<<"X " << cos( i * step ) <<" Y " << sin( i * step )<<endl;
        glVertex2f( cos( i * step ), sin( i * step ) );
    }*/
    
    for( unsigned int i = 0; i < sides; ++i )
    {
        unsigned int cur = ( i + 0 ) % sides;
        unsigned int nxt = ( i + 1 ) % sides;

        //cout<<"PUNTO "<<cur<<" CON "<<nxt<<endl;
        glVertex2f( cos( cur*step)*radio, sin( cur * step)*radio);
        glVertex2f( cos( nxt*step)*radio, sin( nxt * step)*radio);

    


        cout<<"X " << cos( i * step)*radio <<" Y " << sin( i * step)*radio<<endl;
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


    graph_poligon(40,0.8);
    glutSwapBuffers();
}

int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition(0, 0);
    glutCreateWindow( "CREAR UN POLYGONO" );
    glutDisplayFunc( display );
    glutMainLoop();
    return 0;
}