/*==================================
	
	[Input.h]
	DirectInput����
	Author : �o���đ�

==================================*/

#pragma once

#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)	//	DirectInput�̃o�[�W����
#include <dinput.h>
#include "main.h"

//Input�N���X
class Input
{
protected:
	static LPDIRECTINPUT8	m_pInput;
public:
	static bool Init(HINSTANCE hInstance,HWND hWnd);
	static void Uninit();
	static void Update();
};

