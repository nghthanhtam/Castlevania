#pragma once
#include "Weapon.h"

class CDagger:public CWeapon
{
public:
	CDagger();
	CDagger(D3DXVECTOR2 pos);
	~CDagger();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects);
	void Render(Camera *camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	RECT GetBound();

	D3DXVECTOR2 firstPos;

};

