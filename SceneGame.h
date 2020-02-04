/*==================================

	[SceneGame.h]
	Author : 出合翔太

===================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"
#include "Texture.h"
#include "LineManager.h"
#include "GameBG.h"
#include "StageEditor.h"

// SceneGame
class SceneGame : public SceneBase
{
private:
	Texture		m_Texture;		// テクスチャ
	LineManager m_LineMgr;		// ラインのコリジョン
	GameBG		m_Bg;			// 背景
	StageEditor	m_StageEditor;	// ステージエディタ

	unsigned int texture; //	テクスチャの番号を格納
	
	//	Init()のヘルパー関数
	void LoadTexture();		// テクスチャのロード
	//	Update()のヘルパー関数
	void EndCheck();		// ゲーム終了チェック
	// Draw()のヘルパー関数
	void DrawBg();			

public:
	void Init()override;	
	void Uninit()override;
	void Update()override;
	void Draw()override;

	// Getter
	LineManager* GetLineMgr();
	StageEditor* GetStageEditor();
};
