/*==================================

	[Sprite.cpp]
	スプライト描画処理
	Author : 出合翔太

==================================*/

#include "Texture.h"
#include "Sprite.h"

//	マクロ定義
#define MINA	(0.5f)	//	画面の表示位置の修正固定値

D3DCOLOR Sprite::SetColor(int r, int g, int b, int a)
{
	D3DCOLOR color = D3DCOLOR_RGBA(r, g, b,a);
	return color;
}

//	描画 (引数：テクスチャ、X座標、Y座標、テクスチャX座標、テクスチャY座標、テクスチャの横幅、テクスチャの縦幅)
void Sprite::Draw(LPDIRECT3DTEXTURE9 Texture, float dx, float dy, float Width, float Height, D3DXCOLOR Color)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	VERTEX_2D vertexes[] =
	{
		{ D3DXVECTOR4(dx - MINA, dy - MINA, 0.0f, 1.0f), Color, D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR4(dx + Width - MINA, dy - MINA, 0.0f, 1.0f), Color, D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR4(dx - MINA, dy + Height - MINA, 0.0f, 1.0f), Color, D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR4(dx + Width - MINA, dy + Height - MINA, 0.0f, 1.0f), Color, D3DXVECTOR2(1.0f, 1.0f) },
	};

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(VERTEX_2D));
}

void Sprite::Draw(LPDIRECT3DTEXTURE9 Texture, float dx, float dy, float Width, float Height, float tx, float ty, float tw, float th, D3DXCOLOR Color)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	float u[2], v[2];
	u[0] = tx / Width;
	v[0] = ty / Height;
	u[1] = (tx + tw) / Width;
	v[1] = (ty + th) / Height;

	VERTEX_2D vertexes[] =
	{
		{ D3DXVECTOR4(dx - MINA, dy - MINA, 0.0f, 1.0f), Color, D3DXVECTOR2(u[0], v[0]) },
		{ D3DXVECTOR4(dx + tw - MINA, dy - MINA, 0.0f, 1.0f), Color, D3DXVECTOR2(u[1], v[0]) },
		{ D3DXVECTOR4(dx - MINA, dy + th - MINA, 0.0f, 1.0f), Color, D3DXVECTOR2(u[0], v[1]) },
		{ D3DXVECTOR4(dx + tw - MINA, dy + th - MINA, 0.0f, 1.0f), Color, D3DXVECTOR2(u[1], v[1]) },
	};

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(VERTEX_2D));
}

void Sprite::Draw(LPDIRECT3DTEXTURE9 Texture, float dx, float dy, float Width, float Height, float tx, float ty, float tw, float th, float cx, float cy, float sx, float sy, float rotation, D3DXCOLOR Color)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	float u[2], v[2];
	u[0] = tx / Width;
	v[0] = ty / Height;
	u[1] = (tx + tw) / Width;
	v[1] = (ty + th) / Height;

	D3DXMATRIX matBase[4];

	D3DXMatrixTranslation(&matBase[0], -(tw - (tw - cx)), -(th - (th - cy)), 0.0f);
	D3DXMatrixTranslation(&matBase[1], tw - cx, -(th - (th - cy)), 0.0f);
	D3DXMatrixTranslation(&matBase[2], -(tw - (tw - cx)), th - cy, 0.0f);
	D3DXMatrixTranslation(&matBase[3], tw - cx, th - cy, 0.0f);

	D3DXMATRIX matTrans;
	D3DXMATRIX matRot;
	D3DXMATRIX matScale;
	D3DXMATRIX matAll;
	float px[4], py[4];

	D3DXMatrixTranslation(&matTrans, dx, dy, 0.0f);
	D3DXMatrixRotationZ(&matRot, rotation);
	D3DXMatrixScaling(&matScale, sx, sy, 1.0f);

	for (int i = 0; i < 4; i++)
	{
		matAll = matBase[i] * matScale * matRot * matTrans;
		px[i] = matAll._41;
		py[i] = matAll._42;
	}

	VERTEX_2D vertexes[] =
	{
		{ D3DXVECTOR4(px[0] - 0.4f, py[0] - 0.4f, 0.0f, 1.0f), Color, D3DXVECTOR2(u[0], v[0]) },
		{ D3DXVECTOR4(px[1] - 0.4f, py[1] - 0.4f, 0.0f, 1.0f), Color, D3DXVECTOR2(u[1], v[0]) },
		{ D3DXVECTOR4(px[2] - 0.4f, py[2] - 0.4f, 0.0f, 1.0f), Color, D3DXVECTOR2(u[0], v[1]) },
		{ D3DXVECTOR4(px[3] - 0.4f, py[3] - 0.4f, 0.0f, 1.0f), Color, D3DXVECTOR2(u[1], v[1]) },
	};

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(VERTEX_2D));
}
