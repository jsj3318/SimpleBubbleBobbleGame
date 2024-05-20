#pragma once
#include "windows.h"
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>
#include "Digitalv.h"
#include <tchar.h>

template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = NULL;
	}
}

const int MAX_SOUND_CNT = 5;

class SoundMgr
{
public:
	SoundMgr();
	~SoundMgr();

private:
	static SoundMgr*	m_pInst;

public:
	static SoundMgr* GetInst()
	{
		if (m_pInst == NULL)
		{
			m_pInst = new SoundMgr;
		}
		return m_pInst;
	}

	void DestroyInst(void)
	{
		::Safe_Delete(m_pInst);
	}

private:
	MCI_OPEN_PARMS mciFile;
	MCI_PLAY_PARMS mciPlay;
	int dwID[MAX_SOUND_CNT];

public:
	void SetMCIFile(TCHAR* type, TCHAR* fileName);
	void Play(int playType, int index);
	void Stop(int index);
	void Release();

public:
	TCHAR* GetType(int type = 1);
};

