#pragma once
#include "Object.h"

class bigzen :
	public Object
{
public:
	void			Init(int s, int x, int y);
	virtual	void	Init() { return; }
	virtual void	Update(float dt);
	virtual void	Render(HDC hdc, float dt);
	virtual void	Destroy();

	bool			checkcoll(int a);
	void			setCollrect(RECT rc) { Collrect.push_back(rc); }
	void			setWallrect(RECT rc) { Wallrect.push_back(rc); }

	RECT			getrect()
	{
		RECT	rc = { GetX(),GetY(),GetX() + 99,GetY() + 99 };
		return rc;
	}

	int				getstate() { return state; }

	void			gethit(int player)
	{
		blinktime = GetTickCount();
		if (--HP < 1)
		{
			bubbletime = GetTickCount();

			idX = 0;
			bubbledir = 0;

			t = GetTickCount();
			t2 = 0;
			t3 = 0;
			count = 0;
			sight = 0;

			idX = 0;
			if (!rage)
			{
				switch (player)
				{
				case 1:	idY = 5; break;
				case 2: idY = 6; break;
				}
			}
			else idY = 7;

			state = state_bubble;
		}
	}
	
	void			dieevent(int charsight)
	{
		idX = 0;
		idY = 4;
		state = state_die;
		sight = charsight;
		t2 = GetTickCount();
		die_updown = true;
	}

	void			pushX(int dir)
	{
		sight = dir;
		if (!checkcoll(1))	SetX(GetX() - 1 + dir * 2);
		if (!checkcoll(1))	SetX(GetX() - 1 + dir * 2);
		if (!checkcoll(1))	SetX(GetX() - 1 + dir * 2);
	}

	bool erase = false;
	bool appear = false;
	bool movestart = false;

	bool secondHPbar = false;

private:
	Bitmap	m_bigzen;
	Bitmap	chicken;
	Bitmap	HPbar;

	list<RECT>		Collrect;
	list<RECT>		Wallrect;

	int				HP = 80;
	int				blinktime = 0;

	bool			rage = false;
	bool			start = true;
	int				sight;

	int				state;

	int				idX = 0;
	int				idY = 0;

	int	t = 0;
	int	t2 = 0;
	int	t3 = 0;
	int count = 0;
	int bubbletime = 0;

	int bubbledir = 0;
	bool die_updown;

	int	appearY;
};
