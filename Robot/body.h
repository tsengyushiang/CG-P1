#pragma once

#include "glObject.h"
#include <vector>
using namespace std;
#define GL_PI (3.1415926)

class Point3D
{
public:
	GLfloat x;
	GLfloat y;
	GLfloat z;

	Point3D() :x(x), y(y), z(z) {};
	Point3D(float x, float y, float z) :x(x), y(y), z(z) {}
	void Rx(float anlge);
	void Rz(float angle);
};

class Branch:
	public Point3D
{
	float angleX;
	float angleY;
	float angleZ;
public:
	void SetPoint(Point3D p) { x = p.x; y = p.y; z = p.z; }
	void SetAxis(float x, float y, float z) { angleX = x; angleY = y; angleZ = z;}
	void TransAndRotate()
	{
		glTranslatef(x, y, z);
		glRotatef(angleX, 1,0,0);
		glRotatef(angleY, 0,1,0);
		glRotatef(angleZ, 0,0,1);
	}
	void(*func)(void);
};

class Body :	
	public glObj
{	

public:
	float angleX;
	float angleY;
	float angleZ;
	
	float offsetAngleX;
	float offsetAngleY;
	float offsetAngleZ;

	float r;
	float heigh;
	int stack;	

	vector<Body> branches;
	vector<Branch> leaves;
	
	GLint TexBody;
	GLint TexTopLid;
	GLint TexBottomLid;

	float factorX;
	float factorZ;


	Body();
	Body(float radius,int stack,float heigh);	
	~Body();

	void DeleteBranch(int);

	Body* GetBranches(int index);
	int AddBranch(int Lstack, float angle,Body,bool center=0);
	int AddBranch(int ,float, void(func)(void),bool center=0);

	void SetTexture(int Body, int Top, int Bottom);


	void SetRotateAngle(float,float,float);
	void SetoffSetAngle(float, float, float);
	void Draw();
	void clear();
};
