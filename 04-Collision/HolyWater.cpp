#include "HolyWater.h"




CHolyWater::CHolyWater()
{
}

CHolyWater::CHolyWater(D3DXVECTOR2 pos, bool flag)
{
	firstPos = pos;
}

CHolyWater::~CHolyWater()
{
}

void CHolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (this->y >= 480) //TH nếu ném holy water xuống nước ở màn dưới (stage 2)
		isDeleted = true;

	if (isDeleted)
	{
		return;
	}
	CGameObject::Update(dt, colliable_objects);



	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (isDeleted == false)
	{
		CalcPotentialCollisions(colliable_objects, coEvents);
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx; 
		y += dy;

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		//block 	
		x += min_tx * dx;
		y += min_ty * dy + ny * 0.2f;

		/*if (nx != 0)
			vx = 0;*/
		
		if (ny == -1) 
		{ 
			CSound::getInstance()->play("holywater", false, 1);
			isOnGround = true; 
			vy = 0; 
			vx = 0;
		}

	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (isOnGround == false)
	{
		if (abs(x - this->firstPos.x) <= 25) //bay lên  //Nếu muốn ném xa/gần trc khi rơi xuống thì chỉnh số này
		{

			if (nx == 1)
			{
				vx = 0.1f;

			}
			else
			{
				vx = -0.1f;
			}
			vy = -0.02f;  //bay cao thì tăng vy

		}
		else //rơi xuống
		{

			if (nx == 1)
			{
				vx = 0.08f;
			}
			else
			{
				vx = -0.08f;
			}
			vy = 0.14f;
		}
		this->SetPosition(x, y);
	}


}

void CHolyWater::Render(Camera * camera)
{
	if (isOnGround)
	{
		if (timer < 700)
			timer += dt;
		else
		{
			isDeleted = true;
			return;
		}
	}

	if (isOnGround)
		animations[1]->Render(camera->transform(x, y));
	else
		animations[0]->Render(camera->transform(x, y));


	RenderBoundingBox(camera);
}

void CHolyWater::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (isOnGround)
	{
		left = x;
		top = y;
		right = x + 14;
		bottom = y + 15;
	}
	else
	{
		left = x;
		top = y;
		right = x + 6;
		bottom = y + 9;
	}
}

RECT CHolyWater::GetBound()
{
	return CGameObject::GetBound();
}


//void CHolyWater::GetSimonPos(float x, float y)
//{
//	Simon_x = x;
//	Simon_y = y;
//}

//bool CHolyWater::IsOnGround()
//{
//	return isOnGround;
//}


