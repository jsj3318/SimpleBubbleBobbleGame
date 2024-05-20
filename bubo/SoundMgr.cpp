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
	// ���� ���� (�÷��� �ϰ��� �ϴ� ���Ϸ� ����)
	// mpegvideo: mp3, waveaudio: wav, avivideo: avi
	mciFile.lpstrDeviceType = type;
	mciFile.lpstrElementName = fileName; // �����̸�
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciFile);
}

void SoundMgr::Play(int playType, int index)
{
	DWORD type;
	switch (playType)
	{
	case 0: 
		type = MCI_NOTIFY; // �� ���� ���
		break;
	case 1:
		type = MCI_DGV_PLAY_REPEAT; // �ݺ� ���
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
