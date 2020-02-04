/*=====================================================

	[UI.cpp]
	Author : èoçá„ƒëæ

=====================================================*/

#include "UI.h"

void UI::Init()
{
	m_UItexture = m_Texture.LoadTexture("Rom/Texture/UI.png");
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f,1.0f);
	m_Changecolor = 0.01f;
}

void UI::Uninit()
{
	m_Texture.UnLoadTexture(m_UItexture);
}

void UI::Update()
{
	m_Color.a -= m_Changecolor;
	if (m_Color.a < 0.5f)
	{
		m_Color.a = 0.5f;
		m_Changecolor *= -1;
	}
	else if(m_Color.a > 1.0f)
	{
		m_Color.a = 1.0f;
		m_Changecolor *= -1;
	}
}

void UI::Draw(LPDIRECT3DTEXTURE9 Texture)
{
}

void UI::Draw(float x, float y,int n)
{
	m_Sprite.Draw(m_Texture.SetTexture(m_UItexture), x, y, 864.0f, 1728.0f, 0.0f, 215.0f * n, 864.0f, 216.0f,m_Color);
}
