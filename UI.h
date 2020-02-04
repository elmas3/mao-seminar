/*=====================================================

	[UI.h]
	Author : �o���đ�

=====================================================*/

#pragma once
#include "Object.h"
#include "Texture.h"

class UI : public Object
{
private:
	D3DXCOLOR m_Color;
	float m_Changecolor;
	Texture m_Texture;
	unsigned int m_UItexture;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw(LPDIRECT3DTEXTURE9 Texture)override;
	void Draw(float x,float y,int n); // x���W�Ay���W�A�؂���ty���W��n�������ċ��߂�
};

