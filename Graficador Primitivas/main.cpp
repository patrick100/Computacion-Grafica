# include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <map>
#include <string>
#include <vector>
using namespace std;
GLsizei winWidth , winHeight; // Initial display window size.

int xi, xf, xt;
int yi ,yf, yt;
int iFondo = 0;
int iDibujo = 3;
int iFigura = 6;
typedef enum {FONDO1 ,FONDO2 ,FONDO3 ,DIBUJO1 ,DIBUJO2 ,DIBUJO3 ,LINEA ,CIRCULO ,CUADRADO ,ELIPSE} opcionesMenu;
void put_pixel(int x, int y)
{
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}
void DDA (int x1,int y1,int x2,int y2)
{
	float ax,ay,x,y,orientacion;
	abs(x2-x1)>=abs(y2-y1)?orientacion=abs(x2-x1):orientacion=abs(y2-y1);
	ax=(x2-x1)/orientacion;
	ay=(y2-y1)/orientacion;
	x=(float)x1;
	y=(float)y1;
	for (int i = 0; i <= orientacion; ++i){
		put_pixel(floor(x),floor(y));
		x=x+ax;
		y=y+ay;
	}
}
void LSquare(int x1, int y1, int x2, int y2)
{
	DDA(x1,y1,x2,y1);
	DDA(x1,y2,x2,y2);
	DDA(x1,y1,x1,y2);
	DDA(x2,y2,x2,y1);
}
void Square(int x1,int y1,int x2,int y2)
{
	int tam;
	bool def_axis;
	abs(x2-x1)>=abs(y2-y1)?def_axis=true:def_axis=false;
	if(def_axis) tam=abs(x2-x1);
	else tam=abs(y2-y1);
	// Cuadrantes
	if(x2-x1>=0 && y2-y1 >=0)
		LSquare(x1,y1,x1+tam,y1+tam);
	else if(x2-x1>0 && y2-y1<0)
		LSquare(x1,y1,x1+tam,y1-tam);
	else if(x2-x1<0 && y2-y1<0)
		LSquare(x1,y1,x1-tam,y1-tam);
	else if(x2-x1<0 && y2-y1>0)
		LSquare(x1,y1,x1-tam,y1+tam);
}
void circlePlotPoints (int x1, int y1, int x2, int y2)
{
	put_pixel (x1 + x2, y1 + y2);
	put_pixel (x1 - x2, y1 + y2);
	put_pixel (x1 + x2, y1 - y2);
	put_pixel (x1 - x2, y1 - y2);
	put_pixel (x1 + y2, y1 + x2);
	put_pixel (x1 - y2, y1 + x2);
	put_pixel (x1 + y2, y1 - x2);
	put_pixel (x1 - y2, y1 - x2);
}

void circleMidpoint (int x, int y, GLint radius)
{
	GLint x1, y1;
	GLint p = 1 - radius; // Initial value for midpoint parameter.
	x1 = 0;
	y1 = radius;
	circlePlotPoints(x, y, x1, y1);
	/* Plot the initial point in each circle quadrant. */
	circlePlotPoints (x, y, x1, y1);
	/* Calculate next point and plot in each octant. */
	while (x1 < y1) {
		x1++;
		if (p < 0)
			p += 2 * x1 + 1;
		else {
			y1--;
			p += 2 * (x1-y1) + 1;
		}
		circlePlotPoints (x, y, x1, y1);
	}
}
void circle(int x1, int y1, int x2, int y2)
{
	GLint r = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
	circleMidpoint(x1,y1,r);
}
void PlotPoints(int xc,int yc, int x, int y)
{
	put_pixel(xc+x,yc+y);
	put_pixel(xc-x,yc+y);
	put_pixel(xc+x,yc-y);
	put_pixel(xc-x,yc-y);
}
void ElipseMidPoints(int xc, int yc, int rx, int ry)
{
	float x,y,rx2,ry2,p1,p2;
	x=0;
	y=ry;
	rx2=pow(rx,2);
	ry2=pow(ry,2);
	p1=ry2-(rx2*ry)+(0.25*rx2);
	while((ry2*x)<(rx2*y)){
		if(p1<0){ x++;
		p1=p1+(2*ry2*x)+ry2;
		}
		else{
			x++; y--;
			p1=p1+(2*ry2*x)-(2*rx2*y)+ry2;
		}
		PlotPoints(xc,yc,x,y);
	}
	p2=(ry2)*pow((x+0.5) ,2)+(rx2)*pow((y-1) ,2)-(rx2*ry2);
	while(y>0){
		if (p2>0){
			y--;
			p2=p2-(2*rx2*y) +rx2;
		}
		else{
			x++; y--;
			p2=p2+ (2*ry2*x)-(2*rx2*y)+rx2;
		}
		PlotPoints(xc,yc,x,y);
	}
}
void Elipse(int x1, int y1, int x2, int y2)
{
	GLint rx = abs(x2-x1);
	GLint ry = abs(y2-y1);
	ElipseMidPoints(x1,y1,rx,ry);
}
void Pintar(int myFig)
{
	switch(myFig){
	case LINEA: DDA(xi,yi,xf,yf); break;
	case CUADRADO: Square(xi,yi,xf,yf); break;
	case CIRCULO: circle(xi,yi,xf,yf); break;
	case ELIPSE: Elipse(xi,yi,xf,yf); break;
	}
}
void onMenu(int opcion)
{
	switch(opcion){
	case FONDO1: iFondo = 0; break;
	case FONDO2: iFondo = 1; break;
	case FONDO3: iFondo = 2; break;
	case DIBUJO1: iDibujo = 3; break;
	case DIBUJO2: iDibujo = 4; break;
	case DIBUJO3: iDibujo = 5; break;
	case LINEA: iFigura = 6; break;
	case CIRCULO: iFigura = 7; break;
	case CUADRADO: iFigura = 8; break;
	case ELIPSE: iFigura = 9; break;
	}
	glutPostRedisplay();
}
void creacionMenu()
{
	int menuFigura , menuFondo , menuDibujo , menuPrincipal;
	menuFigura = glutCreateMenu(onMenu);
	glutAddMenuEntry("Linea", LINEA);
	glutAddMenuEntry("Circulo", CIRCULO);
	glutAddMenuEntry("Cuadrado", CUADRADO);
	glutAddMenuEntry("Elipse", ELIPSE);
	menuFondo = glutCreateMenu(onMenu);
	glutAddMenuEntry("Negro",FONDO1);
	glutAddMenuEntry("Verde Oscuro",FONDO2);
	glutAddMenuEntry("Azul Oscuro",FONDO3);
	menuDibujo = glutCreateMenu(onMenu);
	glutAddMenuEntry("Blanco",DIBUJO1);
	glutAddMenuEntry("Verde Claro",DIBUJO2);
	glutAddMenuEntry("Azul Claro",DIBUJO3);
	menuPrincipal = glutCreateMenu(onMenu);
	glutAddSubMenu("Figura",menuFigura);
	glutAddSubMenu("Color de Fondo",menuFondo);
	glutAddSubMenu("Color de Dibujo",menuDibujo);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void resize(GLsizei w, GLsizei h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,w,0,h,1.f,-1.f);
	printf("Resize:: %dx%d\n",w,h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void display(void)
{
	int i;
	float colores[6][3] = {
		{0.00f, 0.00f, 0.00f}, // 0 - negro
	{0.06f, 0.25f, 0.13f}, // 1 - verde claro
		{0.10f, 0.07f, 0.33f}, // 2 - azul oscuro
	{1.00f, 1.00f, 1.00f}, // 3 - blanco
		{0.12f, 0.50f, 0.26f}, // 4 - verde claro
	{0.20f, 0.14f, 0.66f}, // 5 - azul claro
	};
	glClearColor (colores[iFondo][0],colores[iFondo][1],colores[iFondo][2], 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(colores[iDibujo][0],colores[iDibujo][1],colores[iDibujo][2]);
	Pintar(iFigura);
	glBegin(GL_POINTS);
	glColor3f(1,0,0);
	for (i = -5; i <= 5; i++){
		glVertex2i(xi+i,yi);
		glVertex2i(xi,yi-i);
	}
	glEnd();
	glutSwapBuffers();
}
void mouse_move(int x, int y)
{
	xt = x;
	yt = winHeight -y;
	glutPostRedisplay();
}
void mouse_drag(int x, int y)
{
	xf = x;
	yf = winHeight - y;
	glutPostRedisplay();
}
typedef GLubyte Color[3];
void getPixel(int x, int y, Color rgb)
{
	glReadPixels(x, y, 1, 1, GL_RGB , GL_UNSIGNED_BYTE , rgb);
}
void mouse_click(int button , int state , int x, int y)
{
	Color c;
	if(state== GLUT_DOWN){
		xi=x;
		yi=winHeight - y;
		xf=xi;
		yf=yi;
		getPixel(xi, yi, c);
		printf("Posicion inicial: %3d, %3d\n",xi,yi);
	}
	if(state==GLUT_UP){
		printf("Posicion final: %3d, %3d\n",xf,yf);
	}
	glutPostRedisplay();
}
void normal_key(GLubyte key, int x, int y)
{
	char s[80] = "";
	if(glutGetModifiers() & GLUT_ACTIVE_SHIFT) sprintf(s, "%s SHIFT ", s);
	if(glutGetModifiers() & GLUT_ACTIVE_CTRL) sprintf(s, "%s CTRL ", s);
	if(glutGetModifiers() & GLUT_ACTIVE_ALT) sprintf(s, "%s ALT ", s);
	if(key >= 32 && key <= 128)
		printf("normal key: �%c� dec:%d %s\n", key, key, s);
	else
		printf("normal key: dec:%d %s\n",key,s);
	if(key==27)
		exit(0);
}
void special_key(int key, int x, int y)
{
	printf("special key # %d\n",key);
}
void timer_function(int value)
{
	printf("Posicion del puntero %d, %d\n",xt,yt);
	glutTimerFunc(8000, timer_function , 1);
}
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(800,0);
	glutCreateWindow("Graficador Primitivas");
	glutDisplayFunc(display);
	creacionMenu();
	glutReshapeFunc(resize);
	glutPassiveMotionFunc(mouse_move);
	glutMotionFunc(mouse_drag);
	glutMouseFunc(mouse_click);
	glutKeyboardFunc(normal_key);
	glutSpecialFunc(special_key);
	glutTimerFunc(33,timer_function ,1);
	glutMainLoop();
	return 0;
}