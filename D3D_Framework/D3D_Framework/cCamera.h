#pragma once

class cCamera
{
protected:
	D_SYNTHESIZE_REF(D3DXVECTOR3, m_vEye, VecEye);
	D3DXVECTOR3												m_vLookAt;
	D3DXVECTOR3												m_vUp;

private:
	POINT													m_ptPrevMouse;
	float													m_fCamRotX;
	float													m_fCamRotY;
	bool													m_bIsLButtonDown;

protected:
	float													m_fCamDistance;

protected:
	virtual void CreateMatView();
	virtual void CreateMatProj();

	virtual void ControlCamDistance();
	virtual void ControlCamRotation();

public:
	cCamera();
	virtual ~cCamera();
};

