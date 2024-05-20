#include "GameDirector.h"

int playerlife[2] = { 0,0 };
int playerxy[4] = { 0,0,0,0 };

GameDirector * GameDirector::GetGameDirector()
{
	static GameDirector dir;
	return &dir;
}

// 콜백함수 WndProc
LRESULT GameDirector::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY :	PostQuitMessage(0);	return 0;
	// 그 외의 다른 모든 메세지들은 system클래스의 메세지 처리기에 전달합니다.
	default: return ApplicationHandle->MessageHandler(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT GameDirector::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 마우스 포지션
	// LOWORD(lParam);	// x좌표
	// HIWORD(lParam);	// y좌표
	switch (message)
	{
	case WM_MOUSEMOVE :
		m_SceneManager->SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void GameDirector::ProcessingLoop()
{
	static DWORD prevFrameTime = 0;

	if (GetTickCount() - prevFrameTime > m_FrameInterval)
	{
		Update(((float)GetTickCount() - (float)prevFrameTime) / 1000.0f);
		
		HDC hdc = GetDC(m_hWnd);

		Render(hdc, ((float)GetTickCount() - (float)prevFrameTime) / 1000.0f);
		ReleaseDC(m_hWnd, hdc);
		prevFrameTime = GetTickCount();
	}
}

void GameDirector::Update(float dt)
{
	// SceneManager 작성 후 Update() 호출
	m_SceneManager->Update(dt);
}

void GameDirector::Render(HDC hdc, float dt)
{
	HDC hMemDC;
	RECT windowRect;
	HBITMAP bitmap;

	GetClientRect(this->GetWndHandle(), &windowRect);

	hMemDC = CreateCompatibleDC(hdc);
	bitmap = CreateCompatibleBitmap(hdc, windowRect.right, windowRect.bottom);

	SelectObject(hMemDC, bitmap);
	FillRect(hMemDC, &windowRect, (HBRUSH)COLOR_BACKGROUND);

	// SceneManager 작성 후 Render() 호출
	m_SceneManager->Render(hMemDC, dt);

	BitBlt(hdc, 0, 0, windowRect.right, windowRect.bottom, hMemDC, 0, 0, SRCCOPY);

	DeleteObject(bitmap);
	DeleteDC(hMemDC);
}

void GameDirector::SetFrameInterval(DWORD interval)
{
	m_FrameInterval = interval;
}

DWORD GameDirector::GetFrameInterval()
{
	return m_FrameInterval;
}

SceneManager * GameDirector::GetSceneManager()
{
	return m_SceneManager;
}

GameDirector::GameDirector() : m_FrameInterval(0)
{
	ApplicationHandle = this;
	m_SceneManager = new SceneManager;
}


GameDirector::~GameDirector()
{
	delete m_SceneManager;
}
