#pragma once

class cSkinnedMesh;

class cXMonster
{
protected:
	cSkinnedMesh* m_Monster;

public:

	cXMonster();
	virtual ~cXMonster();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();

};

