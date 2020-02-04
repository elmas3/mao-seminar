/*==========================================================

	[Collision.h]
	Author : 出合翔太

===========================================================*/
#pragma once
#include "main.h"
#include <Math.h>

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
//		コリジョン構造体と当たり判定処理のテンプレート
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

//	2Dサークル
struct Circle2d
{
	float cx, cy; // 中心座標
	float radian; // 半径
};

template <class Type> 
bool Circle_2d(const Type Collision, const Type *p_Collision)
{
	//引数からベクトル型の変数を作る
	D3DXVECTOR2 dst1(Collision->cx, Collision->cy);
	D3DXVECTOR2 dst2(p_Collision->cx, p_Collision->cy);
	//二点間のベクトルを作る
	D3DXVECTOR2 distance = dst2 - dst1;
	//作ったベクトルの長さを求める
	float length = D3DXVec2Length(&distance);
	//お互いの半径を足した値を求める
	float size = Collision->radian + p_Collision->radian;

	//ベクトルの長さとお互いの半径を足した値を比較する → ベクトルの長さの方が小さければヒット
	if (length < size)
	{
		return true;
	}
	//ヒットしていなかった
	return false;
}

//	3Dサークル
struct Circle3d
{
	float cx, cy, cz; // 中心座標
	float radian;	  // 半径
};

template <class Type>
bool Circle_3d(const Type Collision, const Type * p_Collision)
{
	//引数からベクトル型の変数を作る
	D3DXVECTOR3 dst1(Collision->cx, Collision->cy, Collision->cz);
	D3DXVECTOR3 dst2(p_Collision->cx, p_Collision->cy, p_Collision->cz);
	//二点間のベクトルを作る
	D3DXVECTOR3 distance = dst2 - dst1;
	//作ったベクトルの長さを求める
	float length = D3DXVec3Length(&distance);
	//お互いの半径を足した値を求める
	float size = Collision->radian + p_Collision->radian;

	//ベクトルの長さとお互いの半径を足した値を比較する → ベクトルの長さの方が小さければヒット
	if (length < size)
	{
		return true;
	}
	//ヒットしていなかった
	return false;
}

//	2DAABB
struct AABB2d
{
	float cx, cy; // 中心座標
	float sx, sy; // 短径サイズ
};

template <class Type>
bool AABB_2d(const Type Collision, const Type * p_Collision)
{
	D3DXVECTOR2 minA, minB;	//	最小点
	D3DXVECTOR2 maxA, maxB;	//	最大点

	//	Aのbox最小点
	minA.x = Collision.cx - Collision.sx;
	minA.y = Collision.cy - Collision.sy;

	//	Aのbox最大点
	maxA.x = Collision.cx + Collision.sx;
	maxA.y = Collision.cy + Collision.sy;

	//	Bのbox最小点
	minB.x = p_Collision->cx - p_Collision->sx;
	minB.y = p_Collision->cy - p_Collision->sy;

	//	Bのbox最大点 
	maxB.x = p_Collision->cx + p_Collision->sx;
	maxB.y = p_Collision->cy + p_Collision->sy;
	//	X軸の比較
	if (maxA.x > minB.x && minA.x < maxB.x)
	{
		//	Y軸の比較
		if (maxA.y > minB.y && minA.y < maxB.y)
		{
			return true;
		}
	}
	return false;
}

//	3DAABB
struct AABB3d
{
	float cx, cy, cz; // 中心座標
	float sx, sy, sz; // 短形サイズ
};

template <class Type>
bool AABB_3d(const Type Collision, const Type * p_Collision)
{
	D3DXVECTOR3 minA, minB;	//	最小点
	D3DXVECTOR3 maxA, maxB;	//	最大点

	D3DXVECTOR3 minA, minB;	//	最小点
	D3DXVECTOR3 maxA, maxB;	//	最大点

	//	Aのbox最小点
	minA.x = Collision->cx - Collision->sx;
	minA.y = Collision->cy - Collision->sy;
	minA.z = Collision->cz - Collision->sz;

	//	Aのbox最大点
	maxA.x = Collision->cx + Collision->sx;
	maxA.y = Collision->cy + Collision->sy;
	maxA.z = Collision->cz + Collision->sz;

	//	Bのbox最小点
	minB.x = p_Collision->cx - p_Collision->sx;
	minB.y = p_Collision->cy - p_Collision->sy;
	minB.z = p_Collision->cz - p_Collision->sz;

	//	Bのbox最大点 
	maxB.x = p_Collision->cx + p_Collision->sx;
	maxB.y = p_Collision->cy + p_Collision->sy;
	maxB.z = p_Collision->cz + p_Collision->sz;

	//	X軸の比較
	if (maxA.x > minB.x && minA.x < maxB.x)
	{
		//	Y軸の比較
		if (maxA.y > minB.y && minA.y < maxB.y)
		{
			//	Z軸の比較
			if (maxA.z > minB.z && minA.z < maxB.z)
			{
				return true;
			}
		}
	}
	return false;
}