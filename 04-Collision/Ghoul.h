#pragma once
#include "Enemy.h"

class CGhoul:public CEnemy
{
public:
	CGhoul();
	~CGhoul();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render(Camera* camera);

	RECT GetBound();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	
};

