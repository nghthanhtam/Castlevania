#pragma once
#include "GameObject.h"

class CWeapon:public CGameObject
{
public: 
	CWeapon();
	~CWeapon();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects=NULL);
	virtual void Render(Camera *camera);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual RECT GetBound();
	
	//virtual bool IsDelete();
	//virtual void SetDelete(bool flag);

	virtual bool IsOnGround();

	virtual void SetFlip(bool flag);
	//virtual void GetSimonPos(float x, float y);

protected:
	DWORD timer = 0;
	bool isFlip;
};

