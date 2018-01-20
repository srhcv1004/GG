#pragma once
#include "cCharacter.h"
class cSkinnedMesh;

class cXMonster : public cCharacter
{
protected:
	cSkinnedMesh* m_Monster;

protected:
	//파이프라인 행렬
	D3DXMATRIXA16 matS, matR, matT;
public:

	cXMonster();
	virtual ~cXMonster();

	virtual void Setup(const CHAR* pFolderName, const CHAR* pFileName,D3DXVECTOR3 Size,D3DXVECTOR3 Position,int MonsterInfor,int MonsterLevel);
	virtual void Release();
	virtual void Update();
	virtual void Render();
	virtual void MonsterMove();

};

