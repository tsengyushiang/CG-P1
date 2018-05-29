#include "Robot.h"
#include "TextureApp.h"


Body Head(0.2,30,0.3);
Body LeftHand(0.05,30,0.4);
Body RightHand(0.05, 30, 0.4);
Body RightLeg(0.05, 30, 0.15);
Body LeftLeg(0.05, 30, 0.15);
Body Tail(0.03, 30, 0.3);
Body Upbody(0.2,30,0.2);
Body Downbody(0.2, 30, 0.1);

void DrawTexture()
{
	if (!Texture)return;
	vector<Body*> temp;
	temp.push_back(&Upbody);

	while (temp.size())
	{
		temp[0]->SetTexture(Texture, Texture, Texture);

		for (int i = 0; temp[0]->GetBranches(i); i++)
		{	
			temp.push_back(temp[0]->GetBranches(i));
		}
		temp.erase(temp.begin());
	}
}

void initail()
{
	Head.clear();
	LeftHand.clear();
	RightHand.clear();
	LeftLeg.clear();
	RightLeg.clear();
	Tail.clear();
	Upbody.clear();
	Downbody.clear();
}

void LoadTexture()
{
	GLint tex1 = TextureApp::GenTexture("../Texture/color.jpg");
	GLint tex2 = TextureApp::GenTexture("../Texture/iron.jpg");
	GLint tex3 = TextureApp::GenTexture("../Texture/wood.jpg");
	/*GLint tex4 = TextureApp::GenTexture("../Texture/fur.png");*/
}

void tail()
{
	GLUquadricObj *qObj = gluNewQuadric();
	gluQuadricNormals(qObj, GLU_SMOOTH);
	gluQuadricTexture(qObj, GL_TRUE);
	GLfloat Ke[] = {0.3,0.3,0,0};
	GLfloat Ke2[] = { 0,0,0.0,0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, Ke);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(-Tail.r,0,0);
	gluSphere(qObj, 0.1f, 24, 24);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glMaterialfv(GL_FRONT, GL_EMISSION, Ke2);
}

void Hat()
{
	GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat[] = { 0,0,0,0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);

	glColor3f(0.2, 0.2, 0.2);
	Body base(0.3, 20, 0.05);
	base.SetLocation(0.2, 0, 0);
	Body t(0.2, 20, 0.3);

	base.AddBranch(15, 0, t,1);
	base.Draw();
	glColor3f(1, 1, 1);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
}

void DrawRobot()
{
	Head.AddBranch(15, GL_PI * 2 + 0.8, []() {
		glutSolidSphere(0.08, 20, 20);
		glPushMatrix();
			glTranslatef(0, 0, 0.05);
			glColor3f(0, 0, 0);
			glutSolidSphere(0.05, 20, 20);
			glColor3f(1, 1, 1);
		glPopMatrix();
	});

	Head.AddBranch(15, GL_PI - 0.8, [] {
		glutSolidSphere(0.08, 20, 20);
		glPushMatrix();
			glTranslatef(0, 0, 0.05);
			glColor3f(0, 0, 0);
			glutSolidSphere(0.05, 20, 20);
			glColor3f(1, 1, 1);
		glPopMatrix();
	});		

	Head.AddBranch(8, 1.57, [] {
		glPushMatrix();
		glColor3f(1.0,0.5,0.5 );
		glScalef(1, 0.5, 1);
		glutSolidTorus(0.03,0.05, 20, 20);
		glColor3f(1, 1, 1);
		glPopMatrix();
	});

	LeftHand.SetoffSet(0, 0,-90);
	LeftHand.SetoffSetAngle(0,0,-30);
	
	RightHand.SetoffSet(0, 0,90);
	RightHand.SetoffSetAngle(0, 0, 30);

	Downbody.scaleY = -1;

	RightLeg.SetLocation(0.1, 0, 0);		
	LeftLeg.SetLocation(-0.1, 0, 0);

	Downbody.AddBranch(30, 3.14, RightLeg);
	Downbody.AddBranch(30, 6.28, LeftLeg);

	Tail.SetoffSetAngle(-30, 0, 0);
	Tail.SetoffSet(-90, 0, 0);
	Tail.AddBranch(30, 0, tail);
	Downbody.AddBranch(5, 4.5, Tail);

	Upbody.AddBranch(29, 3.14, Head,1);
	Upbody.AddBranch(20, 3.14, RightHand,1);
	Upbody.AddBranch(20, 6.28, LeftHand,1);
	Upbody.AddBranch(0, 0,Downbody,1);	
	

	if (HatIsOnHead)
		Upbody.GetBranches(HEAD)->AddBranch(30, 3.14, Hat,1);
	else
		Upbody.GetBranches(LEFTHAND)->AddBranch(30, 3.14, Hat);	

	DrawTexture();

	Upbody.Draw();
	initail();
}