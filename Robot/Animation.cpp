#include"Robot.h"
#include "Menu.h"

float Hatstep;
float Walkstep;

void InitializeAngle(float& angle, float ref = 0)
{
	if (angle > ref)
		angle--;
	else if (angle < ref)
		angle++;
}

void StandBy()
{
	Hatstep = 5;
	Walkstep = 5;
	Tail.angleY = 0;
	Tail.angleZ = 0;
	Upbody.offSetRotateX=0;
	Upbody.locationY =0;
	Head.SetRotateAngle(0, 0, 0);
	Upbody.SetRotateAngle(0, 0, 0);
	Downbody.SetRotateAngle(0, 0, 0);
	RightHand.SetRotateAngle(0, 0, 0);
	LeftHand.SetRotateAngle(0, 0, 0);
	RightLeg.SetRotateAngle(0, 0, 0);
	LeftLeg.SetRotateAngle(0, 0, 0);
}
void Walk()
{		
	Tail.angleZ += Walkstep;
	Upbody.angleX += Walkstep / 5;
	RightHand.angleY += Walkstep;
	LeftLeg.angleX += Walkstep;
	LeftHand.angleY += Walkstep;
	RightLeg.angleX -= Walkstep;
	if (LeftLeg.angleX > 90 || LeftLeg.angleX< -90)Walkstep *= -1;
}

void TakeHat()
{	
	
	if (RightHand.angleY > 0)RightHand.angleY-=5;
	if (RightHand.angleY < 0)RightHand.angleY+=5;

	RightHand.angleZ -= Hatstep;

	if ((RightHand.angleZ == -90))
	{
		Hatstep *= -1;
		HatIsOnHead = !HatIsOnHead;
	}

	if ((RightHand.angleZ == 0))
	{
		Hatstep = 5;
		Action = NULL;
	}

}

void Fly()
{
	static float step = 10;
	if (Tail.angleZ < 60)Tail.angleZ++;
	Tail.angleY+=20;

	LeftHand.angleZ+=step;
	RightHand.angleZ-=step;

	if ((LeftHand.angleZ < -50) || (LeftHand.angleZ > 50))step *= -1;

	if (Upbody.offSetRotateX < 70)
	{
		Upbody.offSetRotateX++;
		Upbody.locationY += 0.005;
	}
}

void sit_ups()
{

	if(Downbody.angleX < 30)Downbody.angleX+=5;
	
	if(LeftLeg.angleX>-90)LeftLeg.angleX -= 5;
	if (RightLeg.angleX>-90)RightLeg.angleX-=5;

	if(RightHand.angleX < 90)RightHand.angleX += 5;
	if(LeftHand.angleX < 90)LeftHand.angleX += 5;
	if (Tail.angleZ < 90)Tail.angleZ += 5;

	if (Upbody.offSetRotateX != -90)Upbody.offSetRotateX-=5;
	else
	{
		Action = Ready;
	}

}

void Ready()
{
	static float step = 5;
	if (Upbody.offSetRotateX != -90)Upbody.offSetRotateX--;
	Upbody.angleX += step;
	if ((Upbody.angleX > 80) || (Upbody.angleX<0))step *= -1;

}
