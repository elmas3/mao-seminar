/*=================================================

	[Texture.h]
	テクスチャを管理する処理
	Author : 出合翔太

=================================================*/

#pragma once
#include "main.h"

class Texture
{
private:
	static const unsigned int m_TextureNum = 3;	 //	テクスチャの数
	LPDIRECT3DTEXTURE9	m_Texture[m_TextureNum];	
	unsigned int m_Image;
public:
	Texture();
	unsigned int LoadTexture(const char *pFileName);
	void UnLoadTexture(unsigned int Texture);
	LPDIRECT3DTEXTURE9 SetTexture(unsigned int Texture);
};
