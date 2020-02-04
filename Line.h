/*=======================================================

	[ Line.h]
	Author : 出合翔太

========================================================*/

#pragma once
#include "Collision.h"

class Line
{
public:
	virtual void SetLine(D3DXVECTOR2 Position, float Size_x, float Size_y) = 0;
};

//	上のライン
class Topline : public Line
{
private:
	AABB2d m_aabb;
public:
	void SetLine(D3DXVECTOR2 Position, float Size_x, float Size_y);
	AABB2d* GetCollision();
};

//	下のライン
class Underline : public Line
{
private:
	AABB2d m_aabb;
public:
	void SetLine(D3DXVECTOR2 Position, float Size_x, float Size_y);
	AABB2d* GetCollision();
};

//	左のライン
class Leftline : public Line
{
private:
	AABB2d m_aabb;
public:
	void SetLine(D3DXVECTOR2 Position, float Size_x, float Size_y);
	AABB2d* GetCollision();
};

//	右のライン
class Rightline : public Line
{
private:
	AABB2d m_aabb;
public:
	void SetLine(D3DXVECTOR2 Position, float Size_x, float Size_y);
	AABB2d* GetCollision();
};