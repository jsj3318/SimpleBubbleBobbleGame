#include "GameDefine.h"
#include "GameDirector.h"



// ��Ʈ������Ʈ
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIns, LPSTR lpCmdLine, int nCmdShow)
{
	return GameDirector::GetGameDirector()->Loop(hInstance, lpCmdLine, nCmdShow);
}
