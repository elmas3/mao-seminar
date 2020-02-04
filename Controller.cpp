/*===============================================

	[Controller.cpp]
	コントローラの処理
	Author : 出合翔太

================================================*/

#include "main.h"
#include "Controller.h"

//	キーボード
LPDIRECTINPUTDEVICE8	KeyBoard::m_pDevKeyboard = NULL;								//	キーボードデバイス
BYTE					KeyBoard::m_aKeyState[NUM_KEY_MAX];								//	キーボード情報（押している間）
BYTE					KeyBoard::m_aKeyStateTrigger[NUM_KEY_MAX];						//	キーボード情報（押した瞬間）
BYTE					KeyBoard::m_aKeyStateRelease[NUM_KEY_MAX];						//	キーボード情報（離した瞬間）	

//	ゲームパッド
LPDIRECTINPUTDEVICE8	GamePad::m_pGamePad[GAMEPADMAX] = { NULL, NULL, NULL, NULL };	//	パッドデバイス
DWORD					GamePad::m_padState[GAMEPADMAX];								//	パッド情報（押している間）
DWORD					GamePad::m_padTrigger[GAMEPADMAX];								//	パッド情報（押した瞬間）
int						GamePad::m_padCount = 0;										//	検出したパッドの数

//	マウス
LPDIRECTINPUTDEVICE8	Mouse::m_pMouse = NULL;											//	マウスデバイス
DIMOUSESTATE2			Mouse::m_mouseState;											//	マウスのダイレクトな状態
DIMOUSESTATE2			Mouse::m_mouseTrigger;											//	押された瞬間だけON

//	キーボードの初期化
HRESULT KeyBoard::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return false;
	}

	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return false;
	}
	//													 DISCL_BACKGROUND | DISCL_EXCLUSIVE	
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return false;
	}

	m_pDevKeyboard->Acquire();
	return true;
}

//	キーボードの終了処理
void KeyBoard::Uninit()
{
	SAFE_RELEASE(m_pDevKeyboard);
}

//	キーボードの更新処理
void KeyBoard::Update()
{
	BYTE aKeyState[NUM_KEY_MAX];

	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			m_aKeyStateTrigger[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			m_aKeyStateRelease[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & m_aKeyState[nCnKey];

			m_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		m_pDevKeyboard->Acquire();
	}
}

//　キーボードを押している間
bool KeyBoard::IsPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//　キーボードを押した瞬間
bool KeyBoard::IsTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//　キーボードを離したとき
bool KeyBoard::IsRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//　ゲームパッド用コールバック関数
BOOL GamePad::SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID)
{
	HRESULT result;

	result = m_pInput->CreateDevice(lpddi->guidInstance, &m_pGamePad[m_padCount++], NULL);
	return DIENUM_CONTINUE;	// 次のデバイスを列挙
}

//　ゲームパッドの初期化処理
HRESULT GamePad::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT		result;
	int			i;

	m_padCount = 0;
	// ジョイパッドを探す
	m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchGamePadCallback, NULL, DIEDFL_ATTACHEDONLY);
	// セットしたコールバック関数が、パッドを発見した数だけ呼ばれる。

	for (i = 0; i < m_padCount; i++)
	{
		// ジョイスティック用のデータ・フォーマットを設定
		result = m_pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(result))
			return false; // データフォーマットの設定に失敗

		// モードを設定（フォアグラウンド＆非排他モード）
		//		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		//		if ( FAILED(result) )
		//			return false; // モードの設定に失敗

		// 軸の値の範囲を設定
		// X軸、Y軸のそれぞれについて、オブジェクトが報告可能な値の範囲をセットする。
		// (max-min)は、最大10,000(?)。(max-min)/2が中央値になる。
		// 差を大きくすれば、アナログ値の細かな動きを捕らえられる。(パッドの性能による)
		DIPROPRANGE				diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = RANGE_MIN;
		diprg.lMax = RANGE_MAX;
		// X軸の範囲を設定
		diprg.diph.dwObj = DIJOFS_X;
		m_pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y軸の範囲を設定
		diprg.diph.dwObj = DIJOFS_Y;
		m_pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 各軸ごとに、無効のゾーン値を設定する。
		// 無効ゾーンとは、中央からの微少なジョイスティックの動きを無視する範囲のこと。
		// 指定する値は、10000に対する相対値(2000なら20パーセント)。
		DIPROPDWORD				dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwHow = DIPH_BYOFFSET;
		dipdw.dwData = DEADZONE;
		//X軸の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_X;
		m_pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y軸の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_Y;
		m_pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

		//ジョイスティック入力制御開始
		m_pGamePad[i]->Acquire();
	}

	return true;
}

//	ゲームパッドの終了処理
void GamePad::Uninit()
{
	for (int i = 0; i < GAMEPADMAX; i++)
	{
		SAFE_RELEASE(m_pGamePad[i]);
	}
}

//　ゲームパッドの更新処理
void GamePad::Update()
{
	HRESULT			result;
	DIJOYSTATE2		dijs;	//ゲームパッドの入力値
	int				i;

	for (i = 0; i < m_padCount; i++)
	{
		DWORD lastPadState;
		lastPadState = m_padState[i];	//ゲームパッドのボタン配列
		m_padState[i] = 0x00000000l;	// 入力用32ビットの初期化

		result = m_pGamePad[i]->Poll();	// ジョイスティックにポールをかける
		if (FAILED(result))
		{
			result = m_pGamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = m_pGamePad[i]->Acquire();
		}

		result = m_pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// デバイス状態を読み取る
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
		{
			result = m_pGamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = m_pGamePad[i]->Acquire();
		}

		/*---------------------------------------------------------------------------------------------------
			３２の各ビットに意味を持たせ、ボタン押下に応じてビットをオンにする//long型デフォルト（32767ぐらい）
		-----------------------------------------------------------------------------------------------------*/

		//　緑	両方
		//! 赤　Xboxのみ
		//" 青　PS4のみ
		//!	注意　XboxとPS4の入力を同時に使わないこと

		// Xbox＆PS4:左スティックy-axis (forward)
		if (dijs.lY < 0)					m_padState[i] |= LEFTSTICK_UP;
		// Xbox＆PS4:左スティックy-axis (backward)
		if (dijs.lY > 0)					m_padState[i] |= LEFTSTICK_DOWN;
		// Xbox＆PS4:左スティックx-axis (left)
		if (dijs.lX < 0)					m_padState[i] |= LEFTSTICK_LEFT;
		// Xbox＆PS4:左スティックx-axis (right)
		if (dijs.lX > 0)					m_padState[i] |= LEFTSTICK_RIGHT;

		//! Xbox:右スティックy-axis (forward)
		if (dijs.lRy < 16383)				m_padState[i] |= XboxRIGHTSTICK_UP;
		//! Xbox:右スティックy-axis (backward)
		if (dijs.lRy > 49150)				m_padState[i] |= XboxRIGHTSTICK_DOWN;
		//! Xbox:右スティックx-axis (left)
		if (dijs.lRx < 16383)				m_padState[i] |= XboxRIGHTSTICK_LEFT;
		//! Xbox:右スティックx-axis (right)
		if (dijs.lRx > 49150)				m_padState[i] |= XboxRIGHTSTICK_RIGHT;

		//" PS4:右スティックy-axis (forward)
		if (dijs.lRz < 16383)				m_padState[i] |= PS4RIGHTSTICK_UP;
		//" PS4:右スティックy-axis (backward)
		if (dijs.lRz > 49150)				m_padState[i] |= PS4RIGHTSTICK_DOWN;
		//" PS4:右スティックx-axis (left)
		if (dijs.lZ < 16383)				m_padState[i] |= PS4RIGHTSTICK_LEFT;
		//" PS4:右スティックx-axis (right)
		if (dijs.lZ > 49150)				m_padState[i] |= PS4RIGHTSTICK_RIGHT;

		//! Xbox:LTトリガー
		if (dijs.lZ > 49150)				m_padState[i] |= TRIGGER_LT;
		//! Xbox:RTトリガー
		if (dijs.lZ < 16383)				m_padState[i] |= TRIGGER_RT;
		//" PS4:L2トリガー
		if (dijs.lRx > 10000)				m_padState[i] |= TRIGGER_L2;
		//" PS4:R2トリガー
		if (dijs.lRy > 10000)				m_padState[i] |= TRIGGER_R2;

		//* Xbox:Ａボタン	　PS4：□ボタン
		if (dijs.rgbButtons[0] & 0x80)		m_padState[i] |= BUTTON_1;
		//* Xbox:Ｘボタン	  PS4：〇ボタン
		if (dijs.rgbButtons[2] & 0x80)		m_padState[i] |= BUTTON_2;
		//* Xbox:Ｂボタン	　PS4：×ボタン
		if (dijs.rgbButtons[1] & 0x80)		m_padState[i] |= BUTTON_3;
		//*	Xbox:Ｙボタン	　PS4：△ボタン
		if (dijs.rgbButtons[3] & 0x80)		m_padState[i] |= BUTTON_4;
		//* Xbox:LBボタン	　PS4：L1ボタン
		if (dijs.rgbButtons[4] & 0x80)		m_padState[i] |= BUTTON_LB;
		//* Xbox:RBボタン	　PS4：R1ボタン
		if (dijs.rgbButtons[5] & 0x80)		m_padState[i] |= BUTTON_RB;
		//* Xbox:BACKボタン 　PS4 : OPTIONボタン
		if (dijs.rgbButtons[6] & 0x80)		m_padState[i] |= BUTTON_BACK;
		//* Xbox:STARTボタン　PS4 : SHAREボタン
		if (dijs.rgbButtons[7] & 0x80)		m_padState[i] |= BUTTON_START;

		//! Xbox:L3ボタン	
		if (dijs.rgbButtons[8] & 0x80)		m_padState[i] |= BUTTON_L3;
		//! Xbox:R3ボタン	
		if (dijs.rgbButtons[9] & 0x80)		m_padState[i] |= BUTTON_R3;

		//* Xbox＆PS4：方向キー上
		if (dijs.rgdwPOV[0] <= 0)									m_padState[i] |= BUTTON_UP;
		//* Xbox＆PS4：方向キー下
		if (dijs.rgdwPOV[0] <= 18000 && dijs.rgdwPOV[0] > 9000)		m_padState[i] |= BUTTON_DOWN;
		//* Xbox＆PS4：方向キー左
		if (dijs.rgdwPOV[0] <= 27000 && dijs.rgdwPOV[0] > 18000)	m_padState[i] |= BUTTON_LEFT;
		//* Xbox＆PS4：方向キー右
		if (dijs.rgdwPOV[0] <= 9000 && dijs.rgdwPOV[0] > 0)			m_padState[i] |= BUTTON_RIGHT;

		// Trigger設定
		m_padTrigger[i] = ((lastPadState ^ m_padState[i])	// 前回と違っていて
			& m_padState[i]);					// しかも今ONのやつ

	}
}

//　ゲームパッドのボタンを押している間
BOOL GamePad::IsPress(int padNo, DWORD button)
{
	return (button & m_padState[padNo]);
}

//　ゲームパッドのボタンを押した瞬間
BOOL GamePad::IsTrigger(int padNo, DWORD button)
{
	return (button & m_padTrigger[padNo]);
}

//	マウスの初期化
HRESULT Mouse::Init(HINSTANCE hInst, HWND hWnd, bool bShow)
{
	HRESULT result;
	// デバイス作成
	result = m_pInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);
	if (FAILED(result) || m_pMouse == NULL)
	{
		MessageBox(hWnd, "No mouse", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}
	// データフォーマット設定
	result = m_pMouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(result))

	{
		MessageBox(hWnd, "Can't setup mouse", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}
	// 他のアプリと協調モードに設定
	result = m_pMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(result))
	{
		MessageBox(hWnd, "Mouse mode error", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}

	// デバイスの設定
	DIPROPDWORD prop;

	prop.diph.dwSize = sizeof(prop);
	prop.diph.dwHeaderSize = sizeof(prop.diph);
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;
	prop.dwData = DIPROPAXISMODE_REL;		// マウスの移動値　相対値

	result = m_pMouse->SetProperty(DIPROP_AXISMODE, &prop.diph);
	if (FAILED(result))
	{
		MessageBox(hWnd, "Mouse property error", "Warning", MB_OK | MB_ICONWARNING);
		return result;
	}

	//	マウスカーソルの設定
	ShowCursor(bShow);

	// アクセス権を得る
	m_pMouse->Acquire();
	return result;
}

//	マウスの終了処理
void Mouse::Uninit()
{
	SAFE_RELEASE(m_pMouse);
}

//	マウスの更新処理
HRESULT Mouse::Update()
{
	HRESULT result;
	// 前回の値保存
	DIMOUSESTATE2 lastMouseState = m_mouseState;
	// データ取得
	result = m_pMouse->GetDeviceState(sizeof(m_mouseState), &m_mouseState);
	if (SUCCEEDED(result))
	{
		m_mouseTrigger.lX = m_mouseState.lX;
		m_mouseTrigger.lY = m_mouseState.lY;
		m_mouseTrigger.lZ = m_mouseState.lZ;
		// マウスのボタン状態
		for (int i = 0; i < 8; i++)
		{
			m_mouseTrigger.rgbButtons[i] = ((lastMouseState.rgbButtons[i] ^ m_mouseState.rgbButtons[i]) & m_mouseState.rgbButtons[i]);
		}
	}
	else	// 取得失敗
	{
		// アクセス権を得てみる
		result = m_pMouse->Acquire();
	}
	return result;
}

//	 左クリックした状態
BOOL Mouse::LeftPress()
{
	return (BOOL)(m_mouseState.rgbButtons[0] & 0x80);	// 押されたときに立つビットを検査
}

//	左クリックした瞬間
BOOL Mouse::LeftTrigger()
{
	return (BOOL)(m_mouseTrigger.rgbButtons[0] & 0x80);
}

//	右クリックした状態
BOOL Mouse::RightPress()
{
	return (BOOL)(m_mouseState.rgbButtons[1] & 0x80);
}

//	右クリックした瞬間
BOOL Mouse::RightTrigger()
{
	return (BOOL)(m_mouseTrigger.rgbButtons[1] & 0x80);
}

//  中央クリックした状態
BOOL Mouse::CenterPress()
{
	return (BOOL)(m_mouseState.rgbButtons[2] & 0x80);
}

//  中央クリックした瞬間
BOOL Mouse::CenterTrigger()
{
	return (BOOL)(m_mouseTrigger.rgbButtons[2] & 0x80);
}

//  マウスがX方向に動いた相対値
long Mouse::GetMouseX()
{
	return m_mouseState.lX;
}

//  マウスがY方向に動いた相対値
long Mouse::GetMouseY()
{
	return m_mouseState.lY;
}

//  マウスホイールが動いた相対値
long Mouse::GetMouseZ()
{
	return m_mouseState.lZ;
}

