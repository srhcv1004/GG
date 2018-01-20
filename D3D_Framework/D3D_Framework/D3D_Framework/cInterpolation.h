#pragma once

class cActionSequence;
class cCharacter;

class cInterpolation
{
private:
	std::vector<ST_PC_VERTEX>								m_vecLine;

private:
	cActionSequence*										m_pActionSeq;
	cCharacter*												m_pOwner;

private:
	void SetupVecLine();
	void SetupActionSequence();

public:
	cInterpolation();
	~cInterpolation();

	void Setup(cCharacter* pOwner);
	void Release();
	void Update();
	void Render();
};

