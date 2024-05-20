#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "Bitmap.h"

#include "SoundMgr.h"
#include <tchar.h>

class MenuScene : public Scene
{
public :
	virtual void	Init(SceneManager* sceneManager);
	virtual void	Update(float dt);
	virtual void	Render(HDC hdc, float dt);
	virtual void	Destroy();

	MenuScene();
	~MenuScene();

private :
	Bitmap		title1;
	Bitmap		title2;
	Bitmap		title3;
	Bitmap		title4;
	Bitmap		title5;
	Bitmap		title6;
	
	Bitmap		taito;
	Bitmap		text;

	int count = 1;
	int t = 0;

	SoundMgr m_sound;

};

