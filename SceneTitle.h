/*===================================================

	[SceneTitle.h]
	Author : 出合翔太

====================================================*/

#pragma once
#include "SceneBase.h"
#include "GameBG.h"
#include "Texture.h"
#include "UI.h"

class SceneTitle : public SceneBase 
{
private:
	Texture m_Texture;
	unsigned int texture;
	GameBG	m_Bg;
	UI		m_Ui;

	/// <summary>
	/// Init()のヘルパー関数
	/// </summary>
	void LoadTexture();	// テクスチャのロード
public:
	void Init()override;	//	初期化処理	
	void Uninit()override;	//	終了処理
	void Update()override;	//	更新処理
	void Draw()override;	//	描画処理
};

