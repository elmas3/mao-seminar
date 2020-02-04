/*=========================================================

	[Player.h]
	�v���C���[���Ǘ�����
	Author : �o���đ�

==========================================================*/

#pragma once
#include "Actor.h"
#include "Collision.h "

class Player : public Actor
{
private:
	AABB2d m_aabb; // AABB�R���W����
	float m_Speed; // �␳�X�s�[�h�l

	// Update()�̃w���p�[�֐�
	void Action();		//	���͂̏���
	void Move();		//	�ړ��̍X�V����
	void Collision();	//	�Փ˔���
public:
	void Init()override;
	void Init(float Speed);	// �␳�X�s�[�h�̕ύX
	void Uninit()override;
	void Update()override;
	void Draw(LPDIRECT3DTEXTURE9 Texture)override;
	AABB2d* GetCollision();
	D3DXVECTOR2 GetPosition();
};

