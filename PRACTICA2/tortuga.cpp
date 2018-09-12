#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <vector>


using namespace std;


// how to compile g++ tortuga.cpp -lGL -lGLU -lglut


class Point{

public:
    float x,y;

    Point(float x,float y){
        this->x = x;
        this->y = y;
    }
};



void print_v(vector<Point*> &points){

    for (int i = 0; i < points.size(); ++i)
    {
      cout<<"X "<<  points[i]->x <<" Y " << points[i]->y<<endl; 
    }

}


void graph_poligon( unsigned int sides, float radio, float x , float y )
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
    
    
    vector<Point*> points;    

    for( unsigned int i = 0; i < sides; ++i )
    {

        Point *p1 = new Point(x,y);
        Point *p2 = new Point(x,y);

        unsigned int cur = ( i + 0 ) % sides;
        unsigned int nxt = ( i + 1 ) % sides;
        
        p1->x+= cos( cur*step)*radio;  p1->y+= sin( cur*step)*radio;
        p2->x+= cos( nxt*step)*radio;  p2->y+= sin( nxt*step)*radio; 

        glVertex2f( p1->x, p1->y);
        glVertex2f( p2->x, p2->y);

        //cout<<"PUNTO1 X "<< p1->x <<" Y "<< p1->y <<endl;
        //cout<<"PUNTO1 X "<< p2->x <<" Y "<< p2->y <<endl;
        points.push_back(p1);
        //points.push_back(p2);
        /*if(i!=sides-1){
            points.push_back(p2);
        }*/
        
        //cout<<"X " << cos( i * step)*radio <<" Y " << sin( i * step)*radio<<endl;
    }

    glEnd();
    //points.pop_back();
    //print_v(points);
}


void graph_tortuga(){


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


    //caparazon
    graph_poligon(12,0.25,0,0);
    
    //cabeza
    graph_poligon(18,0.11,0,0.35);


    //extensiones
    //derecha-abajo
    graph_poligon(18,0.06,0.2,-0.25);
    //izquierda-abajo
    graph_poligon(18,0.06,-0.2,-0.25);
    //izquierda-arriba
    graph_poligon(18,0.06,-0.2,0.25);
    //derecha-arriba
    graph_poligon(18,0.06,0.2,0.25);



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
    glutInitWindowSize( 800, 650 );
    glutInitWindowPosition(50, 100);
    glutCreateWindow( "GRAFICAR UNA TORTUGA" );
    
    glutKeyboardFunc(Move);
    glutDisplayFunc( display );
 


    glutMainLoop();
    return 0;
}