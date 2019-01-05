#include "Text.h"



Text::Text()
{
	
}

Text::Text(std::wstring Str, int Width, int Height, int Weight, DWORD Alignment, D3DCOLOR Color, LPCWSTR FontName)
{
	spriteHandler = CGame::GetInstance()->GetSpriteHandler();
	string = Str;
	width = Width;
	height = Height;
	weight = Weight;
	alignment = Alignment;
	color = Color;
	fontName = FontName;
	font = NULL;
	D3DXCreateFont(
		CGame::GetInstance()->GetDirect3DDevice(),
		0.5,
		0,
		weight,
		1,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		fontName,
		&font);
}

Text::~Text()
{
}

void Text::Draw(D3DXVECTOR2 position)
{
	RECT rect;
	rect.left = position.x - width / 2.0f;
	rect.top = position.y - height / 2.0f;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	font->DrawTextW(CGame::GetInstance()->GetSpriteHandler(), string.c_str(), -1, &rect, alignment, color);
}


void Text::SetString(std::wstring value)
{
	string = value;
}

void Text::SetString(int value)
{
	string = std::to_wstring(value);
}
