/*=========================================================

	[Object.h]
	�T�v �F �Q�[���I�u�W�F�N�g�̊��N���X
	Author : �o�� �đ�

==========================================================*/

#pragma once
#include "main.h"
#include "Sprite.h"

class Object
{
protected:
	Sprite m_Sprite;	//	�X�v���C�g�I�u�W�F�N�g�C���X�^���X
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw(LPDIRECT3DTEXTURE9 Texture) = 0;
};

