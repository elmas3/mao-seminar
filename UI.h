/*=====================================================

	[UI.h]
	Author : 出合翔太

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
	void Draw(float x,float y,int n); // x座標、y座標、切り取るty座標にnをかけて求める
};

