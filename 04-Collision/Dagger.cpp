#include "Dagger.h"



CDagger::CDagger()
{

}

CDagger::CDagger(D3DXVECTOR2 pos)
{
	firstPos = pos;
}

CDagger::~CDagger()
{
}

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{	
	if (isDeleted)
	{		
		return;
	}

	CGameObject::Update(dt);

	x += dx;
	//y += dy;

	if (isFlip)
		this->vx = 0.2f;
	else
		this->vx = -0.2f;

	//if (abs(this->x - firstPos.x) >= 20)
	//	vy = -0.2f;
	//if (abs(this->x - firstPos.x) >= 60)
	//	vy = 0.2f;
}


void CDagger::Render(Camera * camera)
{ 		
	if (isDeleted)
		return;

	if (x - camera->GetPosition().x <= 10 || x - camera->GetPosition().x >= 290)
	{
		isDeleted = true;
	}

	animations[0]->Render(camera->transform(x, y));
	RenderBoundingBox(camera);
}

void CDagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x-1;
	top = y;
	right = x + 14;
	bottom = y + 8;
}

RECT CDagger::GetBound()
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
