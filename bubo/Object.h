#pragma once
#include "Bitmap.h"

class Object
{
private:
	
	long			mPosiX = 0;
	long			mPosiY = 0;

public :
	void			SetX(int value)		{ mPosiX = value; }
	void			SetY(int value)		{ mPosiY = value; }
	
	
	long			GetX()				{ return mPosiX; }
	long			GetY()				{ return mPosiY; }

	virtual	void	Init()						= 0;
	virtual void	Update(float dt)			= 0;
	virtual void	Render(HDC hdc, float dt)	= 0;
	virtual void	Destroy()					= 0;
};

