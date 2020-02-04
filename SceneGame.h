/*==================================

	[SceneGame.h]
	Author : �o���đ�

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
	Texture		m_Texture;		// �e�N�X�`��
	LineManager m_LineMgr;		// ���C���̃R���W����
	GameBG		m_Bg;			// �w�i
	StageEditor	m_StageEditor;	// �X�e�[�W�G�f�B�^

	unsigned int texture; //	�e�N�X�`���̔ԍ����i�[
	
	//	Init()�̃w���p�[�֐�
	void LoadTexture();		// �e�N�X�`���̃��[�h
	//	Update()�̃w���p�[�֐�
	void EndCheck();		// �Q�[���I���`�F�b�N
	// Draw()�̃w���p�[�֐�
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
