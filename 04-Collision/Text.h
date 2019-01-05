#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9core.h>
#include <string>
#include "Game.h"

class Text
{
private:
	LPD3DXSPRITE spriteHandler; 

	std::wstring string;
	LPCWSTR fontName;
	int width, height, weight;
	bool isItalic;
	DWORD alignment;
	D3DCOLOR color;
	LPD3DXFONT font;

public:
	Text();
	Text(std::wstring Str, int Width, int Height, int Weight, DWORD Alignment, D3DCOLOR Color, LPCWSTR FontName);
	~Text();

	void Draw(D3DXVECTOR2 position);

	void SetString(std::wstring value);
	void SetString(int value);

};

