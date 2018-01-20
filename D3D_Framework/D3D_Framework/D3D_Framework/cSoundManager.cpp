#include "stdafx.h"
#include "cSoundManager.h"

cSoundManager::cSoundManager()
	: m_pSystem(NULL)
	, m_ppSound(NULL)
	, m_ppChannel(NULL)
	, m_ppChannelGroup(NULL)
{
}

cSoundManager::~cSoundManager()
{
}

void cSoundManager::Setup()
{
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(D_ALLBUFFERMAX, FMOD_INIT_NORMAL, NULL);

	m_ppSound = new FMOD::Sound*[D_SOUNDBUFFERMAX]();
	m_ppChannel = new FMOD::Channel*[D_CHANNELBUFFERMAX]();

	this->SetupMasterChannelGroup();
}

void cSoundManager::Release()
{
	for (int i = 0; i < D_SOUNDBUFFERMAX; i++)
	{
		if (m_ppSound[i])
			m_ppSound[i]->release();
	}

	for (int i = 0; i < D_CHANNELBUFFERMAX; i++)
	{
		if (m_ppChannel[i])
			m_ppChannel[i]->stop();
	}

	D_SAFE_DELETE_ARR(m_ppSound);
	D_SAFE_DELETE_ARR(m_ppChannel);

	for (size_t i = 0; i < m_vecSounds.size(); i++)
	{
		if (m_vecSounds[i])
		{
			D_SAFE_DELETE(m_vecSounds[i]);
		}
	}
}

void cSoundManager::AddSound(std::string strSoundKey, const CHAR * pSoundFileName, bool bIsBgm, bool bIsLoop)
{
	if (bIsLoop)
	{
		if (bIsBgm)
		{
			m_pSystem->createStream(pSoundFileName, FMOD_LOOP_NORMAL, NULL, &m_ppSound[m_vecSounds.size()]);
		}
		else
		{
			m_pSystem->createSound(pSoundFileName, FMOD_DEFAULT, NULL, &m_ppSound[m_vecSounds.size()]);
		}
	}
	else
	{
		if (bIsBgm)
		{
			m_pSystem->createStream(pSoundFileName, FMOD_LOOP_NORMAL, NULL, &m_ppSound[m_vecSounds.size()]);
		}
		else
		{
			m_pSystem->createSound(pSoundFileName, FMOD_DEFAULT, NULL, &m_ppSound[m_vecSounds.size()]);
		}
	}

	ST_SOUND_INFO* pSoundInfo = new ST_SOUND_INFO();
	pSoundInfo->strSoundKey = strSoundKey;
	pSoundInfo->ppSound = &m_ppSound[m_vecSounds.size()];
	m_vecSounds.push_back(pSoundInfo);
}

void cSoundManager::Play(std::string strSoundKey, E_GROUP_KIND eGroupKind)
{
	vecSoundIter vecFind = m_vecSounds.begin();
	int nIdx = 0;

	for (vecFind; vecFind != m_vecSounds.end(); vecFind++, nIdx++)
	{
		if ((*vecFind)->strSoundKey == strSoundKey)
		{
			m_pSystem->playSound(FMOD_CHANNEL_FREE, m_ppSound[nIdx], false, &m_ppChannel[nIdx]);
			m_ppChannel[nIdx]->setChannelGroup(m_ppChannelGroup[eGroupKind]);
			break;
		}
	}
}

void cSoundManager::Stop(std::string strSoundKey)
{
	vecSoundIter vecFind = m_vecSounds.begin();
	int nIdx = 0;

	for (vecFind; vecFind != m_vecSounds.end(); vecFind++, nIdx++)
	{
		if ((*vecFind)->strSoundKey == strSoundKey)
		{
			m_ppChannel[nIdx]->stop();
			break;
		}
	}
}

void cSoundManager::Pause(std::string strSoundKey)
{
	vecSoundIter vecFind = m_vecSounds.begin();
	int nIdx = 0;

	for (vecFind; vecFind != m_vecSounds.end(); vecFind++, nIdx++)
	{
		if ((*vecFind)->strSoundKey == strSoundKey)
		{
			m_ppChannel[nIdx]->setPaused(true);
			break;
		}
	}
}

void cSoundManager::Resume(std::string strSoundKey)
{
	vecSoundIter vecFind = m_vecSounds.begin();
	int nIdx = 0;

	for (vecFind; vecFind != m_vecSounds.end(); vecFind++, nIdx++)
	{
		if ((*vecFind)->strSoundKey == strSoundKey)
		{
			m_ppChannel[nIdx]->setPaused(false);
			break;
		}
	}
}

void cSoundManager::SetVolume(std::string strSoundKey, float fVolume)
{
	vecSoundIter vecFind = m_vecSounds.begin();
	int nIdx = 0;

	for (vecFind; vecFind != m_vecSounds.end(); vecFind++, nIdx++)
	{
		if ((*vecFind)->strSoundKey == strSoundKey)
		{
			m_pSystem->playSound(FMOD_CHANNEL_FREE, m_ppSound[nIdx], false, &m_ppChannel[nIdx]);
			m_ppChannel[nIdx]->setVolume(fVolume);
			break;
		}
	}
}

void cSoundManager::SetGroupVolume(E_GROUP_KIND eGroupKind, float fVolume)
{
	m_ppChannelGroup[eGroupKind]->setVolume(fVolume); 
}

bool cSoundManager::IsPlaySound(std::string strSoundKey)
{
	vecSoundIter vecFind = m_vecSounds.begin();
	int nIdx = 0;
	bool bIsPlaySound = false;

	for (vecFind; vecFind != m_vecSounds.end(); vecFind++, nIdx++)
	{
		if ((*vecFind)->strSoundKey == strSoundKey)
		{
			m_ppChannel[nIdx]->isPlaying(&bIsPlaySound);
			break;
		}
	}
	return bIsPlaySound;
}

bool cSoundManager::IsPauseSound(std::string strSoundKey)
{
	vecSoundIter vecFind = m_vecSounds.begin();
	int nIdx = 0;
	bool bIsPauseSound = false;

	for (vecFind; vecFind != m_vecSounds.end(); vecFind++, nIdx++)
	{
		if ((*vecFind)->strSoundKey == strSoundKey)
		{
			m_ppChannel[nIdx]->isPlaying(&bIsPauseSound);
			break;
		}
	}
	return bIsPauseSound;
}

void cSoundManager::SetupMasterChannelGroup()
{
	m_ppChannelGroup = new FMOD::ChannelGroup*[E_GROUP_END]();

	m_pSystem->createChannelGroup("Effect_group", &m_ppChannelGroup[E_GROUP_EFFECT]);
	m_pSystem->createChannelGroup("Bgm_group", &m_ppChannelGroup[E_GROUP_BGM]);

	m_pSystem->getMasterChannelGroup(&m_ppChannelGroup[E_GROUP_MASTER]);
 	for (int i = 1; i < E_GROUP_END; i++)
	{
    	m_ppChannelGroup[E_GROUP_MASTER]->addGroup(m_ppChannelGroup[i]);
	}
}
