#include "character.h"

extern int playerlife[2];
extern int playerxy[4];


void character::Init(int playernumber)
{
	player = playernumber;

	mbubble.LoadBitmapByPath("resource/bubble.bmp");
	mbubble.setTransparentColor(RGB(0, 64, 192));

	switch (player)
	{
	case 0:
		m_char.LoadBitmapByPath("resource/bubblun/bubblun.bmp");
		m_die.LoadBitmapByPath("resource/bubblun/bubblun_die.bmp");
		m_push.LoadBitmapByPath("resource/bubblun/bubblun_push.bmp");
		m_bubble.LoadBitmapByPath("resource/bubblun/bubblun_bubble.bmp");
		m_lifeicon.LoadBitmapByPath("resource/bubblun/bubblun_life.bmp");
		key_left = 0x41;
		key_right = 0x44;
		key_shoot = 0x46;
		key_jump = 0x47;
		key_start = 0x31;
		
		break;
	case 1:
		m_char.LoadBitmapByPath("resource/bobblun/bobblun.bmp");
		m_die.LoadBitmapByPath("resource/bobblun/bobblun_die.bmp");
		m_push.LoadBitmapByPath("resource/bobblun/bobblun_push.bmp");
		m_bubble.LoadBitmapByPath("resource/bobblun/bobblun_bubble.bmp");
		m_lifeicon.LoadBitmapByPath("resource/bobblun/bobblun_life.bmp");
		key_left = VK_LEFT;
		key_right = VK_RIGHT;
		key_shoot = 0x4C;
		key_jump = 0x4B;
		key_start = VK_RETURN;
		break;
	}


	m_char.setTransparentColor(RGB(0, 64, 192));
	m_die.setTransparentColor(RGB(0, 64, 192));
	m_push.setTransparentColor(RGB(0, 64, 192));
	m_lifeicon.setTransparentColor(RGB(0, 64, 192));
	m_bubble.setTransparentColor(RGB(0, 64, 192));

	life = playerlife[player];
	if (life > 0)
	{
		state = state_bubble;
		count = 0;
		
		SetX(playerxy[player * 2]);
		SetY(playerxy[1 + player * 2]);
	}
	else
	{
		erase = true; 
		state = state_push;
		SetX(75 + player * 600);	SetY(625);
	}

	
	idX = 0;
	idY = 0;
	SX = 0;
	SY = 9;

	t = GetTickCount();
}

void character::Init()
{
}


void character::Update(float dt)
{
	switch (state)
	{
	case state_bubble:

		if (GetX() < 75 + player * 600)	SetX(GetX() + 1);
		else SetX(GetX() - 1);

		if (GetX() < 75 + player * 600)	SetX(GetX() + 1);
		else SetX(GetX() - 1);

		if (GetX() < 75 + player * 600)	SetX(GetX() + 1);
		else SetX(GetX() - 1);


		switch (count)
		{
		case 0:
			if (GetY() < 625 - 27)				SetY(GetY() + 1);
			if (GetY() < 625 - 27)				SetY(GetY() + 1);
			if (GetY() < 625 - 27)				SetY(GetY() + 1);

			if (GetTickCount() - t > 200)
			{
				t = GetTickCount();
				if (idX < 6)
				{
					idX++;
				}
				else
				{
					count = 1;
				}
			}

			break;
		case 1:
			if (GetTickCount() - t > 250)
			{
				t = GetTickCount();
				idX = (idX == 6) ? 7 : 6;
			}

			if (GetY() < 625 - 27)				SetY(GetY() + 1);
			if (GetY() < 625 - 27)				SetY(GetY() + 1);
			if (GetY() < 625 - 27)				SetY(GetY() + 1);
			
			if (GetX() == 75 + player * 600)
			{
				count = 2;
				t = GetTickCount();
				t4 = GetTickCount();
			}
			

			break;

		case 2:
			if (GetY() < 625)				SetY(GetY() + 1);

			if (GetTickCount() - t > 240)
			{
				t = GetTickCount();
				if (idX < 9)idX++;
			}

			if (GetTickCount() - t4 > 750)
			{
				t = GetTickCount();
				state = state_stay;
				idX = 0;
				idY = 0;
				sight = !player;
			}
			break;
		}
		break;

	case state_stay:	case state_walk:
		
		SY = 8 + sight;

		if(GetAsyncKeyState(key_left))
		{
			sight = 0;
			if (state != state_walk)
			{
				state = state_walk;
				t = GetTickCount();
				idX = 0;
				idY = 1;
			}
			else
			{
				if (GetTickCount() - t > 80)
				{
					t = GetTickCount();
					idX++;
					if (idX > 3)idX = 0;
				}
			}

			if (!checkcoll(1))
			{
				SetX(GetX() - 1);
			}
			if (!checkcoll(1))
			{
				SetX(GetX() - 1);
			}
			if (!checkcoll(1))
			{
				SetX(GetX() - 1);
			}


		}

		else if (GetAsyncKeyState(key_right))
		{
			sight = 1;
			if (state != state_walk)
			{
				state = state_walk;
				t = GetTickCount();
				idX = 0;
				idY = 1;
			}
			else
			{
				if (GetTickCount() - t > 80)
				{
					t = GetTickCount();
					idX++;
					if (idX > 3)idX = 0;
				}
			}

			if (!checkcoll(1))
			{
				SetX(GetX() + 1);
			}
			if (!checkcoll(1))
			{
				SetX(GetX() + 1);
			}
			if (!checkcoll(1))
			{
				SetX(GetX() + 1);
			}

		}
		else
		{
			if (state != state_stay)
			{
				t = GetTickCount();
				state = state_stay;
				idX = 0;
				idY = 0;
			}
			else
			{
				if (GetTickCount() - t > 300)
				{
					t = GetTickCount();
					idX = (idX == 0) ? 1 : 0;
				}
			}

		}

		if (GetAsyncKeyState(key_jump) && !JBdelay)
		{
			state = state_jump;
			t = GetTickCount();
			idX = 0;
			idY = 2;
			t4 = GetTickCount();
			t5 = GetTickCount();
			JBdelay = true;
		}

		if (!checkcoll(2))
		{
			state = state_fall;
			idX = 0;
			idY = 3;
			t = GetTickCount();
		}
		break;

	case state_jump:
		SY = 10 + sight;

		if (GetTickCount() - t > 150)
		{
			t = GetTickCount();
			idX = (idX == 0) ? 1 : 0;
		}
		if (GetTickCount() - t5 > 11)
		{
			t5 = GetTickCount();
			SetY(GetY() - 5);
		}

		if (GetTickCount() - t4 > 460)
		{
			state = state_fall;
			idX = 0;
			idY = 3;
			t = GetTickCount();
			t5 = 0;
		}

		if (GetAsyncKeyState(key_left))
		{
			sight = 0;
			if (!checkcoll(1))	SetX(GetX() - 1);
			if (!checkcoll(1))	SetX(GetX() - 1);
		}

		else if (GetAsyncKeyState(key_right))
		{
			sight = 1;
			if (!checkcoll(1))	SetX(GetX() + 1);
			if (!checkcoll(1))	SetX(GetX() + 1);
		}

		break;

	case state_fall:
		SY = 12 + sight;

		if (GetTickCount() - t > 200)
		{
			t = GetTickCount();
			idX = (idX == 0) ? 1 : 0;
		}


		if (GetAsyncKeyState(key_left))
		{
			sight = 0;
			if (!checkcoll(1))
			{
				SetX(GetX() - 1);
			}
			if (!checkcoll(1))
			{
				SetX(GetX() - 1);
			}
		}
		else if (GetAsyncKeyState(key_right))
		{
			sight = 1;
			if (!checkcoll(1))
			{
				SetX(GetX() + 1);
			}
			if (!checkcoll(1))
			{
				SetX(GetX() + 1);
			}
		}

		if (!checkcoll(2))	SetY(GetY() + 1);
		if (!checkcoll(2))	SetY(GetY() + 1);
		if (!checkcoll(2))	SetY(GetY() + 1);


		if (GetY() >= 700)SetY(-48);

		if (checkcoll(2))
		{
			t = GetTickCount();
			state = state_stay;
			idX = 0;
			idY = 0;
		}


		break;

	case state_die:
		
		switch (count)
		{
		case 0:
			idX = 0;
			if (GetTickCount() - t2 > 750)
			{
				count++;
				t2 = GetTickCount();
				idX = 1;
			}
			break;

		case 1:

			if (GetTickCount() - t > 70)
			{
				t = GetTickCount();
				idX = (++idX > 4) ? 1 : idX;
			}
			if (GetTickCount() - t2 > 750)
			{
				count++;
				t2 = GetTickCount();
				idX = 5;
			}
			break;

		case 2:

			if (GetTickCount() - t > 100)
			{
				t = GetTickCount();
				idX = (++idX > 8) ? 5 : idX;

			}

			if (GetTickCount() - t2 > 1000)
			{
				t = GetTickCount();
				t2 = GetTickCount();
				count++;
				idX = 9;
			}

			break;

		case 3:

			if (GetTickCount() - t > 300)
			{
				t = GetTickCount();
				idX++;
			}

			if (GetTickCount() - t2 > 900)
			{
				life--;
				t = GetTickCount();
				t3 = GetTickCount();
				idX = 0;
				count = 0;

				if (life>0)
				{
					state = state_stay;
					idX = 0;
					idY = 0;
					SetX(75 + player * 600);	SetY(625);	sight = !player;

					blink = true;
				}
				else
				{
					state = state_push;

				}
			}

			break;

		}


		break;

	case state_push:

		switch (count)
		{
		case 0:
			if (GetTickCount() - t > 400)
			{
				t = GetTickCount();
				idX = (idX == 0) ? 1 : 0;
			}

			if (GetAsyncKeyState(key_start) && !erase)
			{
				count = 1;
				t2 = GetTickCount();
			}

			break;

		case 1:
			if (GetTickCount() - t > 400)
			{
				t = GetTickCount();
				idX = (idX == 2) ? 3 : 2;
			}

			if (GetTickCount() - t2 > 2000)
			{
				t = GetTickCount();
				state = state_stay;
				idX = 0;
				idY = 0;
				count = 0;
				SetX(75 + player * 600);	SetY(625);	sight = !player;	life = 3;
				t3 = GetTickCount();
				blink = true;
			}
			break;
		}
		break;

	
	}

	switch(state)
	{
	case state_stay:	case state_walk:	case state_jump:	case state_fall:	live = true;
		if (GetAsyncKeyState(key_shoot) && !SBdelay && GetTickCount() - Sdel>370)
		{
			Sdel = GetTickCount();
			St = GetTickCount();
			SX = 0;
			shooting = true;
			SBdelay = true;

			//버블 생성
			bubble	tempbubble;
			tempbubble.Init(GetX(), GetY(), sight, player);
			for (auto it = Collrect.begin(); it != Collrect.end(); ++it)
				tempbubble.setCollrect((*it));
			for (auto it = Wallrect.begin(); it != Wallrect.end(); ++it)
				tempbubble.setWallrect((*it));
			
			bubblelist.push_front(tempbubble);

		}
	}


	if (shooting)
	{
		if (GetTickCount() - St > 80)
		{
			St = GetTickCount();
			if (SX < 3) SX++;
			else shooting = false;
		}
	}

	
	if (!GetAsyncKeyState(key_jump))	JBdelay = false;
	if (!GetAsyncKeyState(key_shoot))	SBdelay = false;
	

	if (bubblelist.size() > 0)
	{
		auto it = bubblelist.begin();
		for (; it != bubblelist.end(); )
		{
			if (it->getboom())
			{
				it->Destroy();
				it = bubblelist.erase(it);

			}
			else
			{
				it->Update(dt);
				++it;
			}
		}
	}



	

}


void character::Render(HDC hdc, float dt)
{
	if (bubblelist.size() > 0)
	{
		auto it = bubblelist.begin();
		for (; it != bubblelist.end(); ++it)
		{
			mbubble.drawBitmapByCropping(hdc, it->GetX(), it->GetY(), char_size, char_size,
				it->getidX()*ori_char_size, it->getidY()*ori_char_size, ori_char_size, ori_char_size);
		}
	}

	

	if (blink)
	{
		if (GetTickCount() - t2 > 15)	visible = !visible;
		if (GetTickCount() - t3 > 3000)
		{
			blink = false;
			visible = true;
		}
	}
	

	switch (state)
	{
	case state_stay:	case state_walk:	case state_jump:	case state_fall:
		if (visible)
		{
			if (shooting)
				m_char.drawBitmapByCropping(hdc, GetX(), GetY(), char_size, char_size,
					SX*ori_char_size, SY*ori_char_size, ori_char_size, ori_char_size);
			else
				m_char.drawBitmapByCropping(hdc, GetX(), GetY(), char_size, char_size,
					idX*ori_char_size, (idY * 2 + sight)*ori_char_size, ori_char_size, ori_char_size);

		}
		break;

	case state_die:
		m_die.drawBitmapByCropping(hdc, GetX(), GetY()-37, char_size, 87,
			idX*ori_char_size, sight*28, ori_char_size, 28);
		break;

	case state_push:
		if (!erase)	m_push.drawBitmapByCropping(hdc, 75 + player * 550, 575, 100, 100, idX * 32, 0, 32, 32);
		break;

	case state_bubble:
		m_bubble.drawBitmapByCropping(hdc, GetX() - 30, GetY() - 27, 94, 94,
			idX * 32, 0, 32, 32);
	}


	switch (life)
	{
	case 3:	m_lifeicon.drawBitmap(hdc, 50 + player * 675, 675, 25, 25);
	case 2: m_lifeicon.drawBitmap(hdc, 25 + player * 725, 675, 25, 25);
	case 1: m_lifeicon.drawBitmap(hdc,		player * 775, 675, 25, 25);
	}

}

void character::Destroy()
{
	Collrect.clear();
	Wallrect.clear();
	if (bubblelist.size() > 0)
	{
		auto it = bubblelist.begin();
		for (; it != bubblelist.end(); ++it)
			it->Destroy();
	}
	bubblelist.clear();

	switch (player)
	{
	case 0:
		playerxy[0] = GetX();
		playerxy[1] = GetY();
		playerlife[0] = life;
		break;
	case 1:
		playerxy[2] = GetX();
		playerxy[3] = GetY();
		playerlife[1] = life;
		break;
	}
}

bool character::checkcoll(int a)
{
	
	RECT dest;
	RECT rect1 = { GetX() - 1 + sight * 2,GetY(),GetX() + 48 + sight * 2,GetY() + 49 };	//앞
	RECT rect2 = { GetX(),GetY() + 49,GetX() + 49,GetY() + 50 };						//아래
	
	switch (a)
	{
	case 1:	//전진

		for (auto it = Wallrect.begin(); it != Wallrect.end(); ++it)	
			if (IntersectRect(&dest, &rect1, &(*it)) && !IntersectRect(&dest, &getrect(), &(*it)))	return true;

		for (auto it = Collrect.begin(); it != Collrect.end(); ++it)
			if (IntersectRect(&dest, &rect1, &(*it)) && !IntersectRect(&dest, &getrect(), &(*it)))	return true;

		break;

	case 2:	//착지
		for (auto it = Collrect.begin(); it != Collrect.end(); ++it)
			if (IntersectRect(&dest, &rect2, &(*it)) && !IntersectRect(&dest, &getrect(), &(*it)))	return true;
		break;
	}
	return false;
}





