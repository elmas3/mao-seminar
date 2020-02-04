/*===============================================

	[GameBG.cpp]
	Author : èoçá„ƒëæ

================================================*/

#include "GameBG.h"

void GameBG::Init()
{
}

void GameBG::Uninit()
{
}

void GameBG::Update()
{
}

void GameBG::Draw(LPDIRECT3DTEXTURE9 Texture)
{
	m_Sprite.Draw(Texture, 0.0f, 0.0f, 1920.0f, 1080.0f);
}
