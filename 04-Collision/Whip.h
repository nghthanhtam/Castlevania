#pragma once
#include "Weapon.h"
 

class CWhip : public CWeapon
{
public:
	CWhip();
	~CWhip();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects=NULL);
	void Render(Camera *camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	RECT GetBound();


	void SetWhipType(int type);
	bool isWhipType(int type);



protected:
	int WhipType = 0;
};

