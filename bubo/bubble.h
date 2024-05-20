#pragma once
#include "Object.h"

class bubble :
	public Object
{
public:
	void			Init(int x,int y,int s,int p);
	virtual	void	Init();
	virtual void	Update(float dt);
	virtual void	Render(HDC hdc, float dt);
	virtual void	Destroy();

	int				getcount() { return count; }
	bool			getboom() { return boom; }
	void			setboom() { boom = true; }

	void			boomevent() { if (count == 2) { count = 3; t2 = GetTickCount(); } }

	bool			checkcoll();
	void			setCollrect(RECT rc) { Collrect.push_back(rc);}
	void			setWallrect(RECT rc) { Wallrect.push_back(rc); }

	RECT			getrect()
	{
		RECT	rc = { GetX(),GetY(),GetX() + char_size - 1,GetY() + char_size - 1 };
		return rc;
	}

	int	getidX() { return idX; }	void	setidX(int value) { if (count == 2) idX = value; }
	int getidY() { return idY; }

	void			pushX(int dir)
	{
		if (count == 2) 
		{
			idX = 8;
			if (!checkcoll())	SetX(GetX() - 1 + dir * 2);
			if (!checkcoll())	SetX(GetX() - 1 + dir * 2);
			if (!checkcoll())	SetX(GetX() - 1 + dir * 2);
		}
	}

private:

	//Bitmap			mbubble;

	list<RECT>		Collrect;
	list<RECT>		Wallrect;

	int		sight;
	int		count=0;
	int		t;
	int		t2;

	int		idX;
	int		idY;

	bool	boom = false;

};

