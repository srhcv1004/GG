#pragma once
#include "cSingletonBase.h"

class cTexMtl;

class cTexMtlManager : public cSingletonBase<cTexMtlManager>
{
private:
	typedef std::map<std::string, cTexMtl*>				mapTexMtl;
	typedef std::map<std::string, cTexMtl*>::iterator		mapTexMtlIter;

private:
	mapTexMtl												m_mapTexMtls;

private:
	void DestroyAll();
	
public:
	cTexMtlManager();
	virtual ~cTexMtlManager();

	void Setup();
	void Release();

	void AddTexMtl(std::string strTexMtlKey, cTexMtl* pTexMtl);
	cTexMtl* FindTexMtl(std::string strTexMtlKey);

	void ReleaseAll();
};

