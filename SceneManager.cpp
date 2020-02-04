/*==============================================

	[SceneManager.cpp]	
	ゲームループを管理するクラス
	Author : 出合翔太

===============================================*/
#include "main.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"

//	スタティック変数
SceneBase			*SceneManager::m_Scene[2];	//	シーンのインスタンスを格納[シーンの配列]
SceneState			SceneManager::m_SceneState;	//	シーンのステートマシン（シーンの状態を格納）
LPDIRECT3DDEVICE9	SceneManager::m_pDevice;	//	デバイス

//	初期化処理
void SceneManager::Init()
{
	m_pDevice = GetD3DDevice();			//	デバイスの取得

	//	メモリの確保
	m_Scene[0] = new SceneTitle;
	m_Scene[1] = new SceneGame;	

	m_SceneState = SCENE_TITLE;			//	初期シーンの設定(ゲームを起動したときの最初のシーン)
	m_Scene[m_SceneState]->Init();		//	初期シーンの初期化
}

//	終了処理
void SceneManager::Uninit()
{
	//	終了時のシーンのUninit()を呼び出す
	m_Scene[m_SceneState]->Uninit();

	//	各シーンのメモリの解放
	delete m_Scene[1];
	delete m_Scene[0];
}

//	更新処理
void SceneManager::Update()
{
	m_Scene[m_SceneState]->Update();	//	各シーンのUpdate関数の呼び出し
	Fade::Update();
}

//	描画処理
void SceneManager::Draw()
{
	m_Scene[m_SceneState]->Draw();		//	各シーンのDraw関数の呼び出し
	Fade::Draw();
}

//	シーン遷移処理
void SceneManager::ChangeSceneState()
{
	switch (m_SceneState)
	{
	case SCENE_TITLE:
		m_Scene[m_SceneState]->Uninit();
		m_SceneState = SCENE_GAME;
		m_Scene[m_SceneState]->Init();
		break;
	case SCENE_GAME:
		m_Scene[m_SceneState]->Uninit();
		m_SceneState = SCENE_TITLE;		//	リザルトへ遷移
		m_Scene[m_SceneState]->Init();
		break;
	}
}

SceneBase * SceneManager::SetSceneGame()
{
	return m_Scene[SCENE_GAME];
}
