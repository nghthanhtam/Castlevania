#include "Candle.h"



CCandle::CCandle()
{
}

CCandle::CCandle(float _x, float _y)
{
	x = _x;
	y = _y;
}

CCandle::~CCandle()
{
}


void CCandle::Update(DWORD dt)
{
}

void CCandle::Render(Camera * camera)
{
	animations[0]->Render(camera->transform(x, y));
	RenderBoundingBox(camera);
}

void CCandle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 9;
	bottom = y+14;
}

RECT CCandle::GetBound()
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

