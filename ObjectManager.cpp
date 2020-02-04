/*=======================================================

	[ObjectManager.h]
	�I�u�W�F�N�g�̃Q�b�^�[���Ǘ�����N���X
	Author : �o���đ�

=======================================================*/

#include "ObjectManager.h"

//	��̃��C��
Topline* ObjectManager::GetTopLine()
{
	return ((SceneGame*)SceneManager::SetSceneGame())->GetLineMgr()->Gettopline();
}

//	���̃��C��
Underline * ObjectManager::GetUnderLine()
{
	return ((SceneGame*)SceneManager::SetSceneGame())->GetLineMgr()->Getunderline();
}

//	���̃��C��
Leftline * ObjectManager::GetLeftLine()
{
	return ((SceneGame*)SceneManager::SetSceneGame())->GetLineMgr()->Getleftline();
}

//	�E�̃��C���@
Rightline * ObjectManager::GetRightLine()
{
	return ((SceneGame*)SceneManager::SetSceneGame())->GetLineMgr()->Getrightline();
}

//	�v���C���[
Player * ObjectManager::GetPlayer()
{
	return ((SceneGame*)SceneManager::SetSceneGame())->GetStageEditor()->GetPlayer();
}

//	�G�l�~�[
Enemy * ObjectManager::GetEnemy()
{
	return ((SceneGame*)SceneManager::SetSceneGame())->GetStageEditor()->GetEnemy();
}

//	���w�S�[��
Goal * ObjectManager::GetGoal()
{
	return ((SceneGame*)SceneManager::SetSceneGame())->GetStageEditor()->GetGoal();
}

//	���葤�S�[��
EnemyGoal * ObjectManager::GetEnemyGoal()
{
	return ((SceneGame*)SceneManager::SetSceneGame())->GetStageEditor()->GetEnemyGoal();
}

//	�{�[��
Ball * ObjectManager::GetBall()
{
	return ((SceneGame*)SceneManager::SetSceneGame())->GetStageEditor()->GetBall();
}




