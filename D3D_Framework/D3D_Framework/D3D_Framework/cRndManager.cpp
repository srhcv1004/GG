#include "stdafx.h"
#include "cRndManager.h"

cRndManager::cRndManager()
{
}

cRndManager::~cRndManager()
{
}

void cRndManager::Setup()
{
	srand(GetTickCount());
}

void cRndManager::Release()
{
}

int cRndManager::getInt(int nMax)
{
	int nRnd = rand() % nMax;
	return nRnd;
}

int cRndManager::getFromIntTo(int nFrom, int nTo)
{
	int nRnd = rand() % (nTo - nFrom + 1) + nFrom;
	return nRnd;
}

float cRndManager::getFloat()
{
	float fRnd = (float)rand() / (float)RAND_MAX;
	return fRnd;
}

float cRndManager::getFloat(float fMax)
{
	float fRnd = (float)rand() / (float)RAND_MAX * fMax; 
	return fRnd;
}

float cRndManager::getFromFloatTo(float fFrom, float fTo)
{
	float fRndTmp = (float)rand() / (float)RAND_MAX;
	float fRnd = fRndTmp * (fTo - fFrom) + fFrom;
	return fRnd;
}
