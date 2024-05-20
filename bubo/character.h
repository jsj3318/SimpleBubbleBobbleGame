#pragma once
#include "bubble.h"
class character :
	public Object
{
public:
	void			Init(int playernumber);
	virtual	void	Init();

	virtual void	Update(float dt);
	virtual void	Render(HDC hdc, float dt);
	virtual void	Destroy();
	bool			checkcoll(int a);

	void			setCollrect(RECT rc) { Collrect.push_back(rc); }
	void			setWallrect(RECT rc) { Wallrect.push_back(rc); }
	void			setstate(int a) {	state = a;	}

	void			dieevent()
	{
		if (!blink&&live)
		{
			state = state_die;
			live = false;
			t = GetTickCount();
			t2 = GetTickCount();
			count = 0;
		}
	}
	
	RECT			getrect()
	{
		RECT	rc = { GetX(),GetY(),GetX() + char_size - 1,GetY() + char_size - 1 };
		return rc;
	}

	RECT			getspikerect()
	{
		RECT	rc = { GetX() + 19 - sight * 16,GetY(),GetX() + 46 - sight * 16,GetY() + 46 };
		return rc;
	}


	int getsight() { return sight; }
	void setlife(int c) { life = c; }
	int getlife() { return life; }

	list<bubble>	bubblelist;
	bool			live=false;
	bool			erase = false;

private:
	int				player = 0;		// 0=1p 1=2p

	int				life;
	bool			shooting = false;
	
	list<RECT>		Collrect;
	list<RECT>		Wallrect;

	Bitmap			m_char;
	Bitmap			m_die;
	Bitmap			m_push;
	Bitmap			m_bubble;
	Bitmap			m_lifeicon;

	Bitmap			mbubble;

	int				t = 0;
	int				t2 = 0;
	int				t3 = 0;
	int				t4 = 0;
	int				t5 = 0;
	int				idX;
	int				idY;

	int				St;
	int				SX;
	int				SY;
	int				Sdel;

	int				count; //die push bubble 에서 사용

	int				state;
	int				sight;

	bool			SBdelay = false;
	bool			JBdelay = false;

	bool			blink = false;
	bool			visible = true;

	int				key_left;
	int				key_right;
	int				key_shoot;
	int				key_jump;
	int				key_start;
};

