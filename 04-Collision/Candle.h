#pragma once
#include "GameObject.h"

class CCandle:public CGameObject
{
public:
	CCandle();
	CCandle(float _x, float _y);
	~CCandle();

	void Update(DWORD dt);
	void Render(Camera* camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	RECT GetBound();
	bool IsDelete;

};

