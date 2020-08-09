#pragma once
#include "Weapon.h"

class HolyWater:public Weapon
{
	DWORD timeStartFire;
public:
	float denta_x;
	HolyWater();
	int isDied;
	void SetDied() { isDied = 1; };
	bool isFirst = false;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void setPosixtion(float _x, float _y, int _nx);
	virtual void SetFirst(bool _isFirst);
	virtual bool GetFirst();
	virtual void Reset(float x_t, float y_t, int nx_temp);

	~HolyWater();
};

