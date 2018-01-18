#pragma once

class cRay
{
private:
	D3DXVECTOR3												m_vPos;
	D3DXVECTOR3												m_vDir;

public:
	cRay();
	~cRay();

	static cRay RayAtViewSpace(int nScreenX, int nScreenY);
	static cRay RayAtWorldSpace(int nScreenX, int nScreenY);

	bool IsPicked(ST_SPHERE* pS);
	bool IntersectTri(D3DXVECTOR3 &v0, D3DXVECTOR3 &v1, D3DXVECTOR3 &v2, D3DXVECTOR3& vPickPosition);
};

