#pragma once
#include "GameDefine.h"

class PrepareWnd;

class WrappedWnd
{
public :
	int					Loop(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow);

private :
	void				registerWndClass(const PrepareWnd& value);
	void				createWindow(const PrepareWnd& value);
	void				showWindow(const PrepareWnd& value);
	int					MessageLoop();

public :
	virtual void		ProcessingLoop() = 0;

protected :
	HWND				m_hWnd;
	HINSTANCE			m_hInstance;

public :
	HWND				GetWndHandle();
	HINSTANCE			GetInstanceHandle();

public:
	WrappedWnd();
	~WrappedWnd();
};

