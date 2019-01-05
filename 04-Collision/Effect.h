#pragma once
#include "GameObject.h"

class CEffect:public CGameObject
{
public:
	CEffect();
	~CEffect();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera *camera);

	DWORD timer;
};

