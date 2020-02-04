/*=========================================================

	[EnemyGoal.h]
	Author : èoçá„ƒëæ

==========================================================*/

#pragma once
#include "Actor.h"
#include "Collision.h"

class EnemyGoal : public Actor
{
private:
	AABB2d m_aabb;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw(LPDIRECT3DTEXTURE9 Texture)override;
	AABB2d* GetCollision();
};

