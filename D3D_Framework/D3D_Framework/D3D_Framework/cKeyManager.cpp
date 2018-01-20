#include "stdafx.h"
#include "cKeyManager.h"

cKeyManager::cKeyManager()
{
}

cKeyManager::~cKeyManager()
{
}

void cKeyManager::Setup()
{
	for (int i = 0; i < D_KEYMAX; i++)
	{
		this->GetKeyUp().set(i, false);
		this->GetKeyDown().set(i, false);
	}
}

void cKeyManager::Release()
{
}

bool cKeyManager::IsOnceKeyDown(int nKey)
{
	if (GetAsyncKeyState(nKey) & 0x8000)
	{
		if (!this->GetKeyDown()[nKey])
		{
			this->SetKeyDown(nKey, true);
			return true;
		}
	}
	else this->SetKeyDown(nKey, false);
	return false;
}

bool cKeyManager::IsOnceKeyUp(int nKey)
{
	if (GetAsyncKeyState(nKey) & 0x8000) this->SetKeyUp(nKey, true);
	else
	{
		if (this->GetKeyUp()[nKey])
		{
			this->SetKeyUp(nKey, false);
			return true;
		}
	}
	return false;
}

bool cKeyManager::IsStayKeyDown(int nKey)
{
	if (GetAsyncKeyState(nKey) & 0x8000) return true;
	return false;
}

bool cKeyManager::IsToggleKey(int nKey)
{
	if (GetKeyState(nKey) & 0x0001) return true;
	return false;
}
