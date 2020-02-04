/*=========================================================

	[Object.h]
	概要 ： ゲームオブジェクトの基底クラス
	Author : 出合 翔太

==========================================================*/

#pragma once
#include "main.h"
#include "Sprite.h"

class Object
{
protected:
	Sprite m_Sprite;	//	スプライトオブジェクトインスタンス
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw(LPDIRECT3DTEXTURE9 Texture) = 0;
};

