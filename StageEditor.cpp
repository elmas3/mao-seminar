/*=========================================================

	[StageEditor.cpp]
	概要 ： ステージエディタ
	Author : 出合翔太

==========================================================*/

#include "StageEditor.h"
#include "Controller.h"
#include "Fade.h"
#include "ObjectManager.h"
#include "Sound.h"

//	初期化処理
void StageEditor::Init()
{
	LoadTexture();			//	テクスチャのロード
	m_Stage = STAGE_1;		//	初期化ステージ
	InitObject(STAGE_1);
	m_StageCount = m_Stage;	//	ステージカウントへ代入
}

//	終了処理
void StageEditor::Uninit()
{
	UninitObject();
	m_Ui.Uninit();
	m_Texture.UnLoadTexture(texture[1]);
	m_Texture.UnLoadTexture(texture[0]);
}

//	更新処理
void StageEditor::Update()
{
	switch (m_Stage)
	{
	case STAGE_CLEAR:
		UpdateFrame(m_NextSelect);
		UpdateStageClear();
		break;
	case STAGE_1:
		UpdateObject();
		break;
	case STAGE_2:
		UpdateObject();
		break;
	case STAGE_3:
		UpdateObject();
		break;
	case STAGE_4:
		UpdateObject();
		break;
	case STAGE_5:
		UpdateObject();
		break;
	case GAME_END:
		break;
	case STAGE_END:
		UpdateFrame(m_Retry);
		UpdateRetry();	//	リトライの更新
		break;
	}
}

//	描画処理
void StageEditor::Draw()
{
	switch (m_Stage)
	{
	case STAGE_CLEAR:
		DrawStageClear();
		break;
	case STAGE_1:
		DrawObject();
		break;
	case STAGE_2:
		DrawObject();
		break;
	case STAGE_3:
		DrawObject();
		break;
	case STAGE_4:
		DrawObject();
		break;
	case STAGE_5:
		DrawObject();
		break;
	case GAME_END:
		break;
	case STAGE_END:
		DrawRetry();
		break;
	}
}

//	ゲーム終了
bool StageEditor::GameEnd()
{
	if (m_Stage == GAME_END) // ゲームエンドで終了
	{
		return true;
	}
	return false;
}

/// <summary>
///	Init()のヘルパー関数
/// </summary>
//	テクスチャのロード
void StageEditor::LoadTexture()
{
	texture[0] = m_Texture.LoadTexture("Rom/Texture/Ball.png");  // ボール
	texture[1] = m_Texture.LoadTexture("Rom/Texture/Bar.png");	 // Player&Goal
	m_Ui.Init();	//	UIテクスチャ
}
//	オブジェクトの初期化
void StageEditor::InitObject(int Stage)
{
	switch (Stage)
	{
	case STAGE_CLEAR:
		m_NextSelect = true; //	選択フラグはtrueにしておく
		break;
	case STAGE_1:
		InitGoal();
		m_Player.Init();
		m_Enemy.Init();
		m_Ball.Init();
		break;
	case STAGE_2:
		InitGoal();
		m_Player.Init();
		m_Enemy.Init(6.0f);
		m_Ball.Init(D3DXVECTOR2(-8.0f, 8.5f));
		break;
	case STAGE_3:
		InitGoal();
		m_Player.Init(0.8f);
		m_Enemy.Init(9.0f, D3DXVECTOR2(960.0f + 320.0f, 100.0f));
		m_Ball.Init(D3DXVECTOR2(-7.0f, 10.5f));
		break;
	case STAGE_4:
		InitGoal();
		m_Player.Init(1.5f);
		m_Enemy.Init(5.0f, D3DXVECTOR2(960.0f + 300.0f, 800.0f));
		m_Ball.Init(D3DXVECTOR2(-7.0f, 10.5f));
		break;
	case STAGE_5:
		InitGoal();
		m_Player.Init(0.5f);
		m_Enemy.Init(20.0f, D3DXVECTOR2(960.0f + 400.0f, 360.0f));
		m_Ball.Init(D3DXVECTOR2(-20.0f, 5.5f));
		break;
	case GAME_END:
		break;
	case STAGE_END:
		Sound::Stop();
		Sound::Play(S_BGM_GAMEEND);
		m_Retry = true;
		break;
	}
}

//	ゴールの初期化
void StageEditor::InitGoal()
{
	m_EnemyGoal.Init();
	m_Goal.Init();
}

/// <summry>
///	Uninit()のヘルパー関数
/// </summary>
//	オブジェクトの終了処理
void StageEditor::UninitObject()
{
	Sound::Stop();
	m_Ball.Uninit();
	m_Enemy.Uninit();
	m_Player.Uninit();
	m_Goal.Uninit();
	m_EnemyGoal.Uninit();
}

/// <summary>
/// Update()のヘルパー関数
/// </summary>
//	オブジェクトの更新
void StageEditor::UpdateObject()
{
	m_Goal.Update();
	m_EnemyGoal.Update();
	m_Player.Update();
	m_Enemy.Update();
	m_Ball.Update();
	EnemyGoalEnd();	//	ゴールに入れたときの処理
	GoalEnd();		//	ゴールに入ったときの処理
}

void StageEditor::UpdateEnemy(int EnemyNum)
{

}

/// <summary>
/// UpdateObject()のヘルパー関数
/// </summary>
//	ゴールに入れたときの処理
void StageEditor::EnemyGoalEnd()
{
	if (m_Ball.GetGoalFlag() == true)
	{
		if (m_StageCount == GAME_END - 1)
		{
			m_Stage = GAME_END;	//	ゲームエンドステートへ
		}
		else
		{
			Fade::Start(false, 30);
			m_Stage = STAGE_CLEAR; // ステートを更新
			InitObject(m_Stage);
		}
	}
}

//	自陣ゴールの処理
void StageEditor::GoalEnd()
{
	if (m_Ball.GetGameEnd() == true) // 自陣ゴールに入る
	{
		Fade::Start(false, 30);
		m_Stage = STAGE_END; // ステートを更新
		InitObject(m_Stage);
	}
}

//	ゲームクリアの更新処理
void StageEditor::UpdateStageClear()
{
	if (KeyBoard::IsTrigger(DIK_UPARROW) || GamePad::IsTrigger(0,LEFTSTICK_UP))
	{
		Sound::Play(S_SE_BUTTON);
		m_NextSelect = true;
	}
	else if (KeyBoard::IsTrigger(DIK_DOWNARROW) || GamePad::IsTrigger(0,LEFTSTICK_DOWN))
	{
		Sound::Play(S_SE_BUTTON);
		m_NextSelect = false;
	}
	if (KeyBoard::IsTrigger(DIK_RETURN) || GamePad::IsTrigger(0,BUTTON_2))
	{
		Sound::Play(S_SE_ANSWER);
		if (m_NextSelect == true)
		{
			m_StageCount++;					// ステージカウントを加算する
			InitObject(m_StageCount);		// 次のステージを初期化	
			m_Stage = (Stage)m_StageCount;	// キャストしてカウントを代入
			Fade::Start(false, 60);
		}
		else
		{
			m_Stage = GAME_END;	//	ゲームエンドステートへ
		}
	}
}

//	リトライの更新
void StageEditor::UpdateRetry()
{
	if (KeyBoard::IsTrigger(DIK_UPARROW) || GamePad::IsTrigger(0, LEFTSTICK_UP))
	{
		Sound::Play(S_SE_BUTTON);
		m_Retry = true;
	}
	else if (KeyBoard::IsTrigger(DIK_DOWNARROW) || GamePad::IsTrigger(0, LEFTSTICK_DOWN))
	{
		Sound::Play(S_SE_BUTTON);
		m_Retry = false;
	}
	if (KeyBoard::IsTrigger(DIK_RETURN) || GamePad::IsTrigger(0, BUTTON_2))
	{
		Sound::Play(S_SE_ANSWER);
		if (m_Retry == true)	//	リトライする
		{
			Sound::Stop();
			InitObject(m_StageCount);		// ステージカウントは加算しないでInit()
			m_Stage = (Stage)m_StageCount;	// キャストしてカウントを代入
			Sound::Play(S_BGM_GAME);
			Fade::Start(false, 60);
		}
		else // リトライしない
		{
			m_Stage = GAME_END; // エンドステートへ
		}
	}
}

//	枠の位置の更新
void StageEditor::UpdateFrame(bool Flag)
{	
	if (Flag == true)
	{
		m_FramePosition = SCREEN_HEIGHT * 0.5f - 100.0f;
	}
	else if (Flag == false)
	{
		m_FramePosition = SCREEN_HEIGHT * 0.5f + 100.0f;
	}
}

/// <summary>
/// Draw()のヘルパー関数
/// </summary>
//	オブジェクトの描画
void StageEditor::DrawObject()
{
	m_Player.Draw(m_Texture.SetTexture(texture[1]));
	m_Enemy.Draw(m_Texture.SetTexture(texture[1]));
	m_Ball.Draw(m_Texture.SetTexture(texture[0]));
	m_Goal.Draw(m_Texture.SetTexture(texture[1]));
	m_EnemyGoal.Draw(m_Texture.SetTexture(texture[1]));
}

//	ゲームクリアの描画処理
void StageEditor::DrawStageClear()
{
	m_Ui.Draw(SCREEN_WIDTH * 0.5 - 432.0f, SCREEN_HEIGHT * 0.5f - 400.0f, 7);
	m_Ui.Draw(SCREEN_WIDTH * 0.5 - 432.0f, SCREEN_HEIGHT * 0.5f - 100.0f, 1);
	m_Ui.Draw(SCREEN_WIDTH * 0.5 - 432.0f, SCREEN_HEIGHT * 0.5f + 100.0f, 2);
	m_Ui.Draw(SCREEN_WIDTH * 0.5 - 432.0f, m_FramePosition, 0);
}

//	リトライ画面の描画処理
void StageEditor::DrawRetry()
{
	m_Ui.Draw(SCREEN_WIDTH * 0.5 - 432.0f, SCREEN_HEIGHT * 0.5f - 400.0f, 6);
	m_Ui.Draw(SCREEN_WIDTH * 0.5 - 432.0f, SCREEN_HEIGHT * 0.5f - 100.0f, 4);
	m_Ui.Draw(SCREEN_WIDTH * 0.5 - 432.0f, SCREEN_HEIGHT * 0.5f + 100.0f, 5);
	m_Ui.Draw(SCREEN_WIDTH * 0.5 - 432.0f, m_FramePosition, 0);
}

/// <summary>
///  Getter
///	</summary>
Player * StageEditor::GetPlayer()
{
	return &m_Player;
}

Enemy * StageEditor::GetEnemy()
{
	return &m_Enemy;
}

Goal * StageEditor::GetGoal()
{
	return &m_Goal;
}

EnemyGoal * StageEditor::GetEnemyGoal()
{
	return &m_EnemyGoal;
}

Ball * StageEditor::GetBall()
{
	return &m_Ball;
}

