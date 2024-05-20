#include "GameDirector.h"

int playerlife[2] = { 0,0 };
int playerxy[4] = { 0,0,0,0 };

GameDirector * GameDirector::GetGameDirector()
{
	static GameDirector dir;
	return &dir;
}

// �ݹ��Լ� WndProc
LRESULT GameDirector::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY :	PostQuitMessage(0);	return 0;
	// �� ���� �ٸ� ��� �޼������� systemŬ������ �޼��� ó���⿡ �����մϴ�.
	default: return ApplicationHandle->MessageHandler(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT GameDirector::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// ���콺 ������
	// LOWORD(lParam);	// x��ǥ
	// HIWORD(lParam);	// y��ǥ
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
	// SceneManager �ۼ� �� Update() ȣ��
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

	// SceneManager �ۼ� �� Render() ȣ��
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
