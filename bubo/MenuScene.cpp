#include "MenuScene.h"

void MenuScene::Init(SceneManager * sceneManager)
{
	m_SceneManager = sceneManager;


	title1.LoadBitmapByPath("resource/map/menuscene/title1.bmp");
	title1.setTransparentColor(RGB(0, 64, 192));

	title2.LoadBitmapByPath("resource/map/menuscene/title2.bmp");
	title2.setTransparentColor(RGB(0, 64, 192));

	title3.LoadBitmapByPath("resource/map/menuscene/title3.bmp");
	title3.setTransparentColor(RGB(0, 64, 192));

	title4.LoadBitmapByPath("resource/map/menuscene/title3.bmp");
	title4.setTransparentColor(RGB(0, 64, 192));

	title5.LoadBitmapByPath("resource/map/menuscene/title5.bmp");
	title5.setTransparentColor(RGB(0, 64, 192));

	title6.LoadBitmapByPath("resource/map/menuscene/title6.bmp");
	title6.setTransparentColor(RGB(0, 64, 192));

	taito.LoadBitmapByPath("resource/map/menuscene/tatio.bmp");	
	taito.setTransparentColor(RGB(0, 64, 192));

	text.LoadBitmapByPath("resource/map/menuscene/text.bmp");	
	text.setTransparentColor(RGB(0, 64, 192));

	m_sound.SetMCIFile(m_sound.GetType(), (TCHAR*)L"resource/sound/menu.wav");
	m_sound.Play(0,0);
}

void MenuScene::Update(float dt)
{

	if (GetAsyncKeyState(49))
	{
		m_SceneManager->reserveChangeScene("Loading");
	}

	if (GetAsyncKeyState(VK_ESCAPE))	PostQuitMessage(0);
}

void MenuScene::Render(HDC hdc, float dt)
{

	RECT rc = { 0,0,800,700 };
	FillRect(hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));

	if (GetTickCount() - t > 60)
	{
		t = GetTickCount();
		count++;
		if (count == 7) count = 1;
	}

	switch (count)
	{
	case 1:	title1.drawBitmap(hdc, 100, 50, 550, 450);	break;
	case 2:	title2.drawBitmap(hdc, 100, 50, 550, 450);	break;
	case 3:	title3.drawBitmap(hdc, 100, 50, 550, 450);	break;
	case 4:	title4.drawBitmap(hdc, 100, 50, 550, 450);	break;
	case 5:	title5.drawBitmap(hdc, 100, 50, 550, 450);	break;
	case 6:	title6.drawBitmap(hdc, 100, 50, 550, 450);	break;
	}


	taito.drawBitmap(hdc, 275, 475, 250, 50);
	text.drawBitmap(hdc, 90, 520, 620, 90);
}

void MenuScene::Destroy()
{
	
}

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

