#pragma once

class cXPlayerAnimation;

class cEquip
{
public:
	enum E_PARTS
	{
		E_PARTS_HEAD,
		E_PARTS_BODY,
		E_PARTS_HAND,
		E_PARTS_LEG,
		E_PARTS_HAIR,
		E_PARTS_END = 5
	};

private:
	cXPlayerAnimation*										m_pXPlayerAnimation;

private:
	D_SYNTHESIZE_REF(std::vector<cSkinnedMesh*>, m_vecSkinnedPlayer, VecSkinnedPlayer);

private:
	D3DXMATRIXA16*											m_pXPlayerWorldTM;
	D3DXMATRIXA16											m_matXHeadWorldTM;

private:
	E_PARTS													m_eChangePartKind;

private:
	int														m_arChangePartsNum[E_PARTS_END];

private:
	void SetupParts();

private:
	void RenderChangeKind();

private:
	void ChangeParts();

public:
	cEquip();
	~cEquip();

	void Setup(D3DXMATRIXA16* pXPlayerWorldTM);
	void Release();
	void Update();
	void Render();

	void SetUpLocalPos(ST_BONE* pRootBone);

	void ConnectXPlayerAnimation(cXPlayerAnimation* pXPlayerAnimation) 
	{ m_pXPlayerAnimation = pXPlayerAnimation; }
};

