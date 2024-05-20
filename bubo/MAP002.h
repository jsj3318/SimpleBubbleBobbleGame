#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "zenchan.h"
#include "character.h"

class MAP002 :
	public Scene
{
private:
	RECT		ground[8] =
	{
		{ 325,175,474,199 },
		{ 250,300,374,324 },
		{ 425,300,549,324 },
		{ 175,425,624,449 },
		{ 100,550,275,574 },
		{ 325,550,474,574 },
		{ 525,550,699,574 },
		{ 50,675,749,699 }
	};
	RECT		wall[2] =
	{
		{ 0,0,49,699 },
		{ 750,0,799,699 },
	};

	character	bubblun;
	character	bobblun;
	zenchan		zen[12];
	int monstercount = 12;

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