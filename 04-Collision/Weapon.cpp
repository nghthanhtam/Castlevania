#include "Weapon.h"

CWeapon::CWeapon()
{
	isDeleted = true;
}

CWeapon::~CWeapon()
{
}

void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

void CWeapon::Render(Camera * camera)
{
}

void CWeapon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

}

RECT CWeapon::GetBound()
{
	return RECT();
}

//bool CWeapon::IsDelete()
//{
//	return this->isDeleted;
//}
//
//void CWeapon::SetDelete(bool flag)
//{
//	this->isDeleted = flag;
//}


bool CWeapon::IsOnGround()
{
	return this->isOnGround;
}

void CWeapon::SetFlip(bool flag)
{
	isFlip = flag;
}

//void CWeapon::GetSimonPos(float x, float y)
//{
//}
