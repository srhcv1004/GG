#include "stdafx.h"
#include "cTimer.h"

cTimer::cTimer()
	: m_bIsHardware(false)
	, m_nLastUpdateTime(0)
	, m_nCurTime(0)
	, m_fElapsedTime(0.F)
	, m_fTimeScale(0.F)
	, m_fWorldTime(0.F)
	, m_fFPSElapsedTime(0.F)
	, m_ulFrameCount(0)
	, m_ulFrameRate(0)
{
}

cTimer::~cTimer()
{
}

void cTimer::Setup()
{

	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_nFrequency))
	{
		m_bIsHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nLastUpdateTime);
		m_fTimeScale = 1.F / m_nFrequency;
	}
	else
	{
		m_bIsHardware = false;
		m_nLastUpdateTime = timeGetTime();
		m_fTimeScale = 0.001F;
	}
}

void cTimer::Update(float fLockFPS)
{

	if (m_bIsHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurTime);
	}
	else
	{
		m_nCurTime = timeGetTime();
	}

	m_fElapsedTime = (m_nCurTime - m_nLastUpdateTime) * m_fTimeScale;

	if (fLockFPS > 0.F)
	{
		while (m_fElapsedTime < (1.F / fLockFPS))
		{
			if (m_bIsHardware)
			{
				QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurTime);
			}
			else
			{
				m_nCurTime = timeGetTime();
			}

			m_fElapsedTime = (m_nCurTime - m_nLastUpdateTime) * m_fTimeScale;
		}
	}

	m_nLastUpdateTime = m_nCurTime;
	m_ulFrameCount++;

	m_fWorldTime += m_fElapsedTime;
	m_fFPSElapsedTime += m_fElapsedTime;

	if (m_fFPSElapsedTime > 1.F)
	{
		m_ulFrameRate = m_ulFrameCount;
		m_ulFrameCount = 0;
		m_fFPSElapsedTime = 0.F;
	}
}
