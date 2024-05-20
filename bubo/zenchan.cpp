#include "zenchan.h"



void zenchan::Init(int s, int x, int y)
{
	sight = s;
	SetX(x);
	SetY(y);
	idY = sight;

	m_zen.LoadBitmapByPath("resource/zenchan.bmp");
	m_zen.setTransparentColor(RGB(0, 64, 192));
	burger.LoadBitmapByPath("resource/hamburger.bmp");
	burger.setTransparentColor(RGB(0, 64, 192));

	state = state_appear;
	appearY = -50;
}

void zenchan::Init()
{
}

void zenchan::Update(float dt)
{
	switch (state)
	{
	case state_appear:

		if (appear)
		{
			if (appearY < GetY()) appearY++;
			if (appearY < GetY()) appearY++;
			if (appearY < GetY()) appearY++;
			if (appearY < GetY()) appearY++;
			else state = state_walk;

			if (GetTickCount() - t > 200)
			{
				t = GetTickCount();
				if (++idX > 3)	idX = 0;
			}
		}

		break;

	case state_walk:
		idY = (!rage) ? sight : 2+sight;

		if (GetTickCount() - t > 200)
		{
			t = GetTickCount();
			if (++idX > 3)	idX = 0;
		}

		if (movestart)
		{
			if (!checkcoll(1))	SetX(GetX() - 1 + sight * 2);
			if (!checkcoll(1))	SetX(GetX() - 1 + sight * 2);
			if (!checkcoll(1))	SetX(GetX() - 1 + sight * 2);
			if (rage)
			{
				if (!checkcoll(1))	SetX(GetX() - 1 + sight * 2);
				if (!checkcoll(1))	SetX(GetX() - 1 + sight * 2);
			}
		}
		
		if (!checkcoll(2))
		{
			state = state_fall;
		}

		if (checkcoll(1))  sight = (!sight) ? 1 : 0;

		if (check_jump())
		{
			state = state_jump;
			count = 0;
			idX = 0;
			t = GetTickCount();
			t2 = GetTickCount();
		}

		break;

	case state_jump:

		switch (count)
		{
		case 0:

			if (GetTickCount() - t > 200)
			{
				t = GetTickCount();
				if(!rage)	idY = (idY == 1) ? 0 : 1;
				else		idY = (idY == 3) ? 2 : 3;
			}

			if (GetTickCount() - t2 > 400)
			{
				count = 1;
				t2 = GetTickCount();
				t = GetTickCount();
				idX = 0;
			}

			break;

		case 1:

			if (GetTickCount() - t > 200)
			{
				t = GetTickCount();
				if (++idX > 3)	idX = 0;
			}

			if (GetTickCount() - t3 > 15)
			{
				t3 = GetTickCount();
				SetY(GetY() - 4);
			}

			if (GetTickCount() - t2 > 1000)
			{
				state = state_fall;
			}
			break;
		}



		break;

	case state_fall:

			if (GetTickCount() - t > 200)
			{
				t = GetTickCount();
				if (++idX > 3)	idX = 0;
			}

			if (!checkcoll(2))	SetY(GetY() + 1);
			if (!checkcoll(2))	SetY(GetY() + 1);
			if (rage)	if (!checkcoll(2))	SetY(GetY() + 1);

			if (GetY() >= 700)SetY(-49);

			if (checkcoll(2))
			{
				state = state_walk;
				fall_setsight();
				idY = (!rage) ? sight : 2 + sight;
			}


			break;

	case state_bubble:

		if (GetTickCount() - t > 500)
		{
			t = GetTickCount();
			switch (bubbledir)
			{
			case 0:	
				switch (idX)
				{
				case 0:	idX = 1;					break;
				case 1:	idX = 2;	bubbledir = 1;	break;
				}
				break;

			case 1:
				switch (idX)
				{
				case 2:	idX = 1;					break;
				case 1:	idX = 0;	bubbledir = 0;	break;
				}
				break;
			}

		}

		if (GetY() > 100)	SetY(GetY() - 1);

		if (GetTickCount() - bubbletime > 4000)
		{
			bubbletime = GetTickCount();
			switch (idY)
			{
			case 5:	case 6:			idY = 7;	break;
			case 7:					idY = 8;	break;
			case 8:	rage = true;	idY = 2 + sight;	state = state_fall;		 break;

			}
		}

		break;
		

	case state_die:
		if (GetTickCount() - t > 300)
		{
			t = GetTickCount();
			if (++idX > 3)	idX = 0;
		}
		if (!checkcoll(3))	SetX(GetX() - 1 + sight * 2);
		if (!checkcoll(3))	SetX(GetX() - 1 + sight * 2);
		if (!checkcoll(3))	SetX(GetX() - 1 + sight * 2);
		if (!checkcoll(3))	SetX(GetX() - 1 + sight * 2);
		if (checkcoll(3)) sight = !sight;

		if (die_updown)
		{
			SetY(GetY() - 1);
			SetY(GetY() - 1);
			SetY(GetY() - 1);
		}
		else
		{
			if (!checkcoll(2))	SetY(GetY() + 1);
			if (!checkcoll(2))	SetY(GetY() + 1);
			if (!checkcoll(2))	SetY(GetY() + 1);
			if (checkcoll(2))	state = state_food;
		}
		if (GetTickCount() - t2 > 1500 || GetY() < 100)
		{
			die_updown = false;
		}

		break;

	}
}

void zenchan::Render(HDC hdc, float dt)
{
	switch (state)
	{
	case state_appear:
		m_zen.drawBitmapByCropping(hdc, GetX(), appearY, char_size, char_size,
			idX*ori_char_size, idY*ori_char_size, ori_char_size, ori_char_size);
		break;
	case state_food:
		burger.drawBitmap(hdc, GetX(), GetY(), char_size, char_size);
		break;
	case state_walk:	case state_jump:	case state_fall:	case state_die:	case state_bubble:
		m_zen.drawBitmapByCropping(hdc, GetX(), GetY(), char_size, char_size,
			idX*ori_char_size, idY*ori_char_size, ori_char_size, ori_char_size);
		break;
	}
	

}

void zenchan::Destroy()
{
	erase = true;
	Collrect.clear();
	Wallrect.clear();
}

bool zenchan::checkcoll(int a)
{
	RECT dest;
	RECT rect1 = { GetX() - 1 + sight * 2,GetY(),GetX() + 48 + sight * 2,GetY() + 49 };	//앞
	RECT rect2 = { GetX(),GetY() + 49,GetX() + 49,GetY() + 50 };						//아래

	switch (a)
	{
	case 1:	//벽 충돌 조사

		for (auto it = Wallrect.begin(); it != Wallrect.end(); ++it)
			if (IntersectRect(&dest, &rect1, &(*it)) && !IntersectRect(&dest, &getrect(), &(*it)))	return true;

		break;

	case 2:	//바닥 착지 조사
		for (auto it = Collrect.begin(); it != Collrect.end(); ++it)
			if (IntersectRect(&dest, &rect2, &(*it)) && IntersectRect(&dest, &getrect(), &(*it)))	return true;

		break;

	case 3:	//날아갈때 벽 충돌
		for (auto it = Wallrect.begin(); it != Wallrect.end(); ++it)
			if (IntersectRect(&dest, &rect1, &(*it)))						return true;
		break;
	}

	return false;

}



void zenchan::setpxy(int x, int y, int x2, int y2)
{
	p1x = x;
	p1y = y;
	p2x = x2;
	p2y = y2;
}

void zenchan::fall_setsight()
{
	if (p1live)
	{
		sight = (GetX() < p1x) ? 1 : 0;

	}
	else if (p2live)
	{
		sight = (GetX() < p2x) ? 1 : 0;
	}
	else
	{
		sight = sight;
	}

}

bool zenchan::check_jump()
{
	if (p1live)
	{
		if (p1y < GetY() && p1x + 10 > GetX() && p1x - 10 < GetX())
		{
			return true;
		}
	}
	else if (p2live)
	{
		if (p2y < GetY() && p2x + 10 > GetX() && p2x - 10 < GetX())
		{
			return true;
		}
	}
	
	return false;
	
}
