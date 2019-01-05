#pragma once
#include <string>
#include <vector>
#include "Camera.h"
#include "Textures.h"
#include "Game.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

using namespace std;


class GameMap
{
public:
	GameMap(LPCWSTR picturePath, int _id, int _translate, int _translate_x);

	CGame *game = CGame::GetInstance();
	CTextures * textures = CTextures::GetInstance();

	void LoadMap(const char* filepath);
	void DrawMap(Camera* camera);

	~GameMap();

private:
	int listTile[50][200];
	int id;
	int width, height;
	int colTileset, rowTileset;
	float remain_x, remain_y;
	int translate_y, translate_x;
};

