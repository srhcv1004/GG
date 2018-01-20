#pragma once
#include "cXNormalMonster.h";

enum E_MonsterKind
{
	E_NORMALMONSTER,
	E_BOSSMONSTER,
	E_END
};
class cXMonsterManager
{
private:

	std::vector<cXMonster*> m_vMonster;

public:
	void Setup();
	void Release();
	void Update();
	void Render();
	void MakeMonster(const CHAR* pFolderName, const CHAR* pFileName, D3DXVECTOR3 Size, D3DXVECTOR3 Position, E_MonsterKind MonsterKind, int MonsterInfor, int MonsterLevel);
	cXMonsterManager();
	~cXMonsterManager();
};

