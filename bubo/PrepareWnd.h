#pragma once
#include "GameDefine.h"

class PrepareWnd
{
public:
	PrepareWnd();
	~PrepareWnd();

public :
	// WNDCLASSEX 정보
	UINT		cbSize;
	UINT		style;
	WNDPROC		lpfnWndProc;
	int			cbClsExtra;
	int			cbWndExtra;
	HINSTANCE	hInstance;
	HICON		hIcon;
	HCURSOR		hCursor;
	HBRUSH		hbrBackground;
	LPCSTR		lpszMenuName;
	LPCSTR		lpszClassName;

	// 윈도우 창 생성 (정보)
public :
	LPCSTR		lpWindowName;
	DWORD		dwStyle;
	int			X;
	int			Y;
	int			nWidth;
	int			nHeight;
	HWND		hWndParent;
	HMENU		hMenu;
	LPVOID		lpParam;

	// 콘솔 표시
public :
	int			nCmdShow;
};

