#include "MAP002.h"

void MAP002::Init(SceneManager * sceneManager)
{
	m_SceneManager = sceneManager;

	m_map.LoadBitmapByPath("resource/map/MAP2.bmp");
	prevmap.LoadBitmapByPath("resource/map/MAP1.bmp");

	bubblun.Init(0);
	bobblun.Init(1);

	zen[0].Init(0, 328, 126);
	zen[1].Init(0, 344, 126);
	zen[2].Init(0, 364, 126);
	zen[3].Init(1, 372, 126);
	zen[4].Init(1, 264, 250);
	zen[5].Init(0, 298, 250);
	zen[6].Init(0, 442, 250);
	zen[7].Init(0, 485, 250);
	zen[8].Init(0, 273, 375);
	zen[9].Init(0, 383, 375);
	zen[10].Init(1, 500, 375);
	zen[11].Init(1, 377, 501);


	for (int i = 0; i < 8; i++)
	{
		bubblun.setCollrect(ground[i]);
		bobblun.setCollrect(ground[i]);
		for (int j = 0; j<12; j++)	zen[j].setCollrect(ground[i]);
	}
	for (int i = 0; i < 2; i++)
	{
		bubblun.setWallrect(wall[i]);
		bobblun.setWallrect(wall[i]);
		for (int j = 0; j<12; j++)	zen[j].setWallrect(wall[i]);
	}
	monstertimer = GetTickCount();
	starttimer = GetTickCount();

}

void MAP002::Update(float dt)
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		Destroy();
		PostQuitMessage(0);
	}

	if (GetTickCount() - monstertimer > 700 )
	{
		for (int i = 0; i < 12; i++)
		{
			if (!zen[i].appear) zen[i].appear = true;
		}
	}
	if (GetTickCount() - starttimer > 3000)
	{
		if (bubblun.erase)	bubblun.erase = false;
		if (bobblun.erase)	bobblun.erase = false;
		for (int i = 0; i < 12; i++)
			if (!zen[i].movestart) zen[i].movestart = true;
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

	for (int i = 0; i < 12; i++)
	{
		if (!zen[i].erase)
		{
			zen[i].setpxy(bubblun.GetX(), bubblun.GetY(), bobblun.GetX(), bobblun.GetY());
			zen[i].p1live = bubblun.live;	zen[i].p2live = bobblun.live;
			if (!debug_stop) zen[i].Update(dt);
		}
	}

	RECT dest;

	//젠과 캐릭터 충돌
	for (int i = 0; i < 12; i++)
	{
		if (!zen[i].erase)
		{
			if (bubblun.live)
			{
				switch (zen[i].getstate())
				{
				case state_walk:	case state_jump:	case state_fall:
					if (IntersectRect(&dest, &bubblun.getrect(), &zen[i].getrect())) bubblun.dieevent(); break;
				case state_bubble:
					if (IntersectRect(&dest, &bubblun.getspikerect(), &zen[i].getrect())) {
						zen[i].dieevent(bubblun.getsight());
						if (!--monstercount)maptimer = GetTickCount();
					}
					else if (IntersectRect(&dest, &bubblun.getrect(), &zen[i].getrect()))
						zen[i].pushX(bubblun.getsight());												 break;
				case state_food:
					if (IntersectRect(&dest, &bubblun.getrect(), &zen[i].getrect())) zen[i].erase = true; break;
				}
			}

			if (bobblun.live)
			{
				switch (zen[i].getstate())
				{
				case state_walk:	case state_jump:	case state_fall:
					if (IntersectRect(&dest, &bobblun.getrect(), &zen[i].getrect())) bobblun.dieevent(); break;
				case state_bubble:
					if (IntersectRect(&dest, &bobblun.getspikerect(), &zen[i].getrect())) {
						zen[i].dieevent(bobblun.getsight());
						if (!--monstercount)maptimer = GetTickCount();
					}
					else if (IntersectRect(&dest, &bobblun.getrect(), &zen[i].getrect()))
						zen[i].pushX(bobblun.getsight());												 break;
				case state_food:
					if (IntersectRect(&dest, &bobblun.getrect(), &zen[i].getrect())) zen[i].erase = true; break;
				}
			}

		}

	}

	//날아가는 버블과 젠충돌		

	for (int i = 0; i < 12; i++)
	{
		if (!zen[i].erase)
		{
			if (bubblun.bubblelist.size() > 0)
			{
				auto it = bubblun.bubblelist.begin();
				for (; it != bubblun.bubblelist.end(); ++it)
				{

					if (it->getcount() == 1 && IntersectRect(&dest, &zen[i].getrect(), &it->getrect()))
					{
						switch (zen[i].getstate())
						{
						case state_walk:	case state_jump:	case state_fall:
							zen[i].bubbleevent(1);	it->setboom();		break;
						}
					}
				}
			}
			if (bobblun.bubblelist.size() > 0)
			{
				auto it = bobblun.bubblelist.begin();
				for (; it != bobblun.bubblelist.end(); ++it)
				{

					if (it->getcount() == 1 && IntersectRect(&dest, &zen[i].getrect(), &it->getrect()))
					{
						switch (zen[i].getstate())
						{
						case state_walk:	case state_jump:	case state_fall:
							zen[i].bubbleevent(2);	it->setboom();	break;
						}
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

	// 몬스터없으면 넘어가기
	if (!monstercount)
	{
		if (GetTickCount() - maptimer > 5000)
		{
			Destroy();
			m_SceneManager->reserveChangeScene("MAP003");
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

void MAP002::Render(HDC hdc, float dt)
{
	m_map.drawBitmap(hdc, 0, mapY, 800, 700);
	prevmap.drawBitmap(hdc, 0, prevmapY, 800, 700);

	for (int i = 0; i < 12; i++)
	{
		if (!zen[i].erase)
		{
			zen[i].Render(hdc, dt);
		}
	}

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

		for (int i = 0; i < 12; i++)
		{
			if (!zen[i].erase)
			{
				FillRect(hdc, &zen[i].getrect(), (HBRUSH)GetStockObject(LTGRAY_BRUSH));
			}
		}


		for (int i = 0; i < 8; i++)
		{
			FillRect(hdc, &ground[i], (HBRUSH)GetStockObject(GRAY_BRUSH));
		}
		for (int i = 0; i < 2; i++)
		{
			FillRect(hdc, &wall[i], (HBRUSH)GetStockObject(GRAY_BRUSH));
		}

	}
}

void MAP002::Destroy()
{
	bubblun.Destroy();
	bobblun.Destroy();
	for (int i = 0; i<12; i++)
		zen[i].Destroy();
}
