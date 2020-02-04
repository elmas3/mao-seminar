/*=========================================================

	[StageEditor.h]
	概要 ： ステージエディタ
	Author : 出合翔太

==========================================================*/

#pragma once
#include "Texture.h"
#include "Player.h"
#include "Enemy.h"
#include "Ball.h"
#include "Goal.h"
#include "EnemyGoal.h"
#include "GameBG.h"
#include "UI.h"

// ステージ
enum Stage
{
	STAGE_CLEAR,
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_5,
	GAME_END,
	STAGE_END
};

class StageEditor
{
private:
	Texture		m_Texture;
	Stage		m_Stage;	// ステージ
	Player		m_Player;	// プレイヤー
	Enemy		m_Enemy;	// エネミー
	Ball		m_Ball;		// ボール
	Goal		m_Goal;		// ゴール
	EnemyGoal	m_EnemyGoal;// 相手側のゴール
	GameBG		m_StageBG;	// ステージクリア背景
	UI			m_Ui;		// UI

	unsigned int texture[2]; // テクスチャを格納
	int	m_StageCount;		 // ステージをカウント
	int m_Frame;			 // フレームカウント
	float m_FramePosition;	 // 枠の位置
	bool m_NextSelect;		 //	選択フラグ(true->次、false->終了)
	bool m_Retry;			 // リトライ選択フラグ(true->リトライする、false->リトライしない)
			
	///	<summry>
	/// Init()のヘルパー関数
	/// </summary>
	void LoadTexture();			// テクスチャのロード
	void InitObject(int Stage);	// オブジェクトの初期化
	void InitGoal();

	/// <summary>
	/// Uninit()のヘルパー関数
	/// </summary>
	void UninitObject();	//	オブジェクトの終了処理

	///	<summary>
	///	Update()のヘルパー関数
	/// </summary>
	void UpdateObject();	// オブジェクトの更新処理
	void UpdateEnemy(int EnemyNum);	// オブジェクトの更新処理
	void UpdateStageClear();// ステージクリアの更新
	void UpdateRetry();		// リトライの更新
	void UpdateFrame(bool Flag);	// 枠の位置の更新(引数でフラグを指定)
	
	//	UpdateObjectのヘルパー関数
	void EnemyGoalEnd();	// 相手ゴールに入れたとき
	void GoalEnd();			// 自陣ゴールに入ったとき

	/// <summary>
	///　Draw()のヘルパー関数
	/// </summary>
	void DrawObject();		// オブジェクトの描画処理
	void DrawEnemy(int EnemyNum);
	void DrawStageClear();	// ステージクリアの描画
	void DrawRetry();		// リトライの描画

public:
	void Init();	// 初期化処理
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Draw();	// 描画処理
	bool GameEnd();	// ゲームエンドチェック

	//	Getter
	Player* GetPlayer();
	Enemy* GetEnemy();
	Goal* GetGoal();
	EnemyGoal* GetEnemyGoal();
	Ball* GetBall();
};

