/*==================================

	[main.h]
	Author : �o���đ�

==================================*/

#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>

#define _USE_MATH_DEFINES
#include <math.h>

//	���C�u�����̃����N
#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")
#endif

//	�}�N����`
#define SCREEN_WIDTH  (1920)												// �X�N���[��(�N���C�A���g�̈�)�̕�
#define SCREEN_HEIGHT (1080)												// �X�N���[��(�N���C�A���g�̈�)�̍���
#define SAFE_RELEASE(p) do {if(p){(p)->Release(); (p) = NULL;} } while(0)	// DirectX�f�o�C�X����}�N��
#define WINMODE	FALSE														// �E�B���h�E���[�h�̎w��iTRUE�F�E�B���h�E���[�h/FALSE:�t���X�N���[���j
#define	FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)				 // 2D�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )	
#define	FVF_VERTEX3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1) // 3D�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���_�J���[ / �e�N�X�`�����W )

// 2D�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
struct VERTEX_2D
{
	D3DXVECTOR4 pos;	// ���_���W
	D3DCOLOR	col;	// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
};

// 3D�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR	col;	// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
};

//	�V�[���X�e�[�g
enum SceneState
{
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT
};

//�@�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetD3DDevice();	//Direct3DDevice�̃Q�b�^�[
HWND GetHWND();						//�E�B���h�E�n���h����Getter
double frand();
