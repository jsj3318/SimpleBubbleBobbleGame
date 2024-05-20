#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "zenchan.h"
#include "character.h"

 

class MAP001 :
	public Scene
{
private:
	RECT		ground[10] =
	{
		{ 50,300,99,324 },
		{ 50,425,99,449 },
		{ 50,550,99,574 },
		{ 175,300,624,324 },
		{ 175,425,624,449 },
		{ 175,550,624,574 },
		{ 700,300,749,324 },
		{ 700,425,749,449 },
		{ 700,550,749,574 },
		{ 50,675,749,699 }
	};
	RECT		wall[2] =
	{
		{ 0,0,49,699 },
		{ 750,0,799,699 },
	};

	character	bubblun;
	character	bobblun;
	zenchan		zen[10];
	int monstercount = 10;

	Bitmap		m_map;
	int maptimer = 0;
	int	monstertimer;
	int starttimer;

	bool viewrect = false;
	bool debug_stop = false;

public:

	virtual	void	Init(SceneManager* sceneManager);
	virtual void	Update(float dt);
	virtual void	Render(HDC hdc, float dt);
	virtual void	Destroy();

};

