/*=====================================================

	[SceneBase.h]
	概要 ： シーンクラスの基底クラス
	Author : 出合翔太

======================================================*/

#pragma once
#include "main.h"
#include "Sprite.h"
#include "Fade.h"

class SceneBase
{
protected:
	bool m_bEnd;
public:
	virtual ~SceneBase() {};
	virtual void Init() = 0;	//	初期化処理
	virtual void Uninit() = 0;	//	終了処理
	virtual void Update() = 0;	//	更新処理
	virtual void Draw() = 0;	//	描画処理
};
