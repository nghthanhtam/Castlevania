#include "Sprites.h"
#include "Game.h"
#include "debug.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

int CSprite::GetId()
{
	return id;
}


CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha, int isFlip)
{
	CGame * game = CGame::GetInstance();
	if (isFlip == -1)
		game->Draw(x, y, texture, left, top, right, bottom, alpha);
	else
		game->DrawFlipX(x, y, texture, left, top, right, bottom, alpha);

}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}


CAnimation::CAnimation()
{
}

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t=this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, int alpha, int isFlip)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1) 
	{
		currentFrame = 0; 
		lastFrameTime = now;
	}
	else
	{		
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size())
			{
				currentFrame = 0;
			}
		}
		
	}
	 


	/*for (int i = 0; i < listID.size(); i++)
	{
		if (frames[currentFrame]->GetSprite()->GetId() == listID.at(i))
		{
			frames[currentFrame]->GetSprite()->Draw(x + offset_x[listID.at(i)], y + offset_y[listID.at(i)], alpha, isFlip);
			return;
		}
	}*/


	float xx = x, yy = y;
	int idSprite = frames[currentFrame]->GetSprite()->GetId();
	if (offset_x.find(idSprite) != offset_x.end())
	{
		xx += offset_x[idSprite];
		yy += offset_y[idSprite];
	}

	frames[currentFrame]->GetSprite()->Draw(xx, yy, alpha, isFlip);

//#pragma region Sprite Adjust
//	if (frames[currentFrame]->GetSprite()->GetId() == 10017)	
//		frames[currentFrame]->GetSprite()->Draw(x-28, y+1, alpha, isFlip);
//		
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10024)	
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y , alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10025)	
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10031)	
//		frames[currentFrame]->GetSprite()->Draw(x-28,y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10034)	
//		frames[currentFrame]->GetSprite()->Draw(x - 5, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10035)	
//		frames[currentFrame]->GetSprite()->Draw(x-16, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10036)	
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10038)	
//		frames[currentFrame]->GetSprite()->Draw(x - 8, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10043)
//		frames[currentFrame]->GetSprite()->Draw(x - 28, y+1, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10044)	
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10045)
//	
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10051)	
//		frames[currentFrame]->GetSprite()->Draw(x - 44, y+1, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10052)	
//		frames[currentFrame]->GetSprite()->Draw(x - 44, y+1, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10053)	
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10054)	
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10055)
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10056)	
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10102)	
//		frames[currentFrame]->GetSprite()->Draw(x - 28, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10103)	
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10104)	
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10110)	
//		frames[currentFrame]->GetSprite()->Draw(x - 43, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10111)	
//		frames[currentFrame]->GetSprite()->Draw(x - 43, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10112)
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10113)	
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10114)	
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10115)	
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 50013)	
//		frames[currentFrame]->GetSprite()->Draw(x -5, y-5, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 50014)		
//		frames[currentFrame]->GetSprite()->Draw(x - 10, y - 5, alpha, isFlip);
//		
//	else if (frames[currentFrame]->GetSprite()->GetId() == 50015)	
//		frames[currentFrame]->GetSprite()->Draw(x - 15, y - 5, alpha, isFlip);
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 30017)		
//		frames[currentFrame]->GetSprite()->Draw(x +5, y, alpha, isFlip);
//	
//	else if(frames[currentFrame]->GetSprite()->GetId()== 10206)
//		frames[currentFrame]->GetSprite()->Draw(x -17, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10207)
//		frames[currentFrame]->GetSprite()->Draw(x - 17, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10208)
//		frames[currentFrame]->GetSprite()->Draw(x - 17, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10209)
//		frames[currentFrame]->GetSprite()->Draw(x - 17, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10210)
//		frames[currentFrame]->GetSprite()->Draw(x - 1, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10211)
//		frames[currentFrame]->GetSprite()->Draw(x - 1, y, alpha, isFlip);	 
//	
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10097)
//		frames[currentFrame]->GetSprite()->Draw(x - 44, y+1, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10199)
//		frames[currentFrame]->GetSprite()->Draw(x - 44, y+1, alpha, isFlip);	
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10216)
//		frames[currentFrame]->GetSprite()->Draw(x - 44, y+1, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10217)
//		frames[currentFrame]->GetSprite()->Draw(x - 44, y+1, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10200)
//	frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10201)
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10202)
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10203)
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10072)
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10073)
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip); 
//		
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10080)
//		frames[currentFrame]->GetSprite()->Draw(x - 28, y+1, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10075)
//		frames[currentFrame]->GetSprite()->Draw(x - 17, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10076)
//		frames[currentFrame]->GetSprite()->Draw(x - 17, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10077)
//		frames[currentFrame]->GetSprite()->Draw(x - 1, y, alpha, isFlip); 
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10071)
//		frames[currentFrame]->GetSprite()->Draw(x - 28, y, alpha, isFlip); 
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10227)
//		frames[currentFrame]->GetSprite()->Draw(x - 8, y, alpha, isFlip); 
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10226)
//		frames[currentFrame]->GetSprite()->Draw(x - 7, y, alpha, isFlip); 
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10221)
//		frames[currentFrame]->GetSprite()->Draw(x - 9, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10220)
//		frames[currentFrame]->GetSprite()->Draw(x - 7, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10232)
//		frames[currentFrame]->GetSprite()->Draw(x - 5, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10233)
//		frames[currentFrame]->GetSprite()->Draw(x - 8, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10234)
//		frames[currentFrame]->GetSprite()->Draw(x - 1, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10092)
//		frames[currentFrame]->GetSprite()->Draw(x - 28, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10084)
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//
//	else if (frames[currentFrame]->GetSprite()->GetId() == 10085)
//		frames[currentFrame]->GetSprite()->Draw(x - 16, y, alpha, isFlip);
//
//#pragma endregion
//	
//	else frames[currentFrame]->GetSprite()->Draw(x, y, alpha, isFlip);
}

void CAnimation::Render(D3DXVECTOR2 pos, int alpha, int isFlip)
{
	Render(pos.x, pos.y, alpha, isFlip);
}

int CAnimation::GetCurrentFrame()
{
	return currentFrame;
}

void CAnimation::SetCurrentFrame(int f)
{
	currentFrame = f;
}

CAnimation * CAnimation::__instance = NULL;
CAnimation * CAnimation::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimation();
	return __instance;
}

void CAnimation::ReadFileid(const char * path)
{

	int idSprite;
	float Foffset_x, Foffset_y;
	FILE* pFile;
	pFile = fopen(path, "r");

	while (!feof(pFile))
	{
		fscanf(pFile, "%d %f %f", &idSprite, &Foffset_x, &Foffset_y);

		listID.push_back(idSprite);
		offset_x[idSprite] = Foffset_x;
		offset_y[idSprite] = Foffset_y;

	}

	fclose(pFile);

}



CAnimations * CAnimations::__instance = NULL;
CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}


