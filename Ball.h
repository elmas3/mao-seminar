/*========================================================

	[Ball.h]
	Author : �o�� �đ�

========================================================*/

#pragma once
#include "Actor.h"
#include "Collision.h"

class Ball : public Actor
{
private:
	AABB2d m_aabb;
	D3DXCOLOR m_Color;
	bool m_GameEnd;	//	���w�S�[���������ǂ���
	bool m_GoalFlag;	//	�S�[���������ǂ�������

	// Update()�̃w���p�[�֐�
	void PlayerCollision();
	void EnemyCollision();
	void LineCollsion();
	void GoalCollsion();
	void EnemyGoalCollision();

public:
	void Init()override;
	void Init(D3DXVECTOR2 Velocity); // �ړ������׃N�g���̕ύX
	void Uninit()override;
	void Update()override;
	void Draw(LPDIRECT3DTEXTURE9 Texture)override;
	AABB2d* GetCollision();
	bool GetGameEnd();
	bool GetGoalFlag();
};
