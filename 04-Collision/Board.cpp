#include "Board.h"



Board::Board(CSimon *simon)
{
	isDecreaseTimer = false;

	this->mSimon = simon;

	this->txt_numHeart = Text(to_wstring(mSimon->GetNumHeart()), 50, 50, 90, 10, D3DCOLOR_XRGB(255, 255, 255), L"Consolas");

	this->txt_numLife = Text(to_wstring(mSimon->GetNumLife()), 50, 50, 90, 10, D3DCOLOR_XRGB(255, 255, 255), L"Consolas");

	this->txt_timeAlive = Text(to_wstring(TimeAlive), 50, 50, 90, 10, D3DCOLOR_XRGB(255, 255, 255), L"Consolas");

	this->txt_numStage = Text(to_wstring(_stage), 50, 50, 90, 10, D3DCOLOR_XRGB(255, 255, 255), L"Consolas");

	this->txt_zero = Text(to_wstring(0), 50, 50, 90, 10, D3DCOLOR_XRGB(255, 255, 255), L"Consolas");

	this->txt_score = Text(to_wstring(mSimon->GetScore()), 55, 50, 90, 10, D3DCOLOR_XRGB(255, 255, 255), L"Consolas");
}


Board::~Board()
{
}

void Board::Update(DWORD dt)
{
#pragma region PROCESS AFTER BOSS DEATH
	if (isDecreaseTimer == false)
	{
		if (countTimer < 1000)
			countTimer += dt;
		else
			if (countTimer >= 1000)
			{
				if (TimeAlive > 0)
					TimeAlive--;
				countTimer = 0;

				txt_timeAlive.SetString(this->TimeAlive);
			}
	}
	else
	{		
		txt_timeAlive.SetString(this->TimeAlive);

		if (countTimer < 5)
		{		
			countTimer += dt;
		}
		else
			if (countTimer >= 5)
			{
				countTimer = 0;

				if (TimeAlive > 0)
				{
					//cứ 1s thì cộng 10đ
					CSound::getInstance()->play("decreasetime", false, 1);
					TimeAlive--;
					mSimon->SetScore(+10);
				}
				else
				{
					if (translateTimer < 500) //sau 800s thì mới lấy tim tính điểm
						translateTimer += dt;
					else
					{
						if (mSimon->GetNumHeart() > 0)
						{
							mSimon->SetNumHeart(-1);
							mSimon->SetScore(100);
							CSound::getInstance()->play("decreasetime", false, 1);					
						}
						else
							isDecreaseTimer = false;
					}
				}
					
			}
	}
#pragma endregion PROCESS AFTER BOSS DEATH

	txt_numLife.SetString(this->mSimon->GetNumLife());
	txt_numHeart.SetString(this->mSimon->GetNumHeart());
	txt_numStage.SetString(this->_stage);
	txt_score.SetString(this->mSimon->GetScore());
}

void Board::Render(Camera *camera)
{
	animations[0]->Render(x, y-3);

	if (mSimon != NULL && mSimon->weaponType == 1)
	{
		/*if (mSimon->GetNumHeart() > 0)
		{*/ 
			animations[1]->Render(x+164, y+20);  //draw dagger
		//}
	}
	else if (mSimon != NULL && mSimon->weaponType == 2)
	{
		//if (mSimon->GetNumHeart() > 0)
		//{
			animations[5]->Render(x + 169, y + 16);  //draw holywater
		//}
	}
	else if (mSimon != NULL && mSimon->weaponType == 3)
	{
		//if (mSimon->GetNumHeart() > 0)
		//{
			animations[6]->Render(x + 164, y + 20);  //draw axe
		//}
	}
	else if (mSimon != NULL && mSimon->weaponType == 4)
	{
		//if (mSimon->GetNumHeart() > 0)
		//{
			animations[7]->Render(x + 169, y + 18);  //draw stop watch
		//}
	}

	if(mSimon->isThrowDouble)
		animations[8]->Render(x + 260, y + 20);  //draw doubleshot icon

	//player HP
	for (int i = 0; i < mSimon->GetNumHP(); i++)
	{
		animations[2]->Render(i*5+62, y + 16);
	}
	for (int i = 0; i < 16- mSimon->GetNumHP(); i++)
	{
		animations[4]->Render(137- i * 5, y + 16);
	}

	//enemy HP
	if (mBoss)
	{
		for (int i = 0; i < mBoss->GetHP(); i++)
		{
			animations[3]->Render(i * 5 + 62, y + 24);
		}
		for (int i = 0; i < 16 - mBoss->GetHP(); i++)
		{ 
			animations[4]->Render(137 - i * 5, y + 24);
		}
	}

	if(mSimon->GetNumHeart() > 99) //khi numHeart có 3 chữ số trở lên thì xích ra xa :))
		this->txt_numHeart.Draw(D3DXVECTOR2(320 - 88, 4));
	else
		this->txt_numHeart.Draw(D3DXVECTOR2(320 - 100, 4));

#pragma region DRAW SCORE && ZERO
	for (int i = 0; i < 6; i++)
	{
		if (mSimon->GetScore() > 99 && mSimon->GetScore() <= 999)
		{
			if (i <= 2)
				this->txt_zero.Draw(D3DXVECTOR2(46 + i * 9, -7));
			else
			{
				this->txt_score.Draw(D3DXVECTOR2(46 + 5 * 9, -7));
				break;
			}
		}
		else if (mSimon->GetScore() > 999 && mSimon->GetScore() <= 9999)
		{
			if (i <= 1)
				this->txt_zero.Draw(D3DXVECTOR2(46 + i * 9, -7));
			else
			{
				this->txt_score.Draw(D3DXVECTOR2(46 + 5 * 9, -7));
				break;
			}
		}
		else if (mSimon->GetScore() > 9999 && mSimon->GetScore() <= 99999)
		{
			if (i <= 0)
				this->txt_zero.Draw(D3DXVECTOR2(46 + i * 9, -7));
			else
			{
				this->txt_score.Draw(D3DXVECTOR2(46 + 5 * 9, -7));
				break;
			}
		}
		else if(mSimon->GetScore() == 0)
			this->txt_zero.Draw(D3DXVECTOR2(46 + i * 9, -7));
	}
#pragma endregion DRAW SCORE

	if(mSimon->GetScore() > 99999)
		this->txt_score.Draw(D3DXVECTOR2(90,-7));
	this->txt_numLife.Draw(D3DXVECTOR2(320 - 100, 15));
	this->txt_timeAlive.Draw(D3DXVECTOR2(320 - 148, -8));
	this->txt_numStage.Draw(D3DXVECTOR2(320 - 55, -9));
}

void Board::SetTimer(int timer)
{
	this->TimeAlive = timer;
}

int Board::GetTimeAlive()
{
	return this->TimeAlive;
}

void Board::SetBossPointer(CBoss * boss)
{
	mBoss = boss;
}

void Board::SetStage(int stage)
{
	if (stage == 0)
		stage = 1;
	else
		if (stage == 1 || stage == 2)
			stage = 2;
		else
			if (stage == 3 || stage == 4)
				stage = 3;

	_stage = stage; //hiển thị stage trên màn hình
}
