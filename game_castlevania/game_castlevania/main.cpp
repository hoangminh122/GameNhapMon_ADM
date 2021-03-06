﻿/* =============================================================
INTRODUCTION TO GAME PROGRAMMING SE102

SAMPLE 00 - INTRODUCTORY CODE

This sample illustrates how to:

1/ Create a window
2/ Initiate DirectX 9, Direct3D, DirectX Sprite
3/ Draw a static brick sprite to the screen

WARNING: This example contains a hell LOT of *sinful* programming practices
================================================================ */


#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Brick.h"
#include <typeinfo>
#include "Map.h"
#include "define.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 40, 100)
//#define SCREEN_WIDTH 300
//#define SCREEN_HEIGHT 250

#define MAX_FRAME_RATE 120

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20

Game* game;

//Mario* mario;
//Goomba* goomba;
//
//vector<LPGAMEOBJECT> objects;
//Map* map1;



//class CSampleKeyHander : public CKeyEventHandler
//{
//	virtual void KeyState(BYTE* states);
//	virtual void OnKeyDown(int KeyCode);
//	virtual void OnKeyUp(int KeyCode);
//};
//
//CSampleKeyHander* keyHandler;
//
//void CSampleKeyHander::OnKeyDown(int KeyCode)
//{
//	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
//	switch (KeyCode)
//	{
//	case DIK_SPACE:
//		mario->SetState(MARIO_STATE_JUMP);
//		break;
//	case DIK_A: // reset
//		mario->SetState(MARIO_STATE_IDLE);
//		mario->SetLevel(MARIO_LEVEL_BIG);
//		mario->SetPosition(50.0f, 0.0f);
//		mario->SetSpeed(0, 0);
//		break;
//	}
//	
//}

//void CSampleKeyHander::OnKeyUp(int KeyCode)
//{
//	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
//}
//
//void CSampleKeyHander::KeyState(BYTE* states)
//{
//	if (game->IsKeyDown(DIK_RIGHT))
//		mario->SetState(MARIO_STATE_WALKING_RIGHT);
//	else if (game->IsKeyDown(DIK_LEFT))
//		mario->SetState(MARIO_STATE_WALKING_LEFT);
//	else mario->SetState(MARIO_STATE_IDLE);
//	if (game->IsKeyDown(DIK_A))
//		mario->SetSpeed(10, 10);
//}

//nhận xử lý sự kiện cuae window, xử lý hằng đợi
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


void Update(DWORD dt)
{
	Game::GetInstance()->GetCurrentScene()->Update(dt);
}

/*
Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
	
	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		Game::GetInstance()->GetCurrentScene()->Render();
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			game->ProcessKeyboard();
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	game = Game::GetInstance();
	game->Init(hWnd);
	game->InitKeyboard();

	//LoadResources();
	game->Load(L"manageScene.txt");

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	//SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}