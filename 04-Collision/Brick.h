#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject
{
public:
	CBrick();
	CBrick(float x, float y);

	virtual void Render(Camera* camera);
	virtual void Update(DWORD dt);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	RECT GetBound();


	bool isStop;
};