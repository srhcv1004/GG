#pragma once
#include "cSingletonBase.h"
#include "inc\fmod.hpp"

#pragma comment(lib, "lib/fmodex_vc.lib")

#define D_SOUNDBUFFERMAX									20
#define D_CHANNELBUFFERMAX									5
#define D_GROUPMAX											5
#define D_ALLBUFFERMAX										D_SOUNDBUFFERMAX + D_CHANNELBUFFERMAX

class cSoundManager : public cSingletonBase<cSoundManager>
{
public:
	enum E_GROUP_KIND
	{
		E_GROUP_MASTER,
		E_GROUP_EFFECT,
		E_GROUP_BGM,
		E_GROUP_END = 3
	};

private:
	struct ST_SOUND_INFO
	{
		std::string											strSoundKey;
		FMOD::Sound**										ppSound;
	};

	struct ST_CHANNEL_INFO
	{
		std::string											strChannelKey;
		FMOD::Channel**										ppChannel;
	};

private:
	typedef std::vector<ST_SOUND_INFO*>						vecSound;
	typedef std::vector<ST_SOUND_INFO*>::iterator			vecSoundIter;
	typedef std::vector<ST_CHANNEL_INFO*>					vecChannel;
	typedef std::vector<ST_CHANNEL_INFO*>::iterator			vecChannelIter;

private:
	vecSound												m_vecSounds;

private:
	FMOD::ChannelGroup**									m_ppChannelGroup;

private:
	FMOD::System*											m_pSystem;
	FMOD::Sound**											m_ppSound;
	FMOD::Channel**											m_ppChannel;

private:
	void SetupMasterChannelGroup();

public:
	cSoundManager();
	virtual ~cSoundManager();

	void Setup();
	void Release();

	void AddSound(std::string strSoundKey, const CHAR* pSoundFileName, bool bIsBgm, bool bIsLoop);
	void Play(std::string strSoundKey, E_GROUP_KIND eGroupKind);
	void Stop(std::string strSoundKey);
	void Pause(std::string strSoundKey);
	void Resume(std::string strSoundKey);

	void SetVolume(std::string strSoundKey, float fVolume = 1.F);
	void SetGroupVolume(E_GROUP_KIND eGroupKind, float fVolume = 1.F);

	bool IsPlaySound(std::string strSoundKey);
	bool IsPauseSound(std::string strSoundKey);
};

