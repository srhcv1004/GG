#pragma once
#include "cSingletonBase.h"
#include <bitset>

#define D_KEYMAX											256

class cKeyManager : public cSingletonBase<cKeyManager>
{
private:
	std::bitset<D_KEYMAX>									m_bIsKeyUp;
	std::bitset<D_KEYMAX>									m_bIsKeyDown;

private:
	std::bitset<D_KEYMAX> GetKeyUp() { return m_bIsKeyUp; }
	std::bitset<D_KEYMAX> GetKeyDown() { return m_bIsKeyDown; }

	void SetKeyUp(int nKey, bool bIsState) { m_bIsKeyUp.set(nKey, bIsState); }
	void SetKeyDown(int nKey, bool bIsState) { m_bIsKeyDown.set(nKey, bIsState); }

public:
	cKeyManager();
	virtual ~cKeyManager();

	void Setup();
	void Release();

	bool IsOnceKeyDown(int nKey);
	bool IsOnceKeyUp(int nKey);
	bool IsStayKeyDown(int nKey);
	bool IsToggleKey(int nKey);
};

