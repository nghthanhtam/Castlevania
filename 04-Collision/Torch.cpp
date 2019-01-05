#include "Torch.h"


CTorch::CTorch()
{
}

CTorch::CTorch(float x, float y)
{
	this->x = x;
	this->y = y;
}

CTorch::~CTorch()
{
}

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
}

void CTorch::Render(Camera *camera)
{
	
	animations[0]->Render(camera->transform(x, y));
	RenderBoundingBox(camera);
	
}

void CTorch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 32;
}

RECT CTorch::GetBound()
{
	return CGameObject::GetBound();

	//RECT r;

	//r.left = x;
	//r.top = y;
	//r.right = x + 16;
	//r.bottom = y + 32;

	//return r;
}
