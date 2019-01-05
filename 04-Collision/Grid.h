﻿#pragma once
#include <vector>
#include "GameObject.h"
#include <set>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define CELL_WIDTH 80  //320/4
#define CELL_HEIGHT 60  //240/4

//each cell in grid = 1/16 screen

using namespace std;

class Grid
{
public:

	Grid() 
	{ 
	}


	void InsertIntoGrid(CGameObject *object);
	void CheckSimonRevive(bool isRevive);

	void GetListCollisionFromGrid(Camera * Camera, vector<CGameObject*> &listColObjects);
	void TakeObjectsFromCell(int rowIndex, int colIndex, vector<CGameObject*> &listColObjects);

	~Grid();
	
private:

	vector<LPGAMEOBJECT> cells[10][200];
	set<CGameObject*> listTemp1;  //set: tồn tại 1 object duy nhất đó và ko trùng

	int rowIndex;
	int colIndex;
	bool isRevive = false;
};

