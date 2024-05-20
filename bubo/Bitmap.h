#pragma once
#include "GameDefine.h"
#include <string>

class Bitmap
{
public:
	Bitmap();
	Bitmap(const std::string fileDir);
	Bitmap(const Bitmap& bitmap);
	~Bitmap();

public :
	bool				LoadBitmapByPath(const std::string fileDir);

public :
	bool				empty() const;

	HBITMAP				getBitmapHandle() const;
	const BITMAP&		getBitmapInfo() const;
	std::string			getFileDirectory() const;

public :
	void				drawBitmap(HDC hdc, int x, int y, int width, int height) const;
	void				drawBitmapByCropping(HDC hdc, int x, int y, int width, int height, int sx, int sy, int sw, int sh) const;

protected :
	HBITMAP				m_BitmapHandle;
	BITMAP				m_BitmapInfo;
	std::string			m_FileDir;

public :
	void				setTransparentColor(DWORD color);
	DWORD				getTransparentColor() const;

private :
	DWORD				m_TransparentColor = RGB(255, 0, 255);
};

