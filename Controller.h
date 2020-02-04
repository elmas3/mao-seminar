/*======================================================

	[Controller.h]
	�R���g���[���̏���
	Author : �o���đ�

======================================================*/

#pragma once
#include "input.h"

//�}�N����`	
#define	NUM_KEY_MAX			(256)
//�Q�[���p�b�h�p�̐ݒ�l
#define DEADZONE		2500			// �e����25%�𖳌��]�[���Ƃ���
#define RANGE_MAX		1000			// �L���͈͂̍ő�l
#define RANGE_MIN		-1000			// �L���͈͂̍ŏ��l

//�Q�[���p�b�h�iXbox��PS4�j�̓��͂̃}�N��
//	��	����	
//!	�ԁ@Xbox�̂�
//"	��	PS4�̂�	

#define LEFTSTICK_UP			0x00000001l	//	Xbox��PS4:���X�e�B�b�N��(.IY<0)
#define LEFTSTICK_DOWN			0x00000002l	//	Xbox��PS4:���X�e�B�b�N��(.IY>0)
#define LEFTSTICK_LEFT			0x00000004l	//	Xbox��PS4:���X�e�B�b�N��(.IX<0)
#define LEFTSTICK_RIGHT			0x00000008l	//	Xbox��PS4:���X�e�B�b�N�E(.IX>0)
#define XboxRIGHTSTICK_UP		0x04000000l	//! Xbox:�E�X�e�B�b�N��(.lRz<16383)
#define XboxRIGHTSTICK_DOWN		0x10000000l	//! Xbox:�E�X�e�B�b�N��(.lRz>49150)
#define XboxRIGHTSTICK_LEFT		0x20000000l	//! Xbox:�E�X�e�B�b�N�E(.lZ<16383)
#define XboxRIGHTSTICK_RIGHT	0x40000000l	//! Xbox:�E�X�e�B�b�N��(.lZ>49150)
#define PS4RIGHTSTICK_UP		0x00000010l	//" PS4:�E�X�e�B�b�N��(.lRz<16383)
#define PS4RIGHTSTICK_DOWN		0x00000020l	//" PS4:�E�X�e�B�b�N��(.lRz>49150)
#define PS4RIGHTSTICK_RIGHT		0x00000040l //" PS4:�E�X�e�B�b�N�E(.lZ<16383)
#define PS4RIGHTSTICK_LEFT		0x00000080l //" PS4:�E�X�e�B�b�N��(.lZ>49150)
#define TRIGGER_LT				0x00000100l //! Xbox:LT�g���K�[(.lZ>49150)
#define TRIGGER_RT				0x00000200l //! Xbox:RT�g���K�[(.lZ<16383)
#define TRIGGER_L2				0x00000400l //" PS4 :L2�g���K�[(.lRx>10000)
#define TRIGGER_R2				0x00000800l //" PS4 :R2�g���K�[(.lRy>10000)
#define BUTTON_1				0x00008000l	//	Xbox:�x�{�^��	PS4�F���^��(.rgbButtons[3]&0x80)
#define BUTTON_2				0x00004000l	//	Xbox:�w�{�^��	PS4�F�Z�{�^��(.rgbButtons[2]&0x80)
#define BUTTON_3				0x00002000l	//	Xbox:�a�{�^��	PS4�F�~�{�^��(.rgbButtons[1]&0x80)
#define BUTTON_4				0x00001000l	//	Xbox:�`�{�^��	PS4�F���{�^��(.rgbButtons[0]&0x80)
#define BUTTON_LB				0x00010000l	//	Xbox:LB�{�^��	PS4�FL1�{�^��(.rgbButtons[4]&0x80)
#define BUTTON_RB				0x00020000l	//	Xbox:RB�{�^��	PS4�FR1�{�^��(.rgbButtons[5]&0x80)
#define BUTTON_BACK				0x00040000l	//	Xbox:BACK�{�^��	PS4�FOPTION�{�^��(.rgbButtons[6]&0x80)
#define BUTTON_START			0x00080000l	//	XboxSTART�{�^��	PS4�FSHARE�{�^��(.rgbButtons[7]&0x80)
#define BUTTON_L3				0x00100000l	//! Xbox:L3�{�^��(.rgbButtons[8]&0x80)
#define BUTTON_R3				0x00200000l	//! Xbox:R3�{�^��(.rgbButtons[9]&0x80)
#define BUTTON_UP				0x00400000l	//	Xbox��PS4:�����L�[��(rgdwPOV[0] = 0)
#define BUTTON_DOWN				0x00800000l //	Xbox��PS4:�����L�[��(.rgdwPOV[0] = 18000)
#define BUTTON_LEFT				0x01000000l //	Xbox��PS4:�����L�[��(.rgdwPOV[0] = 27000)
#define BUTTON_RIGHT			0x02000000l //	Xbox��PS4:�����L�[�E(.rgdwPOV[0] = 9000)
#define GAMEPADMAX				4			//	�����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g

//#	KeyBoard�N���X
/* �L�[�{�[�h�̓��͂��Ǘ� */
class KeyBoard : public Input
{
private:
	static LPDIRECTINPUTDEVICE8	m_pDevKeyboard;						//	�L�[�{�[�h�f�o�C�X
	static BYTE					m_aKeyState[NUM_KEY_MAX];			//	�L�[�{�[�h���(�����Ă���Ƃ�)
	static BYTE					m_aKeyStateTrigger[NUM_KEY_MAX];	//	�L�[�{�[�h���(�������u��)
	static BYTE					m_aKeyStateRelease[NUM_KEY_MAX];	//	�L�[�{�[�h���(�������u��)
public:
	static HRESULT Init(HINSTANCE hInstance, HWND hWnd);			//	����������
	static void Uninit();											//	�I������
	static void Update();											//	�X�V����
	static bool IsPress(int nKey);									//	�����Ă����
	static bool IsTrigger(int nKey);								//	�������u��
	static bool IsRelease(int nKey);								//	�������u��
};

//# GamePad�N���X
/* �Q�[���p�b�h�R���g���[���̓��͂��Ǘ� */
class GamePad : public Input
{
private:
	static LPDIRECTINPUTDEVICE8	m_pGamePad[GAMEPADMAX];								//�@�p�b�h�f�o�C�X
	static DWORD				m_padState[GAMEPADMAX];								//	�p�b�h���(�����Ă���Ƃ�)
	static DWORD				m_padTrigger[GAMEPADMAX];							//	�p�b�h���(�������u��)
	static int					m_padCount;											//�@���o�����p�b�h�̐�
public:
	static BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);	//	�R�[���o�b�N�֐�
	static HRESULT Init(HINSTANCE hInstance, HWND hWnd);							//	������
	static void Uninit();															//	�I������
	static void Update();															//	�X�V����
	static BOOL IsPress(int padNo, DWORD button);									//	�{�^���������Ă����
	static BOOL IsTrigger(int padNo, DWORD button);									//	�{�^�����������u��
};

//#	Mouse�N���X
/* �}�E�X�̓��͂��Ǘ� */
class Mouse : public Input
{
private:
	static LPDIRECTINPUTDEVICE8 m_pMouse;		// �}�E�X�f�o�C�X
	static DIMOUSESTATE2		m_mouseState;	// �}�E�X�̃_�C���N�g�ȏ��
	static DIMOUSESTATE2		m_mouseTrigger;	// �����ꂽ�u�Ԃ���ON
public:
	static HRESULT	Init(HINSTANCE hInst, HWND hWnd,bool bShaw); //	������
	static void		Uninit();									 // �I������
	static HRESULT	Update();									 // �X�V����
	static BOOL		LeftPress();								 // ���N���b�N�������
	static BOOL		LeftTrigger();								 // ���N���b�N�����u��
	static BOOL		RightPress();								 // �E�N���b�N�������
	static BOOL		RightTrigger();								 // �E�N���b�N�����u��
	static BOOL		CenterPress();								 // �����N���b�N�������
	static BOOL		CenterTrigger();							 // �����N���b�N�����u��
	static long		GetMouseX();								 // �}�E�X��X�����ɓ��������Βl
	static long		GetMouseY();								 // �}�E�X��Y�����ɓ��������Βl
	static long		GetMouseZ();								 // �}�E�X�z�C�[�������������Βl
};
