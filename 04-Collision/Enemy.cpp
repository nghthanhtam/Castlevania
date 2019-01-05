#include "Enemy.h"


CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDeleted)
	{
		return;
	}
}

void CEnemy::Render(Camera * camera)
{
	if (isDeleted)
	{
		return;
	}

	if (isFlip) //di tu trai sang phai
	{
		if (x - camera->GetPosition().x >= 350) //di het man hinh ben phai thi bien mat
		{
			isDeleted = true;
			isOutOfCamera = true;
			return;
		}
		else if(x - camera->GetPosition().x <= -50) //di het man hinh ben trai thi bien mat		
		{
			isDeleted = true;
			isOutOfCamera = true;
			return;
		}
	}
	else if(isFlip == false)
	{
		if (x - camera->GetPosition().x <= -10)
		{
			isDeleted = true;
			isOutOfCamera = true;
			return;
		}
		else if (x - camera->GetPosition().x >= 400) //di het man hinh ben phai thi bien mat
		{
			isDeleted = true;
			isOutOfCamera = true;
			return;
		}
	}
}

RECT CEnemy::GetBound()
{
	return RECT();
}

void CEnemy::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

//int CEnemy::GetHP()
//{
//	return 0;
//}
//
//void CEnemy::SetHP(int hp)
//{
//}

bool CEnemy::IsDelete()
{
	return this->isDeleted;
}

void CEnemy::SetDelete(bool flag)
{
	this->isDeleted = flag;
}

bool CEnemy::IsOutOfCamera(Camera * camera)
{
	return isOutOfCamera;
}

void CEnemy::SetFlip(bool flag)
{
	isFlip = flag;
}

