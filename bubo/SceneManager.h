#pragma once
#include "GameDefine.h"

class Scene;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

public :
	void				registerScene(const std::string& sceneName, Scene* scene);
	void				reserveChangeScene(const std::string& sceneName);

	void				Update(float dt);
	void				Render(HDC hdc, float dt);

public :
	DWORD				GetMousePositionX();
	DWORD				GetMousePositionY();

	void				SetMousePosition(DWORD x, DWORD y);

private :
	std::map<std::string, Scene*>	m_SceneContainer;

	Scene*							m_ReserveScene;
	Scene*							m_CurrentScene;

	DWORD							m_MousePositionX = 0;
	DWORD							m_MousePositionY = 0;
};

