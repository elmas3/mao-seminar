/*========================================================

	[Actor.h]
	�v���C���[��G�l�~�[�Ȃǂ̊��N���X
	Author : �o�� �đ�

=========================================================*/

#pragma once
#include "Object.h"

class Actor : public Object
{
protected:
	D3DXVECTOR2 m_Position;	 //	�ʒu
	D3DXVECTOR2 m_Velocity;	 //	���x
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw(LPDIRECT3DTEXTURE9 Texture) = 0;
};