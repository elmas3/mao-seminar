/*=================================================

	[Texture.h]
	�e�N�X�`�����Ǘ����鏈��
	Author : �o���đ�

=================================================*/

#pragma once
#include "main.h"

class Texture
{
private:
	static const unsigned int m_TextureNum = 3;	 //	�e�N�X�`���̐�
	LPDIRECT3DTEXTURE9	m_Texture[m_TextureNum];	
	unsigned int m_Image;
public:
	Texture();
	unsigned int LoadTexture(const char *pFileName);
	void UnLoadTexture(unsigned int Texture);
	LPDIRECT3DTEXTURE9 SetTexture(unsigned int Texture);
};
