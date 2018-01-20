#pragma once
#include "cSingletonBase.h"

class cTimer;

class cTimeManager : public cSingletonBase<cTimeManager>
{
private:
	cTimer*													m_pTimer;
	
public:
	cTimeManager();
	virtual ~cTimeManager();

	void Setup();
	void Update(float fLockFPS = 0.F);
	void Render();

	inline float GetWorldTime();
	inline float GetElapsedTime();
	inline DWORD GetFrameRate();
};

