#include "GameMap.h"



GameMap::GameMap(LPCWSTR picturePath, int _id, int _translate_y, int _translate_x)
{
	id = _id;

	translate_y = _translate_y; 
	translate_x = _translate_x;


	textures->Add(id, picturePath, D3DCOLOR_XRGB(0, 0, 0));

}


GameMap::~GameMap()
{
}


void GameMap::LoadMap(const char* filepath)
{
	FILE* pFile;
	pFile = fopen(filepath, "r");

	fscanf(pFile, "%d %d %d %d", &rowTileset, &colTileset, &width, &height);

	for (int i = 0; i < rowTileset; i++)
	{
		for (int j = 0; j < colTileset; j++)
		{
			fscanf(pFile, "%d", &listTile[i][j]);
		
		}
	}
	fclose(pFile);

}

void GameMap::DrawMap(Camera * camera)
{
	remain_y = fmod(camera->GetPosition().y, height);
	remain_x = fmod(camera->GetPosition().x, width); //phan` du


	int colCamLeft = camera->GetPosition().x / width;
	int colCamRight = colCamLeft + SCREEN_WIDTH / width;
	int rowCamTop = camera->GetPosition().y / height;
	int rowCamBottom = rowCamTop + SCREEN_HEIGHT / height;


	for (int j = colCamLeft; j <= colCamRight; j++) //nếu ko để dấu bằng thì vẽ thiếu 1 cột bên phải
	{
		for (int i = rowCamTop; i < rowCamBottom; i++)
		{
			float pos_x = (j - colCamLeft)*width - remain_x + translate_x;
			float pos_y = (i - rowCamTop)*height - remain_y + translate_y;

			RECT rectTile;
			int index = listTile[i][j];

			rectTile.left = (index % colTileset) * width;
			rectTile.top = (index / colTileset) * height;
			rectTile.right = rectTile.left + width;
			rectTile.bottom = rectTile.top + height;

			game->Draw(pos_x, pos_y, textures->Get(id), rectTile.left, rectTile.top, rectTile.right, rectTile.bottom);
		}
	}

}
