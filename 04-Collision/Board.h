#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "Textures.h"
#include "Sprites.h"
#include "GameObject.h"
#include "Camera.h"
#include "Simon.h"
#include "Text.h"
#include "Boss.h"


class Board:public CGameObject
{
public: 
	Board(CSimon *simon);
	~Board();

	void Update(DWORD dt);
	void Render(Camera* camera);

	void SetTimer(int timer);
	int GetTimeAlive();

	void SetBossPointer(CBoss *boss);
	void SetStage(int stage);

	bool isDecreaseTimer;

protected:
	int _stage;

	CSimon *mSimon;
	CBoss *mBoss;

	Text txt_numHeart;
	Text txt_numLife;
	Text txt_numStage;
	Text txt_timeAlive;
	Text txt_zero;
	Text txt_score;

	DWORD countTimer = 0;
	DWORD translateTimer = 0; //biến này để tính khoảng thgian dừng giữa 2 lần tính điểm khi boss chết
	int TimeAlive = 300;
};

