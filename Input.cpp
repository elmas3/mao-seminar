/*==================================

	[Input.cpp]
	DirectInput����
	Author : �o���đ�

====================================*/

#include "Input.h"
#include "Controller.h"

//	�X�^�e�B�b�N�ϐ�
LPDIRECTINPUT8			Input::m_pInput = NULL;		//	DirectInput�I�u�W�F�N�g

//	���͏����̏�����
bool Input::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//	�쐬�̎��s
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{

			return false;
		}
	}
	//	���̓f�o�C�X�̏�����
	KeyBoard::Init(hInstance, hWnd);
	GamePad::Init(hInstance, hWnd);
	Mouse::Init(hInstance, hWnd,false);	
	return true;
}

//	���͏����̏I������
void Input::Uninit()
{
	Mouse::Uninit();
	GamePad::Uninit();
	KeyBoard::Uninit();
	SAFE_RELEASE(m_pInput);
}

//	���͏����̍X�V����
void Input::Update()
{
	KeyBoard::Update();
	GamePad::Update();
	Mouse::Update();
}
