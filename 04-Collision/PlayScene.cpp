#include "PlayScene.h"


PlayScene::PlayScene()
{
	scene = 1;
	game = CGame::GetInstance();
	Simon = new CSimon();
	board = new Board(Simon);

	camera = new Camera();

	CTextures * textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	animations = CAnimations::GetInstance();

	textures->Add(ID_TEX_Simon, L"textures\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_OBJECT, L"textures\\object.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM, L"textures\\item.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_ENEMY, L"textures\\enemy.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BOARD, L"textures\\board.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));


	texSimon = textures->Get(ID_TEX_Simon);
	texEnemy = textures->Get(ID_TEX_ENEMY);
	texObject = textures->Get(ID_TEX_OBJECT);
	texItem = textures->Get(ID_TEX_ITEM);
	texBoard = textures->Get(ID_TEX_BOARD);

}

void PlayScene::KeyState(BYTE * state)
{
	if (Simon->isEatingItem)
	{
		Simon->SetState(Simon_STATE_IDLE);
		return;
	}

	if (Simon->GetState() == Simon_STATE_DIE) return;
	if (isMoveScene) return;
	if (Simon->isHitEnemy) return;


	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (Simon->state == Simon_STATE_THROWING)
			return;
		if (Simon->isAttack)
			return;
		if (Simon->isSitAttack)
			return;
		if (game->IsKeyDown(DIK_DOWN))  //nhấn đè phím đi mà bấm phím ngồi thì ngồi xuống
		{
			if (Simon->isOnStair == false)
			{
				Simon->SetState(Simon_STATE_SIT);
				return;
			}
		}

#pragma region ONSTAIR

		/*	if (Simon->isOnStair)
			{*/
		for (int i = 0; i < listStair.size(); i++)
		{
			if (listStair.at(i)->ObjectTag == CGameObject::ObjectTypes::bottomstair)
			{
				if (CGame::GetInstance()->AABB(listStair.at(i)->GetBound(), Simon->GetBound()))
				{
					Simon->isHitBottomStair = true;
					break;
				}
			}
			else
			{
				if (CGame::GetInstance()->AABB(listStair.at(i)->GetBound(), Simon->GetBound()))
				{
					Simon->isHitTopStair = true;
					break;
				}
			}
		}

		//if (Simon->StairDirection == 1)  //stair từ trái qua phải
		//{
		//	Simon->isHitTopStair = false;
		//	Simon->isUpstair = true;
		//}
		//else if (Simon->StairDirection == -1)  //stair từ phải qua trái
		//{
		//	if (Simon->isUpstair)
		//	{				
		//		Simon->isUpstair = false;
		//	}
		//	else
		//	{
		//
		//		Simon->isUpstair = false;
		//	}
		//}

		//Simon->isStopOnStair = false;
		//Simon->SetState(Simon_STATE_ONSTAIR);
		//return;
	//}
#pragma endregion ONSTAIR

		if (Simon->isOnStair)
		{
			//dòng này để tránh Simon đang lên cầu thang nhưng lại checkColWithStair do biến isHitBottom vẫn true
			if (Simon->isUpstair)
				Simon->isHitBottomStair = false;
			if (Simon->isUpstair == false)
				Simon->isHitTopStair = false;

			if (Simon->StairDirection == 1)  //stair từ trái qua phải
			{
				Simon->isUpstair = true;
			}
			else if (Simon->StairDirection == -1)  //stair từ phải qua trái
			{
				if (Simon->isUpstair)
				{
					Simon->isUpstair = false;
				}
				else
				{
					Simon->isUpstair = false;
				}
			}


			Simon->isStopOnStair = false;
			Simon->SetState(Simon_STATE_ONSTAIR);
			return;
		}
		else
			Simon->SetState(Simon_STATE_WALKING_RIGHT);
	}

	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (Simon->state == Simon_STATE_THROWING) return;
		if (Simon->isAttack) return;
		if (Simon->isSitAttack) return;
		if (game->IsKeyDown(DIK_DOWN))
		{
			if (Simon->isOnStair == false)
			{
				Simon->SetState(Simon_STATE_SIT);
				return;
			}
		}

#pragma region ONSTAIR

		/*if (Simon->isOnStair)
		{*/
		for (int i = 0; i < listStair.size(); i++)
		{
			if (listStair.at(i)->ObjectTag == CGameObject::ObjectTypes::bottomstair)
			{
				if (CGame::GetInstance()->AABB(listStair.at(i)->GetBound(), Simon->GetBound()))
				{
					Simon->isHitBottomStair = true;
					break;
				}
			}
			else
			{
				if (CGame::GetInstance()->AABB(listStair.at(i)->GetBound(), Simon->GetBound()))
				{
					Simon->isHitTopStair = true;
					break;
				}
			}
		}

		//if (Simon->isUpstair) //dòng này để tránh Simon đang lên cầu thang nhưng lại checkColWithStair do biến isHitBottom vẫn true
		//	Simon->isHitBottomStair = false;
		//if (Simon->isUpstair == false)
		//	Simon->isHitTopStair = false;
		//if (Simon->StairDirection == 1)  //stair từ trái qua phải
		//{
		//	if (Simon->isUpstair)
		//	{
		//		Simon->isUpstair = false;
		//		Simon->isHitBottomStair = false;
		//	}
		//	
		//	else
		//	{
		//		if (Simon->nx < 0)
		//		{
		//			Simon->isUpstair = false;
		//			Simon->isHitBottomStair = false;
		//		}
		//		else
		//			Simon->isUpstair = true;
		//	}
		//}
		//else if (Simon->StairDirection == -1)  //stair từ phải qua trái
		//{
		//	Simon->isUpstair = true;
		//}
		//Simon->isStopOnStair = false;
		//Simon->SetState(Simon_STATE_ONSTAIR);
		//return;
	//}
#pragma endregion ONSTAIR
		if (Simon->isOnStair)
		{
			//dòng này để tránh Simon đang lên cầu thang nhưng lại checkColWithStair do biến isHitBottom vẫn true
			if (Simon->isUpstair)
				Simon->isHitBottomStair = false;
			if (Simon->isUpstair == false)
				Simon->isHitTopStair = false;

			if (Simon->StairDirection == 1)  //stair từ trái qua phải
			{
				if (Simon->isUpstair)
				{
					Simon->isUpstair = false;
				}
				else
				{
					if (Simon->nx < 0)
					{
						Simon->isUpstair = false;
					}
					else
						Simon->isUpstair = true;
				}
			}
			else if (Simon->StairDirection == -1)  //stair từ phải qua trái
			{
				Simon->isUpstair = true;
			}

			Simon->isStopOnStair = false;
			Simon->SetState(Simon_STATE_ONSTAIR);
			return;
		}
		else
			Simon->SetState(Simon_STATE_WALKING_LEFT);
	}

	else if (game->IsKeyDown(DIK_DOWN))
	{
		if (Simon->isAttack)
			return;
		if (Simon->state == Simon_STATE_THROWING)
			return;

		for (int i = 0; i < listStair.size(); i++)
		{
			if (listStair.at(i)->ObjectTag == CGameObject::ObjectTypes::bottomstair)
			{
				if (CGame::GetInstance()->AABB(listStair.at(i)->GetBound(), Simon->GetBound()))
				{
					Simon->isHitBottomStair = true;
				}
			}
			else if (listStair.at(i)->ObjectTag == CGameObject::ObjectTypes::topstair)
			{
				if (CGame::GetInstance()->AABB(listStair.at(i)->GetBound(), Simon->GetBound()))
				{
					if (Simon->nx > 0)
					{
						Simon->StairDirection = -1;
						if (listStair.at(i)->StairTag == CGameObject::StairTypes::ToLeft)
						{
							Simon->StairDirection = 1;
						}

					}
					else if (Simon->nx < 0)
					{
						Simon->StairDirection = 1;
						if (listStair.at(i)->StairTag == CGameObject::StairTypes::ToRight)
						{
							Simon->StairDirection = -1;
						}
					}

#pragma region Adjust Simon And Stair

					if (abs(Simon->x - listStair.at(i)->x) <= 10)
					{
						if (listStair.at(i)->StairTag == CGameObject::StairTypes::ToLeft)
						{
							Simon->isHitTop = true;
							Simon->isWalkingToStair = true;
							Simon->SetState(Simon_STATE_WALKING_LEFT);
						}
					}
					else
					{
						Simon->isOnStair = true;

						/*		if (listStair.at(i)->StairTag == CGameObject::StairTypes::ToRight)
								{
									Simon->SetPosition(listStair.at(i)->x, Simon->GetPosition().y);
									Simon->isOnStair = true;
								}
								else
									Simon->isOnStair = true;*/
					}

					if (listStair.at(i)->StairTag == CGameObject::StairTypes::ToRight)
					{
						Simon->isHitTop = true;
						Simon->SetPosition(listStair.at(i)->x, Simon->GetPosition().y);
						Simon->isOnStair = true;

					}

#pragma endregion Adjust Simon And Stair	

				}
			}
		}

		if (Simon->isOnStair)
		{
			Simon->isHitTop = false;
			Simon->isStopOnStair = false;

			if (Simon->isUpstair) //dòng này để tránh Simon đang lên cầu thang nhưng lại checkColWithStair do biến isHitBottom vẫn true
				Simon->isHitBottomStair = false;

			Simon->isUpstair = false;

			Simon->SetState(Simon_STATE_ONSTAIR);
		}
		else //ngoi, ngoi danh
		{
			if (Simon->isHitTop == false)
			{
				if (Simon->isAttack == false && Simon->isJumping == false)
					Simon->SetState(Simon_STATE_SIT);
			}
		}
	}

	else if (game->IsKeyDown(DIK_UP))
	{
		if (Simon->state == Simon_STATE_JUMP) return;
		if (Simon->isAttack) return; //khi đánh trên cầu thang thì k lên	
		if (Simon->state == Simon_STATE_THROWING) return;
			

		for (int i = 0; i < listStair.size(); i++)
		{
			if (listStair.at(i)->ObjectTag == CGameObject::ObjectTypes::bottomstair)
			{
				if (CGame::GetInstance()->AABB(listStair.at(i)->GetBound(), Simon->GetBound()))
				{
					if (listStair.at(i)->StairTag == CGameObject::StairTypes::ToLeft)
						Simon->StairDirection = -1;
					else if (listStair.at(i)->StairTag == CGameObject::StairTypes::ToRight)
						Simon->StairDirection = 1;

#pragma region Adjust Simon And Stair

					if (abs(Simon->x - listStair.at(i)->x) < 14)
					{
						if (listStair.at(i)->StairTag == CGameObject::StairTypes::ToRight)
						{

							Simon->isWalkingToStair = true;
							Simon->SetState(Simon_STATE_WALKING_RIGHT);
						}
						else
							if (listStair.at(i)->StairTag == CGameObject::StairTypes::ToLeft)
							{

								Simon->isWalkingToStair = true;
								Simon->SetState(Simon_STATE_WALKING_LEFT);
							}
					}
					else
					{

						Simon->isWalkingToStair = false;
						Simon->isOnStair = true;
						break;
					}

#pragma endregion Adjust Simon And Stair			

				}
			}
			else if (listStair.at(i)->ObjectTag == CGameObject::ObjectTypes::topstair)
			{
				if (CGame::GetInstance()->AABB(listStair.at(i)->GetBound(), Simon->GetBound()))
				{
					Simon->isHitTopStair = true;
				}
			}
		}
		if (Simon->isOnStair)
		{
			Simon->isStopOnStair = false;

			if (Simon->isUpstair == false) //dòng này để tránh Simon đang xuống cầu thang nhưng lại checkColWithStair do biến isHitTopStair vẫn true
				Simon->isHitTopStair = false;

			Simon->isUpstair = true;

			Simon->SetState(Simon_STATE_ONSTAIR);
		}
	}
}

void PlayScene::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (Simon->isEatingItem)
	{
		Simon->SetState(Simon_STATE_IDLE);
		return;
	}
	if (Simon->GetState() == Simon_STATE_DIE) return;
	if (isMoveScene) return;

	switch (KeyCode)
	{
	case DIK_S:
		if (Simon->isHitEnemy) return;
		if (Simon->isAttack) return;
		if (Simon->isOnStair) return;
		if (Simon->isJumping == false)
		{
			Simon->SetState(Simon_STATE_JUMP);
			Simon->isJumping = true;
		}
		break;

	//case DIK_A: // reset de test
	//	Simon->isOnStair = false;
	//	Simon->isStopOnStair = false;
	//	Simon->SetState(Simon_STATE_IDLE);
	//	Simon->SetPosition(Simon->GetPosition().x + 600, 0);
	//	Simon->SetSpeed(0, 0);
	//	break;

	case DIK_A:
		if (game->IsKeyDown(DIK_UP))
		{
			if (Simon->isAttack) return;
			if (Simon->isSitAttack) return;

			if (Simon->GetNumHeart() > 0 && Simon->weaponType != 0)
			{
				if (Simon->isThrowDouble)
				{
					if (Simon->weaponType != 4)
					{
						if (count < 2)
						{
							count++;

							if (Simon->state == Simon_STATE_SIT)
								Simon->isSitThrow = true;
							else
							{
								Simon->SetState(Simon_STATE_THROWING);
							}

							if (Simon->listWeapon.size() == 0)
							{
								count = 0;
							}
						}
						else
						{
							if (Simon->listWeapon.size() == 0)
							{
								count = 0;

								count++;
								if (Simon->state == Simon_STATE_SIT)
									Simon->isSitThrow = true;
								else
									Simon->SetState(Simon_STATE_THROWING);

							}
						}
					}
					else if (Simon->weaponType == 4) //subweapon=stopwatch - khi ăn double shot thì ko thêm vô listWeapon
					{
						if (Simon->GetNumHeart() >= 5)
						{
							Simon->isThrow = true;

							Simon->isUseStopWatch = true;
						}
					}
				}
				else
				{
					Simon->isThrow = true;

					if (Simon->pWeapon->IsDelete() == true) //Chỉ có 1 vũ khí xuất hiện trên màn hình
					{
						if (Simon->weaponType != 4)
						{
							if (Simon->state == Simon_STATE_SIT)
								Simon->isSitThrow = true;
							else
								Simon->SetState(Simon_STATE_THROWING);

						}
						else if (Simon->weaponType == 4 && Simon->GetNumHeart() >= 5)
							Simon->isUseStopWatch = true;
					}
				}
			}

			if (Simon->state != Simon_STATE_THROWING)
			{
				if (game->IsKeyDown(DIK_DOWN) && Simon->isOnStair == false)
				{
					if (Simon->isSitThrow == false)
						Simon->isSitAttack = true; //ngồi ném
				}
				else
				{
					if (Simon->isSitAttack) return;
					if (Simon->isHitEnemy) return;

					Simon->isAttack = true;
					Simon->SetState(Simon_STATE_ATTACK);
				}
				break;
			}
		}
		if (Simon->state != Simon_STATE_THROWING)
		{
			if (game->IsKeyDown(DIK_DOWN) && Simon->isOnStair == false) //ngồi đánh
			{
				Simon->isSitAttack = true;
			}
			else //đứng đánh
			{
				if (Simon->isSitAttack) return;
				if (Simon->isHitEnemy) return;

				Simon->isAttack = true;
				Simon->SetState(Simon_STATE_ATTACK);
			}
			break;
		}

		break;
		//case DIK_X:
		//	if (game->IsKeyDown(DIK_UP))
		//	{
		//		if (Simon->isThrowDouble)
		//		{
		//			if (Simon->weaponType != 4)
		//			{
		//				if (count < 2)
		//				{
		//					count++;
		//					Simon->SetState(Simon_STATE_THROWING);
		//					if (Simon->listWeapon.size() == 0)
		//					{
		//						count = 0;
		//					}
		//				}
		//				else
		//				{
		//					if (Simon->listWeapon.size() == 0)
		//					{
		//						count = 0;
		//						count++;
		//						Simon->SetState(Simon_STATE_THROWING);
		//					}
		//				}
		//			}
		//			else if (Simon->weaponType == 4) //subweapon=stopwatch - khi ăn double shot thì ko thêm vô listWeapon
		//			{
		//				if (Simon->GetNumHeart() >= 5)
		//				{
		//					Simon->isThrow = true;
		//					Simon->isUseStopWatch = true;
		//				}
		//			}
		//		}
		//		else
		//		{
		//			Simon->isThrow = true;
		//			if (Simon->pWeapon->IsDelete() == true) //Chỉ có 1 vũ khí xuất hiện trên màn hình
		//			{
		//				if (Simon->weaponType != 4)
		//				{
		//					Simon->SetState(Simon_STATE_THROWING);
		//				}
		//				else if (Simon->weaponType == 4 && Simon->GetNumHeart() >= 5)
		//					Simon->isUseStopWatch = true;
		//			}
		//		}
		//		break;
		//	}
	}
}

void PlayScene::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	if (Simon->GetState() == Simon_STATE_DIE) return;
	if (isMoveScene) return;
	if (isMoveCamera) return;


	switch (KeyCode)
	{
	case DIK_LEFT:
		if (Simon->isOnStair)
		{
			Simon->isStopOnStair = true;
			Simon->vy = 0;
			Simon->vx = 0;
		}
		else
		{
			if (Simon->isAttack) return;
			if (Simon->isHitEnemy) return;
			if (Simon->state == Simon_STATE_SIT) return;
			Simon->SetState(Simon_STATE_IDLE);
		}
		break;

	case DIK_RIGHT:
		if (Simon->isOnStair)
		{
			Simon->isStopOnStair = true;
			Simon->vy = 0;
			Simon->vx = 0;
		}
		else
		{
			if (Simon->isAttack) return;
			if (Simon->isHitEnemy) return;
			if (Simon->state == Simon_STATE_SIT) return;
			Simon->SetState(Simon_STATE_IDLE);
		}
		break;

	case DIK_DOWN:
		//Simon->isSitting = false;
		if (Simon->isOnStair)
		{
			Simon->isStopOnStair = true;
			Simon->vy = 0;
			Simon->vx = 0;
		}
		else
		{
			if (Simon->isAttack) return;
			if (Simon->isSitAttack) return;
			if (Simon->isSitThrow) return;
			Simon->SetState(Simon_STATE_IDLE);
		}

		break;

	case DIK_UP:
		Simon->isStopOnStair = true;
		Simon->vy = 0;
		Simon->vx = 0;
		break;

	}
}

void PlayScene::LoadResources()
{
	board->SetStage(0);

	camera->SetCamera(Simon->x - SCREEN_WIDTH / 2, 0);


	grid = new Grid();

	if (scene == 1)
	{
		gameMap = new GameMap(L"textures/map/Level1Entrance.png", ID_TEX_MAP1, 40, 0);
		gameMap->LoadMap("textures/map/Level1Entrance.csv");

		ReadSprites("textures/readfile/sprites.txt");
		ReadAnimation("textures/readfile/animations.txt");
		ReadObjects("textures/readfile/ObjectScene1.txt");

		Simon->SetPosition(20, 150);

 


		for (UINT i = 0; i < listCandle.size(); i++)  //list torch/candle
		{
			grid->InsertIntoGrid(listCandle.at(i));
		}
		for (UINT i = 0; i < listBrick.size(); i++)  //list brick
		{
			grid->InsertIntoGrid(listBrick.at(i));
		}

	}
	else
	{
		listBrick.clear();
		listCandle.clear();
		listDoor.clear();
		listStair.clear();
		listEnemy.clear();
		listItem.clear();


		gameMap = new GameMap(L"textures/map/InTheCastlee1.png", ID_TEX_MAP2, 36, -4);
		gameMap->LoadMap("textures/map/InTheCastlee.csv");

		ReadSprites("textures/readfile/sprites2.txt");
		ReadAnimation("textures/readfile/animations2.txt");
		ReadObjects("textures/readfile/ObjectScene2.txt");

		Simon->SetPosition(20, 150);
		stage = 0;



		for (UINT i = 0; i < listBrick.size(); i++)
		{
			grid->InsertIntoGrid(listBrick.at(i));
		}
		for (UINT i = 0; i < listCandle.size(); i++)
		{
			grid->InsertIntoGrid(listCandle.at(i));
		}
		for (UINT i = 0; i < listStair.size(); i++)
		{
			grid->InsertIntoGrid(listStair.at(i));
		}
	}


#pragma region Animation Board

	board->AddAnimation(805);  //0
	board->AddAnimation(806);  //1
	board->AddAnimation(807);  //2
	board->AddAnimation(808);  //3
	board->AddAnimation(809);  //4
	board->AddAnimation(810);  //5
	board->AddAnimation(811);  //6
	board->AddAnimation(812);  //7
	board->AddAnimation(813);  //8 doubleshot

#pragma endregion

#pragma region Animation Simon

	Simon->AddAnimation(400);		//0 idle right big
	Simon->AddAnimation(401);		//1 idle left big
	Simon->AddAnimation(402);		//2 idle right small
	Simon->AddAnimation(403);		//3 idle left small

	Simon->AddAnimation(500);		//4  walk right big
	Simon->AddAnimation(501);		//5 walk left big
	Simon->AddAnimation(502);		//6 walk right small
	Simon->AddAnimation(600);		//7 die right

	Simon->AddAnimation(599);		//8 die left

	Simon->AddAnimation(404);	    //9 attackleft
	Simon->AddAnimation(405);		//10 attackright

	Simon->AddAnimation(504);		//11 jump left
	Simon->AddAnimation(505);       //12 jump right

	Simon->AddAnimation(406);       //13 sit left
	Simon->AddAnimation(407);		//14 sit right
	Simon->AddAnimation(408);		//15 sit attack left
	Simon->AddAnimation(409);		//16 sit attack right

	Simon->AddAnimation(410);       //17 throw left
	Simon->AddAnimation(411);		//18 throw right
	Simon->AddAnimation(412);		//19 attack type 2 left
	Simon->AddAnimation(413);		//20 attack type 2 right
	Simon->AddAnimation(414);		//21 attack type 3 left
	Simon->AddAnimation(415);		//22 attack type 3 right

	Simon->AddAnimation(416);		//23 sit attack type 2 left
	Simon->AddAnimation(417);		//24 sit attack type 2 right
	Simon->AddAnimation(418);		//25 sit attack type 3 left
	Simon->AddAnimation(419);		//26 sit attack type 3 right
	Simon->AddAnimation(420);		//27 up stair right
	Simon->AddAnimation(421);		//28 stop on stair right (up)
	Simon->AddAnimation(422);		//29 down stair left
	Simon->AddAnimation(423);		//30 stop on stair left (down)
	Simon->AddAnimation(424);		//31 hit enemy left
	Simon->AddAnimation(425);		//32 hit enemy rights
	Simon->AddAnimation(426);		//33 up stair left
	Simon->AddAnimation(427);		//34 down stair right
	Simon->AddAnimation(428);		//35 stop on stair right (down)
	Simon->AddAnimation(429);		//36 stop on stair left (up)
	Simon->AddAnimation(430);		//37 attack type 1 onstair LEFT
	Simon->AddAnimation(431);		//38 attack type 1 onstair RIGHT
	Simon->AddAnimation(432);		//39 attack type 1 upstair RIGHT
	Simon->AddAnimation(433);		//40 attack type 1 upstair LEFT
	Simon->AddAnimation(434);		//41 attack type 2 onstair LEFT
	Simon->AddAnimation(435);		//42 attack type 2 onstair RIGHT
	Simon->AddAnimation(436);		//43 attack type 2 upstair RIGHT
	Simon->AddAnimation(437);		//44 attack type 2 upstair LEFT
	Simon->AddAnimation(438);		//45 attack type 3 onstair LEFT
	Simon->AddAnimation(439);		//46 attack type 3 onstair RIGHT
	Simon->AddAnimation(440);		//47 attack type 3 upstair RIGHT
	Simon->AddAnimation(441);		//48 attack type 3 upstair LEFT
	Simon->AddAnimation(442);		//49 throw upstair left
	Simon->AddAnimation(443);		//50 throw upstair right
	Simon->AddAnimation(444);		//51 throw downstair left
	Simon->AddAnimation(445);		//52 throw downstair right
	Simon->AddAnimation(446);		//53 sit throw left
	Simon->AddAnimation(447);		//54 sit throw right
	Simon->AddAnimation(448);		//55 idle change color right
	Simon->AddAnimation(449);		//56 idle change color left

#pragma endregion


}

void PlayScene::Update(DWORD dt)
{
	//DebugOut(L"[INFO] KeyDown: %f\n", Simon->GetPosition().x);
	//

#pragma region MOVE SCENE

	if (isMoveScene)
	{
		if (isMoveCamera) //camera di chuyển khi chạm cửa
			camera->SetCamera(t++, 0);

		if (camera->GetPosition().x >= stageStartPoint) //kết thúc 
		{
			brick = new CBrick(stageStartPoint - 12, 20);
			brick->ObjectTag = CGameObject::brickblockstage2;
			grid->InsertIntoGrid(brick);
			listBrick.push_back(brick);

			isMoveScene = false;
			isMoveCamera = false;
		}

		if (Simon->x - camera->GetPosition().x <= 40)
		{
			isMoveCamera = false;
			brick = new CBrick();  //mở cửa
			brick->AddAnimation(810);
			brick->AddAnimation(817);
			brick->SetPosition(stageStartPoint, 52);
			brick->ObjectTag = CGameObject::ObjectTypes::door2ani;

			listDoor.push_back(brick);

			Simon->SetState(Simon_STATE_WALKING_RIGHT);
		}
		else if (Simon->x - camera->GetPosition().x >= 100 && isMoveCamera == false)
		{
			Simon->SetState(Simon_STATE_IDLE);
			isMoveCamera = true;
		}
	}
	else
	{
		if (stage == 2)
			camera->SetCamera(Simon->x - SCREEN_WIDTH / 2, 210);  //đi xuống nước
		else
		{
			camera->SetCamera(Simon->x - SCREEN_WIDTH / 2, 0);
		}

		t = camera->GetPosition().x - 110;
	}

#pragma endregion MOVE SCENE

#pragma region CAMERA UPDATE

	if (stage == 2)
	{
		camera->Update(dt, scene, isMoveScene, 2);
	}
	else if (stage == 1)
	{
		camera->Update(dt, scene, isMoveScene, 1);
	}
	else if (stage == 3)
	{
		camera->Update(dt, scene, isMoveScene, 3);
	}
	else if (stage == 4)
	{
		camera->Update(dt, scene, isMoveScene, 4);
	}
	else
	{
		camera->Update(dt, scene, isMoveScene, 0);
	}
#pragma endregion CAMERA UPDATE

#pragma region GET LIST_COLLISION _OBJECT FROM FRID

	grid->GetListCollisionFromGrid(camera, listColObjects);
	listCandle.clear();
	listBrick.clear();
	listStair.clear();
	for (UINT i = 0; i < listColObjects.size(); i++)
	{
		if (listColObjects.at(i)->ObjectTag == CGameObject::candle || listColObjects.at(i)->ObjectTag == CGameObject::torch)
			listCandle.push_back(listColObjects.at(i));
		else
			if (listColObjects.at(i)->ObjectTag == CGameObject::bottomstair || listColObjects.at(i)->ObjectTag == CGameObject::topstair)
				listStair.push_back(listColObjects.at(i));
			else
				listBrick.push_back(listColObjects.at(i));
	}

#pragma endregion GET LIST_COLLISION _OBJECT FROM FRID

#pragma region CHANGE COLOR WHEN SIMON HIT CROSS

	if (isChangeColor)
	{
		if (timerChangeColor < 90)
		{
			isGrey = true;
			timerChangeColor += dt;
		}
		else
		{
			isGrey = false;
			timerChangeColor = 0;
			countChangeColor++;
		}
		if (countChangeColor >= 7)
			isChangeColor = false;
	}

#pragma endregion CHANGE COLOR WHEN SIMON HIT CROSS

	board->SetStage(stage);
	board->Update(dt);
	if (board->GetTimeAlive() == 0 && Simon->state != Simon_STATE_DIE && isProcessedAfterBossDeath == false)
		Simon->SetState(Simon_STATE_DIE);

#pragma region Change STAGE

	for (int i = 0; i < listDoor.size(); i++)
	{
		if (listDoor.at(i)->ObjectTag == CGameObject::ObjectTypes::door)
		{
			if (Simon->CheckCollision(listDoor.at(i)))
			{
				scene = 2;
				LoadResources();
				return;
			}
		}
		if (CGame::GetInstance()->AABB(Simon->GetBound(), listDoor.at(i)->GetBound()))
		{
			if (listDoor.at(i)->ObjectTag == CGameObject::ObjectTypes::door2)
			{
				stage = 1;
				isMoveScene = true;
				stageStartPoint = 1522;
			}
			else if (listDoor.at(i)->ObjectTag == CGameObject::ObjectTypes::door3)
			{
				stage = 3;
				isMoveScene = true;
				stageStartPoint = 2042;
			}
			else if (listDoor.at(i)->ObjectTag == CGameObject::ObjectTypes::doortowater)
			{
				stage = 2;
				if (Simon->isUpstair)
					stage = 1;
			}
			else if (listDoor.at(i)->ObjectTag == CGameObject::ObjectTypes::doorfromwater)
			{
				if (Simon->isOnStair && stage == 1)
					stage = 2;
				if (Simon->isUpstair)
					stage = 1;


			}
		}
	}

	if (Simon->GetPosition().x > 2660) //chuyển qua màn boss
	{
		stage = 4;
	}

#pragma endregion CHANGE STAGE

	if (scene == 2)
	{
#pragma region CREATE ENEMIES

		if (Simon->x > 700 && Simon->x < 720 && isCreatePanther == true)
		{
			panther = new CPanther(Simon, 860);
			NumPantherAlive++;
			isCreatePanther = false;

			/*	panther->AddAnimation(105);
				panther->AddAnimation(106);
				panther->AddAnimation(823);*/

			panther->SetPosition(870, 86);
			panther->nx = -1;
			panther->ObjectTag = CGameObject::ObjectTypes::panther;
			panther->itemInside = CGameObject::ItemInside::iSmallHeart;

			listEnemy.push_back(panther);



			panther = new CPanther(Simon, 950);
			NumPantherAlive++;
			isCreatePanther = false;

			panther->SetPosition(940, 120);
			panther->nx = -1;
			panther->ObjectTag = CGameObject::ObjectTypes::panther;
			panther->itemInside = CGameObject::ItemInside::iSmallHeart;

			listEnemy.push_back(panther);
		}

		else if (Simon->x > 30 && Simon->x < 300 && isCreateGhoul == true)
		{
			for (int i = 0; i < 3; i++)
			{
				ghoul = new CGhoul();
				NumGhoulAlive++;

				timerGhoul = 0;
				isCreateGhoul = false;

				//ghoul->AddAnimation(104);
				ghoul->SetPosition(i * 22 + camera->GetPosition().x + 300, 165);
				ghoul->ObjectTag = CGameObject::ObjectTypes::ghoul;
				ghoul->itemInside = CGameObject::ItemInside::iSmallHeart;

				listEnemy.push_back(ghoul);
			}
		}

		else if (Simon->x > 1170 && Simon->x < 1400 && isCreateGhoul == true)
		{
			for (int i = 0; i < 3; i++)
			{
				ghoul = new CGhoul();
				NumGhoulAlive++;

				timerGhoul = 0;
				isCreateGhoul = false;


				//ghoul->AddAnimation(104);
				ghoul->SetPosition(i * 21 + camera->GetPosition().x + 280, 165);
				ghoul->ObjectTag = CGameObject::ObjectTypes::ghoul;
				ghoul->itemInside = CGameObject::ItemInside::iSmallHeart;

				listEnemy.push_back(ghoul);
			}

			ghoul = new CGhoul();
			NumGhoulAlive++;

			timerGhoul = 0;
			isCreateGhoul = false;

			//ghoul->AddAnimation(104);
			ghoul->SetFlip(true);
			ghoul->SetPosition(camera->GetPosition().x + 15, 165);
			ghoul->ObjectTag = CGameObject::ObjectTypes::ghoul;
			ghoul->itemInside = CGameObject::ItemInside::iSmallHeart;

			listEnemy.push_back(ghoul);
		}

		else if (Simon->x >= 1525 && Simon->x <= 1525 + 300 && Simon->y <= 180 && Simon->y >= 50 && isCreateBat == true)
		{
			bat = new CBat(D3DXVECTOR2(Simon->GetPosition().x, Simon->GetPosition().y + 5));  //truyền vị trí hiện tại vào
			NumBatAlive++;

			timerBat = 0;
			isCreateBat = false;


			if (Simon->nx > 0)
			{
				bat->SetPosition(Simon->GetPosition().x + 300, Simon->GetPosition().y + 5);
			}
			else if (Simon->nx < 0)
			{
				bat->SetFlip(true);
				bat->SetPosition(1530, Simon->GetPosition().y + 5);
			}

			bat->ObjectTag = CGameObject::ObjectTypes::bat;
			bat->itemInside = CGameObject::ItemInside::iSmallHeart;

			listEnemy.push_back(bat);
		}

		else if (Simon->x >= 1600 && Simon->x <= 2090 && Simon->y <= 383 && Simon->y >= 240 && isCreateFishmen == true)
		{
			fishmen = new CFishmen(Simon->GetPosition().x + 105, Simon);
			NumFishmenAlive++;

			timerFishmen = 0;
			isCreateFishmen = false;

			/*		fishmen->AddAnimation(813);
					fishmen->AddAnimation(814);
					fishmen->AddAnimation(815);*/

			fishmen->nx = -1;

			fishmen->SetPosition(Simon->GetPosition().x + 100, Simon->GetPosition().y + 120);
			fishmen->ObjectTag = CGameObject::ObjectTypes::fishmen;
			fishmen->itemInside = CGameObject::ItemInside::iNone;

			breakingRock = new CEffect();
			CSound::getInstance()->play("watereffect", false, 1);
			breakingRock->SetPosition(fishmen->GetPosition().x, fishmen->GetPosition().y + 5);
			breakingRock->AddAnimation(826);
			listEffect.push_back(breakingRock);

			listEnemy.push_back(fishmen);




			fishmen = new CFishmen(Simon->GetPosition().x - 36, Simon);
			NumFishmenAlive++;

			timerFishmen = 0;
			isCreateFishmen = false;

			fishmen->nx = 1;

			fishmen->SetPosition(Simon->GetPosition().x - 36, Simon->GetPosition().y + 110);
			fishmen->ObjectTag = CGameObject::ObjectTypes::fishmen;
			fishmen->itemInside = CGameObject::ItemInside::iSmallHeart;

			breakingRock = new CEffect();
			CSound::getInstance()->play("watereffect", false, 1);
			breakingRock->SetPosition(fishmen->GetPosition().x, fishmen->GetPosition().y + 10);
			breakingRock->AddAnimation(826);
			listEffect.push_back(breakingRock);

			listEnemy.push_back(fishmen);

		}

		else if (Simon->x >= 2122 && Simon->x <= 2200 && isCreateGhoul == true)
		{
			for (int i = 0; i < 2; i++)
			{
				ghoul = new CGhoul();
				ghoul->SetDelete(false);
				NumGhoulAlive++;

				timerGhoul = 0;
				isCreateGhoul = false;


				//ghoul->AddAnimation(104);
				ghoul->SetPosition(i * 23 + camera->GetPosition().x + 300, 100);
				ghoul->ObjectTag = CGameObject::ObjectTypes::ghoul;
				ghoul->itemInside = CGameObject::ItemInside::iNone;

				listEnemy.push_back(ghoul);
			}

			for (int i = 0; i < 2; i++)
			{
				ghoul = new CGhoul();
				ghoul->SetDelete(false);
				NumGhoulAlive++;

				timerGhoul = 0;
				isCreateGhoul = false;


				//ghoul->AddAnimation(104);
				ghoul->SetPosition(i * 23 + camera->GetPosition().x + 340, 160);
				ghoul->ObjectTag = CGameObject::ObjectTypes::ghoul;
				ghoul->itemInside = CGameObject::ItemInside::iSmallHeart;

				listEnemy.push_back(ghoul);
			}
		}
		else if (Simon->x >= 2336 && Simon->x <= 2446 && isCreateGhoul == true)
		{
			for (int i = 0; i < 2; i++)
			{
				ghoul = new CGhoul();
				ghoul->SetDelete(false);
				NumGhoulAlive++;

				timerGhoul = 0;
				isCreateGhoul = false;


				//ghoul->AddAnimation(104);
				ghoul->SetFlip(true);
				ghoul->SetPosition(camera->GetPosition().x - 22 * i, 160);

				ghoul->ObjectTag = CGameObject::ObjectTypes::ghoul;
				ghoul->itemInside = CGameObject::ItemInside::iNone;

				listEnemy.push_back(ghoul);
			}
			for (int i = 0; i < 2; i++)
			{
				ghoul = new CGhoul();
				ghoul->SetDelete(false);
				NumGhoulAlive++;

				timerGhoul = 0;
				isCreateGhoul = false;


				//ghoul->AddAnimation(104);
				ghoul->SetFlip(true);
				ghoul->SetPosition(camera->GetPosition().x - 23 * i, 100);

				ghoul->ObjectTag = CGameObject::ObjectTypes::ghoul;
				ghoul->itemInside = CGameObject::ItemInside::iNone;

				listEnemy.push_back(ghoul);
			}
		}
		else if (Simon->x >= 2505 && isCreateBoss == true)
		{
			boss = new CBoss(Simon);
			boss->SetDelete(false);
			isCreateBoss = false;
			board->SetBossPointer(boss);

			/*boss->AddAnimation(821);
			boss->AddAnimation(822);*/

			boss->SetPosition(2650, 70);
			boss->ObjectTag = CGameObject::ObjectTypes::boss;
			boss->itemInside = CGameObject::ItemInside::iNone;

			listEnemy.push_back(boss);
		}

#pragma endregion CREATE ENEMIES
	}

	/*if (Simon->isAttack == true && Simon->pWeapon->IsDelete() == false)
	{
		CheckCollision_WeaponAndEnemy();
	}
	else
		if (Simon->isSitAttack == true && Simon->pWeapon->IsDelete() == false)
		{
			CheckCollision_WeaponAndEnemy();
		}
		else*/
	if (Simon->pWeapon->IsDelete() == false)  //subweapon
	{
		CheckCollision_WeaponAndEnemy();
	}
	else
		if (Simon->weaponType == 4 && Simon->isUseStopWatch == true) //Nếu dùng đồng hồ thì mất tim và set freeze cho enemy
		{
			CSound::getInstance()->play("stopwatch", false, 1);
			Simon->SetNumHeart(-5);
			Simon->isUseStopWatch = false;
			startTimeFreeze = GetTickCount();
			isFreeze = true;
		}


	if (Simon->isAttack == true && Simon->pWhip->IsDelete() == false)
	{
		CheckCollision_WhipAndEnemy();
	}
	else
		if (Simon->isSitAttack == true && Simon->pWhip->IsDelete() == false)
		{
			CheckCollision_WhipAndEnemy();
		}
		else
			if (Simon->pWhip->IsDelete() == false)
			{
				CheckCollision_WhipAndEnemy();
			}


	CheckCollision_ItemAndSimon();
	CheckCollision_SimonAndEnemy();


	Simon->Update(dt, &listBrick); 	//listBrick chua' brick

#pragma region Adjust Simon with the whole map

	if (Simon->x <= 0)
		Simon->x = 1;

	if (stage == 4)
	{
		if (Simon->x <= 2505)
			Simon->x = 2505;

		if (Simon->x >= 2786)
			Simon->x = 2786;
	}
	//else
	//	if (stage == 3 && Simon->x <= 2044 && isMoveScene == false)
	//		Simon->x = 2044;
		//else
		//	if (stage == 1 && Simon->x <= 1528 && isMoveScene == false)
		//		Simon->x = 1528;

#pragma endregion Adjust Simon with the whole map

#pragma region SIMON UNTOUCHABLE WHEN HIT ENEMY

	if (Simon->isUntouchable) //set thgian untouchable
	{
		if (timerUntouachable < 2000)
			timerUntouachable += dt;
		else
		{
			timerUntouachable = 0;
			Simon->isUntouchable = false;
		}
	}
#pragma endregion SIMON UNTOUCHABLE WHEN HIT ENEMY

#pragma region SIMON INVISIBLE

	if (Simon->isInvisible) //set thgian untouchable
	{
		if (timerInvisible < 5000)
			timerInvisible += dt;
		else
		{
			timerInvisible = 0;
			Simon->isInvisible = false;
		}
	}

#pragma endregion SIMON INVISIBLE


	for (UINT i = 0; i < listEffect.size(); i++)
	{
		if (listEffect.at(i)->IsDelete() == true)
			listEffect.erase(listEffect.begin() + i);
		else
			listEffect.at(i)->Update(dt);
	}

	for (UINT i = 0; i < listItem.size(); i++)
	{
		if (listItem[i]->IsDelete() == false)
			listItem[i]->Update(dt, &listBrick);
	}

	for (UINT i = 0; i < listBrick.size(); i++)  //list brick
	{
		if (listBrick.at(i)->ObjectTag == CGameObject::ObjectTypes::blackbrickchicken)
		{
			if (Simon->isBreakRockChicken)
			{
				listBrick.at(i)->SetDelete(true);

				Simon->isBreakRockChicken = false;
			}
		}
		else if (listBrick.at(i)->ObjectTag == CGameObject::ObjectTypes::blackbrickmoney)
		{
			if (Simon->isBreakRock)
			{
				listBrick.at(i)->SetDelete(true);

				Simon->isBreakRock = false;
			}
		}
	}

	//DebugOut(L"N colObj: %d\n", listCandle.size() + listBrick.size());

	for (UINT i = 0; i < listCandle.size(); i++)
	{
		if (listCandle[i]->IsDelete() == false)
			listCandle[i]->Update(dt, &listBrick);
	}

	for (UINT i = 0; i < listEnemy.size(); i++)
	{
		listEnemy[i]->Update(dt, &listBrick);

		if (Simon->isRevive) //Nếu revive mà gạch đã đc đánh để ăn gà thì sẽ refresh lại 
		{
			if (listEnemy.at(i)->ObjectTag == CGameObject::ObjectTypes::brickchicken || listEnemy.at(i)->ObjectTag == CGameObject::ObjectTypes::brickmoney)
			{
				if (listEnemy.at(i)->IsDelete())
					listEnemy.at(i)->SetDelete(false);
			}
		}

		if (listEnemy.at(i)->ObjectTag == CGameObject::ObjectTypes::fishmen)
		{
			if (listEnemy.at(i)->IsDelete() == false)
			{
				if (listEnemy.at(i)->GetState() == 20)  //state attack
				{
					if (listEnemy.at(i)->animations[2]->GetCurrentFrame() == 0 && listEnemy.at(i)->isCreateFireBall == true)
					{
						listEnemy.at(i)->isCreateFireBall = false;
						fireball = new CFireBall();
						fireball->AddAnimation(816);
						fireball->SetDelete(false);  //cho phép xét va chạm
						fireball->ObjectTag = CGameObject::ObjectTypes::fireball;


						if (listEnemy.at(i)->nx == -1)
						{
							fireball->SetPosition(listEnemy.at(i)->x - 6, listEnemy.at(i)->y + 8);
							fireball->SetFlip(false);
						}
						else
						{
							fireball->SetPosition(listEnemy.at(i)->x, listEnemy.at(i)->y + 8);
							fireball->SetFlip(true);
						}

						listEnemy.push_back(fireball);
					}
				}
			}
		}

		if (isKillEnemyOnScreen || Simon->isRevive)
		{
			if (listEnemy.at(i)->IsDelete() == false)
			{
				if (listEnemy.at(i)->GetPosition().x >= camera->GetPosition().x && listEnemy.at(i)->GetPosition().x <= camera->GetPosition().x + 320)
				{
					if (listEnemy.at(i)->ObjectTag != CGameObject::ObjectTypes::candle && listEnemy.at(i)->ObjectTag != CGameObject::ObjectTypes::brickchicken
						&& listEnemy.at(i)->ObjectTag != CGameObject::ObjectTypes::brickmoney)
					{
						listEnemy.at(i)->SetDelete(true);
						listEnemy.at(i)->SetIsOutOfCamera(true);
					}
				}
			}
		}

		if (Simon->isEatingItem)
		{
			if (listEnemy.at(i)->IsDelete() == false)
			{
				if (listEnemy.at(i)->ObjectTag != CGameObject::ObjectTypes::boss)
					listEnemy.at(i)->SetStop(true);
			}
		}
		else
		{
			if (listEnemy.at(i)->IsDelete() == false)
			{
				listEnemy.at(i)->SetStop(false);
			}
		}

		if (isFreeze)
		{
			if (listEnemy.at(i)->IsDelete() == false)
			{
				if (listEnemy.at(i)->ObjectTag != CGameObject::ObjectTypes::boss)
					listEnemy.at(i)->SetFreeze(true);
			}

			if (GetTickCount() - startTimeFreeze >= Enemy_FREEZE_TIME)
			{
				isFreeze = false;
			}
		}
		else
		{
			if (listEnemy.at(i)->IsDelete() == false)
			{
				listEnemy.at(i)->SetFreeze(false);
			}
		}


		if (listEnemy.at(i)->ObjectTag == CGameObject::ObjectTypes::ghoul && listEnemy.at(i)->IsOutOfCamera())
		{
			if (NumGhoulAlive > 0)
			{
				NumGhoulAlive--;
				listEnemy.at(i)->SetIsOutOfCamera(false);
			}
		}
		else if (listEnemy.at(i)->ObjectTag == CGameObject::ObjectTypes::panther && listEnemy.at(i)->IsOutOfCamera())
		{
			if (NumPantherAlive > 0)
			{
				NumPantherAlive--;
				listEnemy.at(i)->SetIsOutOfCamera(false);
			}
		}
		else if (listEnemy.at(i)->ObjectTag == CGameObject::ObjectTypes::bat && listEnemy.at(i)->IsOutOfCamera())
		{
			if (NumBatAlive > 0)
			{
				NumBatAlive--;
				listEnemy.at(i)->SetIsOutOfCamera(false);
			}
		}
		else if (listEnemy.at(i)->ObjectTag == CGameObject::ObjectTypes::fishmen && listEnemy.at(i)->IsOutOfCamera())
		{
			if (NumFishmenAlive > 0)
			{
				NumFishmenAlive--;
				listEnemy.at(i)->SetIsOutOfCamera(false);
			}
		}
	}
	isKillEnemyOnScreen = false;


	if (NumGhoulAlive == 0 && ((Simon->x > 30 && Simon->x < 300) || (Simon->x > 1170 && Simon->x < 1400) || (Simon->x >= 2122 && Simon->x <= 2200) || (Simon->x >= 2336 && Simon->x <= 2446)))
		timerGhoul += dt;
	if (timerGhoul >= 2000)
		isCreateGhoul = true;

	if (NumPantherAlive == 0 && Simon->x > 700 && Simon->x < 720)
		isCreatePanther = true;

	if (NumBatAlive == 0 && Simon->x >= 1525 && Simon->x <= 1525 + 300 && Simon->y <= 180 && Simon->y >= 50)
		timerBat += dt;
	if (timerBat >= 1200)
		isCreateBat = true;

	if (NumFishmenAlive == 0 && (Simon->x > 1600 && Simon->x < 2090 && Simon->y >= 240))
		timerFishmen += dt;
	if (timerFishmen >= 1500)
		isCreateFishmen = true;

#pragma region CRYSTAL APPEAR

	if (boss && boss->isDead)
	{
		if (timerAppearCrystalBall < 2500)
			timerAppearCrystalBall += dt;
		else
		{
			boss->isDead = false;
			item = new CItem();
			item->ObjectTag = CGameObject::ObjectTypes::crystalball;
			item->AddAnimation(830);
			item->SetPosition(2650, 120);
			listItem.push_back(item);
		}

	}

#pragma endregion CRYSTAL APPEAR

#pragma region SET EFFECT FALLING INTO WATER

	if (Simon->y >= 370 && Simon->y <= 400)
	{
		Simon->SetPosition(Simon->GetPosition().x, 600);

		breakingRock = new CEffect();
		CSound::getInstance()->play("watereffect", false, 1);
		breakingRock->AddAnimation(826);
		breakingRock->SetPosition(Simon->GetPosition().x, 370);
		listEffect.push_back(breakingRock);
	}

#pragma endregion SET EFFECT FALLING INTO WATER

#pragma region SIMON REVIVE

	grid->CheckSimonRevive(Simon->isRevive);

	if (Simon->isRevive)
	{
		Simon->isRevive = false;

		Simon->SetDelete(false);
		Simon->SetState(Simon_STATE_IDLE);
		Simon->SetNumHP(16 - Simon->GetNumHP());
		Simon->pWhip->SetWhipType(0);
		Simon->weaponType = 0;
		Simon->numLife--;
		Simon->isThrowDouble = false;
		board->SetTimer(300);

		if (Simon->GetNumLife() < 0)
		{
			Simon->SetNumLife(3 + 1);
			scene = 1;
			LoadResources();
			stage = 0; //scene1
			//Simon->SetPosition(10, 150);

			return;
		}
		else
		{
			if (stage == 0)
			{
				Simon->SetPosition(10, 150);
			}
			else if (stage == 1 || stage == 2)
			{
				stage = 1;
				Simon->SetPosition(1530, 10);
			}
			else if (stage == 3 || stage == 4)
			{
				stage = 3;
				Simon->SetPosition(2060, 20);
				boss->SetDelete(true);
				isCreateBoss = true;
			}
		}
	}

#pragma endregion SIMON REVIVE

}

void PlayScene::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		//d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		if (isGrey)
			d3ddv->ColorFill(bb, NULL, D3DCOLOR_XRGB(128, 128, 128));
		else
			d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);


		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);


		//draw map
		gameMap->DrawMap(camera);

		//draw brick/stair
		for (UINT i = 0; i < listBrick.size(); i++) //brick
		{
			listBrick[i]->Render(camera);
		}

		//draw items
		for (UINT i = 0; i < listItem.size(); i++)
		{
			if (listItem.at(i)->IsDelete() == false)
				listItem[i]->Render(camera);
		}

		//draw candle
		for (UINT i = 0; i < listCandle.size(); i++)
		{
			listCandle.at(i)->Render(camera);
		}

		//draw list door
		for (UINT i = 0; i < listDoor.size(); i++)
		{
			listDoor.at(i)->Render(camera);
		}

		//draw enemy
		for (UINT i = 0; i < listEnemy.size(); i++)
		{
			if (isKillEnemyOnScreen)
			{
				listEnemy.at(i)->SetDelete(true);
			}

			if (listEnemy.at(i)->IsDelete() == false)
				listEnemy[i]->Render(camera);
		}
		isKillEnemyOnScreen = false;


		//draw box stair
		for (UINT i = 0; i < listStair.size(); i++)
		{
			listStair.at(i)->Render(camera);
		}

		//draw listeffect
		for (int i = 0; i < listEffect.size(); i++)
			if (listEffect.at(i)->IsDelete() == false)
				listEffect.at(i)->Render(camera);

		//draw simon
		Simon->Render(camera);

		//draw board
		board->Render(camera);



		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void PlayScene::CheckCollision_SimonAndEnemy()
{
	if (Simon->state == Simon_STATE_DIE)
		return;

	for (UINT i = 0; i < listEnemy.size(); i++)
	{
		if (listEnemy.at(i)->ObjectTag != CGameObject::ObjectTypes::candle && listEnemy.at(i)->ObjectTag != CGameObject::ObjectTypes::brickchicken
			&& listEnemy.at(i)->ObjectTag != CGameObject::ObjectTypes::brickmoney)
		{
			if (listEnemy.at(i)->IsDelete() == false)
			{
				if (Simon->isUntouchable == false && Simon->isInvisible == false)
				{
					LPCOLLISIONEVENT e = Simon->SweptAABBEx(listEnemy.at(i));

					if (e->t > 0 && e->t <= 1.0f)
					{
						if (listEnemy.at(i)->ObjectTag == CGameObject::ObjectTypes::bat) //nếu dơi đụng simon thì dơi biến mất
						{
							listEnemy.at(i)->SetDelete(true);
							NumBatAlive--;


							breakingRock = new CEffect();
							breakingRock->SetPosition(listEnemy.at(i)->GetPosition());
							breakingRock->AddAnimation(828);
							listEffect.push_back(breakingRock);
						}

						if (Simon->isOnStair == false)
						{
							if (e->nx == -1)
							{
								Simon->isHitLeft = false;
							}
							else
								if (e->nx == 1)
								{
									Simon->isHitLeft = true;
								}

							Simon->SetState(Simon_STATE_HIT_ENEMY);
						}

						if (Simon->GetNumHP() > 0)
							Simon->SetNumHP(-1);
						Simon->isHitEnemy = true;
						Simon->isUntouchable = true;
					}
					else if (CGame::GetInstance()->AABB(Simon->GetBound(), listEnemy.at(i)->GetBound()))
					{
						if (listEnemy.at(i)->ObjectTag == CGameObject::ObjectTypes::bat) //nếu dơi đụng simon thì dơi biến mất
						{
							listEnemy.at(i)->SetDelete(true);
							NumBatAlive--;

							breakingRock = new CEffect();
							breakingRock->SetPosition(listEnemy.at(i)->GetPosition());
							breakingRock->AddAnimation(828);
							listEffect.push_back(breakingRock);
						}

						if (Simon->isOnStair == false)
						{
							if (Simon->x < listEnemy.at(i)->x)
								Simon->isHitLeft = false;
							else
								Simon->isHitLeft = true;

							Simon->SetState(Simon_STATE_HIT_ENEMY);
						}

						if (Simon->GetNumHP() > 0)
							Simon->SetNumHP(-1);
						Simon->isHitEnemy = true;
						Simon->isUntouchable = true;

					}

				}
			}
		}
	}
}

void PlayScene::CheckCollision_WeaponAndEnemy()
{
	bool res = false;
	bool res1 = false;

	for (UINT i = 0; i < listEnemy.size(); i++)
	{
		if (Simon->isThrowDouble)
		{
			for (UINT j = 0; j < Simon->listWeapon.size(); j++)
			{
				if (j == 0)
					res = Simon->listWeapon.at(j)->CheckCollision(listEnemy.at(i));
				if (j == 1)
					res1 = Simon->listWeapon.at(1)->CheckCollision(listEnemy.at(i));

			}
		}
		else
		{
			res = Simon->pWeapon->CheckCollision(listEnemy.at(i));
		}


		if (listEnemy.at(i)->IsDelete() == false)
		{
			if (res == true || res1 == true)
			{
				if (Simon->weaponType == 1)
					Simon->pWeapon->SetDelete(true);

				if (listEnemy.at(i)->ObjectTag == CGameObject::ObjectTypes::boss && Simon->isDamageBoss == true)
				{
					breakingRock = new CEffect();
					breakingRock->SetPosition(listEnemy.at(i)->GetPosition());
					breakingRock->AddAnimation(828);
					listEffect.push_back(breakingRock);

					if (boss->GetHP() > 0)
					{
						boss->SetHP(-2);
						Simon->isDamageBoss = false;

						if (boss->GetHP() <= 0)
						{
							listEnemy.at(i)->SetDelete(true);
							boss->isDead = true;

							breakingRock = new CEffect();
							breakingRock->ObjectTag = CGameObject::ObjectTypes::effectbossdie;
							breakingRock->SetPosition(listEnemy.at(i)->GetPosition());
							breakingRock->AddAnimation(829);
							listEffect.push_back(breakingRock);
						}
					}
					continue;
				}

				if (listEnemy.at(i)->itemInside == CGameObject::ItemInside::iNone)
				{
					if (listEnemy.at(i)->ObjectTag == CGameObject::ObjectTypes::boss)
						continue;
					else
					{
						item = new CItem();
						item->ObjectTag = CGameObject::ObjectTypes::None;
					}

				}
				else if (listEnemy.at(i)->itemInside == CGameObject::ItemInside::iHeart)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::largeheart;
					item->AddAnimation(800);
				}
				else if (listEnemy.at(i)->itemInside == CGameObject::ItemInside::iDagger)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::dagger;
					item->AddAnimation(801);
				}
				else if (listEnemy.at(i)->itemInside == CGameObject::ItemInside::iStopWatch)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::stopwatch;
					item->AddAnimation(803);
				}
				else if (listEnemy.at(i)->itemInside == CGameObject::ItemInside::iSmallHeart)
				{
					item = new CItem(listEnemy.at(i)->GetPosition());
					item->ObjectTag = CGameObject::ObjectTypes::smallheart;
					item->AddAnimation(834);
				}
				else if (listEnemy.at(i)->itemInside == CGameObject::ItemInside::iChicken)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::chicken;
					item->SetPosition(1785, 182);
					item->AddAnimation(812);

					breakingRock = new CEffect();
					breakingRock->SetPosition(listEnemy.at(i)->GetPosition());
					breakingRock->AddAnimation(811);
					listEffect.push_back(breakingRock);
					Simon->isBreakRockChicken = true;
				}
				else if (listEnemy.at(i)->itemInside == CGameObject::ItemInside::iMoney)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::whitemoneybag;
					item->SetPosition(1004, 134);
					item->AddAnimation(818);


					breakingRock = new CEffect();
					breakingRock->SetPosition(listEnemy.at(i)->GetPosition());
					breakingRock->AddAnimation(811);
					listEffect.push_back(breakingRock);
					Simon->isBreakRock = true;
				}


				if (listEnemy.at(i)->ObjectTag == CGameObject::ObjectTypes::ghoul)
					NumGhoulAlive--;
				else if (listEnemy.at(i)->ObjectTag == CGameObject::ObjectTypes::panther)
					NumPantherAlive--;
				else if (listEnemy.at(i)->ObjectTag == CGameObject::ObjectTypes::bat)
					NumBatAlive--;
				else if (listEnemy.at(i)->ObjectTag == CGameObject::ObjectTypes::fishmen)
					NumFishmenAlive--;


				if (listEnemy.at(i)->itemInside != CGameObject::ItemInside::iChicken && listEnemy.at(i)->itemInside != CGameObject::ItemInside::iMoney)
				{
					item->SetPosition(listEnemy.at(i)->GetPosition()); //set vị trí cho itemiside xuất hiện

					//effect
					breakingRock = new CEffect();
					breakingRock->SetPosition(listEnemy.at(i)->GetPosition());
					breakingRock->AddAnimation(827);
					listEffect.push_back(breakingRock);
					//effect
				}
				listItem.push_back(item);
				listEnemy.at(i)->SetDelete(true); //delete enemy
			}
		}
	}



	for (UINT i = 0; i < listCandle.size(); i++)
	{
		if (Simon->isThrowDouble)
		{
			for (UINT j = 0; j < Simon->listWeapon.size(); j++)
			{
				if (j == 0)
					res = Simon->listWeapon.at(j)->CheckCollision(listCandle.at(i));
				if (j == 1)
					res1 = Simon->listWeapon.at(1)->CheckCollision(listCandle.at(i));
			}
		}
		else
		{
			res = Simon->pWeapon->CheckCollision(listCandle.at(i));
		}

		if (listCandle.at(i)->IsDelete() == false)
		{
			if (res == true || res1 == true)
			{
				if (Simon->weaponType == 1)
					Simon->pWeapon->SetDelete(true);

				if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iStopWatch)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::stopwatch;
					item->AddAnimation(803);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iSmallHeart)
				{
					item = new CItem(listCandle.at(i)->GetPosition());
					item->ObjectTag = CGameObject::ObjectTypes::smallheart;
					item->AddAnimation(834);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iHeart)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::largeheart;
					item->AddAnimation(800);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iWhipUpgrade)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::whipupgrade;
					item->AddAnimation(802);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iDagger)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::dagger;
					item->AddAnimation(801);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iPurpleMoneyBag)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::purplemoneybag;
					item->AddAnimation(831);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iRedMoneyBag)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::redmoneybag;
					item->AddAnimation(832);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iHolyWater)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::holywater;
					item->AddAnimation(806);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iCross)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::cross;
					item->AddAnimation(809);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iAxe)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::axe;
					item->AddAnimation(820);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iDoubleShot)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::doubleshot;
					item->AddAnimation(824);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iPotion)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::potion;
					item->AddAnimation(825);
				}

				breakingRock = new CEffect();
				breakingRock->SetPosition(listCandle.at(i)->GetPosition());
				breakingRock->AddAnimation(827);
				listEffect.push_back(breakingRock);

				item->SetPosition(listCandle.at(i)->GetPosition());

				listItem.push_back(item);

				listCandle.at(i)->SetDelete(true); //delete candle
			}
		}
	}
}

void PlayScene::CheckCollision_WhipAndEnemy()
{
	for (UINT i = 0; i < listEnemy.size(); i++)
	{
		if (listEnemy.at(i)->IsDelete() == false)
		{
			if (Simon->pWhip->CheckCollision(listEnemy.at(i)))
			{
				if (listEnemy.at(i)->ObjectTag == CGameObject::boss && Simon->isDamageBoss == true)
				{
					breakingRock = new CEffect();
					breakingRock->SetPosition(listEnemy.at(i)->GetPosition());
					breakingRock->AddAnimation(828);
					listEffect.push_back(breakingRock);

					if (boss->GetHP() > 0)
					{
						Simon->isDamageBoss = false;
						boss->SetHP(-2);


						if (boss->GetHP() <= 0)
						{
							listEnemy.at(i)->SetDelete(true);
							boss->isDead = true;

							breakingRock = new CEffect();
							breakingRock->ObjectTag = CGameObject::effectbossdie;
							breakingRock->SetPosition(listEnemy.at(i)->GetPosition());
							breakingRock->AddAnimation(829);
							listEffect.push_back(breakingRock);
						}
					}
					continue;
				}
				if (listEnemy.at(i)->itemInside == CGameObject::iNone)
				{
					if (listEnemy.at(i)->ObjectTag == CGameObject::boss)
						continue;
					else
					{
						item = new CItem();
						item->ObjectTag = CGameObject::None;
					}
				}
				else if (listEnemy.at(i)->itemInside == CGameObject::iSmallHeart)
				{
					item = new CItem(listEnemy.at(i)->GetPosition());
					item->ObjectTag = CGameObject::ObjectTypes::smallheart;
					item->AddAnimation(834);
				}
				else if (listEnemy.at(i)->itemInside == CGameObject::iChicken)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::chicken;
					item->SetPosition(1785, 182);
					item->AddAnimation(812);


					breakingRock = new CEffect();
					breakingRock->SetPosition(listEnemy.at(i)->GetPosition());
					breakingRock->AddAnimation(811);
					listEffect.push_back(breakingRock);
					Simon->isBreakRockChicken = true;
				}
				else if (listEnemy.at(i)->itemInside == CGameObject::iMoney)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::whitemoneybag;
					item->SetPosition(1004, 134);
					item->AddAnimation(818);

					breakingRock = new CEffect();
					breakingRock->SetPosition(listEnemy.at(i)->GetPosition());
					breakingRock->AddAnimation(811);
					listEffect.push_back(breakingRock);
					Simon->isBreakRock = true;
				}


				if (listEnemy.at(i)->ObjectTag == CGameObject::ghoul)
					NumGhoulAlive--;
				else if (listEnemy.at(i)->ObjectTag == CGameObject::panther)
					NumPantherAlive--;
				else if (listEnemy.at(i)->ObjectTag == CGameObject::bat)
					NumBatAlive--;
				else if (listEnemy.at(i)->ObjectTag == CGameObject::fishmen)
					NumFishmenAlive--;



				if (listEnemy.at(i)->itemInside != CGameObject::iChicken && listEnemy.at(i)->itemInside != CGameObject::iMoney)
				{
					item->SetPosition(listEnemy.at(i)->GetPosition());

					breakingRock = new CEffect();
					breakingRock->SetPosition(listEnemy.at(i)->GetPosition());
					breakingRock->AddAnimation(827);
					listEffect.push_back(breakingRock);
				}

				listItem.push_back(item);

				listEnemy.at(i)->SetDelete(true); //delete enemy
			}
		}
	}



	for (UINT i = 0; i < listCandle.size(); i++)
	{
		if (listCandle.at(i)->IsDelete() == false)
		{
			if (Simon->pWhip->CheckCollision(listCandle.at(i)))
			{
				if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iStopWatch)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::stopwatch;
					item->AddAnimation(803);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iHeart)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::largeheart;
					item->AddAnimation(800);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iSmallHeart)
				{
					item = new CItem(listCandle.at(i)->GetPosition());
					item->ObjectTag = CGameObject::ObjectTypes::smallheart;
					item->AddAnimation(834);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iDagger)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::dagger;
					item->AddAnimation(801);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iWhipUpgrade)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::whipupgrade;
					item->AddAnimation(802);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iPurpleMoneyBag)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::purplemoneybag;
					item->AddAnimation(831);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iRedMoneyBag)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::redmoneybag;
					item->AddAnimation(832);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iHolyWater)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::holywater;
					item->AddAnimation(806);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iCross)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::cross;
					item->AddAnimation(809);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iAxe)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::axe;
					item->AddAnimation(820);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iDoubleShot)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::doubleshot;
					item->AddAnimation(824);
				}
				else if (listCandle.at(i)->itemInside == CGameObject::ItemInside::iPotion)
				{
					item = new CItem();
					item->ObjectTag = CGameObject::ObjectTypes::potion;
					item->AddAnimation(825);
				}

				item->SetPosition(listCandle.at(i)->GetPosition());

				breakingRock = new CEffect();
				breakingRock->SetPosition(listCandle.at(i)->GetPosition());
				breakingRock->AddAnimation(827);
				listEffect.push_back(breakingRock);

				listItem.push_back(item);

				listCandle.at(i)->SetDelete(true); //delete candle
			}
		}
	}
}

void PlayScene::CheckCollision_ItemAndSimon()
{
	for (UINT i = 0; i < listItem.size(); i++)
	{
		if (listItem.at(i)->IsDelete() == false)
		{
			if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::breakingrock)
				continue;
			if (Simon->CheckCollision(listItem.at(i)))
			{

				CSound::getInstance()->play("collectitem", false, 1);

				if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::whipupgrade)
				{
					Simon->isEatingItem = true;

					if (Simon->pWhip->isWhipType(0))
						Simon->pWhip->SetWhipType(1);
					else if (Simon->pWhip->isWhipType(1))
						Simon->pWhip->SetWhipType(2);
				}
				else if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::smallheart)
				{
					Simon->SetNumHeart(1);
				}
				else if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::largeheart)
				{
					Simon->SetNumHeart(5);
				}
				else if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::dagger)
				{
					Simon->weaponType = 1;
				}
				else if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::holywater)
				{
					Simon->weaponType = 2;
				}
				else if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::cross)
				{
					CSound::getInstance()->play("holycross", false, 1);
					isKillEnemyOnScreen = true;
					isChangeColor = true;
				}
				else if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::chicken)
				{
					if (Simon->GetNumHP() < 16)
						Simon->SetNumHP(16 - Simon->GetNumHP());
				}
				else if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::axe)
				{
					Simon->weaponType = 3;
				}
				else if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::stopwatch)
				{
					Simon->weaponType = 4;
				}
				else if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::doubleshot)
				{
					Simon->isThrowDouble = true;
				}
				else if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::potion)
				{
					Simon->isInvisible = true;
				}
				else if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::purplemoneybag)
				{
					Simon->SetScore(400);

				}
				else if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::redmoneybag)
				{
					Simon->SetScore(100);
				}
				else if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::whitemoneybag)
				{
					Simon->SetScore(700);
				}
				else if (listItem.at(i)->ObjectTag == CGameObject::ObjectTypes::crystalball)
				{
					ProcessAfterBossDeath();
				}

				listItem.at(i)->SetDelete(true);
			}
		}
	}
}

void PlayScene::ProcessAfterBossDeath()
{
	isProcessedAfterBossDeath = true;
	Simon->SetNumHP(16 - Simon->GetNumHP());
	board->isDecreaseTimer = true;

}

void PlayScene::ReadSprites(const char * path)
{
	int id, left, top, right, bottom, idTextures;

	FILE* pFile;
	pFile = fopen(path, "r");
	while (!feof(pFile))
	{

		fscanf(pFile, "%d %d %d %d %d %d", &id, &left, &top, &right, &bottom, &idTextures);

		LPDIRECT3DTEXTURE9 textemp = NULL;

		switch (idTextures)
		{
		case ID_TEX_Simon:
			textemp = texSimon;
			break;
		case ID_TEX_ENEMY:
			textemp = texEnemy;
			break;
		case ID_TEX_OBJECT:
			textemp = texObject;
			break;
		case ID_TEX_ITEM:
			textemp = texItem;
			break;
		case ID_TEX_BOARD:
			textemp = texBoard;
			break;
		}
		sprites->Add(id, left, top, right, bottom, textemp);
	}

	fclose(pFile);
}

void PlayScene::ReadAnimation(const char * path)
{
	int time, idAni, numRow;

	FILE* pFile;
	pFile = fopen(path, "r");
	while (!feof(pFile))
	{
		fscanf(pFile, "%d %d %d", &time, &idAni, &numRow);

		int idSprite[10];
		for (int i = 0; i < numRow; i++)
		{
			fscanf(pFile, "%d", &idSprite[i]);
		}

		ani = new CAnimation(time);
		for (int i = 0; i < numRow; i++)
		{
			ani->Add(idSprite[i]);
		}

		animations->Add(idAni, ani);
	}

	fclose(pFile);
}

void PlayScene::ReadObjects(const char * path)
{
	int type, itemInIt, objectTag;
	float x, y;
	FILE* pFile;
	pFile = fopen(path, "r");

	while (!feof(pFile))
	{
		fscanf(pFile, "%d %d %d %f %f", &type, &itemInIt, &objectTag, &x, &y);
		CGameObject *tmp = nullptr;

		switch (type)
		{
		case 0: //torch
			tmp = new CTorch(x, y);
			tmp->AddAnimation(102);
			break;
		case 1: //brick
			tmp = new CBrick(x, y);
			break;
		case 2: //candle
			tmp = new CCandle(x, y);
			tmp->AddAnimation(103);
			break;
		case 100: //stair
			tmp = new CBrick(x, y);
			tmp->StairTag = CGameObject::StairTypes::ToRight;
			break;
		case -100: //stair
			tmp = new CBrick(x, y);
			tmp->StairTag = CGameObject::StairTypes::ToLeft;
			break;
		}

		switch (itemInIt)
		{
		case 0:
			tmp->itemInside = CGameObject::ItemInside::iHeart;
			break;
		case 1:
			tmp->itemInside = CGameObject::ItemInside::iWhipUpgrade;
			break;
		case 2:
			tmp->itemInside = CGameObject::ItemInside::iDagger;
			break;
		case 3:
			tmp->itemInside = CGameObject::ItemInside::iStopWatch;
			break;
		case 4:
			tmp->itemInside = CGameObject::ItemInside::iSmallHeart;
			break;
		case 5:
			tmp->itemInside = CGameObject::ItemInside::iHolyWater;
			break;
		case 6:
			tmp->itemInside = CGameObject::ItemInside::iCross;
			break;
		case 7:
			tmp->itemInside = CGameObject::ItemInside::iAxe;
			break;
		case 8:
			tmp->itemInside = CGameObject::ItemInside::iDoubleShot;
			break;
		case 9:
			tmp->itemInside = CGameObject::ItemInside::iPotion;
			break;
		case 10:
			tmp->itemInside = CGameObject::ItemInside::iPurpleMoneyBag;
			break;
		case 11:
			tmp->itemInside = CGameObject::ItemInside::iRedMoneyBag;
			break;
		case 12:
			tmp->itemInside = CGameObject::ItemInside::iChicken;
			break;
		case 13:
			tmp->itemInside = CGameObject::ItemInside::iMoney;
			break;
		defaul:
			break;
		}

		switch (objectTag)
		{
		case 0:
			tmp->ObjectTag = CGameObject::ObjectTypes::torch;
			break;
		case 1:
			tmp->ObjectTag = CGameObject::ObjectTypes::brick;
			break;
		case 2:
			tmp->ObjectTag = CGameObject::ObjectTypes::door;
			break;
		case 3:
			tmp->ObjectTag = CGameObject::ObjectTypes::brickscene2;
			break;
		case 4:
			tmp->ObjectTag = CGameObject::ObjectTypes::candle;
			break;
		case 5:
			tmp->ObjectTag = CGameObject::ObjectTypes::floatingbrick1;
			break;
		case 6:
			tmp->ObjectTag = CGameObject::ObjectTypes::floatingbrick2;
			break;
		case 7:
			tmp->ObjectTag = CGameObject::ObjectTypes::floatingbrick3;
			break;
		case 8:
			tmp->ObjectTag = CGameObject::ObjectTypes::floatingbrick4;
			break;
		case 9:
			tmp->ObjectTag = CGameObject::ObjectTypes::brickblockstage2;
			break;
		case 10:
			tmp->ObjectTag = CGameObject::ObjectTypes::door2;
			break;
		case 11:
			tmp->ObjectTag = CGameObject::ObjectTypes::blackbrickchicken;
			break;
		case 12:
			tmp->ObjectTag = CGameObject::ObjectTypes::floatingbrick9;
			break;
		case 13:
			tmp->ObjectTag = CGameObject::ObjectTypes::floatingbrick10;
			break;
		case 14:
			tmp->ObjectTag = CGameObject::ObjectTypes::brickchicken;
			tmp->AddAnimation(108);
			break;
		case 15:
			tmp->ObjectTag = CGameObject::ObjectTypes::bottomstair;
			break;
		case 16:
			tmp->ObjectTag = CGameObject::ObjectTypes::topstair;
			break;
		case 17:
			tmp->ObjectTag = CGameObject::ObjectTypes::floatingbrick6;
			break;
		case 18:
			tmp->ObjectTag = CGameObject::ObjectTypes::floatingbrick5;
			break;
		case 19:
			tmp->ObjectTag = CGameObject::ObjectTypes::floatingbrick7;
			break;
		case 20:
			tmp->ObjectTag = CGameObject::ObjectTypes::doorfromwater;
			break;
		case 21:
			tmp->ObjectTag = CGameObject::ObjectTypes::doortowater;
			break;
		case 22:
			tmp->ObjectTag = CGameObject::ObjectTypes::door3;
			break;
		case 23:
			tmp->ObjectTag = CGameObject::ObjectTypes::blackbrickmoney;
			break;
		case 24:
			tmp->ObjectTag = CGameObject::ObjectTypes::brickmoney;
			tmp->AddAnimation(109);
			break;
		case 25:
			tmp->ObjectTag = CGameObject::ObjectTypes::floatingbrick8;
			break;
		case 26:
			tmp->ObjectTag = CGameObject::ObjectTypes::floatingbrick11;
			break;
		}

		if (tmp->ObjectTag == CGameObject::ObjectTypes::torch || tmp->ObjectTag == CGameObject::ObjectTypes::candle)
			listCandle.push_back(tmp);
		else if (tmp->ObjectTag == CGameObject::ObjectTypes::bottomstair || tmp->ObjectTag == CGameObject::ObjectTypes::topstair)
			listStair.push_back(tmp);
		else if (tmp->ObjectTag == CGameObject::ObjectTypes::brickmoney || tmp->ObjectTag == CGameObject::ObjectTypes::brickchicken)
			listEnemy.push_back(tmp);
		else if (tmp->ObjectTag == CGameObject::ObjectTypes::door2 || tmp->ObjectTag == CGameObject::ObjectTypes::door3 ||
			tmp->ObjectTag == CGameObject::ObjectTypes::doortowater || tmp->ObjectTag == CGameObject::ObjectTypes::doorfromwater ||
			tmp->ObjectTag == CGameObject::ObjectTypes::door)
			listDoor.push_back(tmp);
		else
			listBrick.push_back(tmp);
	}

	fclose(pFile);
}

PlayScene::~PlayScene()
{
	delete grid;
	grid = nullptr;

	delete gameMap;
	gameMap = nullptr;
}
