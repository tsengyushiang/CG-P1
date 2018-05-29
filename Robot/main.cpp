
#include "Menu.h"
#include<cmath>

#define TIMERINTERVAL (25)
#define GL_PI (3.1415926)

void Init();
void Reshape(int, int);
void Timer(int value);
void Display();

//-----------------------------------------------camera
float cameraAngleX;
float cameraAngleY;
bool mouseLeftDown;
float mouseX, mouseY;
void mouse(int, int, int, int);
void mouseMotion(int, int);
//-----------------------------------------------camera


int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);

	/*Create Windwo*/
	glutInitWindowPosition(250, 250);
	glutInitWindowSize(500, 500);
	glutCreateWindow("ROBOT");

	/*Init*/
	Init();

	/*Funcs*/
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutTimerFunc(TIMERINTERVAL, Timer, 1);
	/*Menu*/
	CreateUserMenu();
	
	LoadTexture();

	glutMainLoop();

	return 0;
}

void light0()
{
	glEnable(GL_LIGHT0);
	float ambient[4] = { 0.2, 0.2, 0.2, 1.0 };
	float diffuse[4] = { 0.5, 0.5, 0.5, 1.0 };
	float specular[4] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat position[4] = { 1,0,1,0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);

	GLfloat matAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat matDiffuse[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat shininess = 128.0f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);


}

void Init()
{
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	light0();

}

void Reshape(int w, int h)
{
	if (h == 0)h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -50, 50);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt
	(
		0, 0, 1,
		0, 0, 0,
		0, 1, 0
	);

}


float test = 0;

void Timer(int value)
{
	static float step = 1;
	test += step;
	if (test >10 || test < -10)
		step *= -1;
	if(Action)Action();
	glutTimerFunc(TIMERINTERVAL, Timer, value);
	glutPostRedisplay();
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	glPushMatrix();
	//-----------------------------------------------camera
	glRotatef(cameraAngleX, 1, 0, 0);
	glRotatef(cameraAngleY, 0, 1, 0);
	//-----------------------------------------------	
	glScalef(1, 1, 1);
	glTranslatef(0, -0.5, 0);
	DrawRobot();

	glPopMatrix();
	glutSwapBuffers();

}

void mouse(int button, int state, int x, int y)//camera
{
	mouseX = x;
	mouseY = y;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseLeftDown = true;
		}
		else if (state == GLUT_UP)
			mouseLeftDown = false;
	}

}


void mouseMotion(int x, int y)//camera
{
	if (mouseLeftDown)
	{
		cameraAngleY += (x - mouseX);
		cameraAngleX += (y - mouseY);
		mouseX = x;
		mouseY = y;
	}
}