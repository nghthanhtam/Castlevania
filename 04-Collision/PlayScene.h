#pragma once
#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "debug.h"
#include "Game.h"
#include "Grid.h"

#include "Scene.h"
#include "GameObject.h"
#include "Textures.h"
#include "Sprites.h"

#include "Simon.h"
#include "Brick.h"
#include "Whip.h"
#include "Candle.h"
#include "Torch.h"
#include "Item.h"
#include "Camera.h"
#include "GameMap.h"
#include "Board.h"

#include "Ghoul.h"
#include "Panther.h"
#include "Bat.h"
#include "Fishmen.h"
#include "Boss.h"
#include "Effect.h"
#include "FireBall.h"


class PlayScene:public Scene
{
public:
	PlayScene();
	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void LoadResources();
	void Update(DWORD dt);
	void Render();

	void CheckCollision_SimonAndEnemy();
	void CheckCollision_WeaponAndEnemy();
	void CheckCollision_WhipAndEnemy();
	void CheckCollision_ItemAndSimon();

	void ProcessAfterBossDeath();


	~PlayScene();

	CAnimations * animations;
	CSprites *sprites;
	LPANIMATION ani;

	LPDIRECT3DTEXTURE9 texSimon;
	LPDIRECT3DTEXTURE9 texEnemy;
	LPDIRECT3DTEXTURE9 texObject;
	LPDIRECT3DTEXTURE9 texItem;
	LPDIRECT3DTEXTURE9 texBoard;

	void ReadSprites(const char* path);
	void ReadAnimation(const char* path);
	void ReadObjects(const char* path);

	CSimon *Simon;
	CItem* item;
	Camera* camera;
	GameMap* gameMap;
	CGame *game;
	CTorch *torch;
	CGhoul* ghoul;
	CPanther *panther;
	Board *board;
	CBrick *brick;
	CBat *bat;
	CEffect *breakingRock;
	CFishmen *fishmen;
	CBoss *boss;
	Grid* grid;
	CFireBall *fireball;



	bool isInNewScene = false;
	bool isMoveScene;
	bool isMoveCamera;

	bool isCreateGhoul = true;
	bool isCreatePanther = true;
	bool isCreateBat = true;
	bool isCreateFishmen = true;
	bool isCreateBoss = true;
	bool isProcessedAfterBossDeath = false; //biến này dùng để khi trừ time để tính điểm thì Simon ko chết
	bool isFreeze;
	bool isChangeColor;
	bool isGrey;
	bool isKillEnemyOnScreen = false;

	int NumGhoulAlive = 0;
	int NumPantherAlive = 0;
	int NumBatAlive = 0;
	int NumFishmenAlive = 0;

	DWORD timerGhoul = 0;
	DWORD timerBat = 0;
	DWORD timerUntouachable = 0;
	DWORD timerInvisible = 0;
	DWORD timerFishmen = 0;
	DWORD timerAppearCrystalBall = 0;
	DWORD startTimeFreeze;
	DWORD timerChangeColor;
	

	int count;
	float t;
	int stage;
	int stageStartPoint;
	int countChangeColor;
	int scene;

	vector<LPGAMEOBJECT> listBrick;
	vector<LPGAMEOBJECT> listItem;
	vector<LPGAMEOBJECT> listEnemy;
	vector<LPGAMEOBJECT> listCandle;
	vector<LPGAMEOBJECT> listStair;
	vector<LPGAMEOBJECT> listDoor;
	vector<LPGAMEOBJECT> listEffect;
	vector<LPGAMEOBJECT> listColObjects;
};

