#include "Bat.h"


CBat::CBat()
{
}

CBat::CBat(D3DXVECTOR2 pos)
{
	FirstY = pos.y;

	vx = 0.04f;
	vy = 0.03f;

	this->AddAnimation(107);
	this->AddAnimation(111);
}

CBat::~CBat()
{
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDeleted)
		return;

	CGameObject::Update(dt);

	if (!isFreezed && !isStop)
	{
		if (isFlip)
			x += dx;
		else
			x -= dx;

		y += dy;
	}

	if (vy < 0 && y < FirstY)
	{
		y = FirstY; vy = -vy;
	}

	if (vy > 0 && y > FirstY + 20)
	{
		y = FirstY + 20; vy= -vy;
	}
}

void CBat::Render(Camera * camera)
{
	CEnemy::Render(camera);

	if (isFreezed || isStop)
	{
		if (isFlip)	
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

RECT CBat::GetBound()
{
	return CGameObject::GetBound();
}

void CBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (isFlip)
	{
		left = x-16;
		top = y;
		right = x;
		bottom = y + 14;
	}
	else
	{
		left = x;
		top = y;
		right = x + 16;
		bottom = y + 14;
	}


}

