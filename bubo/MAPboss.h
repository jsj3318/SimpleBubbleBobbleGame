#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "character.h"
#include "bigzen.h"

class MAPboss :
	public Scene
{
private:
	RECT		ground[6] =
	{
		{ 150,175,649,199 },
		{ 50,300,274,324 },
		{ 525,300,749,324 },
		{ 150,425,649,449 },
		{ 50,550,274,574 },
		{ 525,550,749,574 }
	};
	RECT		wall[3] =
	{
		{ 0,0,49,699 },
		{ 750,0,799,699 },
		{ 375,200,424,574 }
	};

	character	bubblun;
	character	bobblun;

	bigzen		boss;

	Bitmap		m_map;
	int mapY = 700;
	Bitmap		prevmap;
	int prevmapY = 0;

	int maptimer = 0;
	int	monstertimer;
	int starttimer;
	int mapmovetime;


	bool viewrect = false;
	bool debug_stop = false;

public:
	virtual	void	Init(SceneManager* sceneManager);
	virtual void	Update(float dt);
	virtual void	Render(HDC hdc, float dt);
	virtual void	Destroy();
};
