#pragma once
#include "Weapon.h"
#include "Sound.h"

class CHolyWater:public CWeapon
{
public:
	CHolyWater();
	CHolyWater(D3DXVECTOR2 pos, bool flag);
	~CHolyWater();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects);
	void Render(Camera *camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	RECT GetBound();

	D3DXVECTOR2 firstPos;
	float Simon_x, Simon_y, gravity;
	//void GetSimonPos(float x, float y);
	//bool IsOnGround();
};

