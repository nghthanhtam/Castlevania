#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>


using namespace std;


class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left; 
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public: 
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	int GetId();
	void Draw(float x, float y, int alpha=255, int isFlip=-1);
};


typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);

	static CSprites * GetInstance();
};

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
protected:
	static CAnimation * __instance;
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
	int id;

public:
	CAnimation(int defaultTime) 
	{ 
		this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; 
		if (check == 0)
		{
			check = 1;
			ReadFileid("textures/readfile/IdSprite.txt");
		}
	}
	CAnimation();

	int check;

	vector <int> listID;

	unordered_map<int, float> offset_x;
	unordered_map<int, float> offset_y;

	int GetCurrentFrame();
	void SetCurrentFrame(int);
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, int alpha=255, int isFlip=-1);
	void Render(D3DXVECTOR2 pos, int alpha = 255, int isFlip = -1);
	static CAnimation * GetInstance();
	void ReadFileid(const char* path);
	
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static CAnimations * GetInstance();
};

