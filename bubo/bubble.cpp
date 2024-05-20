#include "bubble.h"


void bubble::Init(int x, int y, int s,int p)
{
	// mbubble.LoadBitmapByPath("resource/bubble.bmp");
	// mbubble.setTransparentColor(RGB(0, 64, 192));
	
	SetX(x);
	SetY(y);
	sight = s;
	idY = p;

	idX = 0;

	t = GetTickCount();
	t2 = GetTickCount();
	count = 1;
}

void bubble::Init()
{
	
}

void bubble::Update(float dt)
{

	switch (count)
	{

	case 1:

		if (GetTickCount() - t > 70)
		{
			t = GetTickCount();
			if(idX<5)	idX++;
		}

		if (!checkcoll())	SetX(GetX() - 1 + (sight * 2));
		if (!checkcoll())	SetX(GetX() - 1 + (sight * 2));
		if (!checkcoll())	SetX(GetX() - 1 + (sight * 2));
		if (!checkcoll())	SetX(GetX() - 1 + (sight * 2));
		if (!checkcoll())	SetX(GetX() - 1 + (sight * 2));
		if (!checkcoll())	SetX(GetX() - 1 + (sight * 2));
		if (!checkcoll())	SetX(GetX() - 1 + (sight * 2));
		if (!checkcoll())	SetX(GetX() - 1 + (sight * 2));
		if (!checkcoll())	SetX(GetX() - 1 + (sight * 2));
		if (!checkcoll())	SetX(GetX() - 1 + (sight * 2));

		if (GetTickCount() - t2 > 400 || checkcoll())
		{
			t = GetTickCount();
			t2 = GetTickCount();
			idX = 6;
			count = 2;
		}

		

		break;

	case 2:
		if (GetY() > 100)	SetY(GetY() - 1);
		if (GetTickCount() - t > 7000)	boomevent();

		break;

	case 3:
		idX = 0;
		idY = 2;
		if(GetTickCount()-t2>400)	boom = true;


		break;

	}
}

void bubble::Render(HDC hdc, float dt)
{
	/*mbubble.drawBitmapByCropping(hdc, GetX(), GetY(), char_size, char_size,
		idX*ori_char_size, idY*ori_char_size, ori_char_size, ori_char_size);*/
}

void bubble::Destroy()
{
	Collrect.clear();
	Wallrect.clear();
}

bool bubble::checkcoll()
{
	RECT dest;
	RECT rect1 = { GetX() - 1 + sight * 2,GetY(),GetX() + 48 + sight * 2,GetY() + 49 };	//¾Õ
	
	for (auto it = Collrect.begin(); it != Collrect.end(); ++it)
		if (IntersectRect(&dest, &rect1, &(*it)))	return true;
	for (auto it = Wallrect.begin(); it != Wallrect.end(); ++it)
		if (IntersectRect(&dest, &rect1, &(*it)))	return true;

	return false;

}


