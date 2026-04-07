#include <iostream>
#include "freeglut.h"

void OnDraw(void);		 
void OnTimer(int value); 
void OnKeyboardDown(unsigned char key, int x, int y); 	

int ancho = 800, alto = 800;

void mouseClick(int button, int state, int x, int y);
void mousePassive(int x, int y);
void mouseDrag(int x, int y);

int mouseX = 0, mouseY = 0;
int estado = 0;
float anchoColor = ancho / 16.0;
float colorX = ancho/8.0, colorY = alto/8.0;
float colorY1 = 7 * colorY, colorY2 = 6 * colorY, colorY3 = 5 * colorY;
int color = 1;
int lastX = -1, lastY;

int puntos[1000][2];
int datosRegistrados = 0;
bool primerDato = true;

float umbral = 15;
float distanciaAnterior(int x, int y);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(ancho, alto);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Para doble buffer
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // Para buffer simple
	glutCreateWindow("Lienzo Virtual");

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glDisable(GL_LIGHTING);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, ancho, 0, alto, 50, -50); 
	//glutFullScreen();

	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(mousePassive);
	glutMotionFunc(mouseDrag);

	/*glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Por si se quiere dibujado sin borrado
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/

	glutMainLoop();

	return 0;
}
void OnDraw(void)
{	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	if (estado == 0) // solo borra si no se está dibujando
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
   
	glColor3ub(0,0,0); //NEGRO
	glPushMatrix();
	glTranslated(colorX, colorY1, 0);
	glutSolidCube(anchoColor);
	glPopMatrix();

	glColor3ub(230, 25, 25); // ROJO
	glPushMatrix();
	glTranslated(colorX, colorY2, 0);
	glutSolidCube(anchoColor);
	glPopMatrix();

	glColor3ub(25, 25, 230); // AZUL
	glPushMatrix();
	glTranslated(colorX, colorY3, 0);
	glutSolidCube(anchoColor);
	glPopMatrix();

	if (estado == 1) // dibujando
	{
		if (color == 1) glColor3ub(0, 0, 0);
		if (color == 2) glColor3ub(230, 25, 25);
		if (color == 3) glColor3ub(25, 25, 230);
		 
		if (lastX != -1)
		{
			glLineWidth(10.0); // Grosor del "pincel"
			glEnable(GL_LINE_SMOOTH);
			glBegin(GL_LINE_STRIP);
			glVertex2f(lastX, lastY);
			glVertex2f(mouseX, mouseY);
			glEnd();
			lastX = mouseX;
			lastY = mouseY;
		}
	}

	//glutSwapBuffers(); // Para buffer doble
	glFlush(); // Para buffer simple
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{

}

void OnTimer(int value)
{
		glutTimerFunc(250, OnTimer, 0);
		glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y) {
	
	mouseX = x;
	mouseY = alto - y;

	lastX = mouseX;
	lastY = mouseY;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		if (mouseX > colorX - anchoColor/2 && mouseX < colorX + anchoColor/2)
		{
			if (mouseY > colorY1 - anchoColor / 2 && mouseY < colorY1 + anchoColor / 2) { color = 1; printf("NEGRO\n"); }
			if (mouseY > colorY2 - anchoColor / 2 && mouseY < colorY2 + anchoColor / 2) { color = 2; printf("ROJO\n"); }
			if (mouseY > colorY3 - anchoColor / 2 && mouseY < colorY3 + anchoColor / 2) { color = 3; printf("AZUL\n"); }
		}
	}
}

void mousePassive(int x, int y) 
{
	mouseX = x;
	mouseY = alto - y;
	estado = 0;

	lastX = -1;
}

void mouseDrag(int x, int y)
{
	mouseX = x;
	mouseY = alto - y;
	estado = 1;

	if (datosRegistrados < 999)
	{
		if (primerDato)
		{
			puntos[datosRegistrados][0] = mouseX;
			puntos[datosRegistrados][1] = mouseY;
			primerDato = false;
		}
		else
		if (distanciaAnterior(puntos[datosRegistrados][0], puntos[datosRegistrados][1]) > umbral)
		{
			datosRegistrados++;
			puntos[datosRegistrados][0] = mouseX;
			puntos[datosRegistrados][1] = mouseY;
			std::cout << "(" << puntos[datosRegistrados][0] << "," << puntos[datosRegistrados][1] << ")" << "    Datos Registrados:" << datosRegistrados << std::endl;
		

			glColor3ub(250, 105, 25); // Dibuja puntos guardados
			glPushMatrix();
			glTranslated(puntos[datosRegistrados][0], puntos[datosRegistrados][1], 0);
			glutSolidCube(5);
			glPopMatrix();
		}
	}

	glutPostRedisplay();
}

float distanciaAnterior(int x, int y) {

	float distancia;
	distancia = sqrt(pow(x - mouseX, 2) + pow(y - mouseY, 2));

	return distancia;
}