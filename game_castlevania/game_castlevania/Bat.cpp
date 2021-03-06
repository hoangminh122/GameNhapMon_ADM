﻿#include "Bat.h"
#include "Simon.h"
#include "Grid.h"
#include "Map.h"
#include "Item.h"

Bat::Bat(float x, float y)
{
	start_x = x;
	start_y = y;
	vx = vy = 0;
	this->x = x;
	this->y = y;
	//isDied = 0;
}

int Bat::heard = 0;

void Bat::SetColi(bool t)
{
	isColi = t;
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	//isDied = 1;
	
	if (this ->isDied == 1) {
		Grid* grid = Grid::GetInstance();
		grid->deleteObject(this);
	}

	
	/*if (this->ID_Item == 0)
	{*/
		float simonX = 0, simonY = 0;

		Simon::GetInstance()->GetPosition(simonX, simonY);											//quai  chay theo simon => lay vi tri cua simon
		DebugOut(L"simonX:%f, simonY:%f, x:%f, y:%f, left_max=%f, right_max=%f, top_max=%f, bot_max=%f\n", simonX, simonY, x, y, left_max, right_max, top_max, bot_max);

		/*if (y - simonY >= -20)
		{
			vy = -abs(vy) - dt;
			vy = -0.02f;
		}
		else if (y - simonY <= 20)
		{
			vy = abs(vy)+dt;
			vy = 0.02f;
		}
		else
			vy = 0;*/

		if (left_max < simonX && simonX < right_max && top_max < simonY && simonY < bot_max)
		{
			this->state = 1;
			vx = 0.03f;
			vy = 0.02;
			if (y_de == NULL)
				y_de = simonY;
		}
		if (y<simonY + 10 && y>simonY - 10)
		{
			if (vx > 0)
				y = simonY;
			vy = 0;
		}

		GameObject::Update(dt); // Update dt, dx, dy
		//DebugOut(L"vx=%f,vy=%f,dx:%f, dy:%f\n", vx,vy,dx,dy);
		y += dy;
		x += dx;
		if (y > y_de + 42) y = y_de + 42;
		if (y < 1) y = 1;
		Map* map = Map::GetInstance();
		if (x > map->GetWidth() - 10)
		{
			x = start_x;
			y = start_y;
			vx = 0;
			vx = 0;
			this->state = 0;


		}
		//else
			//grid->Update(this);

	

	
	
	

}

void Bat::Render()
{
	/*if (this->state == 3) {
		this->isDied = 1;
	}*/
	//else {
		animation_set->at(state)->Render(x, y);
		RenderBoundingBox();
	//}
}

void Bat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + 16;
	bottom = top + 16;
}
