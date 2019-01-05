 #include "Brick.h"

CBrick::CBrick()
{
}

CBrick::CBrick(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CBrick::Render(Camera* camera)
{
	if (this->isDeleted)
		return;

	if (this->ObjectTag == CGameObject::ObjectTypes::door2ani)
	{
		if (this->animations[0]->GetCurrentFrame() == 3)
		{
			isStop = true;
		}
		
		if(isStop == false)
			animations[0]->Render(camera->transform(x, y));
		else 
			animations[1]->Render(camera->transform(x, y));
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::brickchicken)
	{
		animations[0]->Render(camera->transform(x, y));
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::brickmoney)
	{
		animations[0]->Render(camera->transform(x, y));
	}

	RenderBoundingBox(camera);
}

void CBrick::Update(DWORD dt)
{

}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (this->ObjectTag == CGameObject::ObjectTypes::door)
	{
		l = x;
		t = y;
		r = x + 15; 
		b = y + 50;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::door2 || this->ObjectTag == CGameObject::ObjectTypes::door3)
	{
		l = x;
		t = y;
		r = x + 6;
		b = y + 40;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::door2ani)
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::brickblockstage2)
	{
		l = x;
		t = y;
		r = x + 15;
		b = y + 200;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::brickchicken)
	{
		l = x;
		t = y;
		r = x + 14;
		b = y + 31;
		
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::blackbrickchicken)
	{
		if (isDeleted == false)
		{
			l = x;
			t = y;
			r = x + 16;
			b = y + 31;
		}
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::doortowater)
	{
		l = x;
		t = y;
		r = x + 14;
		b = y + 15;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::doorfromwater)
	{
		l = x;
		t = y;
		r = x + 14;
		b = y + 20;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::bottomstair)
	{
		l = x;
		t = y;
		r = x + 14;
		b = y + 15;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::blackbrickmoney)
	{
		if (isDeleted == false)
		{
			l = x;
			t = y;
			r = x + 14;
			b = y + 15;
		}
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::brickmoney)
	{	
		l = x;
		t = y;
		r = x + 14;
		b = y + 15;		
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::topstair)
	{
		l = x;
		t = y;
		r = x + 9;
		b = y + 15;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::floatingbrick1)
	{
		l = x;
		t = y;
		r = x + 48;
		b = y + 15;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::floatingbrick2)
	{
		l = x;
		t = y;
		r = x + 160;
		b = y + 15;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::floatingbrick3)
	{
		l = x;
		t = y;
		r = x + 81;
		b = y + 15;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::floatingbrick4)
	{
		l = x;
		t = y;
		r = x + 270;
		b = y + 15;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::floatingbrick5)
	{
		l = x;
		t = y;
		r = x + 30;
		b = y + 15;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::floatingbrick6)
	{
		l = x;
		t = y;
		r = x + 224;
		b = y + 15;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::floatingbrick7)
	{
		l = x;
		t = y;
		r = x + 160;
		b = y + 15;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::floatingbrick8)
	{
		l = x;
		t = y;
		r = x + 208;
		b = y + 15;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::floatingbrick9)
	{
		l = x;
		t = y;
		r = x + 47;
		b = y + 62;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::floatingbrick10)
	{
		l = x;
		t = y;
		r = x + 62;
		b = y + 40;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::floatingbrick11)
	{
		l = x;
		t = y;
		r = x + 178;
		b = y + 15;
	}
	else if (this->ObjectTag == CGameObject::ObjectTypes::brickscene2)
	{
		l = x;
		t = y+2;
		r = x + 2908; //2908 la width cua map 2
		b = y + BRICK_BBOX_HEIGHT;
	}
	else 
	{
		l = x;
		t = y;
		r = x + 770; //770 la width cua map 1
		b = y + BRICK_BBOX_HEIGHT;
	}

}

RECT CBrick::GetBound()
{
	return CGameObject::GetBound();
}

