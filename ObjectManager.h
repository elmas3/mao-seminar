/*=======================================================

	[ObjectManager.h]
	�I�u�W�F�N�g�̃Q�b�^�[���Ǘ�����N���X
	Author : �o���đ�

=======================================================*/

#pragma once
#include "SceneGame.h"
#include "SceneManager.h"

class ObjectManager
{
public:
	static Topline * GetTopLine();		// ��̃��C��
	static Underline * GetUnderLine();	// ���̃��C��
	static Leftline * GetLeftLine();	// ���̃��C��
	static Rightline * GetRightLine();	// �E�̃��C���@
	static Player * GetPlayer();		// �v���C���[
	static Enemy* GetEnemy();			// �G�l�~�[
	static Goal* GetGoal();				// ���w�S�[��
	static EnemyGoal* GetEnemyGoal();	// ���葤�S�[��
	static Ball* GetBall();				// �{�[��
};

