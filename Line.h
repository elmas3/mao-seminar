/*=======================================================

	[ Line.h]
	Author : �o���đ�

========================================================*/

#pragma once
#include "Collision.h"

class Line
{
public:
	virtual void SetLine(D3DXVECTOR2 Position, float Size_x, float Size_y) = 0;
};

//	��̃��C��
class Topline : public Line
{
private:
	AABB2d m_aabb;
public:
	void SetLine(D3DXVECTOR2 Position, float Size_x, float Size_y);
	AABB2d* GetCollision();
};

//	���̃��C��
class Underline : public Line
{
private:
	AABB2d m_aabb;
public:
	void SetLine(D3DXVECTOR2 Position, float Size_x, float Size_y);
	AABB2d* GetCollision();
};

//	���̃��C��
class Leftline : public Line
{
private:
	AABB2d m_aabb;
public:
	void SetLine(D3DXVECTOR2 Position, float Size_x, float Size_y);
	AABB2d* GetCollision();
};

//	�E�̃��C��
class Rightline : public Line
{
private:
	AABB2d m_aabb;
public:
	void SetLine(D3DXVECTOR2 Position, float Size_x, float Size_y);
	AABB2d* GetCollision();
};