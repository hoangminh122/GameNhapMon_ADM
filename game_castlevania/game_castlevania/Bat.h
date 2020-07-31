#pragma once
#include "GameObject.h"

class Bat:public GameObject
{

	float start_x;
	float start_y;
	float y_de = NULL;
	
	
public:
	int isDied = 0;
	bool isIdle;
	float left_max, right_max, top_max, bot_max;
	void SetDied() { isDied = 1; };
	Bat(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

