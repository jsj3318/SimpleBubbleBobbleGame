#include "END.h"

void END::Init(SceneManager * sceneManager)
{
	m_SceneManager = sceneManager;

	m_map.LoadBitmapByPath("resource/map/END.bmp");
	prevmap.LoadBitmapByPath("resource/map/MAPboss.bmp");

	bubblun.Init(0);
	bobblun.Init(1);

	boss[0].Init(1, 200, 100);
	boss[1].Init(0, 500, 100);	boss[1].secondHPbar = true;

	for (int i = 0; i < 13; i++)
	{
		bubblun.setCollrect(ground[i]);
		bobblun.setCollrect(ground[i]);
		
		boss[0].setCollrect(ground[i]);
		boss[1].setCollrect(ground[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		bubblun.setWallrect(wall[i]);
		bobblun.setWallrect(wall[i]);
		boss[0].setWallrect(wall[i]);
		boss[1].setWallrect(wall[i]);
	}	
	monstertimer = GetTickCount();
	starttimer = GetTickCount();
}

void END::Update(float dt)
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		Destroy();
		PostQuitMessage(0);
	}

	if (GetTickCount() - monstertimer > 700 )
	{
		for(int i=0;i<2;i++)
			if (!boss[i].appear) boss[i].appear = true;
	}
	if (GetTickCount() - starttimer > 3000)
	{
		if (bubblun.erase)	bubblun.erase = false;
		if (bobblun.erase)	bobblun.erase = false;
		for (int i = 0; i<2; i++)
			if (!boss[i].movestart) boss[i].movestart = true;
	}
	else
	{
		if (mapY != 0) { mapY--;	prevmapY--; }
		if (mapY != 0) { mapY--;	prevmapY--; }
		if (mapY != 0) { mapY--;	prevmapY--; }
		if (mapY != 0) { mapY--;	prevmapY--; }
		if (mapY != 0) { mapY--;	prevmapY--; }
	}

	bubblun.Update(dt);
	bobblun.Update(dt);
	if (!debug_stop) boss[0].Update(dt);
	if (!debug_stop) boss[1].Update(dt);

	RECT dest;

	//boss 캐릭터 충돌
	for(int i=0;i<2;i++)
	if (!boss[i].erase)
	{
		if (bubblun.live)
		{
			switch (boss[i].getstate())
			{
			case state_walk:		case state_fall:
				if (IntersectRect(&dest, &bubblun.getrect(), &boss[i].getrect())) bubblun.dieevent(); break;
			case state_bubble:
				if (IntersectRect(&dest, &bubblun.getspikerect(), &boss[i].getrect())) {
					boss[i].dieevent(bubblun.getsight());	
				}
				else if (IntersectRect(&dest, &bubblun.getrect(), &boss[i].getrect()))
					boss[i].pushX(bubblun.getsight());												 break;
			case state_food:
				if (IntersectRect(&dest, &bubblun.getrect(), &boss[i].getrect()))
					boss[i].erase = true; break;
			}
		}

		if (bobblun.live)
		{
			switch (boss[i].getstate())
			{
			case state_walk:		case state_fall:
				if (IntersectRect(&dest, &bobblun.getrect(), &boss[i].getrect())) bobblun.dieevent(); break;
			case state_bubble:
				if (IntersectRect(&dest, &bobblun.getspikerect(), &boss[i].getrect())) {
					boss[i].dieevent(bobblun.getsight());
				}
				else if (IntersectRect(&dest, &bobblun.getrect(), &boss[i].getrect()))
					boss[i].pushX(bobblun.getsight());												 break;
			case state_food:
				if (IntersectRect(&dest, &bobblun.getrect(), &boss[i].getrect()))
					boss[i].erase = true;  break;
			}
		}

	}

	//날아가는 버블과 boss충돌		
	for(int i=0;i<2;i++)
	if (!boss[i].erase)
	{
		if (bubblun.bubblelist.size() > 0)
		{
			auto it = bubblun.bubblelist.begin();
			for (; it != bubblun.bubblelist.end(); ++it)
			{

				if (it->getcount() == 1 && IntersectRect(&dest, &boss[i].getrect(), &it->getrect()))
				{
					switch (boss[i].getstate())
					{
					case state_walk:	case state_jump:	case state_fall:
						boss[i].gethit(1);	it->setboom();		break;
					}
				}
			}
		}
		if (bobblun.bubblelist.size() > 0)
		{
			auto it = bobblun.bubblelist.begin();
			for (; it != bobblun.bubblelist.end(); ++it)
			{
				if (it->getcount() == 1 && IntersectRect(&dest, &boss[i].getrect(), &it->getrect()))
				{
					switch (boss[i].getstate())
					{
					case state_walk:	case state_jump:	case state_fall:
						boss[i].gethit(2);	it->setboom();	break;
					}
				}
			}
		}
	}


	//거품과 케릭터

	if (bubblun.bubblelist.size() > 0)
	{
		auto it = bubblun.bubblelist.begin();
		for (; it != bubblun.bubblelist.end(); ++it)
		{
			if (bubblun.live)
			{
				if (IntersectRect(&dest, &bubblun.getspikerect(), &it->getrect()))	it->boomevent();
				else if (IntersectRect(&dest, &bubblun.getrect(), &it->getrect()))	it->pushX(bubblun.getsight());
				else	it->setidX(6);
			}
			if (bobblun.live)
			{
				if (IntersectRect(&dest, &bobblun.getspikerect(), &it->getrect()))	it->boomevent();
				else if (IntersectRect(&dest, &bobblun.getrect(), &it->getrect()))	it->pushX(bobblun.getsight());
				else	it->setidX(6);
			}
		}
	}
	if (bobblun.bubblelist.size() > 0)
	{
		auto it = bobblun.bubblelist.begin();
		for (; it != bobblun.bubblelist.end(); ++it)
		{
			if (bubblun.live)
			{
				if (IntersectRect(&dest, &bubblun.getspikerect(), &it->getrect()))	it->boomevent();
				else if (IntersectRect(&dest, &bubblun.getrect(), &it->getrect()))	it->pushX(bubblun.getsight());
				else	it->setidX(6);
			}
			if (bobblun.live)
			{
				if (IntersectRect(&dest, &bobblun.getspikerect(), &it->getrect()))	it->boomevent();
				else if (IntersectRect(&dest, &bobblun.getrect(), &it->getrect()))	it->pushX(bobblun.getsight());
				else	it->setidX(6);
			}
		}
	}

	if (GetAsyncKeyState('R') & 0x0001)
	{
		viewrect = !viewrect;
	}
	if (GetAsyncKeyState('Q') & 0x0001)
	{
		debug_stop = !debug_stop;
	}

}

void END::Render(HDC hdc, float dt)
{
	m_map.drawBitmap(hdc, 0, mapY, 800, 700);
	prevmap.drawBitmap(hdc, 0, prevmapY, 800, 700);

	for(int i=0;i<2;i++)
		if (!boss[i].erase)	boss[i].Render(hdc, dt);

	bobblun.Render(hdc, dt);
	bubblun.Render(hdc, dt);

	if (viewrect)
	{
		FillRect(hdc, &bubblun.getrect(), (HBRUSH)GetStockObject(DKGRAY_BRUSH));
		FillRect(hdc, &bobblun.getrect(), (HBRUSH)GetStockObject(DKGRAY_BRUSH));

		if (bubblun.bubblelist.size() > 0)
		{
			for (list<bubble>::iterator it = bubblun.bubblelist.begin(); it != bubblun.bubblelist.end(); ++it)
			{
				FillRect(hdc, &it->getrect(), (HBRUSH)GetStockObject(WHITE_BRUSH));
			}
		}
		if (bobblun.bubblelist.size() > 0)
		{
			for (list<bubble>::iterator it = bobblun.bubblelist.begin(); it != bobblun.bubblelist.end(); ++it)
			{
				FillRect(hdc, &it->getrect(), (HBRUSH)GetStockObject(WHITE_BRUSH));
			}
		}

		for (int i = 0; i<2; i++)
			if (!boss[i].erase)	
				FillRect(hdc, &boss[i].getrect(), (HBRUSH)GetStockObject(LTGRAY_BRUSH));


		for (int i = 0; i < 13; i++)
		{
			FillRect(hdc, &ground[i], (HBRUSH)GetStockObject(GRAY_BRUSH));
		}
		for (int i = 0; i < 4; i++)
		{
			FillRect(hdc, &wall[i], (HBRUSH)GetStockObject(GRAY_BRUSH));
		}
	}
}

void END::Destroy()
{
	bubblun.Destroy();
	bobblun.Destroy();
	for (int i = 0; i<2; i++)
		boss[i].Destroy();
}
