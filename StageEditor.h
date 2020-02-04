/*=========================================================

	[StageEditor.h]
	�T�v �F �X�e�[�W�G�f�B�^
	Author : �o���đ�

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

// �X�e�[�W
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
	Stage		m_Stage;	// �X�e�[�W
	Player		m_Player;	// �v���C���[
	Enemy		m_Enemy;	// �G�l�~�[
	Ball		m_Ball;		// �{�[��
	Goal		m_Goal;		// �S�[��
	EnemyGoal	m_EnemyGoal;// ���葤�̃S�[��
	GameBG		m_StageBG;	// �X�e�[�W�N���A�w�i
	UI			m_Ui;		// UI

	unsigned int texture[2]; // �e�N�X�`�����i�[
	int	m_StageCount;		 // �X�e�[�W���J�E���g
	int m_Frame;			 // �t���[���J�E���g
	float m_FramePosition;	 // �g�̈ʒu
	bool m_NextSelect;		 //	�I���t���O(true->���Afalse->�I��)
	bool m_Retry;			 // ���g���C�I���t���O(true->���g���C����Afalse->���g���C���Ȃ�)
			
	///	<summry>
	/// Init()�̃w���p�[�֐�
	/// </summary>
	void LoadTexture();			// �e�N�X�`���̃��[�h
	void InitObject(int Stage);	// �I�u�W�F�N�g�̏�����
	void InitGoal();

	/// <summary>
	/// Uninit()�̃w���p�[�֐�
	/// </summary>
	void UninitObject();	//	�I�u�W�F�N�g�̏I������

	///	<summary>
	///	Update()�̃w���p�[�֐�
	/// </summary>
	void UpdateObject();	// �I�u�W�F�N�g�̍X�V����
	void UpdateEnemy(int EnemyNum);	// �I�u�W�F�N�g�̍X�V����
	void UpdateStageClear();// �X�e�[�W�N���A�̍X�V
	void UpdateRetry();		// ���g���C�̍X�V
	void UpdateFrame(bool Flag);	// �g�̈ʒu�̍X�V(�����Ńt���O���w��)
	
	//	UpdateObject�̃w���p�[�֐�
	void EnemyGoalEnd();	// ����S�[���ɓ��ꂽ�Ƃ�
	void GoalEnd();			// ���w�S�[���ɓ������Ƃ�

	/// <summary>
	///�@Draw()�̃w���p�[�֐�
	/// </summary>
	void DrawObject();		// �I�u�W�F�N�g�̕`�揈��
	void DrawEnemy(int EnemyNum);
	void DrawStageClear();	// �X�e�[�W�N���A�̕`��
	void DrawRetry();		// ���g���C�̕`��

public:
	void Init();	// ����������
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Draw();	// �`�揈��
	bool GameEnd();	// �Q�[���G���h�`�F�b�N

	//	Getter
	Player* GetPlayer();
	Enemy* GetEnemy();
	Goal* GetGoal();
	EnemyGoal* GetEnemyGoal();
	Ball* GetBall();
};

