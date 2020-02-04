/*==================================

	[SceneGame.cpp]
	Author : 出合翔太

===================================*/

#include "SceneGame.h"
#include "SceneManager.h"
#include "Sound.h"

//	ゲームの初期化処理
void SceneGame::Init()
{
	m_bEnd = false;
	Fade::Start(false, 90);
	LoadTexture();			// テクスチャのロード
	m_LineMgr.Set();		// ラインのセット	
	Sound::Play(S_BGM_GAME);
	m_StageEditor.Init();	//	ステージエディタ
}

//	ゲームの終了処理
void SceneGame::Uninit()
{
	m_StageEditor.Uninit();		
	m_Texture.UnLoadTexture(texture); //	テクスチャのアンロード
}

//	ゲームの更新処理
void SceneGame::Update()
{
	m_StageEditor.Update();
	EndCheck();
}

//	ゲームの描画処理
void SceneGame::Draw()
{
	DrawBg();
	m_StageEditor.Draw();
}

/// <summary>
///	Init()のヘルパー関数
///	</summary>
//	テクスチャのロード
void SceneGame::LoadTexture()
{
	texture = m_Texture.LoadTexture("Rom/Texture/GameBG.png");	// ゲーム背景
}

/// <summary>
/// Update()のヘルパー関数
/// </summary>
//	ゲーム終了チェック
void SceneGame::EndCheck()
{
	if (m_bEnd == false)
	{
		//	自陣ゴールの当たったらリザルト
		if (m_StageEditor.GameEnd() == true)


		{
			Fade::Start(true, 30);
			m_bEnd = true;
		}
	}
	else
	{
		if (!Fade::IsFade())
		{
			SceneManager::ChangeSceneState();
		}
	}
}

/// <summary>
///	Draw()のヘルパー関数
/// </summary>
// 背景描画
void SceneGame::DrawBg()
{
	m_Bg.Draw(m_Texture.SetTexture(texture));
}

/// <summary>
///	 Getter
/// </summary>
//	ラインオブジェクト
LineManager * SceneGame::GetLineMgr()
{
	return &m_LineMgr;
}
//	ステージエディタオブジェクト
StageEditor * SceneGame::GetStageEditor()
{
	return &m_StageEditor;
}


