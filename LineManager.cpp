/*========================================================

	[LineManager.cpp]
	Author : èoçá„ƒëæ

=========================================================*/

#include "LineManager.h"

void LineManager::Set()
{
	m_Topline.SetLine(D3DXVECTOR2(SCREEN_WIDTH * 0.5f,0.0f),1920.0f,10.0f);
	m_Underline.SetLine(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - 10.0f), 1920.0f, 10.0f);
	m_Leftline.SetLine(D3DXVECTOR2(50.0f,SCREEN_HEIGHT * 0.5f),15.0f,1080.0f);
	m_Rightline.SetLine(D3DXVECTOR2(SCREEN_WIDTH - 80.0f, SCREEN_HEIGHT* 0.5), 15.0f, 1080.0f);
}

Topline* LineManager::Gettopline()
{
	return &m_Topline;
}

Underline * LineManager::Getunderline()
{
	return &m_Underline;
}

Leftline * LineManager::Getleftline()
{
	return &m_Leftline;
}

Rightline * LineManager::Getrightline()
{
	return &m_Rightline;
}


