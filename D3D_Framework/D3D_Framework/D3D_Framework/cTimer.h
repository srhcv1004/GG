#pragma once

class cTimer
{
private:
	bool													m_bIsHardware;

	__int64													m_nLastUpdateTime;
	__int64													m_nCurTime;
	__int64													m_nFrequency;

	float													m_fElapsedTime;
	float													m_fTimeScale;

	float													m_fWorldTime;
	float													m_fFPSElapsedTime;

	DWORD													m_ulFrameCount;
	DWORD													m_ulFrameRate;

public:
	cTimer();
	~cTimer();

	void Setup();
	void Update(float fLockFPS = 1.F);

	inline float GetWorldTime() { return m_fWorldTime; }
	inline float GetElapsedTime() { return m_fElapsedTime; }
	inline DWORD GetFrameRate() { return m_ulFrameRate; }
};

