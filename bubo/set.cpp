#include "GameDirector.h"
#include "SceneManager.h"
#include "PrepareWnd.h"

#include "MenuScene.h"
#include "Loading.h"
#include "MAP001.h"
#include "MAP002.h"
#include "MAP003.h"
#include "MAPboss.h"
#include "END.h"

// 콘솔 사용
// #pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment (lib, "Msimg32.lib")

void settingWnd(PrepareWnd& value)
{
	value.lpWindowName = "BubbleBobble by JSJ key[1p (a d f g 1)  2p (← → k L enter)]";
}

void settingGame()
{
	GameDirector *director = GameDirector::GetGameDirector();

	director->GetSceneManager()->registerScene("MenuScene", new MenuScene);
	director->GetSceneManager()->registerScene("Loading", new Loading);
	director->GetSceneManager()->registerScene("MAP001", new MAP001);
	director->GetSceneManager()->registerScene("MAP002", new MAP002);
	director->GetSceneManager()->registerScene("MAP003", new MAP003);
	director->GetSceneManager()->registerScene("MAPboss", new MAPboss);
	director->GetSceneManager()->registerScene("END", new END);

	director->GetSceneManager()->reserveChangeScene("MenuScene");
}
