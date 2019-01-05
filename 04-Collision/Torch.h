#pragma once
#include "GameObject.h"

class CTorch :public CGameObject
{
public:
	CTorch();
	CTorch(float x, float y);
	~CTorch();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects);
	void Render(Camera *camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	RECT GetBound();
	bool IsDelete;
};

