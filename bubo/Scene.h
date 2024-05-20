#pragma once
#include "GameDefine.h"

class SceneManager;
class Scene
{
public :
	Scene() = default;
	virtual ~Scene() = default;

public :
	virtual void	Init(SceneManager* sceneManager)	= 0;
	virtual void	Update(float dt)					= 0;
	virtual void	Render(HDC hdc, float dt)			= 0;
	virtual void	Destroy()							= 0;

protected :
	SceneManager*	m_SceneManager;
};