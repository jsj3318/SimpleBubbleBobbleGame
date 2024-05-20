#include "MAPboss.h"

void MAPboss::Init(SceneManager * sceneManager)
{
	m_SceneManager = sceneManager;

	m_map.LoadBitmapByPath("resource/map/MAPboss.bmp");
	prevmap.LoadBitmapByPath("resource/map/MAP3.bmp");

	bubblun.Init(0);
	bobblun.Init(1);

	boss.Init(1, 225, 75);

	for (int i = 0; i < 6; i++)
	{
		bubblun.setCollrect(ground[i]);
		bobblun.setCollrect(ground[i]);
		boss.setCollrect(ground[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		bubblun.setWallrect(wall[i]);
		bobblun.setWallrect(wall[i]);
		boss.setWallrect(wall[i]);
	}
	monstertimer = GetTickCount();
	starttimer = GetTickCount();
}

void MAPboss::Update(float dt)
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		Destroy();
		PostQuitMessage(0);
	}

	if (GetTickCount() - monstertimer > 700 )
	{
		if (!boss.appear) boss.appear = true;
	}
	if (GetTickCount() - starttimer > 3000)
	{
		if (bubblun.erase)	bubblun.erase = false;
		if (bobblun.erase)	bobblun.erase = false;
		if (!boss.movestart) boss.movestart = true;
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
	if (!debug_stop) boss.Update(dt);
	
	RECT dest;

	//boss 캐릭터 충돌
		if (!boss.erase)
		{
			if (bubblun.live)
			{
				switch (boss.getstate())
				{
				case state_walk:		case state_fall:
					if (IntersectRect(&dest, &bubblun.getrect(), &boss.getrect())) bubblun.dieevent(); break;
				case state_bubble:
					if (IntersectRect(&dest, &bubblun.getspikerect(), &boss.getrect())) {
						boss.dieevent(bubblun.getsight());	maptimer = GetTickCount();
					}
					else if (IntersectRect(&dest, &bubblun.getrect(), &boss.getrect()))
						boss.pushX(bubblun.getsight());												 break;
				case state_food:
					if (IntersectRect(&dest, &bubblun.getrect(), &boss.getrect())) 
						boss.erase = true; maptimer = GetTickCount(); break;
				}
			}

			if (bobblun.live)
			{
				switch (boss.getstate())
				{
				case state_walk:		case state_fall:
					if (IntersectRect(&dest, &bobblun.getrect(), &boss.getrect())) bobblun.dieevent(); break;
				case state_bubble:
					if (IntersectRect(&dest, &bobblun.getspikerect(), &boss.getrect())) {
						boss.dieevent(bobblun.getsight()); maptimer = GetTickCount();
					}
					else if (IntersectRect(&dest, &bobblun.getrect(), &boss.getrect()))
						boss.pushX(bobblun.getsight());												 break;
				case state_food:
					if (IntersectRect(&dest, &bobblun.getrect(), &boss.getrect()))
						boss.erase = true; maptimer = GetTickCount(); break;
				}
			}

		}

	//날아가는 버블과 boss충돌		
		if (!boss.erase)
		{
			if (bubblun.bubblelist.size() > 0)
			{
				auto it = bubblun.bubblelist.begin();
				for (; it != bubblun.bubblelist.end(); ++it)
				{

					if (it->getcount() == 1 && IntersectRect(&dest, &boss.getrect(), &it->getrect()))
					{
						switch (boss.getstate())
						{
						case state_walk:	case state_jump:	case state_fall:
							boss.gethit(1);	it->setboom();		break;
						}
					}
				}
			}
			if (bobblun.bubblelist.size() > 0)
			{
				auto it = bobblun.bubblelist.begin();
				for (; it != bobblun.bubblelist.end(); ++it)
				{
					if (it->getcount() == 1 && IntersectRect(&dest, &boss.getrect(), &it->getrect()))
					{
						switch (boss.getstate())
						{
						case state_walk:	case state_jump:	case state_fall:
							boss.gethit(2);	it->setboom();	break;
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

	if (boss.erase)
	{
		if (GetTickCount() - maptimer > 5000)
		{
			Destroy();
			m_SceneManager->reserveChangeScene("END");
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

void MAPboss::Render(HDC hdc, float dt)
{
	m_map.drawBitmap(hdc, 0, mapY, 800, 700);
	prevmap.drawBitmap(hdc, 0, prevmapY, 800, 700);

	if(!boss.erase)	boss.Render(hdc, dt);
		
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

		if (!boss.erase)
		{
			FillRect(hdc, &boss.getrect(), (HBRUSH)GetStockObject(LTGRAY_BRUSH));
		}
		

		for (int i = 0; i < 6; i++)
		{
			FillRect(hdc, &ground[i], (HBRUSH)GetStockObject(GRAY_BRUSH));
		}
		for (int i = 0; i < 3; i++)
		{
			FillRect(hdc, &wall[i], (HBRUSH)GetStockObject(GRAY_BRUSH));
		}

	}

}

void MAPboss::Destroy()
{
	bubblun.Destroy();
	bobblun.Destroy();
	boss.Destroy();
}
