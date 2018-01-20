#pragma once

class cCharacter
{
protected:
	D3DXMATRIXA16											m_matWorldTM;

protected:
	D_SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	D_SYNTHESIZE(D3DXVECTOR3, m_vDirection, Direction);
	D_SYNTHESIZE_REF(D3DXVECTOR3, m_vChangeDir, ChangeDir);

protected:
	float													m_fSpeed;

protected:
	float													m_fRotY;

public:
	cCharacter();
	virtual ~cCharacter();

	void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};