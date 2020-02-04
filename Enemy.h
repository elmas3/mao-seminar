/*=========================================================

	[Enemy.h]
	Author : �o���đ�

==========================================================*/

#pragma once
#include "Player.h"

class Enemy : public Player
{
private:
	AABB2d	m_aabb;

	// Update()�̃w���p�[�֐�
	void Move();
	void Collision();

public:
	void Init()override;
	void Init(float Speed,D3DXVECTOR2 Position = D3DXVECTOR2((480.0f * 3) - 32.0f, 540.0f)); //	Y���̈ړ��X�s�[�h,�����ʒu�̕ύX
	void Uninit()override;
	void Update()override;
	void Draw(LPDIRECT3DTEXTURE9 Texture)override;
	AABB2d* GetCollision();
	D3DXVECTOR2 GetPosition();
};

