#pragma once
#include "GameObject.h"
#include "Simon.h"

class CEnemy:public CGameObject
{
public:
	CEnemy();
	~CEnemy();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Camera* camera);

	virtual RECT GetBound();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	//virtual int GetHP();
	//virtual void SetHP(int hp);

	bool IsDelete();
	void SetDelete(bool flag);
	bool IsOutOfCamera(Camera* camera);
	virtual void SetFlip(bool flag);

protected:
	bool isFlip;
};

