
#pragma once
#include "WrappedWnd.h"
#include "SceneManager.h"

class GameDirector : public WrappedWnd
{
public :
	static GameDirector*		GetGameDirector();
	static LRESULT CALLBACK		WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT	CALLBACK			MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public :
	virtual void				ProcessingLoop() override;

	void						Update(float dt);
	void						Render(HDC hdc, float dt);
	void						SetFrameInterval(DWORD interval);
	DWORD						GetFrameInterval();

	SceneManager*				GetSceneManager();

private : 
	SceneManager*				m_SceneManager;
	DWORD						m_FrameInterval;
public:
	GameDirector();
	~GameDirector();
};
// 프로그램 핸들러
static GameDirector*			ApplicationHandle = 0;
static GameDirector*			GetApplicationHandle()	{ return ApplicationHandle; }

