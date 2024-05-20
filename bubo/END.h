#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "character.h"
#include "bigzen.h"

class END :
	public Scene
{
public:
	virtual	void	Init(SceneManager* sceneManager);
	virtual void	Update(float dt);
	virtual void	Render(HDC hdc, float dt);
	virtual void	Destroy();
private:
	RECT		ground[13] =
	{
		{ 50,300,99,324 },
		{ 50,425,99,449 },
		{ 50,550,99,574 },
		{ 700,300,749,324 },
		{ 700,425,749,449 },
		{ 700,550,749,574 },
		{ 0,0,149,74 },
		{ 650,0,799,74 },
		{ 150,200,649,224 },
		{ 50,675,149,699 },
		{ 650,675,749,699 },
		{ 150,175,174,199 },
		{ 625,175,649,199 }
	};
	RECT		wall[4] =
	{
		{ 0,0,49,699 },
		{ 750,0,799,699 },
		{ 150,175,174,199 },
		{ 625,175,649,199 }
	};

	character	bubblun;
	character	bobblun;

	bigzen		boss[2];

	Bitmap		m_map;
	int mapY = 700;
	Bitmap		prevmap;
	int prevmapY = 0;

	int	monstertimer;
	int starttimer;

	bool viewrect = false;
	bool debug_stop = false;

};

