#pragma once
#include "GameDefine.h"

class PrepareWnd
{
public:
	PrepareWnd();
	~PrepareWnd();

public :
	// WNDCLASSEX ����
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

	// ������ â ���� (����)
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

	// �ܼ� ǥ��
public :
	int			nCmdShow;
};

