#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "Torch.h"
#include "Brick.h"
#include "Bat.h"
#include "Knight.h"
#include "Ghost.h"
#include "Monkey.h"
#include "HolyWater.h"

class Whip: public GameObject
{
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render(int level,int nx, int frame, int alpha=255);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

