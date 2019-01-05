#pragma once
#include "Enemy.h"

class CBat:public CEnemy
{
public:
	CBat();
	CBat(D3DXVECTOR2 pos);
	~CBat();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render(Camera* camera);

	RECT GetBound();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	float FirstY;
};

