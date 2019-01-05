#include "Item.h"
#include "debug.h"


CItem::CItem(CSimon *Simon)
{
	mSimon = Simon;
}

CItem::CItem()
{
}

CItem::CItem(D3DXVECTOR2 pos)
{
	vx = -0.05f;
	firstX = pos.x;
}


CItem::~CItem()
{
}


void CItem::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{		
	if (this->ObjectTag != CGameObject::crystalball)
	{
		if (timer < 3000)
			timer += dt;
		else
		{
			isDeleted = true;
			return;
		}
	}


	if (isOnGround == false)
	{
		if (vx < 0 && x < firstX)
		{
			x = firstX; vx = -vx;
		}

		if (vx > 0 && x > firstX + 10)
		{
			x = firstX + 10; vx = -vx;
		}
	}

	CGameObject::Update(dt);
	this->vy += 0.0003*dt;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx; //dx=vx*dt
		y += dy;
	}
	else
	{
		
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		y += min_ty * dy + ny * 0.2f;

		if (nx != 0) vx = 0;
		if (ny == -1) { isOnGround = true; vy = 0; vx = 0; }
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CItem::Render(Camera *camera)
{	
	if (this->ObjectTag == CGameObject::ObjectTypes::None)
		return;

	animations[0]->Render(camera->transform(x, y));

	RenderBoundingBox(camera);
}

void CItem::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (this->ObjectTag == CGameObject::None)
		return;

	if (this->ObjectTag == CGameObject::whipupgrade)
	{
		left = x;
		top = y;
		right = x + 17;
		bottom = y + 15;
	}
	else if (this->ObjectTag == CGameObject::stopwatch)
	{
		left = x;
		top = y;
		right = x + 15;
		bottom = y + 16;
	}
	else if (this->ObjectTag == CGameObject::smallheart)
	{
		left = x;
		top = y;
		right = x + 9;
		bottom = y + 8;
	}
	else if (this->ObjectTag == CGameObject::holywater)
	{
		left = x;
		top = y;
		right = x + 13;
		bottom = y + 17;
	}
	else if (this->ObjectTag == CGameObject::cross)
	{
		left = x;
		top = y;
		right = x + 13;
		bottom = y + 16;
	}
	else if (this->ObjectTag == CGameObject::chicken)
	{
		left = x;
		top = y;
		right = x + 16;
		bottom = y + 13;
	}
	else if (this->ObjectTag == CGameObject::axe)
	{
		left = x;
		top = y;
		right = x + 16;
		bottom = y + 15;
	}
	else if (this->ObjectTag == CGameObject::whitemoneybag)
	{
		left = x;
		top = y;
		right = x + 16;
		bottom = y + 15;
	}
	else if (this->ObjectTag == CGameObject::doubleshot)
	{
		left = x;
		top = y;
		right = x + 14;
		bottom = y + 14;
	}
	else if (this->ObjectTag == CGameObject::potion)
	{
		left = x;
		top = y;
		right = x + 13;
		bottom = y + 17;
	}
	else if (this->ObjectTag == CGameObject::crystalball)
	{
		left = x;
		top = y;
		right = x + 13;
		bottom = y + 15;
	}
	else if (this->ObjectTag == CGameObject::purplemoneybag
		|| this->ObjectTag == CGameObject::redmoneybag)
	{
		left = x;
		top = y;
		right = x + 13;
		bottom = y + 15;
	}
	//else if (this->ObjectTag == CGameObject::ObjectTypes::breakingrock)
	//{
	//	left = 0;
	//	top = 0;
	//	right = 0;
	//	bottom = 0;
	//}
	else //small heart
	{
		left = x;
		top = y;
		right = x + 12;
		bottom = y + 8;
	}
}

RECT CItem::GetBound()
{
	RECT rect;
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	rect.left = l;
	rect.top = t;
	rect.right = r;
	rect.bottom = b;

	return rect;
}

