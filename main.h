/*==================================

	[main.h]
	Author : 出合翔太

==================================*/

#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>

#define _USE_MATH_DEFINES
#include <math.h>

//	ライブラリのリンク
#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")
#endif

//	マクロ定義
#define SCREEN_WIDTH  (1920)												// スクリーン(クライアント領域)の幅
#define SCREEN_HEIGHT (1080)												// スクリーン(クライアント領域)の高さ
#define SAFE_RELEASE(p) do {if(p){(p)->Release(); (p) = NULL;} } while(0)	// DirectXデバイス解放マクロ
#define WINMODE	FALSE														// ウィンドウモードの指定（TRUE：ウィンドウモード/FALSE:フルスクリーン）
#define	FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)				 // 2Dポリゴン頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )	
#define	FVF_VERTEX3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1) // 3Dポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 頂点カラー / テクスチャ座標 )

// 2Dポリゴン頂点フォーマットに合わせた構造体を定義
struct VERTEX_2D
{
	D3DXVECTOR4 pos;	// 頂点座標
	D3DCOLOR	col;	// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
};

// 3Dポリゴン頂点フォーマットに合わせた構造体を定義
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR	col;	// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
};

//	シーンステート
enum SceneState
{
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT
};

//　プロトタイプ宣言
LPDIRECT3DDEVICE9 GetD3DDevice();	//Direct3DDeviceのゲッター
HWND GetHWND();						//ウィンドウハンドルのGetter
double frand();
