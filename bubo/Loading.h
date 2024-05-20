#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "Bitmap.h"

class Loading :
	public Scene
{
private:
	int		scenetime;
	Bitmap	bubblun;	int x1,	y1;
	Bitmap	bobblun;	int x2, y2;
	Bitmap	background;
	int idX, idXtime, movecount = 0, movecounttime, movedelay;

public:
	virtual	void	Init(SceneManager* sceneManager);
	virtual void	Update(float dt);
	virtual void	Render(HDC hdc, float dt);
	virtual void	Destroy();

};

