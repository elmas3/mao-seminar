/*=======================================

	[main.cpp]
	Author : �o���đ�

========================================*/

//	�C���N���[�h�t�@�C��
#include "main.h"
#include "Input.h"
#include "SceneManager.h"
#include <time.h>
#include "Sound.h"

//	�}�N����`
#define CLASS_NAME     "GameWindow"       // �E�C���h�E�N���X�̖��O
#define WINDOW_CAPTION "�Q�[���E�B���h�E" // �E�B���h�E�̖��O

// �O���[�o���ϐ��錾
static	HWND g_hWnd;								// �E�B���h�E�n���h��
static	LPDIRECT3D9			g_pD3D = NULL;          // Direct3D�C���^�[�t�F�[�X
static	LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Direct3D�f�o�C�X

//	�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��(�R�[���o�b�N�֐�)
bool Window(HINSTANCE hInstance, int nCmdShow);									// �E�B���h�E�֐�
bool D3DInit(HWND hWnd);														// �f�o�C�X�̏�����
void D3DUninit();																// �f�o�C�X�̏I������
bool Init(HINSTANCE hInst);														// �Q�[���̏�����
void Uninit();																	// �Q�[���̏I������
void Update();																	// �Q�[���̍X�V����
void Draw();																	// �Q�[���̕`��֐�


//�@���C���֐��F�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �g�p���Ȃ��ꎞ�ϐ��𖾎�
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//�\������E�B���h�E�̒�`�A�o�^�A�\��
	if (!Window(hInstance, nCmdShow))		// InitApp�֐����Ăяo���A
	{
		return false;								// ����ɏI������Ύ��Ƀ��b�Z�[�W���[�v��
	}

	// �Q�[���̏�����
	Init(hInstance);

	//DWORD�^�cunsigned lond�^�i�����Ȃ��j
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	// ����\��ݒ�
	timeBeginPeriod(1);

	// �t���[���J�E���g������
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;	//�����l��0�ɂ��邱�Ƃ�Y��Ȃ��悤�ɁiFPS���擾�����Ƃ��S�~�������邱�Ɩh������)
	// Windows�Q�[���p���C�����[�v
	MSG msg = {}; 
	while (WM_QUIT != msg.message)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// ���b�Z�[�W������ꍇ�̓��b�Z�[�W������D��
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			dwCurrentTime = timeGetTime();
		
			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			//!	1�t���[�����ƂɎ��s�i����������҂��Ȃ��j60FPS�ɌŒ�@-> ���j�^�[�ɂ���Ď��s���x�̕ω���h��
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}

	// �Q�[���̏I������
	Uninit();

	return (int)msg.wParam;
}

// �E�B���h�E�v���V�[�W��(�R�[���o�b�N�֐�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) 
	{
	//�L�[���������Ƃ�
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)//ESC�L�[ 
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0); // WM_CLOSE���b�Z�[�W�̑��M
		}
		break;

	//�J�[�\���̐ݒ�
	case WM_SETCURSOR:
		SetCursor(NULL);
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd); // �w��̃E�B���h�E��WM_DESTROY���b�Z�[�W�𑗂�
		return 0; // DefWindowProc�֐��Ƀ��b�Z�[�W�𗬂����I�����邱�Ƃɂ���ĉ����Ȃ��������Ƃɂ���

	case WM_DESTROY: // �E�B���h�E�̔j�����b�Z�[�W
		PostQuitMessage(0); // WM_QUIT���b�Z�[�W�̑��M
		return 0;
	};

	// �ʏ탁�b�Z�[�W�����͂��̊֐��ɔC����
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
	

//	�E�B���h�E�֐�
bool Window(HINSTANCE hInstance, int nCmdShow)
{
	// �E�B���h�E�N���X�\����
	WNDCLASSEX wc;

	// �E�B���h�E�N���X���`����
	wc.cbSize = sizeof(WNDCLASSEX);						// WNDCLASSEX�\���̂̃T�C�Y��ݒ�
	wc.style = NULL;									// �E�B���h�E�X�^�C���i�f�t�H���g�j
	wc.lpfnWndProc = WndProc;							// �E�B���h�E�v���V�[�W���̎w��
	wc.cbClsExtra = 0;									// �ʏ�͎g��Ȃ��i�O�ɂ��Ă����j
	wc.cbWndExtra = 0;									// �ʏ�͎g��Ȃ��i�O�ɂ��Ă����j
	wc.lpszClassName = CLASS_NAME;						// �N���X���̐ݒ�
	wc.hInstance = hInstance;							// �C���X�^���X�n���h���̎w��
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);	// �E�C���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�
	wc.hIcon = NULL;									// ���[�W�A�C�R���i�Ȃ��j
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// �J�[�\���X�^�C��
	wc.lpszMenuName = NULL;								// ���j���[�i�Ȃ��j
	wc.hIconSm = NULL;									// �X���[���A�C�R���i�Ȃ��j

	// �E�B���h�E�N���X�̓o�^
	if (!RegisterClassEx(&wc)) return false;

	//�E�B���h�E�𐶐�����
	if (WINMODE)//TRUE�̂Ƃ�
	{
		//"	�E�B���h�E���[�h
		g_hWnd = CreateWindow
		(
			CLASS_NAME,             // �E�B���h�E�N���X�̖��O
			WINDOW_CAPTION,         // �E�B���h�E�^�C�g��
			WS_OVERLAPPEDWINDOW,    // �E�B���h�E�X�^�C��
			0,                      // �E�B���h�E�̍��p�w���W
			0,                      // �E�B���h�E�̍��p�x���W
			SCREEN_WIDTH,			//�E�B���h�E�̕�
			SCREEN_HEIGHT,			// �E�B���h�E�̍���
			NULL,                   // �e�E�B���h�E�i�Ȃ��j
			NULL,                   // ���j���[�i�Ȃ��j
			hInstance,              // ���̃v���O�����̃C���X�^���X�̃n���h��
			NULL                    // �ǉ������i�Ȃ��j
		);

		RECT wRect, cRect;  // �E�B���h�E�S�̂̋�`�A�N���C�A���g�̈�̋�`
		int ww, wh;         // �E�B���h�E�S�̂̕��A����
		int cw, ch;         // �N���C�A���g�̈�̕��A����

		// �E�B���h�E�S�̂̕��E�������v�Z
		GetWindowRect(g_hWnd, &wRect);
		ww = wRect.right - wRect.left;
		wh = wRect.bottom - wRect.top;
		// �N���C�A���g�̈�̕��E�������v�Z
		GetClientRect(g_hWnd, &cRect);
		cw = cRect.right - cRect.left;
		ch = cRect.bottom - cRect.top;
		// �N���C�A���g�̈�ȊO�ɕK�v�ȃT�C�Y���v�Z
		ww = ww - cw;
		wh = wh - ch;
		// �E�B���h�E�S�̂ɕK�v�ȃT�C�Y���v�Z
		ww = SCREEN_WIDTH + ww;
		wh = SCREEN_HEIGHT + wh;

		// �v�Z�������ƍ������E�B���h�E�ɐݒ�
		SetWindowPos(g_hWnd, HWND_TOP, 0, 0, ww, wh, SWP_NOMOVE);
	}
	else//FALSE�̂Ƃ�
	{
		//"	�t���X�N���[�����[�h
		g_hWnd = CreateWindow
		(
			CLASS_NAME,             // �E�B���h�E�N���X�̖��O
			WINDOW_CAPTION,         // �E�B���h�E�^�C�g��
			WS_VISIBLE | WS_POPUP,  // �E�B���h�E�X�^�C��
			0,                      // �E�B���h�E�̍��p�w���W
			0,                      // �E�B���h�E�̍��p�x���W
			SCREEN_WIDTH,           // �E�B���h�E�̕�
			SCREEN_HEIGHT,          // �E�B���h�E�̍���
			NULL,                   // �e�E�B���h�E�i�Ȃ��j
			NULL,                   // ���j���[�i�Ȃ��j
			hInstance,              // ���̃v���O�����̃C���X�^���X�̃n���h��
			NULL                    // �ǉ������i�Ȃ��j
		);
	}

	ShowWindow(g_hWnd, nCmdShow); // �E�B���h�E��\��
	ValidateRect(g_hWnd, 0);      // WM_PAINT���Ă΂�Ȃ��悤�ɂ���
	UpdateWindow(g_hWnd);         // �E�B���h�E�̍X�V

	return true;              // InitApp�֐��̐���I��
}

//	�f�o�C�X�̏������֐�
bool D3DInit(HWND hWnd)
{
	// Direct3D�C���^�[�t�F�[�X�̎擾
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL) 
	{
		// Direct3D�C���^�[�t�F�[�X�̎擾�Ɏ��s
		MessageBox(hWnd, "Direct3D�C���^�[�t�F�[�X�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return false;
	}

	// �f�o�C�X�̐����ɗ��p������\���̂̍쐬
	D3DPRESENT_PARAMETERS d3dpp = {};

	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// �o�b�N�o�b�t�@�̉���				
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// �o�b�N�o�b�t�@�̏c��
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;						// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�w��
	d3dpp.BackBufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// �X���b�v�G�t�F�N�g�i�X���b�v���@�j�̐ݒ�		
	d3dpp.Windowed = TRUE;											// �E�B���h�E���[�h or �t���X�N���[��
	d3dpp.EnableAutoDepthStencil = TRUE;							// �[�x�o�b�t�@�E�X�e���V���o�b�t�@�̎g�p				
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// �[�x�o�b�t�@�E�X�e���V���o�b�t�@�̃t�H�[�}�b�g�w��
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// �t���X�N���[�����̃��t���b�V�����[�g�̎w��
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// ���t���b�V�����[�g��Present�����̊֌W

	// Direct3D�f�o�C�X�̎擾
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetHWND(), D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))) {
		// �f�o�C�X�̍쐬�Ɏ��s
		MessageBox(hWnd, "Direct3D�f�o�C�X�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return false;
	}

	//���C�g���I�t�ɂ���
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);

	//g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);

	//�A�h���b�V���O���[�h�F���b�v�i�摜���J��Ԃ��j
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�A�h���b�V���O���[�h�F�~���[�i�摜�𔽓]�����ČJ��Ԃ��j
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	//�A�h���b�V���O���[�h�F�N�����v�i�Ō�̃J���[�ňȍ~��h��Ԃ��j
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	//�A�h���b�V���O���[�h�F�{�[�_�[�i����̐F�œh��Ԃ��j
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 0, 0, 255));

	//�e�N�X�`���t�B���^�[�F�|�C���g
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	//�e�N�X�`���t�B���^�[�F�o�C���j�A�t�B���^
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//�e�N�X�`���t�B���^�[�F�ٕ����t�B���^
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);

	//	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);
	//	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);


	// �A���t�@�u�����h�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG0, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG0, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// ���_�J���[�ƃe�N�X�`���̃u�����h�ݒ�
	//	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	return true;
}

// �f�o�C�X�̏I������
void D3DUninit()
{
	SAFE_RELEASE(g_pD3DDevice);	//	Direct3D�f�o�C�X�̉��
	SAFE_RELEASE(g_pD3D);		//	Direct3D�C���^�t�F�[�X�̉��
}

//�@�����������֐�
bool Init(HINSTANCE hInst)
{
	//�V�[�h�̏�����
	srand((unsigned int)time(NULL));

	// �Q�[���̏�����(Direct3D�̏�����)
	if (!D3DInit(g_hWnd))
	{
		return false;	// �Q�[���̏������Ɏ��s����
	}
	
	//	���͏����̏�����
	if (!Input::Init(hInst,g_hWnd))
	{
		return false;
	}

	if (!Sound::Init(g_hWnd))
	{
		return false;
	}
	
	//	�Q�[������������
	SceneManager::Init();

	return true;
}

//�@�I�������֐�
void Uninit()
{
	//	XAudio�̏I������
	Sound::Uninit();

	//	�Q�[���I������
	SceneManager::Uninit();

	//	���͏����̏I������
	Input::Uninit();

	// �Q�[���̏I������(Direct3D�̏I������)
	D3DUninit();
}

// �X�V�����֐�
void Update()
{	
	//	���͏����̍X�V
	Input::Update();

	//	�Q�[���X�V����
	SceneManager::Update();

}

// �`�揈���֐�
void Draw()
{
	LPDIRECT3DDEVICE9 pD3DDevice = GetD3DDevice();

	// ��ʂ̃N���A
	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(50, 50, 50, 255), 1.0f, 0);

	// �`��o�b�`���߂̊J�n
	pD3DDevice->BeginScene();

	//	�Q�[���`�揈��
	SceneManager::Draw();

	// �`��o�b�`���߂̏I��
	pD3DDevice->EndScene();

	// �o�b�N�o�b�t�@���t���b�v�i�^�C�~���O��D3DPRESENT_PARAMETERS�̐ݒ�ɂ��j
	pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//	Direct3DDevice�̃Q�b�^�[
LPDIRECT3DDEVICE9 GetD3DDevice() 
{
	return g_pD3DDevice;
}


//	�E�B���h�E�n���h���̃Q�b�^�[
HWND GetHWND()
{
	return g_hWnd;
}


double frand() 
{
	return (double)rand() / RAND_MAX;
}
