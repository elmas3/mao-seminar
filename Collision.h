/*==========================================================

	[Collision.h]
	Author : �o���đ�

===========================================================*/
#pragma once
#include "main.h"
#include <Math.h>

// ������������������������������������������������������������
//		�R���W�����\���̂Ɠ����蔻�菈���̃e���v���[�g
// ������������������������������������������������������������

//	2D�T�[�N��
struct Circle2d
{
	float cx, cy; // ���S���W
	float radian; // ���a
};

template <class Type> 
bool Circle_2d(const Type Collision, const Type *p_Collision)
{
	//��������x�N�g���^�̕ϐ������
	D3DXVECTOR2 dst1(Collision->cx, Collision->cy);
	D3DXVECTOR2 dst2(p_Collision->cx, p_Collision->cy);
	//��_�Ԃ̃x�N�g�������
	D3DXVECTOR2 distance = dst2 - dst1;
	//������x�N�g���̒��������߂�
	float length = D3DXVec2Length(&distance);
	//���݂��̔��a�𑫂����l�����߂�
	float size = Collision->radian + p_Collision->radian;

	//�x�N�g���̒����Ƃ��݂��̔��a�𑫂����l���r���� �� �x�N�g���̒����̕�����������΃q�b�g
	if (length < size)
	{
		return true;
	}
	//�q�b�g���Ă��Ȃ�����
	return false;
}

//	3D�T�[�N��
struct Circle3d
{
	float cx, cy, cz; // ���S���W
	float radian;	  // ���a
};

template <class Type>
bool Circle_3d(const Type Collision, const Type * p_Collision)
{
	//��������x�N�g���^�̕ϐ������
	D3DXVECTOR3 dst1(Collision->cx, Collision->cy, Collision->cz);
	D3DXVECTOR3 dst2(p_Collision->cx, p_Collision->cy, p_Collision->cz);
	//��_�Ԃ̃x�N�g�������
	D3DXVECTOR3 distance = dst2 - dst1;
	//������x�N�g���̒��������߂�
	float length = D3DXVec3Length(&distance);
	//���݂��̔��a�𑫂����l�����߂�
	float size = Collision->radian + p_Collision->radian;

	//�x�N�g���̒����Ƃ��݂��̔��a�𑫂����l���r���� �� �x�N�g���̒����̕�����������΃q�b�g
	if (length < size)
	{
		return true;
	}
	//�q�b�g���Ă��Ȃ�����
	return false;
}

//	2DAABB
struct AABB2d
{
	float cx, cy; // ���S���W
	float sx, sy; // �Z�a�T�C�Y
};

template <class Type>
bool AABB_2d(const Type Collision, const Type * p_Collision)
{
	D3DXVECTOR2 minA, minB;	//	�ŏ��_
	D3DXVECTOR2 maxA, maxB;	//	�ő�_

	//	A��box�ŏ��_
	minA.x = Collision.cx - Collision.sx;
	minA.y = Collision.cy - Collision.sy;

	//	A��box�ő�_
	maxA.x = Collision.cx + Collision.sx;
	maxA.y = Collision.cy + Collision.sy;

	//	B��box�ŏ��_
	minB.x = p_Collision->cx - p_Collision->sx;
	minB.y = p_Collision->cy - p_Collision->sy;

	//	B��box�ő�_ 
	maxB.x = p_Collision->cx + p_Collision->sx;
	maxB.y = p_Collision->cy + p_Collision->sy;
	//	X���̔�r
	if (maxA.x > minB.x && minA.x < maxB.x)
	{
		//	Y���̔�r
		if (maxA.y > minB.y && minA.y < maxB.y)
		{
			return true;
		}
	}
	return false;
}

//	3DAABB
struct AABB3d
{
	float cx, cy, cz; // ���S���W
	float sx, sy, sz; // �Z�`�T�C�Y
};

template <class Type>
bool AABB_3d(const Type Collision, const Type * p_Collision)
{
	D3DXVECTOR3 minA, minB;	//	�ŏ��_
	D3DXVECTOR3 maxA, maxB;	//	�ő�_

	D3DXVECTOR3 minA, minB;	//	�ŏ��_
	D3DXVECTOR3 maxA, maxB;	//	�ő�_

	//	A��box�ŏ��_
	minA.x = Collision->cx - Collision->sx;
	minA.y = Collision->cy - Collision->sy;
	minA.z = Collision->cz - Collision->sz;

	//	A��box�ő�_
	maxA.x = Collision->cx + Collision->sx;
	maxA.y = Collision->cy + Collision->sy;
	maxA.z = Collision->cz + Collision->sz;

	//	B��box�ŏ��_
	minB.x = p_Collision->cx - p_Collision->sx;
	minB.y = p_Collision->cy - p_Collision->sy;
	minB.z = p_Collision->cz - p_Collision->sz;

	//	B��box�ő�_ 
	maxB.x = p_Collision->cx + p_Collision->sx;
	maxB.y = p_Collision->cy + p_Collision->sy;
	maxB.z = p_Collision->cz + p_Collision->sz;

	//	X���̔�r
	if (maxA.x > minB.x && minA.x < maxB.x)
	{
		//	Y���̔�r
		if (maxA.y > minB.y && minA.y < maxB.y)
		{
			//	Z���̔�r
			if (maxA.z > minB.z && minA.z < maxB.z)
			{
				return true;
			}
		}
	}
	return false;
}