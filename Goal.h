/*==============================================

	[Goal.h]
	Author : èoçá„ƒëæ

===============================================*/

#pragma once
#include "Player.h"
#include "Collision.h"

class Goal : public Actor
{
private:
	AABB2d	m_aabb;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw(LPDIRECT3DTEXTURE9 Texture)override;
	AABB2d* GetCollision();
};

