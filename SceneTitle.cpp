/*===================================================

	[SceneTitle.cpp]
	Author : 出合翔太

====================================================*/

#include "SceneTitle.h"
#include "SceneManager.h"
#include "Controller.h"
#include "Sound.h"

void SceneTitle::Init()
{
	LoadTexture();
	m_Ui.Init();
	Sound::Play(S_BGM_TITLE);
	Fade::Start(false,90);
	m_bEnd = false;
}

void SceneTitle::Uninit()
{
	Sound::Stop();
	m_Ui.Uninit();	
	m_Texture.UnLoadTexture(texture);
}

void SceneTitle::Update()
{
	m_Ui.Update();
	if (!m_bEnd)
	{
		//	ゲームへ遷移
		if (KeyBoard::IsTrigger(DIK_RETURN) || GamePad::IsTrigger(0, BUTTON_2))
		{
			Sound::Play(S_SE_ANSWER);
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

void SceneTitle::Draw()
{
	m_Bg.Draw(m_Texture.SetTexture(texture));
	m_Ui.Draw(SCREEN_WIDTH * 0.5f - 400.0f,SCREEN_HEIGHT * 0.5,3);
}

/// <summary>
/// Init()のヘルパー関数
/// </summary>
// テクスチャのロード
void SceneTitle::LoadTexture()
{
	texture= m_Texture.LoadTexture("Rom/Texture/Title.png");
}