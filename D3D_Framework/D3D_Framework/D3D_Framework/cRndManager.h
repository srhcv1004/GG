#pragma once
#include "cSingletonBase.h"

class cRndManager : public cSingletonBase<cRndManager>
{
public:
	cRndManager();
	virtual ~cRndManager();

	void Setup();
	void Release();

	int getInt(int nMax);
	int getFromIntTo(int nFrom, int nTo);

	float getFloat();
	float getFloat(float fMax);
	float getFromFloatTo(float fFrom, float fTo);
};

