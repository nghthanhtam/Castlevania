#include "Ghoul.h"



CGhoul::CGhoul()
{
	this->AddAnimation(104);
	this->AddAnimation(110);
}

CGhoul::~CGhoul()
{
}

void CGhoul::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDeleted)
		return;

	CGameObject::Update(dt, coObjects);
	
	vy += 0.015f*dt;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		if (!isFreezed && !isStop)
		{
			x += dx; //dx=vx*dt
			y += dy;
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		y += min_ty * dy + ny * 0.2f;

		if (!isFreezed && !isStop)
		{
			// block 
			if (nx != 1)
				x += min_tx * dx + nx * 0.2f;;

			if (nx == 1)  //đụng trái	
				x += dx;
		}

		if (ny != 0) vy = 0;
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


	if (isFlip)
		vx = 0.052f;
	else
		vx = -0.052f;

	if (x >= 1520 && x <= 1530 && isFlip==true) //Simon đụng tường phải của màn 0 thì quay lại
	{
		isFlip = false;
		x = 1505;
	}
}

void CGhoul::Render(Camera * camera)
{
	CEnemy::Render(camera);

	if (isFreezed || isStop)
	{
		if(isFlip)
			animations[1]->Render(camera->transform(x, y), 255, 1);
		else
			animations[1]->Render(camera->transform(x, y));
	}
	else
	{
		if (isFlip)
			animations[0]->Render(camera->transform(x, y), 255, 1);
		else
			animations[0]->Render(camera->transform(x, y));
	}
	RenderBoundingBox(camera);
}

RECT CGhoul::GetBound()
{
	return CGameObject::GetBound();
}

void CGhoul::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (isFlip)
	{
		left = x-16;
		top = y;
		right = x;
		bottom = y + 32;
	}
	else
	{
		left = x+1;
		top = y;
		right = x + 16;
		bottom = y + 32;
	}
}
