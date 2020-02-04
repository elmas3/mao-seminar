/*==================================

	[SceneGame.cpp]
	Author : �o���đ�

===================================*/

#include "SceneGame.h"
#include "SceneManager.h"
#include "Sound.h"

//	�Q�[���̏���������
void SceneGame::Init()
{
	m_bEnd = false;
	Fade::Start(false, 90);
	LoadTexture();			// �e�N�X�`���̃��[�h
	m_LineMgr.Set();		// ���C���̃Z�b�g	
	Sound::Play(S_BGM_GAME);
	m_StageEditor.Init();	//	�X�e�[�W�G�f�B�^
}

//	�Q�[���̏I������
void SceneGame::Uninit()
{
	m_StageEditor.Uninit();		
	m_Texture.UnLoadTexture(texture); //	�e�N�X�`���̃A�����[�h
}

//	�Q�[���̍X�V����
void SceneGame::Update()
{
	m_StageEditor.Update();
	EndCheck();
}

//	�Q�[���̕`�揈��
void SceneGame::Draw()
{
	DrawBg();
	m_StageEditor.Draw();
}

/// <summary>
///	Init()�̃w���p�[�֐�
///	</summary>
//	�e�N�X�`���̃��[�h
void SceneGame::LoadTexture()
{
	texture = m_Texture.LoadTexture("Rom/Texture/GameBG.png");	// �Q�[���w�i
}

/// <summary>
/// Update()�̃w���p�[�֐�
/// </summary>
//	�Q�[���I���`�F�b�N
void SceneGame::EndCheck()
{
	if (m_bEnd == false)
	{
		//	���w�S�[���̓��������烊�U���g
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
///	Draw()�̃w���p�[�֐�
/// </summary>
// �w�i�`��
void SceneGame::DrawBg()
{
	m_Bg.Draw(m_Texture.SetTexture(texture));
}

/// <summary>
///	 Getter
/// </summary>
//	���C���I�u�W�F�N�g
LineManager * SceneGame::GetLineMgr()
{
	return &m_LineMgr;
}
//	�X�e�[�W�G�f�B�^�I�u�W�F�N�g
StageEditor * SceneGame::GetStageEditor()
{
	return &m_StageEditor;
}


