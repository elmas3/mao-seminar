/*==================================

	[Input.cpp]
	DirectInput処理
	Author : 出合翔太

====================================*/

#include "Input.h"
#include "Controller.h"

//	スタティック変数
LPDIRECTINPUT8			Input::m_pInput = NULL;		//	DirectInputオブジェクト

//	入力処理の初期化
bool Input::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//	作成の失敗
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{

			return false;
		}
	}
	//	入力デバイスの初期化
	KeyBoard::Init(hInstance, hWnd);
	GamePad::Init(hInstance, hWnd);
	Mouse::Init(hInstance, hWnd,false);	
	return true;
}

//	入力処理の終了処理
void Input::Uninit()
{
	Mouse::Uninit();
	GamePad::Uninit();
	KeyBoard::Uninit();
	SAFE_RELEASE(m_pInput);
}

//	入力処理の更新処理
void Input::Update()
{
	KeyBoard::Update();
	GamePad::Update();
	Mouse::Update();
}
