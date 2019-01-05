#pragma once
#include "Weapon.h"
#include "Simon.h"

class CAxe:public CWeapon
{
public:
	CAxe(D3DXVECTOR2 pos, bool flag);
	//CAxe(CSimon *simon, bool flag);
	CAxe();
	~CAxe();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects);
	void Render(Camera *camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	RECT GetBound();

	D3DXVECTOR2 firstPos;
};

