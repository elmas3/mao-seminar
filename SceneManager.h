/*======================================================

	[SceneManager.h]
	ゲームループを管理するクラス
	Author : 出合翔太

======================================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"

//#	SceneManagerクラス
class SceneManager
{
private:
	static SceneBase			*m_Scene[2];	//	シーン管理ポインタ変数
	static SceneState			m_SceneState;	//	シーンステートの管理変数
	static LPDIRECT3DDEVICE9	m_pDevice;		//	デバイスの取得変数
public:
	static void Init();					//	初期化処理
	static void Uninit();				//	終了処理
	static void Update();				//	更新処理
	static void Draw();					//	描画処理
	static void ChangeSceneState();		//	シーン遷移処理
	static SceneBase* SetSceneGame();	
};

