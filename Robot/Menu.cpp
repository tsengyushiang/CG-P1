#include "Menu.h"

using namespace std;

void(*Action)(void)=NULL;
int Texture=0;
bool HatIsOnHead;


void ChoseActions(int index)
{
	if (index == 0)
		Action = StandBy;
	if (index == 1)
		Texture = !Texture ;
	if (index == 2)
		Action = Walk;
	if (index == 3)
		Action = TakeHat;
	if (index == 4)
		Action = Fly;
	if (index == 5)
		Action = sit_ups;
		
}

void Textures(int index)
{
	Texture = index;

}


void CreateUserMenu()
{
	int actions = glutCreateMenu(ChoseActions);
	int Texture = glutCreateMenu(Textures);
	Action = StandBy;	

	glutSetMenu(actions);
	glutAddMenuEntry("Stand", 0);
	glutAddSubMenu("Textures",Texture);
	glutAddMenuEntry("Walk", 2);
	glutAddMenuEntry("Hat", 3);
	glutAddMenuEntry("FLY", 4);
	glutAddMenuEntry("Sit_Ups", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutSetMenu(Texture);
	glutAddMenuEntry("None", 0);
	glutAddMenuEntry("Color",1);
	glutAddMenuEntry("iron", 2);
	glutAddMenuEntry("Wood", 3);

}