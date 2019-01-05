#pragma once
#include "GameObject.h"
#include "Simon.h"
#define Item_APPEAR 1000

class CItem:public CGameObject
{
public:
	CItem(CSimon *Simon);
	CItem();
	CItem(D3DXVECTOR2 pos);

	~CItem();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render(Camera *camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	RECT GetBound();

	float firstX;
	bool isOnGround = false;
	CSimon *mSimon = new CSimon();

	DWORD timer = 0;
	DWORD timerChicken = 0;
};

