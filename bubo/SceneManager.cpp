#include "SceneManager.h"
#include "Scene.h"

using namespace std;

SceneManager::SceneManager() : m_CurrentScene(nullptr), m_ReserveScene(nullptr)
{

}


SceneManager::~SceneManager()
{
	for (auto it = m_SceneContainer.begin(); it != m_SceneContainer.end(); ++it)
	{
		it->second->Destroy();
		delete it->second;
	}
}

void SceneManager::registerScene(const std::string & sceneName, Scene * scene)
{
	if (scene == nullptr || sceneName.compare("") == 0)
		return ;

	m_SceneContainer.insert(m_SceneContainer.end(), pair<string, Scene*>(sceneName, scene));
}

void SceneManager::reserveChangeScene(const std::string & sceneName)
{
	auto it = m_SceneContainer.find(sceneName);

	if (it != m_SceneContainer.end())
	{
		m_ReserveScene = it->second;
	}
	else
	{
		m_ReserveScene = nullptr;
	}
}

void SceneManager::Update(float dt)
{
	if (m_ReserveScene != nullptr)
	{
		m_ReserveScene->Init(this);
		m_CurrentScene = m_ReserveScene;

		m_ReserveScene = nullptr;
	}

	if (m_CurrentScene != nullptr)
		m_CurrentScene->Update(dt);
}

void SceneManager::Render(HDC hdc, float dt)
{
	if (m_CurrentScene != nullptr)
		m_CurrentScene->Render(hdc, dt);
}

DWORD SceneManager::GetMousePositionX()
{
	return m_MousePositionX;
}

DWORD SceneManager::GetMousePositionY()
{
	return m_MousePositionY;
}

void SceneManager::SetMousePosition(DWORD x, DWORD y)
{
	m_MousePositionX = x;
	m_MousePositionY = y;
}
