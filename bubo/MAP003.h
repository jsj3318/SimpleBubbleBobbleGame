#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "zenchan.h"
#include "character.h"

class MAP003 :
	public Scene
{
private:
	RECT		ground[16] =
	{
		{ 50,0,224,74 },
		{ 325,0,474,74 },
		{ 575,0,749,74 },
		{ 125,175,324,199 },
		{ 475,175,674,199 },
		{ 150,300,349,324 },
		{ 450,300,649,324 },
		{ 150,425,374,449 },
		{ 425,425,649,449 },
		{ 50,550,174,574 },
		{ 225,550,299,574 },
		{ 500,550,574,574 },
		{ 625,550,749,574 },
		{ 50,675,224,699 },
		{ 325,675,474,699 },
		{ 575,675,749,700 }
	};
	RECT		wall[4] =
	{
		{ 0,0,49,699 },
		{ 750,0,799,699 },
		{125,200,149,449},
		{650,200,674,449 }
	};

	character	bubblun;
	character	bobblun;
	zenchan		zen[14];
	int monstercount = 14;

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

