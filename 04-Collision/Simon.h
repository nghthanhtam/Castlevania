#pragma once
#include "GameObject.h"
#include "Whip.h"
#include "Weapon.h"
#include "Dagger.h"
#include "HolyWater.h"
#include "Camera.h"
#include "Axe.h"
#include "Sound.h"


class CSimon : public CGameObject
{
	int untouchable;//
	DWORD untouchable_start;//

public: 
	CSimon() : CGameObject()
	{
		numLife = 3;
		numHP = 16;
		numHeart = 5;
		weaponType = 0;

		untouchable = 0;
		pWhip = new CWhip();
		pWhip->SetDelete(true);

		pWeapon = new CWeapon();
		pWeapon->SetDelete(true);

	}

	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects);
	void Render(Camera *camera);
	void SetState(int state);
	
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }//

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	RECT GetBound();
	void CheckCollisionOnStair(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects);
	void CheckCollisionWithGround(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects);

	vector<CWeapon*> listWeapon;
	CWhip *pWhip;
	CWeapon* pWeapon;
	Camera* camera;

	bool isJumping = false;
	bool isSitThrow = false; //chỉ dùng để quản lý animation ngồi đánh 
	bool isSitAttack = false;
	bool isAttack = false;
	bool isThrow = false;
	bool isUseStopWatch = false;
	bool isHitDoor = false;
	bool isHitEnemy = false;
	bool isUntouchable = false;
	bool isBreakRock;
	bool isBreakRockChicken;
	bool isInvisible;
	bool isRevive;
	bool isEatingItem;
	bool isLand = false;

	int check;
	bool isThrowDouble = false;
	bool isDamageBoss = true;
	int count;

	int StairDirection;
	bool isWalkingToStair; //biến dùng để xác định lúc đang đi bộ đến vị trí lên cầu thang thì đi chậm
	bool isOnStair = false;
	bool isStopOnStair = false;
	bool isHitTopStair = false;
	bool isHitBottomStair = false;
	bool isUpstair = false;

	bool isHitTop = false; //biến này dùng để ko cho Simon ngồi xuống khi ấn phím xuống cầu thang
	bool isHitLeft = false;

	float firstY;

	DWORD timerHitEnemy = 0;
	DWORD timerDie = 0;
	DWORD timerChangeColor = 0;
	DWORD timerLand = 0;


	//BOARD
	int weaponType;

	int numHeart;
	int GetNumHeart();
	void SetNumHeart(int heart);

	int numLife;
	int GetNumLife();
	void SetNumLife(int life);

	int numHP;
	int GetNumHP();
	void SetNumHP(int hp);

	int score;
	int GetScore();
	void SetScore(int score);

};