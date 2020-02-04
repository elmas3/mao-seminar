/*=================================================

	[Texture.cpp]
	テクスチャを管理する処理
	Author : 出合翔太

=================================================*/

#include "Texture.h"

Texture::Texture()
{
	m_Image = 0;
}

unsigned int Texture::LoadTexture(const char * pFileName)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	unsigned int texture = 0;
	D3DXCreateTextureFromFile(pDevice, pFileName, &m_Texture[m_Image++]);
	texture = m_Image -1;
	return texture;
}

void Texture::UnLoadTexture(unsigned int Texture)
{
	SAFE_RELEASE(m_Texture[Texture]);
	m_Image = 0;
}

LPDIRECT3DTEXTURE9 Texture::SetTexture(unsigned int Texture)
{
	return m_Texture[Texture];
}
