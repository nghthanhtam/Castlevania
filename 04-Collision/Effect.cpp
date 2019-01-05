#include "Effect.h"


CEffect::CEffect()
{
}

CEffect::~CEffect()
{
}

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (isDeleted)
	{
		return;
	}

	if (this->ObjectTag == CGameObject::ObjectTypes::effectbossdie) 
	{
		if (timer < 2000)
			timer += dt;
		else
		{
			timer = 0;
			isDeleted = true;
		}
	}
	else
	{
		if (timer < 250)
			timer += dt;
		else
		{
			timer = 0;
			isDeleted = true;
		}
	}
}

void CEffect::Render(Camera * camera)
{
	if (this->isDeleted)
	{
		return;
	}

	animations[0]->Render(camera->transform(x, y));

	RenderBoundingBox(camera);
}

