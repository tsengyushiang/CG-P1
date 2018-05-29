#pragma once

#include "vgl.h"

class glObj
{
public:
	glObj(glObj*);
	glObj();
	void SetLocation(float, float, float);	
	void SetScale(float, float, float);
	void TransAndScale();
	void SetoffSet(float, float, float);	
	float locationX;
	float locationY;
	float locationZ;	
	float scaleX;
	float scaleY;
	float scaleZ;
	float offSetRotateX;
	float offSetRotateY;
	float offSetRotateZ;

};
