#include "Boss.h"



CBoss::CBoss()
{
}

CBoss::CBoss(CSimon * simon)
{
	this->HP = 16;
	mSimon = simon;

	this->AddAnimation(821);
	this->AddAnimation(822);
}


CBoss::~CBoss()
{
}

void CBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	x += dx;
	y += dy;

	CGameObject::SetState(state);

	if (mSimon->GetPosition().x > x && state == 0) //khi Simon đi gần dơi đang ngủ, nó thức dậy và tấn công
	{
		state = FLY_AFTER_SLEEP; 
	}

	//Nếu boss đụng biên thì bay ngược lại
	if (x <= 2505) 
		vx = -vx;
	if (x >= 2800)
		vx = -vx;
	if (y <= 30)
		vy = 0.03f;

	switch (state)
	{
	case FLY_AFTER_SLEEP: 
		if (y <= 105) //bay xuống 1 khoảng sau khi ngủ, trc khi attack
		{
			vx = 0.02f;
			vy = 0.03f;
		}
		else
		{
			vx = 0;
			vy = 0;
			state = 20;
		}
		break;

	case ATTACK:  //attack
		if (timerAttack < 3000)
		{
			timerAttack += dt;
		}
		else
		{
			timerAttack = 0;
			isAttack = true;
		}

		if ((abs(x - mSimon->GetPosition().x) >= 70 && isHitSimon == false) || isAttack==true) //khi Simon cách boss 1 khoảng nào đó thì boss mới attack
		{
			if (mSimon->GetPosition().x < x)
			{
				vx = -0.08f;
				vy = 0.078f;
				isHitSimon = true;
			}
			else
			{
				vx = 0.08f;
				vy = 0.078f;
				isHitSimon = true;
			}
			isAttack = false;
		}

		if (abs(y - mSimon->GetPosition().y) <= 5) //khi boss xuống gần Simon
		{
			vy = 0; //ko cho boss xuống nữa
			if (abs(mSimon->GetPosition().x - x) >= 5)
			{							
				vy = -0.038f;
				state = FLY_AFTER_ATTACK;
			}
		}
		if (y - mSimon->GetPosition().y >= 60) //dành cho TH Simon nhảy qua đầu dơi thì dơi ko bay xuống hoài
		{
			vy = -0.038f;
			state = FLY_AFTER_ATTACK;
		}

		break;

	case FLY_AFTER_ATTACK: //bay lên tự do
		if (timerFlyUp < 1200)
			timerFlyUp += dt;
		else
		{
			timerFlyUp = 0;
			state = FLY_TO_THE_MIDDLE;
		}
		break;

	case FLY_TO_THE_MIDDLE: 
		if (x != 2655)  //2505 cạnh trái màn hình
		{
			if (x < 2650)
			{
				vx = 0.07f;
				vy = -0.01f;
			}
			else
			{
				vx = -0.07f;
				vy = -0.01f;
			}
		}
		if (x >= 2650 - 20 && x < 2650 + 10) //khi vào đúng vị trí trong khoảng lý tưởng thì set qua state aim liền 
		{
			vx = 0;
			vy = 0;
			state = 50;
		}
		break;

	case AIM: 
		if (this->y <= 120)  //cho boss bay xuống khi đang aim
			vy = 0.02f;
		else 
			vy = 0;

		if (abs(x - mSimon->GetPosition().x) > 60)
		{
			if(mSimon->GetPosition().x < x)
				vx = -0.055f;
		}
		else
		{
			vx = 0;
		}

		isHitSimon = false;
		if (timerAim < 2000)
		{
			timerAim += dt;
		}
		else
		{
			state = ATTACK;
			timerAim = 0;
		}
		break;
	}
}

void CBoss::Render(Camera * camera)
{
	if (isDeleted)
		return;


	if (state == FLY_AFTER_SLEEP)
	{
		ani = 1;
	}

	animations[ani]->Render(camera->transform(x, y));
	RenderBoundingBox(camera);
}

RECT CBoss::GetBound()
{
	return CGameObject::GetBound();
}

void CBoss::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 42;
	bottom = y + 20;
}

