#include "body.h"

void Point3D::Rx(float angle)
{
	Point3D t = *this;
	angle = angle*GL_PI / 180;
	t.x = x;
	t.y = cos(angle)*y - sin(angle)*z;
	t.z = sin(angle)*y + cos(angle)*z;
	*this = t;
}

void Point3D::Rz(float angle)
{
	Point3D t = *this;
	angle = angle*GL_PI / 180;
	t.x = cos(angle)*x - sin(angle)*y;
	t.y = sin(angle)*x + cos(angle)*y;
	t.z = z;
	*this = t;
}

Body::~Body()
{
}

Body::Body()
{
	r = 0.2;
	stack = 30;
	heigh = 0.5;
	angleX = 0;
	angleY = 0;
	angleZ = 0;
	factorX = 1;
	factorZ = 1;
	offsetAngleX = 0;
	offsetAngleY = 0;
	offsetAngleZ = 0;
}

Body::Body(float radius, int s, float h)
{
	r = radius;
	stack = s;
	heigh = h;
	angleX = 0;
	angleY = 0;
	angleZ = 0;
	factorX = 1;
	factorZ = 1;
	offsetAngleX =0;
	offsetAngleY =0;
	offsetAngleZ =0;
	TexBody=0;
	TexTopLid=0;
	TexBottomLid=0;
}

void Body::SetRotateAngle(float X, float Y, float Z)
{
	angleX = X;
	angleY = Y;
	angleZ = Z;
	factorX = angleX > 0 ? 1 : -1;
	factorZ = angleZ > 0 ? 1 : -1;
}

void Body::DeleteBranch(int index)
{
	if(index<leaves.size())
	leaves.erase(leaves.begin()+index);
}

int Body::AddBranch(int LStack, float angle, void(func)(void),bool center)
{
	float angleX = Body::angleX + offsetAngleX;
	float angleY = Body::angleY + offsetAngleY;
	float angleZ = Body::angleZ + offsetAngleZ;
	factorX = angleX > 0 ? 1 : -1;
	factorZ = angleZ > 0 ? 1 : -1;

	Branch newB;	

	newB.SetPoint(Point3D(cos(angle)*r + r*factorZ, (heigh / stack * (LStack + 1)), sin(angle)*r - r*factorX));
	newB.Rz(angleZ / stack * (LStack + 1));
	newB.Rx(angleX / stack * (LStack + 1));
	newB.SetAxis(angleX / stack * (LStack + 1), 0, angleZ / stack * (LStack + 1));
	newB.func = func;

	leaves.push_back(newB);
	
	return int(leaves.size()) - 1;
}

void Body::clear()
{
	branches.clear();
	leaves.clear();
	TexBody = 0;
	TexBottomLid = 0;
	TexTopLid = 0;
}

Body* Body::GetBranches(int index)
{
	if(branches.size()&&index<branches.size())
		return &branches[index];
	return NULL;
}

void Body::SetoffSetAngle(float x, float y, float z)
{
	offsetAngleX = x;
	offsetAngleY = y;
	offsetAngleZ = z;		
}

int Body::AddBranch(int Lstack, float angle,Body newB,bool center)
{
	float angleX = Body::angleX + offsetAngleX;
	float angleY = Body::angleY + offsetAngleY;
	float angleZ = Body::angleZ + offsetAngleZ;
	factorX = angleX > 0 ? 1 : -1;
	factorZ = angleZ > 0 ? 1 : -1;

	Point3D p(cos(angle)*r + r*factorZ, (heigh / stack * (Lstack + 1)), sin(angle)*r - r*factorX);

	if (center)
		p = Point3D(r*factorZ, (heigh / stack * (Lstack + 1)), -r*factorX);
	
	float X=newB.locationX;
	float Y=newB.locationY;
	float Z=newB.locationZ;
	
	float offX = newB.offSetRotateX ;
	float offY = newB.offSetRotateY ;
	float offZ = newB.offSetRotateZ;

	p.Rx(angleX / stack * (Lstack + 1));
	p.Rz(angleZ / stack * (Lstack + 1));	

	newB.SetLocation(p.x+X,p.y+Y,p.z+Z);
	
	newB.SetoffSet(angleX / stack * (Lstack + 1) +offX, offY, angleZ / stack * (Lstack + 1) +offZ);

	branches.push_back(newB);

	return branches.size()-1;
}


void Body::SetTexture(int Body, int Top, int Bottom)
{
	TexBody = Body;
	TexTopLid = Top;
	TexBottomLid = Bottom;
}

void Body::Draw()
{
	float angleX = Body::angleX + offsetAngleX;
	float angleY = Body::angleY + offsetAngleY;
	float angleZ = Body::angleZ + offsetAngleZ;
	factorX = angleX > 0 ? 1 : -1;
	factorZ = angleZ > 0 ? 1 : -1;


	vector<Point3D> lastCircle;
	vector<Point3D> firstCircle;

	Point3D base;
	Point3D end;

	float TexHigh = (float)1 / stack;
	float TexX, TexY = 0;
	int TexIndex = 0;


	glPushMatrix();

		TransAndScale();
		glRotatef(angleY, 0, 1, 0);
		glTranslatef(-r*factorZ, 0, r*factorX);

		if (TexBody);
		glEnable(GL_TEXTURE_2D);  /*------------------------texture*/		
		glBindTexture(GL_TEXTURE_2D, TexBody);

		glBegin(GL_TRIANGLE_STRIP);

		for (float i = 0; i < stack; i++, TexY += TexHigh)
		{
			TexIndex = 0;
			TexX = 0;
			for (float a = 0; a < GL_PI * 2 + 0.1; a += 0.1, TexX += (float)1 / 60)
			{
				Point3D Origion(r*factorZ, (heigh / stack * i),- r*factorX);
				base = Point3D(cos(a)*r + r*factorZ, (heigh / stack * i), sin(a)*r - r*factorX);
				end = Point3D(cos(a)*r + r*factorZ, (heigh / stack * (i + 1)), sin(a)*r - r*factorX);

				base.Rz(angleZ / stack * i);
				base.Rx(angleX / stack * i);

				glNormal3f(base.x-Origion.x, base.y - Origion.y, base.z - Origion.z);
				glTexCoord2d(TexX, TexY);
				glVertex3f(base.x, base.y, base.z);

				end.Rz(angleZ / stack * (i + 1));
				end.Rx(angleX / stack * (i + 1));

				glNormal3f(end.x - Origion.x, end.y - Origion.y, end.z - Origion.z);
				glTexCoord2d(TexX, TexY + TexHigh);
				glVertex3f(end.x, end.y, end.z);

				//----------------------------------------top & bottom lid
				if (i == stack - 1) {
					lastCircle.push_back(end);
				}
				if (!i) {
					firstCircle.push_back(base);
				}
				//-----------------------------------------			
				TexIndex++;
			}
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);

		/*Top lid*/

		if (TexTopLid)
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, TexTopLid);
		glBegin(GL_TRIANGLE_FAN);
		float a = 0;
		for (Point3D p : lastCircle)
		{
			glNormal3f(0, 1, 0);
			glTexCoord2f(cos(a)*0.5 + 0.5, sin(a)*0.5 + 0.5);
			glVertex3f(p.x, p.y, p.z);
			a += 0.1;
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);

		/*bottom lid*/
		if (TexBottomLid)
			glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, TexBottomLid);
		glBegin(GL_TRIANGLE_FAN);
		for (Point3D p : firstCircle)
		{
			glNormal3f(0, -1, 0);
			glTexCoord2f(cos(a)*0.5 + 0.5, sin(a)*0.5 + 0.5);
			glVertex3f(p.x, p.y, p.z);
			a += 0.1;
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);		


		/*Added Object*/
		for (Branch b : leaves)
		{
			glPushMatrix();
				b.TransAndRotate();
				if (b.func)
				b.func();				
			glPopMatrix();
		}

		for (Body b : branches)
		{		
			b.Draw();			
		}


	glPopMatrix();
}