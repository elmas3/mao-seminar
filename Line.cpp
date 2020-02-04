/*=========================================================

	[Line.h]
	Author : èoçá„ƒëæ

==========================================================*/

#include "Line.h"

void Topline::SetLine(D3DXVECTOR2 Position, float Size_x, float Size_y)
{
	m_aabb.cx = Position.x;
	m_aabb.cy = Position.y;
	m_aabb.sx = Size_x;
	m_aabb.sy = Size_y;
}

AABB2d * Topline::GetCollision()
{
	return &m_aabb;
}

void Underline::SetLine(D3DXVECTOR2 Position, float Size_x, float Size_y)
{
	m_aabb.cx = Position.x;
	m_aabb.cy = Position.y;
	m_aabb.sx = Size_x;
	m_aabb.sy = Size_y;
}

AABB2d * Underline::GetCollision()
{
	return &m_aabb;
}

void Leftline::SetLine(D3DXVECTOR2 Position, float Size_x, float Size_y)
{
	m_aabb.cx = Position.x;
	m_aabb.cy = Position.y;
	m_aabb.sx = Size_x;
	m_aabb.sy = Size_y;
}

AABB2d * Leftline::GetCollision()
{
	return &m_aabb;
}

void Rightline::SetLine(D3DXVECTOR2 Position, float Size_x, float Size_y)
{
	m_aabb.cx = Position.x;
	m_aabb.cy = Position.y;
	m_aabb.sx = Size_x;
	m_aabb.sy = Size_y;
}

AABB2d * Rightline::GetCollision()
{
	return &m_aabb;
}
