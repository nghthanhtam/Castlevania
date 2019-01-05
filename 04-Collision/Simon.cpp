#include <algorithm>
#include "debug.h"

#include "Brick.h"
#include "Simon.h"
#include "Game.h"
#include "Sprites.h"
#include "Torch.h"


void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (this->numHP == 0)
	{
		if (isHitEnemy == false)
		{
			SetState(Simon_STATE_DIE);
		}
	}
	else if (this->y >= 370)
	{
		isDeleted = true;
		SetState(Simon_STATE_DIE);
	}

	if (state == Simon_STATE_DIE)
	{
		vx = 0;
		if (timerDie < 2500)
			timerDie += dt;
		else
		{
			timerDie = 0;
			isRevive = true;
		}
	}

	if (this->isDeleted)
		return;


	if (isLand)
	{
		SetState(Simon_STATE_SIT);

		if (timerLand < 300)
			timerLand += dt;
		else
		{
			timerLand = 0;
			isLand = false;
			isJumping = false;
			SetState(Simon_STATE_IDLE);
		}
		
	}

	if (isThrowDouble==true && check==0)
	{
		isThrow = true;
		check = 1;
	}

	if (isEatingItem)
	{
		pWhip->SetDelete(true);
		if (timerChangeColor < 700)
			timerChangeColor += dt;
		else
		{
			isEatingItem = false;
			timerChangeColor = 0;
		}
	}

	

	if (GetState() == Simon_STATE_ATTACK)
	{
		vx = 0;
		if (isOnStair)
			vy = 0;

		int ani;

		if (nx < 0)
		{
			if (pWhip->isWhipType(0))
			{
				if (isOnStair == true && isUpstair == false)
					ani = Simon_ANI_DOWNSTAIR_ATTACK_TYPE1_LEFT;
				else if (isOnStair == true && isUpstair == true)
					ani = Simon_ANI_UPSTAIR_ATTACK_TYPE1_LEFT;
				else
					ani = Simon_ANI_ATTACK_LEFT;
			}
			else
				if (pWhip->isWhipType(1))
				{
					if (isOnStair == true && isUpstair == false)
						ani = Simon_ANI_DOWNSTAIR_ATTACK_TYPE2_LEFT;
					else if (isOnStair == true && isUpstair == true)
						ani = Simon_ANI_UPSTAIR_ATTACK_TYPE2_LEFT;
					else
						ani = Simon_ANI_ATTACK_TYPE2_LEFT;
				}
				else
					if (pWhip->isWhipType(2))
					{
						if (isOnStair == true && isUpstair == false)
							ani = Simon_ANI_DOWNSTAIR_ATTACK_TYPE3_LEFT;
						else if (isOnStair == true && isUpstair == true)
							ani = Simon_ANI_UPSTAIR_ATTACK_TYPE3_LEFT;
						else
							ani = Simon_ANI_ATTACK_TYPE3_LEFT;
					}
		}
		else
		{
			if (pWhip->isWhipType(0))
			{
				if (isOnStair == true && isUpstair == true)
					ani = Simon_ANI_UPSTAIR_ATTACK_TYPE1_RIGHT;
				else if (isOnStair == true && isUpstair == false)
					ani = Simon_ANI_DOWNSTAIR_ATTACK_TYPE1_RIGHT;
				else
					ani = Simon_ANI_ATTACK_RIGHT;
			}
			else
				if (pWhip->isWhipType(1))
				{
					if (isOnStair == true && isUpstair == true)
						ani = Simon_ANI_UPSTAIR_ATTACK_TYPE2_RIGHT;
					else if (isOnStair == true && isUpstair == false)
						ani = Simon_ANI_DOWNSTAIR_ATTACK_TYPE2_RIGHT;
					else
						ani = Simon_ANI_ATTACK_TYPE2_RIGHT;
				}
				else
					if (pWhip->isWhipType(2))
					{
						if (isOnStair == true && isUpstair == true)
							ani = Simon_ANI_UPSTAIR_ATTACK_TYPE3_RIGHT;
						else if (isOnStair == true && isUpstair == false)
							ani = Simon_ANI_DOWNSTAIR_ATTACK_TYPE3_RIGHT;
						else
							ani = Simon_ANI_ATTACK_TYPE3_RIGHT;
					}
		}



		if (pWhip->isWhipType(2)) //roi 3
		{
			if (animations[ani]->GetCurrentFrame() == 5)
			{
				CSound::getInstance()->play("usingwhip", false, 1);

				pWhip->SetWhipType(2); ////--------------------------------------------------
				pWhip->SetDelete(false); //cho phep Weapon xet va cham

				if (nx < 0) //simon quay trai
				{
					pWhip->SetPosition(this->x - 28, this->y + 5);
				}
				else
				{
					pWhip->SetPosition(this->x + 34, this->y + 5);
				}

			}
			if (animations[ani]->GetCurrentFrame() == 6)
			{
				isAttack = false;
				isDamageBoss = true;
				animations[ani]->SetCurrentFrame(-1);

				if (isHitEnemy == false)
				{
					if (isOnStair)
						SetState(Simon_STATE_ONSTAIR);
					else
						SetState(Simon_STATE_IDLE);
				}

				pWhip->SetDelete(true);
			}
		}
		else //roi 1,2
		{
			if (animations[ani]->GetCurrentFrame() == 2)
			{
				CSound::getInstance()->play("usingwhip", false, 1);
				pWhip->SetDelete(false); //cho phep Weapon xet va cham

				if (nx < 0) //simon quay trai
				{
					pWhip->SetPosition(this->x - 27, this->y + 8);
				}
				else
				{
					pWhip->SetPosition(this->x + 23, this->y + 8);
				}
			}
			if (animations[ani]->GetCurrentFrame() == 3)
			{
				isAttack = false;
				isDamageBoss = true;
				animations[ani]->SetCurrentFrame(-1);

				if (isHitEnemy == false)
				{
					if (isOnStair)
					{
						SetState(Simon_STATE_ONSTAIR);
					}
					else
						SetState(Simon_STATE_IDLE);
				}

				pWhip->SetDelete(true);

			}
		}
	}

	else
		if (isSitAttack)
		{
			int ani;

			if (nx < 0) //quay trai
			{
				if (pWhip->isWhipType(0))
					ani = Simon_ANI_SIT_ATTACK_LEFT;
				else
					if (pWhip->isWhipType(1))
						ani = Simon_ANI_SIT_ATTACK_TYPE2_LEFT;
					else
						if (pWhip->isWhipType(2))
							ani = Simon_ANI_SIT_ATTACK_TYPE3_LEFT;
			}
			else //quay phai
			{
				if (pWhip->isWhipType(0))
					ani = Simon_ANI_SIT_ATTACK_RIGHT;
				else if (pWhip->isWhipType(1))
					ani = Simon_ANI_SIT_ATTACK_TYPE2_RIGHT;
				else if (pWhip->isWhipType(2))
					ani = Simon_ANI_SIT_ATTACK_TYPE3_RIGHT;
			}
			if (pWhip->isWhipType(2)) //roi 3
			{
				if (animations[ani]->GetCurrentFrame() == 5)
				{
					CSound::getInstance()->play("usingwhip", false, 1);
					pWhip->SetWhipType(2);
					pWhip->SetDelete(false); //cho phep Weapon xet va cham

					if (nx < 0) //simon quay trai
					{
						pWhip->SetPosition(this->x - 28, this->y + 12);
					}
					else
					{
						pWhip->SetPosition(this->x + 34, this->y + 12);
					}
				}
				if (animations[ani]->GetCurrentFrame() == 6)
				{
					isSitAttack = false;
					isDamageBoss = true;
					animations[ani]->SetCurrentFrame(-1);

					if (isHitEnemy == false)
						SetState(Simon_STATE_IDLE);

					pWhip->SetDelete(true);
				}
			}
			else //roi 1,2
			{
				if (animations[ani]->GetCurrentFrame() == 2)
				{
					CSound::getInstance()->play("usingwhip", false, 1);

					pWhip->SetDelete(false); //cho phep Weapon xet va cham


					if (nx < 0) //simon quay trai
					{
						pWhip->SetPosition(this->x - 28, this->y + 15);
					}
					else
					{
						pWhip->SetPosition(this->x + 25, this->y + 15);
					}
				}

				if (animations[ani]->GetCurrentFrame() == 3)
				{
					isSitAttack = false;
					isDamageBoss = true;
					animations[ani]->SetCurrentFrame(-1);

					if (isHitEnemy == false)
						SetState(Simon_STATE_IDLE);

					pWhip->SetDelete(true);

				}
			}
		}
		else
			if (GetState() == Simon_STATE_THROWING || isSitThrow) //throw weapon
			{
				if(isSitThrow)
					vx = 0;
				if (isOnStair)
				{
					isSitThrow = false; //vừa đi vừa ném ở cầu thang, khi xuống cầu thang r thì ko vào nữa
					vx = 0;
					vy = 0;
				}
				

				int ani;
				if (nx < 0) //quay trai
				{
					if (isOnStair == true && isUpstair==true)
						ani = Simon_ANI_UPSTAIR_THROW_LEFT;
					else if(isOnStair == true && isUpstair == false)
						ani = Simon_ANI_DOWNSTAIR_THROW_LEFT;
					else
					{
						if (isSitThrow)
							ani = Simon_ANI_SIT_THROW_LEFT;
						else
							ani = Simon_ANI_THROWING_LEFT;
					}
				} 
				else  //quay phai
				{
					if (isOnStair == true && isUpstair == true)
						ani = Simon_ANI_UPSTAIR_THROW_RIGHT;
					else if(isOnStair == true && isUpstair == false)
						ani = Simon_ANI_DOWNSTAIR_THROW_RIGHT;
					else
					{
						if (isSitThrow)
							ani = Simon_ANI_SIT_THROW_RIGHT;
						else
							ani = Simon_ANI_THROWING_RIGHT;
					}
				}

				if (animations[ani]->GetCurrentFrame() == 2)
				{
					if (weaponType == 1 && GetNumHeart() > 0 && isThrow == true)
					{
						CSound::getInstance()->play("dagger", false, 1);

						SetNumHeart(-1);
						isThrow = false;
			
						isDamageBoss = true;

						pWeapon = new CDagger();
						

						pWeapon->SetDelete(false); //cho phep Weapon xet va cham

						if (nx < 0) //simon quay trai
						{
							pWeapon->AddAnimation(804);
							pWeapon->SetFlip(false);
							pWeapon->SetPosition(this->x - 25, this->y + 6);				
						}
						else
						{
							pWeapon->AddAnimation(801);
							pWeapon->SetFlip(true);
							pWeapon->SetPosition(this->x + 25, this->y + 6);
						}
#pragma region doubleshot

						if (isThrowDouble) //doubleshot
						{
							if (count < 2)
							{
								if (listWeapon.size() == 0) //if này là để khi simon ném 1 cái, sau đó ngưng, r tiếp tục ném thì ném dc 2 cái
								{					
									count = 0;
									listWeapon.push_back(pWeapon);
									isDamageBoss = true;
									count++;
								}
								else
								{
									listWeapon.push_back(pWeapon);
									isDamageBoss = true;
									count++;
								}
							}
							else
							{
								if (listWeapon.size() == 0)
								{
									count = 0;
									listWeapon.push_back(pWeapon);
									isDamageBoss = true;
									count++;
								}
							}
						}

#pragma endregion double shot

					}
					else
						if (weaponType == 2 && GetNumHeart() > 0 && isThrow == true)
						{
							SetNumHeart(-1);
							isThrow = false;
			

							if (nx < 0) //simon quay trai
							{
								pWeapon = new CHolyWater(this->GetPosition(), true);
								pWeapon->nx = -1;
								pWeapon->SetPosition(this->x - 10, this->y + 8);
							}
							else
							{
								pWeapon = new CHolyWater(this->GetPosition(), false);
								pWeapon->nx = 1;
								pWeapon->SetPosition(this->x + 10, this->y + 8);
							}

							pWeapon->SetDelete(false); //cho phep Weapon xet va cham
							pWeapon->AddAnimation(833);
							pWeapon->AddAnimation(808);
							//pWeapon->GetSimonPos(this->x, this->y);

#pragma region doubleshot

							if (isThrowDouble) //doubleshot
							{
								if (count < 2)
								{
									if (listWeapon.size() == 0) //if này là để khi simon ném 1 cái, sau đó ngưng, r tiếp tục ném thì ném dc 2 cái
									{

										count = 0;
										listWeapon.push_back(pWeapon);
										isDamageBoss = true;
										count++;
									}
									else
									{
										listWeapon.push_back(pWeapon);
										isDamageBoss = true;
										count++;
									}
								}
								else
								{
									if (listWeapon.size() == 0)
									{
										count = 0;
										listWeapon.push_back(pWeapon);
										isDamageBoss = true;
										count++;
									}
								}
							}

#pragma endregion double shot

						}
						else
							if (weaponType == 3 && GetNumHeart() > 0 && isThrow == true)
							{
								SetNumHeart(-1);
								isThrow = false;
					
								isDamageBoss = true;
								CSound::getInstance()->play("axe", true, 1);

								if (this->nx < 0) //simon quay trai
								{
									pWeapon = new CAxe(this->GetPosition(), true);
									pWeapon->SetPosition(this->x - 5, this->y - 10);

								}
								else
								{
									pWeapon = new CAxe(this->GetPosition(), false);
									pWeapon->SetPosition(this->x + 5, this->y - 10);
								}
								pWeapon->SetDelete(false); //cho phep Weapon xet va cham
								pWeapon->AddAnimation(819);
#pragma region double shot
								if (isThrowDouble) //doubleshot
								{
									if (count < 2)
									{
										if (listWeapon.size() == 0) //if này là để khi simon ném 1 cái, sau đó ngưng, r tiếp tục ném thì ném dc 2 cái
										{
											count = 0;
											listWeapon.push_back(pWeapon);
											isDamageBoss = true;
											count++;
										}
										else
										{
											listWeapon.push_back(pWeapon);
											isDamageBoss = true;
											count++;
										}
									}
									else
									{
										if (listWeapon.size() == 0)
										{
											count = 0;
											listWeapon.push_back(pWeapon);
											isDamageBoss = true;
											count++;
										}
									}
								}

#pragma endregion double shot
							}

				}
				else
					if (animations[ani]->GetCurrentFrame() == 3)
					{						
						isThrow = true;
						animations[ani]->SetCurrentFrame(-1);

						if (isHitEnemy == false)
						{
							if (isOnStair)
							{						
								SetState(Simon_STATE_ONSTAIR);
							}
							else
							{
								isSitThrow = false;
								SetState(Simon_STATE_IDLE);
							}
						}
					}
			}

			//if (GetNumHeart() <= 0)
			//	weaponType = 0; //khi ném hết trái tim, set để simon ko có subweapon nữa

	if (isHitEnemy)
	{
		if (timerHitEnemy < 400)  //thời gian bị nẩy lên khi đụng enemy là 400ms
		{
			timerHitEnemy += dt;
		}
		else
		{
			timerHitEnemy = 0;
			isHitEnemy = false;
			isAttack = false;
			isSitAttack = false;

			if (isOnStair)
				SetState(Simon_STATE_ONSTAIR);
			else
				SetState(Simon_STATE_IDLE);
		}

		if (pWhip->IsDelete() == false)
			pWhip->SetDelete(true);
	}

#pragma region UPDATE WEAPON

	if (isThrowDouble)
	{
		for (UINT i = 0; i < listWeapon.size(); i++)
		{
			if (listWeapon.at(i)->IsDelete() == true)
			{
				listWeapon.erase(listWeapon.begin() + i);
			}
			else
				listWeapon.at(i)->Update(dt, coObjects);
		}
	}
	else
	{
		if (pWeapon)
		{
			pWeapon->Update(dt, coObjects);
		}
	}

#pragma endregion UPDATE WEAPON

	// Calculate dx, dy 
	CGameObject::Update(dt);


	/*if (state != Simon_STATE_ONSTAIR && state != Simon_STATE_ATTACK && state != Simon_STATE_THROWING)
		isOnStair = false;*/


	if (!isOnStair)
	{
		//fall down
		vy += Simon_GRAVITY * dt;
		CheckCollisionWithGround(dt, coObjects);

		isWalkingToStair = false;  //chỉnh speed lại thành đi bth 
	}
	else
	{
		x += dx;
		y += dy;
	}

	//if (isHitTopStair || isHitBottomStair)
	//{
	//	CheckCollisionOnStair(dt, coObjects);
	//}

	if (isOnStair)
	{
		if (isHitTopStair == true && isUpstair == true)
		{
			CheckCollisionOnStair(dt, coObjects);
		}
		else if (isHitBottomStair == true && isUpstair == false)
		{
			CheckCollisionOnStair(dt, coObjects);
		}
	}
}

void CSimon::Render(Camera *camera)
{
	int ani;

	if (state == Simon_STATE_DIE)
	{
		if (nx < 0)
			ani = Simon_ANI_DIE;
		else
			ani = Simon_ANI_DIE_RIGHT;
	}
	else if (state == Simon_STATE_ONSTAIR)
	{
		if (isUpstair)
		{
			if (isStopOnStair)
			{
				if (nx > 0)
					ani = Simon_ANI_UPSTAIR_STOP_RIGHT;
				else
					ani = Simon_ANI_UPSTAIR_STOP_LEFT;
			}
			else
			{
				if (nx > 0)
					ani = Simon_ANI_UPSTAIR_RIGHT;
				else
					ani = Simon_ANI_UPSTAIR_LEFT;
			}
		}
		else if (isUpstair == false)
		{
			if (isStopOnStair)
			{
				if (nx < 0)
					ani = Simon_ANI_DOWNSTAIR_STOP_LEFT;
				else
					ani = Simon_ANI_DOWNSTAIR_STOP_RIGHT;
			}
			else
			{
				if (nx < 0)
					ani = Simon_ANI_DOWNSTAIR_LEFT;
				else
					ani = Simon_ANI_DOWNSTAIR_RIGHT;
			}
		}
	}
	else if (state == Simon_STATE_SIT)
	{
		if (nx < 0)
		{
			ani = Simon_ANI_SIT_LEFT;
			if (isSitThrow)
				ani = Simon_ANI_SIT_THROW_LEFT;
			else
				if (isSitAttack)
				{
					if (pWhip->isWhipType(1))
						ani = Simon_ANI_SIT_ATTACK_TYPE2_LEFT;
					else if (pWhip->isWhipType(2))
						ani = Simon_ANI_SIT_ATTACK_TYPE3_LEFT;
					else
						ani = Simon_ANI_SIT_ATTACK_LEFT;
				}
		}
		else
		{
			ani = Simon_ANI_SIT_RIGHT;
			if (isSitThrow)
				ani = Simon_ANI_SIT_THROW_RIGHT;
			if (isSitAttack)
			{
				if (pWhip->isWhipType(1))
					ani = Simon_ANI_SIT_ATTACK_TYPE2_RIGHT;
				else if (pWhip->isWhipType(2))
					ani = Simon_ANI_SIT_ATTACK_TYPE3_RIGHT;
				else
					ani = Simon_ANI_SIT_ATTACK_RIGHT;
			}
		}
	}
	else if (state == Simon_STATE_JUMP)
	{
		if (nx < 0)
		{
			ani = Simon_ANI_JUMP_LEFT;
		}
		else ani = Simon_ANI_JUMP_RIGHT;
	}
	else if (state == Simon_STATE_ATTACK)
	{
		if (pWhip->isWhipType(1))
		{
			if (nx < 0)
			{
				if (isOnStair == true && isUpstair == false)
					ani = Simon_ANI_DOWNSTAIR_ATTACK_TYPE2_LEFT;
				else if (isOnStair == true && isUpstair == true)
					ani = Simon_ANI_UPSTAIR_ATTACK_TYPE2_LEFT;
				else
					ani = Simon_ANI_ATTACK_TYPE2_LEFT;
			}
			else
			{
				if (isOnStair == true && isUpstair == true)
					ani = Simon_ANI_UPSTAIR_ATTACK_TYPE2_RIGHT;
				else if (isOnStair == true && isUpstair == false)
					ani = Simon_ANI_DOWNSTAIR_ATTACK_TYPE2_RIGHT;
				else
					ani = Simon_ANI_ATTACK_TYPE2_RIGHT;
			}
		}
		else if (pWhip->isWhipType(2))
		{
			if (nx < 0)
			{
				if (isOnStair == true && isUpstair == false)
					ani = Simon_ANI_DOWNSTAIR_ATTACK_TYPE3_LEFT;
				else if (isOnStair == true && isUpstair == true)
					ani = Simon_ANI_UPSTAIR_ATTACK_TYPE3_LEFT;
				else
					ani = Simon_ANI_ATTACK_TYPE3_LEFT;
			}
			else
			{
				if (isOnStair == true && isUpstair == true)
					ani = Simon_ANI_UPSTAIR_ATTACK_TYPE3_RIGHT;
				else if (isOnStair == true && isUpstair == false)
					ani = Simon_ANI_DOWNSTAIR_ATTACK_TYPE3_RIGHT;
				else
					ani = Simon_ANI_ATTACK_TYPE3_RIGHT;
			}
		}
		else
		{
			if (nx < 0)
			{
				if (isOnStair == true && isUpstair == false)
					ani = Simon_ANI_DOWNSTAIR_ATTACK_TYPE1_LEFT;
				else if (isOnStair == true && isUpstair == true)
					ani = Simon_ANI_UPSTAIR_ATTACK_TYPE1_LEFT;
				else
					ani = Simon_ANI_ATTACK_LEFT;
			}
			else if (nx > 0)
			{
				if (isOnStair == true && isUpstair == true)
					ani = Simon_ANI_UPSTAIR_ATTACK_TYPE1_RIGHT;
				else if (isOnStair == true && isUpstair == false)
					ani = Simon_ANI_DOWNSTAIR_ATTACK_TYPE1_RIGHT;
				else
					ani = Simon_ANI_ATTACK_RIGHT;
			}
		}
	}
	else if (state == Simon_STATE_THROWING)
	{
		if (nx < 0)
		{
			if (isOnStair == true && isUpstair == true)
				ani = Simon_ANI_UPSTAIR_THROW_LEFT;
			else if (isOnStair == true && isUpstair == false)
				ani = Simon_ANI_DOWNSTAIR_THROW_LEFT;
			else
				ani = Simon_ANI_THROWING_LEFT;
		}
		else if(nx > 0)
		{
			if (isOnStair == true && isUpstair == true)
				ani = Simon_ANI_UPSTAIR_THROW_RIGHT;
			else if (isOnStair == true && isUpstair == false)
				ani = Simon_ANI_DOWNSTAIR_THROW_RIGHT;
			else
				ani = Simon_ANI_THROWING_RIGHT;
		}
	}
	else if (state == Simon_STATE_HIT_ENEMY)
	{
		if (isHitLeft)
			ani = Simon_ANI_HIT_ENEMY_LEFT;
		else
			ani = Simon_ANI_HIT_ENEMY_RIGHT;
	}
	else
	{
		if (vx == 0)
		{
			if (nx > 0)
			{
				if (isEatingItem)
					ani = Simon_ANI_CHANGE_COLOR_RIGHT;
				else
					ani = Simon_ANI_IDLE_RIGHT;
			}
			else
			{
				if (isEatingItem)
					ani = Simon_ANI_CHANGE_COLOR_LEFT;
				else
					ani = Simon_ANI_IDLE_LEFT;
			}
		}
		else if (vx > 0)
		{
			if (isJumping == false)
				ani = Simon_ANI_WALKING_RIGHT; //Neu dang nhay thi ko update ani walk
			else
			{
				ani = Simon_ANI_JUMP_RIGHT;
			}
		}
		else if (vx < 0)
			if (isJumping == false)
				ani = Simon_ANI_WALKING_LEFT;
			else
			{
				ani = Simon_ANI_JUMP_LEFT;
			}
	}

	int alpha = 255;

	if (isUntouchable) alpha = 150;
	else 
		if (isInvisible) alpha = 50;

	if (isDeleted == false)
	{
		animations[ani]->Render(camera->transform(x, y), alpha);
		RenderBoundingBox(camera);
	}
	

	if (isThrowDouble)
	{
		for (UINT i = 0; i < listWeapon.size(); i++)
			listWeapon.at(i)->Render(camera);
	}
	else
	{
		if (pWeapon->IsDelete() == false)
			pWeapon->Render(camera);
	}

	if (pWhip)
		pWhip->Render(camera);
}

void CSimon::SetState(int state) 
{
	CGameObject::SetState(state);

	switch (state)
	{
	case Simon_STATE_SIT:
		vx = 0;
		//vy = 0;
		break;
	case Simon_STATE_THROWING:
		vx = 0;
		//vy = 0;
		break;
	case Simon_STATE_WALKING_RIGHT:
		if (isWalkingToStair)
			vx = Simon_WALKING_TO_STAIR_SPEED;
		else
			vx = Simon_WALKING_SPEED;
		nx = 1;
		isSitThrow = false;
		break;
	case Simon_STATE_WALKING_LEFT:
		if (isWalkingToStair)
			vx = -Simon_WALKING_TO_STAIR_SPEED;
		else
			vx = -Simon_WALKING_SPEED;
		nx = -1;
		isSitThrow = false;
		break;

	case Simon_STATE_JUMP:
		vy = -Simon_JUMP_SPEED_Y;
		break;

	case Simon_STATE_HIT_ENEMY:
		vy = -0.15f;
		if (isHitLeft)
			vx = 0.1f;
		else
			vx = -0.1f;
		break;

	case Simon_STATE_IDLE:
		vx = 0; 
		isSitAttack = false;
		isAttack = false;
		isSitThrow = false;
		//isThrow = false;
		break;

	case Simon_STATE_ONSTAIR:
		if (isUpstair)
		{
			nx = StairDirection;
			if (nx > 0)
			{
				vx = 0.04f;
				vy = -0.04f;
			}
			else
			{
				vx = -0.04f;
				vy = -0.04f;
			}
		}
		else
			if (isUpstair == false)
			{
				nx = -StairDirection;
				if (nx > 0)
				{
					vx = 0.04f;
					vy = 0.04f;
				}
				else
				{
					vx = -0.04f;
					vy = 0.04f;
				}
			}

		//////////////////
		if (isStopOnStair)
		{
			vx = 0;
			vy = 0;
			isSitAttack = false;
			isAttack = false;
		}
		//////////////////
		break;
	}
}


void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == Simon_STATE_SIT)
	{
		left = x;
		top = y + 6;
		right = x + Simon_BIG_BBOX_WIDTH;
		bottom = y + Simon_BIG_BBOX_HEIGHT + 2;
	}
	else if (state == Simon_STATE_DIE)
	{
		left = x;
		top = y;
		right = x + 32;
		bottom = y + 15;
	}
	else
	{
		left = x;
		top = y;
		right = x + Simon_BIG_BBOX_WIDTH;
		bottom = y + Simon_BIG_BBOX_HEIGHT + 2;

	}
}

RECT CSimon::GetBound()
{
	RECT rect;
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	rect.left = l;
	rect.top = t;
	rect.right = r;
	rect.bottom = b;

	return rect;
}

int CSimon::GetNumHeart()
{
	return this->numHeart;
}

void CSimon::SetNumHeart(int heart)
{
	numHeart += heart;
}

int CSimon::GetNumLife()
{
	return numLife;
}

void CSimon::SetNumLife(int life)
{
	numLife += life;
}

int CSimon::GetNumHP()
{
	return numHP;
}

void CSimon::SetNumHP(int hp)
{
	numHP += hp;
}

int CSimon::GetScore()
{
	return this->score;
}

void CSimon::SetScore(int score)
{
	this->score += score;
}

void CSimon::CheckCollisionOnStair(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;


	y -= 60.0f;  //kéo vy lên 1 đoạn
	vy = 100000.0f;  //kéo xuống lại ngay lập tức 
	//(diễn ra trong 1 frame)

	CGameObject::Update(dt);

	coEvents.clear();

	CalcPotentialCollisions(colliable_objects, coEvents);

	if (coEvents.size() == 0)
	{
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		y += min_ty * dy + ny * 0.2f;

		if (ny != 0)
		{
			vy = 0;
			vx = 0;
			isOnStair = false;
			isHitTopStair = false;
			isHitBottomStair = false;
			isStopOnStair = false;
			isWalkingToStair = false;
	

			//if (isSiting == false)
			SetState(Simon_STATE_IDLE);
		}
	}

	vy = Simon_GRAVITY *dt;
	CGameObject::Update(dt);
}

void CSimon::CheckCollisionWithGround(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();


	CalcPotentialCollisions(colliable_objects, coEvents);


	//// reset untouchable timer if untouchable time has passed
	//if (GetTickCount() - untouchable_start > Simon_UNTOUCHABLE_TIME)
	//{
	//	untouchable_start = 0;
	//	untouchable = 0;
	//}


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx; //dx=vx*dt
		y += dy;

	}
	else
	{
		isOnGround = true;
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		//block 	
		x += min_tx * dx + nx * 0.2f;
		y += min_ty * dy + ny * 0.2f;

	
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		if (ny == -1)
		{
			if (this->GetPosition().y - firstY >= 50 /*&& isLand == false*/)
			{
				isLand = true;
			}
			firstY = this->GetPosition().y;
		}

		if (ny == -1 && isJumping == true)
		{		
			if (isAttack == false && isHitEnemy == false) //set đk này để khi chạm đất mà đánh chưa xong thì phải hoàn thành hd đánh r mới đứng yên
				SetState(Simon_STATE_IDLE);

			isJumping = false;
		}

	
	}


	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

