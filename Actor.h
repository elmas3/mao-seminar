/*========================================================

	[Actor.h]
	プレイヤーやエネミーなどの基底クラス
	Author : 出合 翔太

=========================================================*/

#pragma once
#include "Object.h"

class Actor : public Object
{
protected:
	D3DXVECTOR2 m_Position;	 //	位置
	D3DXVECTOR2 m_Velocity;	 //	速度
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw(LPDIRECT3DTEXTURE9 Texture) = 0;
};