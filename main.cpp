/*=======================================

	[main.cpp]
	Author : 出合翔太

========================================*/

//	インクルードファイル
#include "main.h"
#include "Input.h"
#include "SceneManager.h"
#include <time.h>
#include "Sound.h"

//	マクロ定義
#define CLASS_NAME     "GameWindow"       // ウインドウクラスの名前
#define WINDOW_CAPTION "ゲームウィンドウ" // ウィンドウの名前

// グローバル変数宣言
static	HWND g_hWnd;								// ウィンドウハンドル
static	LPDIRECT3D9			g_pD3D = NULL;          // Direct3Dインターフェース
static	LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Direct3Dデバイス

//	プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャ(コールバック関数)
bool Window(HINSTANCE hInstance, int nCmdShow);									// ウィンドウ関数
bool D3DInit(HWND hWnd);														// デバイスの初期化
void D3DUninit();																// デバイスの終了処理
bool Init(HINSTANCE hInst);														// ゲームの初期化
void Uninit();																	// ゲームの終了処理
void Update();																	// ゲームの更新処理
void Draw();																	// ゲームの描画関数


//　メイン関数：エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 使用しない一時変数を明示
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//表示するウィンドウの定義、登録、表示
	if (!Window(hInstance, nCmdShow))		// InitApp関数を呼び出し、
	{
		return false;								// 正常に終了すれば次にメッセージループへ
	}

	// ゲームの初期化
	Init(hInstance);

	//DWORD型…unsigned lond型（符号なし）
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	// 分解能を設定
	timeBeginPeriod(1);

	// フレームカウント初期化
	dwExecLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;	//初期値を0にすることを忘れないように（FPSを取得したときゴミが混ざること防ぐため)
	// Windowsゲーム用メインループ
	MSG msg = {}; 
	while (WM_QUIT != msg.message)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// メッセージがある場合はメッセージ処理を優先
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			dwCurrentTime = timeGetTime();
		
			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			//!	1フレームごとに実行（垂直同期を待たない）60FPSに固定　-> モニターによって実行速度の変化を防ぐ
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}

	// ゲームの終了処理
	Uninit();

	return (int)msg.wParam;
}

// ウィンドウプロシージャ(コールバック関数)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) 
	{
	//キーを押したとき
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)//ESCキー 
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0); // WM_CLOSEメッセージの送信
		}
		break;

	//カーソルの設定
	case WM_SETCURSOR:
		SetCursor(NULL);
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd); // 指定のウィンドウにWM_DESTROYメッセージを送る
		return 0; // DefWindowProc関数にメッセージを流さず終了することによって何もなかったことにする

	case WM_DESTROY: // ウィンドウの破棄メッセージ
		PostQuitMessage(0); // WM_QUITメッセージの送信
		return 0;
	};

	// 通常メッセージ処理はこの関数に任せる
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
	

//	ウィンドウ関数
bool Window(HINSTANCE hInstance, int nCmdShow)
{
	// ウィンドウクラス構造体
	WNDCLASSEX wc;

	// ウィンドウクラスを定義する
	wc.cbSize = sizeof(WNDCLASSEX);						// WNDCLASSEX構造体のサイズを設定
	wc.style = NULL;									// ウィンドウスタイル（デフォルト）
	wc.lpfnWndProc = WndProc;							// ウィンドウプロシージャの指定
	wc.cbClsExtra = 0;									// 通常は使わない（０にしておく）
	wc.cbWndExtra = 0;									// 通常は使わない（０にしておく）
	wc.lpszClassName = CLASS_NAME;						// クラス名の設定
	wc.hInstance = hInstance;							// インスタンスハンドルの指定
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);	// ウインドウのクライアント領域の背景色を設定
	wc.hIcon = NULL;									// ラージアイコン（なし）
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// カーソルスタイル
	wc.lpszMenuName = NULL;								// メニュー（なし）
	wc.hIconSm = NULL;									// スモールアイコン（なし）

	// ウィンドウクラスの登録
	if (!RegisterClassEx(&wc)) return false;

	//ウィンドウを生成する
	if (WINMODE)//TRUEのとき
	{
		//"	ウィンドウモード
		g_hWnd = CreateWindow
		(
			CLASS_NAME,             // ウィンドウクラスの名前
			WINDOW_CAPTION,         // ウィンドウタイトル
			WS_OVERLAPPEDWINDOW,    // ウィンドウスタイル
			0,                      // ウィンドウの左角Ｘ座標
			0,                      // ウィンドウの左角Ｙ座標
			SCREEN_WIDTH,			//ウィンドウの幅
			SCREEN_HEIGHT,			// ウィンドウの高さ
			NULL,                   // 親ウィンドウ（なし）
			NULL,                   // メニュー（なし）
			hInstance,              // このプログラムのインスタンスのハンドル
			NULL                    // 追加引数（なし）
		);

		RECT wRect, cRect;  // ウィンドウ全体の矩形、クライアント領域の矩形
		int ww, wh;         // ウィンドウ全体の幅、高さ
		int cw, ch;         // クライアント領域の幅、高さ

		// ウィンドウ全体の幅・高さを計算
		GetWindowRect(g_hWnd, &wRect);
		ww = wRect.right - wRect.left;
		wh = wRect.bottom - wRect.top;
		// クライアント領域の幅・高さを計算
		GetClientRect(g_hWnd, &cRect);
		cw = cRect.right - cRect.left;
		ch = cRect.bottom - cRect.top;
		// クライアント領域以外に必要なサイズを計算
		ww = ww - cw;
		wh = wh - ch;
		// ウィンドウ全体に必要なサイズを計算
		ww = SCREEN_WIDTH + ww;
		wh = SCREEN_HEIGHT + wh;

		// 計算した幅と高さをウィンドウに設定
		SetWindowPos(g_hWnd, HWND_TOP, 0, 0, ww, wh, SWP_NOMOVE);
	}
	else//FALSEのとき
	{
		//"	フルスクリーンモード
		g_hWnd = CreateWindow
		(
			CLASS_NAME,             // ウィンドウクラスの名前
			WINDOW_CAPTION,         // ウィンドウタイトル
			WS_VISIBLE | WS_POPUP,  // ウィンドウスタイル
			0,                      // ウィンドウの左角Ｘ座標
			0,                      // ウィンドウの左角Ｙ座標
			SCREEN_WIDTH,           // ウィンドウの幅
			SCREEN_HEIGHT,          // ウィンドウの高さ
			NULL,                   // 親ウィンドウ（なし）
			NULL,                   // メニュー（なし）
			hInstance,              // このプログラムのインスタンスのハンドル
			NULL                    // 追加引数（なし）
		);
	}

	ShowWindow(g_hWnd, nCmdShow); // ウィンドウを表示
	ValidateRect(g_hWnd, 0);      // WM_PAINTが呼ばれないようにする
	UpdateWindow(g_hWnd);         // ウィンドウの更新

	return true;              // InitApp関数の正常終了
}

//	デバイスの初期化関数
bool D3DInit(HWND hWnd)
{
	// Direct3Dインターフェースの取得
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL) 
	{
		// Direct3Dインターフェースの取得に失敗
		MessageBox(hWnd, "Direct3Dインターフェースの作成に失敗しました", "エラー", MB_OK);
		return false;
	}

	// デバイスの生成に利用する情報構造体の作成
	D3DPRESENT_PARAMETERS d3dpp = {};

	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// バックバッファの横幅				
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// バックバッファの縦幅
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;						// バックバッファのフォーマット指定
	d3dpp.BackBufferCount = 1;										// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// スワップエフェクト（スワップ方法）の設定		
	d3dpp.Windowed = TRUE;											// ウィンドウモード or フルスクリーン
	d3dpp.EnableAutoDepthStencil = TRUE;							// 深度バッファ・ステンシルバッファの使用				
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// 深度バッファ・ステンシルバッファのフォーマット指定
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// フルスクリーン時のリフレッシュレートの指定
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// リフレッシュレートとPresent処理の関係

	// Direct3Dデバイスの取得
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetHWND(), D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice))) {
		// デバイスの作成に失敗
		MessageBox(hWnd, "Direct3Dデバイスの作成に失敗しました", "エラー", MB_OK);
		return false;
	}

	//ライトをオフにする
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);

	//g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);

	//アドレッシングモード：ラップ（画像を繰り返す）
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//アドレッシングモード：ミラー（画像を反転させて繰り返す）
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	//アドレッシングモード：クランプ（最後のカラーで以降を塗りつぶし）
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	//アドレッシングモード：ボーダー（特定の色で塗りつぶし）
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 0, 0, 255));

	//テクスチャフィルター：ポイント
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	//テクスチャフィルター：バイリニアフィルタ
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//テクスチャフィルター：異方性フィルタ
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);

	//	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);
	//	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);


	// アルファブレンドの設定
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

	// 頂点カラーとテクスチャのブレンド設定
	//	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	return true;
}

// デバイスの終了処理
void D3DUninit()
{
	SAFE_RELEASE(g_pD3DDevice);	//	Direct3Dデバイスの解放
	SAFE_RELEASE(g_pD3D);		//	Direct3Dインタフェースの解放
}

//　初期化処理関数
bool Init(HINSTANCE hInst)
{
	//シードの初期化
	srand((unsigned int)time(NULL));

	// ゲームの初期化(Direct3Dの初期化)
	if (!D3DInit(g_hWnd))
	{
		return false;	// ゲームの初期化に失敗した
	}
	
	//	入力処理の初期化
	if (!Input::Init(hInst,g_hWnd))
	{
		return false;
	}

	if (!Sound::Init(g_hWnd))
	{
		return false;
	}
	
	//	ゲーム初期化処理
	SceneManager::Init();

	return true;
}

//　終了処理関数
void Uninit()
{
	//	XAudioの終了処理
	Sound::Uninit();

	//	ゲーム終了処理
	SceneManager::Uninit();

	//	入力処理の終了処理
	Input::Uninit();

	// ゲームの終了処理(Direct3Dの終了処理)
	D3DUninit();
}

// 更新処理関数
void Update()
{	
	//	入力処理の更新
	Input::Update();

	//	ゲーム更新処理
	SceneManager::Update();

}

// 描画処理関数
void Draw()
{
	LPDIRECT3DDEVICE9 pD3DDevice = GetD3DDevice();

	// 画面のクリア
	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(50, 50, 50, 255), 1.0f, 0);

	// 描画バッチ命令の開始
	pD3DDevice->BeginScene();

	//	ゲーム描画処理
	SceneManager::Draw();

	// 描画バッチ命令の終了
	pD3DDevice->EndScene();

	// バックバッファをフリップ（タイミングはD3DPRESENT_PARAMETERSの設定による）
	pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//	Direct3DDeviceのゲッター
LPDIRECT3DDEVICE9 GetD3DDevice() 
{
	return g_pD3DDevice;
}


//	ウィンドウハンドルのゲッター
HWND GetHWND()
{
	return g_hWnd;
}


double frand() 
{
	return (double)rand() / RAND_MAX;
}
