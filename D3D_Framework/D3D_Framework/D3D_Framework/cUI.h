#pragma once

class cUI
{
protected:
	D_SYNTHESIZE(cUI*, m_pParentUI, ParentUI);

protected:
	std::vector<cUI*>										m_vecChild;

protected:
	D3DXMATRIXA16											m_matWorldTM;
	D3DXVECTOR3												m_vLocalPos;

protected:
	bool													m_bIsHidden;

public:
	cUI();
	virtual ~cUI();

	void Setup();
	void Release();
	virtual void Update();
	virtual void Render();

	void AddChild(cUI* pUI);
};

