#include "GameDefine.h"
#include "GameDirector.h"



// 엔트리포인트
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIns, LPSTR lpCmdLine, int nCmdShow)
{
	return GameDirector::GetGameDirector()->Loop(hInstance, lpCmdLine, nCmdShow);
}
