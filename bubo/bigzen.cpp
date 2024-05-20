#include "bigzen.h"

void bigzen::Init(int s, int x, int y)
{
	sight = s;
	SetX(x);
	SetY(y);
	idY = sight;

	m_bigzen.LoadBitmapByPath("resource/zenchan.bmp");
	m_bigzen.setTransparentColor(RGB(0, 64, 192));
	chicken.LoadBitmapByPath("resource/chicken.bmp");
	chicken.setTransparentColor(RGB(0, 64, 192));
	HPbar.LoadBitmapByPath("resource/HPbar.bmp");

	state = state_appear;
	appearY = -99;
}

void bigzen::Update(float dt)
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
		idY = (!rage) ? sight : 2 + sight;

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
				if (!checkcoll(1))	SetX(GetX() - 1 + sight * 2);
			}
		}

		if (!checkcoll(2))
		{
			state = state_fall;
		}

		else if (checkcoll(1))  sight = !sight;

		break;

	case state_fall:

		if (GetTickCount() - t > 200)
		{
			t = GetTickCount();
			if (++idX > 3)	idX = 0;
		}

		if (!checkcoll(2))	SetY(GetY() + 1);
		if (!checkcoll(2))	SetY(GetY() + 1);
		if (!checkcoll(2))	SetY(GetY() + 1);
		if (rage)
		{
			if (!checkcoll(2))	SetY(GetY() + 1);
			if (!checkcoll(2))	SetY(GetY() + 1);
		}
		if (GetY() >= 700)SetY(-98);

		if (checkcoll(2))
		{
			state = state_walk;
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
				case 0:	idX = 1;				break;
				case 1:	idX = 2;	bubbledir = 1;	break;
				}
				break;

			case 1:
				switch (idX)
				{
				case 2:	idX = 1;				break;
				case 1:	idX = 0;	bubbledir = 0;	break;
				}
				break;
			}

		}
		SetY(GetY() - 1);
		SetY(GetY() - 1);
		SetY(GetY() - 1);
		SetY(GetY() - 1);
		if (GetY() < -99) SetY(700);

		if (GetTickCount() - bubbletime > 2500)
		{
			bubbletime = GetTickCount();
			switch (idY)
			{
			case 5:	case 6:			idY = 7;	break;
			case 7:					idY = 8;	break;
			case 8:	rage = true;	idY = 2 + sight;	state = state_fall;		HP = 10;	break;

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
		if (!checkcoll(3))	SetX(GetX() - 1 + sight * 2);
		if (checkcoll(3)) sight = !sight;

		if (GetY() >= 700)SetY(-98);
		if (GetY() < -99) SetY(700);

		if (die_updown)
		{
			SetY(GetY() - 1);
			SetY(GetY() - 1);
			SetY(GetY() - 1);
			SetY(GetY() - 1);
		}
		else
		{
			if (!checkcoll(2))	SetY(GetY() + 1);
			if (!checkcoll(2))	SetY(GetY() + 1);
			if (!checkcoll(2))	SetY(GetY() + 1);
			if (!checkcoll(2))	SetY(GetY() + 1);
			if (checkcoll(2))	state = state_food;
		}
		if (GetTickCount() - t2 > 1500)
		{
			die_updown = false;
		}

		break;

	}
}

void bigzen::Render(HDC hdc, float dt)
{
	switch (state)
	{
	case state_appear:
		m_bigzen.drawBitmapByCropping(hdc, GetX(), appearY, 100, 100,
			idX*ori_char_size, idY*ori_char_size, ori_char_size, ori_char_size);
		break;
	case state_food:
		chicken.drawBitmap(hdc, GetX(), GetY(), 100, 100);
		break;
	case state_walk:	case state_fall:	case state_die:		case state_bubble:
		if (GetTickCount() - blinktime > 100)
			m_bigzen.drawBitmapByCropping(hdc, GetX(), GetY(), 100, 100,
			idX*ori_char_size, idY*ori_char_size, ori_char_size, ori_char_size);
		break;
	}

	if (HP > 0)
		(secondHPbar) ? HPbar.drawBitmap(hdc, 0, 25, HP * 10, 24) : HPbar.drawBitmap(hdc, 0, 0, HP * 10, 24);
}

void bigzen::Destroy()
{
	Collrect.clear();
	Wallrect.clear();
}

bool bigzen::checkcoll(int a)
{
	RECT dest;
	RECT rect1 = { GetX() - 1 + sight * 2,GetY(),GetX() + 98 + sight * 2,GetY() + 99 };	//앞
	RECT rect2 = { GetX(),GetY() + 98,GetX() + 99,GetY() + 100 };						//아래

	switch (a)
	{
	case 1:	//벽 충돌 조사

		for (auto it = Wallrect.begin(); it != Wallrect.end(); ++it)
			if (IntersectRect(&dest, &rect1, &(*it)))	return true;

		break;

	case 2:	//바닥 착지 조사
		for (auto it = Collrect.begin(); it != Collrect.end(); ++it)
			if (IntersectRect(&dest, &rect2, &(*it)))	return true;

		break;

	case 3:	//날아갈때 벽 충돌
		for (auto it = Wallrect.begin(); it != Wallrect.end(); ++it)
			if (IntersectRect(&dest, &rect1, &(*it)))	return true;
		break;
	}

	return false;
}
