/*=======================================================

	[ObjectManager.h]
	オブジェクトのゲッターを管理するクラス
	Author : 出合翔太

=======================================================*/

#pragma once
#include "SceneGame.h"
#include "SceneManager.h"

class ObjectManager
{
public:
	static Topline * GetTopLine();		// 上のライン
	static Underline * GetUnderLine();	// 下のライン
	static Leftline * GetLeftLine();	// 左のライン
	static Rightline * GetRightLine();	// 右のライン　
	static Player * GetPlayer();		// プレイヤー
	static Enemy* GetEnemy();			// エネミー
	static Goal* GetGoal();				// 自陣ゴール
	static EnemyGoal* GetEnemyGoal();	// 相手側ゴール
	static Ball* GetBall();				// ボール
};

