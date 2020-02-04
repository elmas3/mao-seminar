/*==================================
	
	[Sprite.h]
	スプライト描画処理
	Author : 出合翔太

=================================*/

#pragma once
#include "main.h"

//Spriteクラス
class Sprite
{
public:
	D3DCOLOR SetColor(int r, int g, int b, int a);	//	カラーの設定
	//	描画 (引数：テクスチャ、X座標、Y座標、テクスチャX座標、テクスチャY座標、テクスチャの横幅、テクスチャの縦幅)
	void Draw(LPDIRECT3DTEXTURE9 Texture, float dx, float dy, float Width, float Height, D3DXCOLOR Color = D3DCOLOR_RGBA(255, 255, 255, 255));
	//	描画 (引数：テクスチャ、X座標、Y座標、テクスチャの横幅、テクスチャの縦幅、テクスチャX座標、テクスチャY座標、描画する横幅、描画する縦幅)
	void Draw(LPDIRECT3DTEXTURE9 Texture, float dx, float dy, float Width, float Height, float tx, float ty, float tw, float th, D3DXCOLOR Color = D3DCOLOR_RGBA(255, 255, 255, 255));
	//	描画 (引数：テクスチャ、X座標、Y座標、テクスチャX座標、テクスチャY座標、テクスチャの横幅、テクスチャの縦幅、テクスチャの中心座標、拡大縮小、回転)
	void Draw(LPDIRECT3DTEXTURE9 Texture, float dx, float dy, float Width, float Height, float tx, float ty, float tw, float th, float cx, float cy, float sx, float sy, float rotation, D3DXCOLOR Color = D3DCOLOR_RGBA(255, 255, 255, 255));
};
