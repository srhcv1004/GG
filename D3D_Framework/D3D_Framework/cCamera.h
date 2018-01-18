#pragma once

class cCamera
{
private:
	D3DXVECTOR3												m_vEye;
	D3DXVECTOR3												m_vLookAt;
	D3DXVECTOR3												m_vUp;

private:
	POINT													m_ptPrevMouse;
	float													m_fCamRotX;
	float													m_fCamRotY;
	bool													m_bIsLButtonDown;

private:
	float													m_fCamDistance;

private:
	void CreateMatView();
	void CreateMatProj();

	void ControlCamDistance();
	void ControlCamRotation();

public:
	cCamera();
	~cCamera();

	void Setup();
	void Release();
	void Update();
};

