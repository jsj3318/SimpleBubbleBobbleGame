#include "Bitmap.h"


Bitmap::Bitmap() : m_BitmapHandle(nullptr), m_FileDir("")
{
	memset(&m_BitmapInfo, 0, sizeof(m_BitmapInfo));
}

Bitmap::Bitmap(const std::string fileDir)
{
	this->LoadBitmapByPath(fileDir);
}

Bitmap::Bitmap(const Bitmap & bitmap)
{
	this->LoadBitmapByPath(bitmap.getFileDirectory());
}


Bitmap::~Bitmap()
{
	if (!this->empty()){
		DeleteObject(m_BitmapHandle);
	}
}

bool Bitmap::LoadBitmapByPath(const std::string fileDir)
{
	if (m_BitmapHandle) return true;

	m_BitmapHandle = (HBITMAP)LoadImageA(nullptr, fileDir.c_str(), 
		IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE | LR_DEFAULTSIZE);

	if (this->empty())
		return false;

	GetObject(m_BitmapHandle, sizeof(m_BitmapInfo), &m_BitmapInfo);
	m_FileDir = fileDir;

	return true;
}

bool Bitmap::empty() const
{
	return m_BitmapHandle == nullptr;
}

HBITMAP Bitmap::getBitmapHandle() const
{
	return m_BitmapHandle;
}

const BITMAP& Bitmap::getBitmapInfo() const
{
	return m_BitmapInfo;
}

std::string Bitmap::getFileDirectory() const
{
	return m_FileDir;
}

void Bitmap::drawBitmap(HDC hdc, int x, int y, int width, int height) const
{
	this->drawBitmapByCropping(hdc, x, y, width, height, 0, 0, m_BitmapInfo.bmWidth, m_BitmapInfo.bmHeight);
}

void Bitmap::drawBitmapByCropping(HDC hdc, int x, int y, int width, int height, int sx, int sy, int sw, int sh) const
{
	HDC hMemDC;

	hMemDC = CreateCompatibleDC(hdc);

	SelectObject(hMemDC, m_BitmapHandle);

	TransparentBlt(
		hdc, x, y,
		width == 0 ? m_BitmapInfo.bmWidth : width,
		height == 0 ? m_BitmapInfo.bmWidth : height,
		hMemDC, sx, sy, sw, sh, getTransparentColor());

	DeleteDC(hMemDC);
}

void Bitmap::setTransparentColor(DWORD color)
{
	m_TransparentColor = color;
}

DWORD Bitmap::getTransparentColor() const
{
	return m_TransparentColor;
}
