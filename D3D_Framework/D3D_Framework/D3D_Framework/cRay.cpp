#include "stdafx.h"
#include "cRay.h"

cRay::cRay()
	: m_vPos(0.F, 0.F, 0.F)
	, m_vDir(0.F, 0.F, 0.F)
{
}

cRay::~cRay()
{
}

cRay cRay::RayAtViewSpace(int nScreenX, int nScreenY)
{
	D3DVIEWPORT9 sD3DVp;
	D_DEVICE->GetViewport(&sD3DVp);

	D3DXMATRIXA16 matProj;
	D_DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);

	cRay r;

	r.m_vDir.x = ((2.F * nScreenX) / sD3DVp.Width - 1.F) / matProj._11;
	r.m_vDir.y = ((-2.F * nScreenY) / sD3DVp.Height + 1.F) / matProj._22;
	r.m_vDir.z = 1.F;

	return r;
}

cRay cRay::RayAtWorldSpace(int nScreenX, int nScreenY)
{
	cRay r = RayAtViewSpace(nScreenX, nScreenY);

	D3DXMATRIXA16 matWorld, matInvWorld;

	D_DEVICE->GetTransform(D3DTS_VIEW, &matWorld);
	D3DXMatrixInverse(&matInvWorld, NULL, &matWorld);

	D3DXVec3TransformCoord(&r.m_vPos, &r.m_vPos, &matInvWorld);
	D3DXVec3TransformNormal(&r.m_vDir, &r.m_vDir, &matInvWorld);
	D3DXVec3Normalize(&r.m_vDir, &r.m_vDir);

	return r;
}

bool cRay::IsPicked(ST_SPHERE* pS)
{
	cRay r = (*this);

	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixIdentity(&matInvWorld);
	matInvWorld._41 = -pS->vCenter.x;
	matInvWorld._42 = -pS->vCenter.y;
	matInvWorld._43 = -pS->vCenter.z;

	D3DXVec3TransformCoord(&r.m_vPos, &r.m_vPos, &matInvWorld);
	D3DXVec3TransformNormal(&r.m_vDir, &r.m_vDir, &matInvWorld);

	float vv = D3DXVec3Dot(&r.m_vDir, &r.m_vDir);
	float qv = D3DXVec3Dot(&r.m_vPos, &r.m_vDir);
	float qq = D3DXVec3Dot(&r.m_vPos, &r.m_vPos);
	float rr = pS->fRadius * pS->fRadius;

	return qv * qv - vv * (qq - rr) >= 0;
}

bool cRay::IntersectTri(D3DXVECTOR3 & v0, D3DXVECTOR3 & v1, D3DXVECTOR3 & v2, D3DXVECTOR3 & vPickPosition)
{
	float u, v, t;

	bool b = D3DXIntersectTri(&v0, &v1, &v2, &m_vPos, &m_vDir, &u, &v, &t);

	vPickPosition = m_vPos + (t * m_vDir);

	return b;
}