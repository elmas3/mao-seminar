/*==============================================

	[GameBG.h]
	Author : èoçá„ƒëæ

===============================================*/

#pragma once
#include "Object.h"

class GameBG : public Object
{
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw(LPDIRECT3DTEXTURE9 Texture)override;
};

