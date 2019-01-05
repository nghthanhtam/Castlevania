#include "Whip.h"
#include "Simon.h"


CWhip::CWhip()
{
}

CWhip::~CWhip()
{
}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	if (this->IsDelete()==true)
		return;
	CGameObject::Update(dt);
}

void CWhip::Render(Camera *camera)
{
	if (this->IsDelete())
		return;
	//animations[0]->Render(x, y);
	RenderBoundingBox(camera);

}

void CWhip::SetWhipType(int type)
{
	WhipType = type;
}

bool CWhip::isWhipType(int type)
{
	if (WhipType == type)
		return true;
	else 
		return false;
}

void CWhip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (WhipType == 2)
	{
		left = x-16;
		top = y+6;
		right = x + 26;
		bottom = y+10;
	}
	else {
		left = x;
		top = y;
		right = x + 21;
		bottom = y + 6;
	}
}

RECT CWhip::GetBound()
{
	return CGameObject::GetBound();
}






