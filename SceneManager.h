/*======================================================

	[SceneManager.h]
	�Q�[�����[�v���Ǘ�����N���X
	Author : �o���đ�

======================================================*/

#pragma once
#include "main.h"
#include "SceneBase.h"

//#	SceneManager�N���X
class SceneManager
{
private:
	static SceneBase			*m_Scene[2];	//	�V�[���Ǘ��|�C���^�ϐ�
	static SceneState			m_SceneState;	//	�V�[���X�e�[�g�̊Ǘ��ϐ�
	static LPDIRECT3DDEVICE9	m_pDevice;		//	�f�o�C�X�̎擾�ϐ�
public:
	static void Init();					//	����������
	static void Uninit();				//	�I������
	static void Update();				//	�X�V����
	static void Draw();					//	�`�揈��
	static void ChangeSceneState();		//	�V�[���J�ڏ���
	static SceneBase* SetSceneGame();	
};

