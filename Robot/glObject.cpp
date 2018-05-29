#include "glObject.h"

glObj::glObj()
{
	locationX = 0;
	locationY = 0;
	locationZ = 0;
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	offSetRotateX = 0;
	offSetRotateY = 0;
	offSetRotateZ = 0;
}

glObj::glObj(glObj* a)
{
	locationX = a->locationX;
	locationY = a->locationY;
	locationZ = a->locationZ;
	scaleX = a->scaleX;
	scaleY = a->scaleY;
	scaleZ = a->scaleZ;
	offSetRotateX = a->offSetRotateX;
	offSetRotateY = a->offSetRotateY;
	offSetRotateZ = a->offSetRotateZ;
}

void glObj::SetLocation(float X, float Y, float Z)
{
	locationX = X;
	locationY = Y;
	locationZ = Z;
}

void glObj::SetScale(float x, float y, float z)
{
	scaleX = x;
	scaleY = y;
	scaleZ = z;
}

void glObj::SetoffSet(float x, float y, float z)
{
	
	offSetRotateX = x;
	offSetRotateY = y;
	offSetRotateZ = z;
}

void glObj::TransAndScale()
{
	glTranslatef(locationX, locationY, locationZ);
	glScalef(scaleX, scaleY, scaleZ);
	glRotatef(offSetRotateX,1,0,0);
	glRotatef(offSetRotateY,0,1,0);
	glRotatef(offSetRotateZ,0,0,1);

}
