#include "Axe.h"




CAxe::CAxe(D3DXVECTOR2 pos, bool flag)
{
	firstPos = pos;
	isFlip = flag;
}


CAxe::CAxe()
{
}

CAxe::~CAxe()
{
}

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (isDeleted)
	{
		return;
	}

	CGameObject::Update(dt);
	 
	vy += 0.0005f*dt; //gravity
	y += dy;
	x += dx;

	if (abs(x - this->firstPos.x) <= 12 ) //bay lên  //Nếu muốn ném xa/gần trc khi rơi xuống thì chỉnh số này
	{
		if (isFlip == false)
		{				
			vx = 0.0093f*dt;			
		}
		else
			{				
				vx = -0.0093f*dt;		
			}
			//x += dx;
			vy = -0.15f;
	
	}
	else //rơi xuống
	{
		if (isFlip == false)
		{		
			vx = 0.009f*dt;
		}
		else 
		{
			vx = -0.009f*dt;
		}

		//x += dx;
		if (abs(x - this->firstPos.x) >= 70)  //quãng đg búa đi trc khi hạ xuống (để tạo vòng cung)
			vy = 0.3f;
			
	}

	this->SetPosition(x, y);
}

void CAxe::Render(Camera * camera)
{
	if (this->isDeleted)
		return;

	/*if (x - camera->GetPosition().x <= 5 || x - camera->GetPosition().x >= 290)
	{
		CSound::getInstance()->stop("axe");
		isDeleted = true;
	}*/

	if (this->y - camera->GetPosition().y > 195)
	{
		CSound::getInstance()->stop("axe");
		isDeleted = true;
	}

	animations[0]->Render(camera->transform(x, y));

	//RenderBoundingBox(camera);
}

void CAxe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 16;
	bottom = y + 15;
}

RECT CAxe::GetBound()
{
	return CGameObject::GetBound();
}
