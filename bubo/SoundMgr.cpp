#include "SoundMgr.h"

SoundMgr* SoundMgr::m_pInst = NULL;

SoundMgr::SoundMgr()
{
	ZeroMemory(dwID, sizeof(dwID));
}

SoundMgr::~SoundMgr()
{
	this->Release();
}

void SoundMgr::SetMCIFile(TCHAR* type, TCHAR* fileName)
{
	// 파일 열기 (플레이 하고자 하는 파일로 세팅)
	// mpegvideo: mp3, waveaudio: wav, avivideo: avi
	mciFile.lpstrDeviceType = type;
	mciFile.lpstrElementName = fileName; // 파일이름
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciFile);
}

void SoundMgr::Play(int playType, int index)
{
	DWORD type;
	switch (playType)
	{
	case 0: 
		type = MCI_NOTIFY; // 한 번만 재생
		break;
	case 1:
		type = MCI_DGV_PLAY_REPEAT; // 반복 재생
		break;
	}

	if (NULL == dwID[index])
	{
		dwID[index] = mciFile.wDeviceID;
		mciSendCommand(dwID[index], MCI_PLAY, type, (DWORD)(LPVOID)&mciPlay);
	}
}

void SoundMgr::Stop(int index)
{
	mciSendCommand(dwID[index], MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
}

void SoundMgr::Release()
{
	for (int i = 0; i < MAX_SOUND_CNT; ++i)
	{
		mciSendCommand(dwID[i], MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	}
}

TCHAR * SoundMgr::GetType(int type)
{
	switch (type)
	{
	case 0: // mp3
		return (TCHAR*)L"mpegvideo";
	case 1: // wav
		return (TCHAR*)L"waveaudio";
	case 2: // avi
		return (TCHAR*)L"avivideo";
	}

	return (TCHAR*)L"mpegvideo";
}
