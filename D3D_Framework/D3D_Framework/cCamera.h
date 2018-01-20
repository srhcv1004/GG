#pragma once

class cCamera
{
protected:
	D_SYNTHESIZE(D3DXVECTOR3*, m_pFollowPosition, FollowPosition);

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
	void CreateMatView();
	void CreateMatProj();

	void ControlCamDistance();
	void ControlCamRotation();

private:
	void CamFollowPosition();

public:
	cCamera();
	virtual ~cCamera();

	virtual void Setup(D3DXVECTOR3* pFollowPosition = NULL);
	virtual void Update();
};

