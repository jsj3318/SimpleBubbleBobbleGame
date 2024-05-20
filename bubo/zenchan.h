#pragma once
#include "Object.h"

class zenchan :
	public Object
{
public :
	void			Init(int s,int x,int y);
	virtual	void	Init();
	virtual void	Update(float dt);
	virtual void	Render(HDC hdc, float dt);
	virtual void	Destroy();

	bool			checkcoll(int a);
	void			setCollrect(RECT rc) {	Collrect.push_back(rc);	}
	void			setWallrect(RECT rc) { Wallrect.push_back(rc); }

	RECT			getrect()
	{
		RECT	rc = { GetX(),GetY(),GetX() + char_size - 1,GetY() + char_size - 1 };
		return rc;
	}

	void			setpxy(int x,int y, int x2, int y2);
	void			fall_setsight();
	bool			check_jump();

	int				getstate() { return state; }

	void			bubbleevent(int a) 
	{ 
		bubbletime = GetTickCount();

		t = GetTickCount();
		t2 = 0;
		t3 = 0;
		count = 0;
		sight = 0;

		bubbledir = 0;
		idX = 0;
		if (!rage)
		{
			switch (a)
			{
			case 1:	idY = 5; break;
			case 2: idY = 6; break;
			}
		}
		else idY = 7;

		state = state_bubble;
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
	bool p1live;
	bool p2live;
	bool appear = false;
	bool movestart = false;

private:
	Bitmap	m_zen;
	Bitmap	burger;

	list<RECT>		Collrect;
	list<RECT>		Wallrect;

	int	p1x;		
	int p1y;		
	int p2x;
	int p2y;

	bool			rage = false;
	bool			start = true;
	int				sight;

	int				state;

	int				idX = 0;
	int				idY = 0;

	int	t=0;
	int	t2=0;
	int	t3=0;
	int count = 0;
	int bubbletime = 0;

	int bubbledir = 0;
	bool die_updown;

	int	appearY;
};

