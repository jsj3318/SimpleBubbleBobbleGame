#include "Loading.h"
extern int playerlife[2];
extern int playerxy[4];

void Loading::Init(SceneManager * sceneManager)
{
	m_SceneManager = sceneManager;

	background.LoadBitmapByPath("resource/map/loading_background.bmp");

	bubblun.LoadBitmapByPath("resource/bubblun/bubblun_bubble.bmp");
	bubblun.setTransparentColor(RGB(0, 64, 192));

	bobblun.LoadBitmapByPath("resource/bobblun/bobblun_bubble.bmp");
	bobblun.setTransparentColor(RGB(0, 64, 192));
	idX = 6;

	scenetime = GetTickCount();
	movecounttime = GetTickCount();
	x1 = 210;
	y1 = 310;
	x2 = 540;
	y2 = 310;
	movecount = 1;
	movedelay = 0;
}

void Loading::Update(float dt)
{
	if (GetAsyncKeyState(VK_ESCAPE))	PostQuitMessage(0);

	if (GetTickCount() - idXtime > 250)
	{
		idXtime = GetTickCount();
		idX = (idX == 6) ? 7 : 6;
	}
	if (GetTickCount() - movecounttime > 125)
	{
		movecounttime = GetTickCount();
		movecount++;
		if (movecount >8)	movecount = 1;
	}

	if (GetTickCount() - movedelay > 40)
	{
		movedelay = GetTickCount();
		switch (movecount)
		{
		case 1:		x1 += 10;	y1 += 5;	x2 -= 10;	y2 += 5;	break;
		case 2:		x1 += 5;	y1 += 10;	x2 -= 5;	y2 += 10;	break;
		case 3:		x1 -= 5;	y1 += 10;	x2 += 5;	y2 += 10;	break;
		case 4:		x1 -= 10;	y1 += 5;	x2 += 10;	y2 += 5;	break;
		case 5:		x1 -= 10;	y1 -= 5;	x2 += 10;	y2 -= 5;	break;
		case 6:		x1 -= 5;	y1 -= 10;	x2 += 5;	y2 -= 10;	break;
		case 7:		x1 += 5;	y1 -= 10;	x2 -= 5;	y2 -= 10;	break;
		case 8:		x1 += 10;	y1 -= 5;	x2 -= 10;	y2 -= 5;	break;
		}
	}
	

	if (GetTickCount() - scenetime > 8000)
	{
		Destroy();
		m_SceneManager->reserveChangeScene("MAP001");
	}
}

void Loading::Render(HDC hdc, float dt)
{
	background.drawBitmap(hdc, 0, 0, 800, 700);

	bubblun.drawBitmapByCropping(hdc, x1 - 30, y1 - 27, 94, 94,
		idX * 32, 0, 32, 32);
	bobblun.drawBitmapByCropping(hdc, x2 - 30, y2 - 27, 94, 94,
		idX * 32, 0, 32, 32);
}

void Loading::Destroy()
{
	playerxy[0] = x1;
	playerxy[1] = y1;
	playerxy[2] = x2;
	playerxy[3] = y2;
	playerlife[0] = 3;
	playerlife[1] = 0;
}
