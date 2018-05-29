#pragma once

#include "body.h"


enum {HEAD,LEFTHAND,RIGHTHAND,RIGHTLEG,LEFTLEG,TAIL};

extern Body Head;
extern Body LeftHand;
extern Body RightHand;
extern Body RightLeg;
extern Body LeftLeg;
extern Body Tail;
extern Body Upbody;
extern Body Downbody;

void InitializeAngle(float&, float);
void DrawRobot();
void LoadTexture();


extern int Texture;

void Walk();
void StandBy();
void Fly();

void Ready();
void sit_ups();

void TakeHat();
extern bool HatIsOnHead;