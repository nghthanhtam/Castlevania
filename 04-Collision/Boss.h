#pragma once
#include "Enemy.h"
#include "Simon.h"



class CBoss:public CEnemy
{
public:
	CBoss();
	CBoss(CSimon *simon);
	~CBoss();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render(Camera* camera);

	RECT GetBound();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	bool isDead;

protected:
	CSimon *mSimon;
	int ani;

	DWORD timerFlyUp = 0;
	DWORD timerAim = 0;
	DWORD timerAttack = 0;
	bool isAttack;
	bool isHitSimon;
	bool isAtBottom;

};

