#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <fstream>
#include <math.h>

#include "Game.h"
#include "Sprites.h"
#include "Camera.h"
#include "define.h"

using namespace std;

#define ID_TEX_BBOX -100	

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
public:

	enum ObjectTypes
	{
		None,
		torch,
		candle,
		brick,
		brickscene2,
		largeheart,
		smallheart,
		purplemoneybag,
		redmoneybag,
		holywater,
		whipupgrade,
		stopwatch,
		dagger,
		axe,
		cross,
		chicken,
		whitemoneybag,
		doubleshot,
		potion,
		door,
		door2,
		door3,
		doorfromwater,
		doortowater,
		door2ani,
		floatingbrick1,
		floatingbrick2,
		floatingbrick3,
		floatingbrick4,
		floatingbrick5,
		floatingbrick6,
		floatingbrick7,
		floatingbrick8,
		floatingbrick9,
		floatingbrick10,
		floatingbrick11,
		brickblockstage2,
		blackbrickchicken,
		blackbrickmoney,
		brickchicken,
		brickmoney,
		breakingrock,
		bottomstair,
		topstair,
		ghoul,
		bat,
		panther,
		fishmen,
		fireball,
		boss,
		effectbossdie,
		crystalball
		
	};
	ObjectTypes ObjectTag;

	enum ItemInside
	{
		iNone,
		iHeart,
		iSmallHeart,
		iDagger,
		iWhipUpgrade,
		iStopWatch,
		iHolyWater,
		iCross,
		iChicken,
		iMoney,
		iAxe,
		iDoubleShot,
		iPotion,
		iPurpleMoneyBag,
		iRedMoneyBag,
		iCrystalBall
	};
	ItemInside itemInside;

	enum StairTypes
	{
		Null,
		ToLeft,
		ToRight
	};
	StairTypes StairTag;

	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;	 

	int state;

	DWORD dt; 

	vector<LPANIMATION> animations;

public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetPosition(D3DXVECTOR2 pos) { SetPosition(pos.x, pos.y); }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	D3DXVECTOR2 GetPosition() { return D3DXVECTOR2(x, y); }

	
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	int GetState() { return this->state; }

	void RenderBoundingBox(Camera *camera);

	bool CheckCollision(CGameObject *object);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);

	void AddAnimation(int aniId);

	CGameObject();

	virtual RECT GetBound();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera* camera) = 0;
	virtual void SetState(int state) { this->state = state; }


	//object state
	virtual bool IsDelete();
	virtual void SetDelete(bool flag);

	virtual bool IsFreeze();
	virtual void SetFreeze(bool flag);

	virtual void SetStop(bool flag);

	virtual int GetHP();
	virtual void SetHP(int hp);
	//virtual void GetSimonPos(float x, float y);

	virtual bool IsOutOfCamera();
	virtual void SetIsOutOfCamera(bool flag);

	virtual bool IsOnGround();
	virtual void SetOnGround(bool flag);
	bool isOnGround = false;

	bool isCreateFireBall = false;

	int isTakeForCollision = 0;

	~CGameObject();

protected:
	bool isFreezed;
	bool isDeleted = false;
	bool isOutOfCamera;
	bool isStop;
	int HP;
};

