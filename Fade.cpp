/*==============================================

	[Fade.cpp]
	Author : o‡ãÄ‘¾

==============================================*/

#include "Fade.h"

struct FadeVertex
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
};
#define FVF_FADE_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

D3DXCOLOR Fade::m_FadeColor(0.0f, 0.0f, 0.0f, 1.0f);
float	  Fade::m_Alpha = 0.0f;
float     Fade::m_AddAlpha = 0.0f;
bool      Fade::m_bOut = false;
bool      Fade::m_bIsFade = false;

Fade::Fade()
{
	m_bIsFade = false;
	m_Alpha = 0.0f;
}

void Fade::Update()
{

	if (!m_bIsFade) {
		return;
	}

	m_Alpha += m_AddAlpha;

	if (m_bOut)
	{
		if (m_Alpha >= 1.0f) 
		{
			m_Alpha = 1.0f;
			m_bIsFade = false;
		}
	}
	else
	{
		if (m_Alpha <= 0.0f) 
		{
			m_Alpha = 0.0f;
			m_bIsFade = false;
		}
	}
}

void Fade::Draw()
{
	if (m_Alpha == 0.0f) 
	{
		return;
	}

	m_FadeColor.a = m_Alpha;
	D3DCOLOR color = m_FadeColor;

	FadeVertex v[] = 
	{
		{ D3DXVECTOR4(0.0f,0.0f, 0.0f, 1.0f), color },
		{ D3DXVECTOR4(SCREEN_WIDTH,0.0f, 0.0f, 1.0f), color },
		{ D3DXVECTOR4(0.0f, SCREEN_HEIGHT, 0.0f, 1.0f), color },
		{ D3DXVECTOR4(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f), color },
	};

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	pDevice->SetFVF(FVF_FADE_VERTEX);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(FadeVertex));
}

void Fade::Start(bool bOut, int frame, D3DCOLOR color)
{
	m_bOut = bOut;
	m_AddAlpha = 1.0f / frame;
	m_FadeColor = color;
	m_bIsFade = true;

	if (m_bOut) {
		m_Alpha = 0.0f;
	}
	else 
	{
		m_Alpha = 1.0f;
		m_AddAlpha = -m_AddAlpha;
	}
}

bool Fade::IsFade()
{
	return m_bIsFade;
}
