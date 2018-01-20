#include "stdafx.h"
#include "utils.h"

void NS_UTILS::GetDirection(OUT D3DXMATRIXA16 & matR, OUT D3DXVECTOR3 & vCurDir, IN D3DXVECTOR3 vChangeDir)
{
	D3DXVec3Normalize(&vChangeDir, &vChangeDir);
	vCurDir = vChangeDir;

	D3DXVECTOR3 vUp;
	D3DXVECTOR3 vRight;

	vUp = D3DXVECTOR3(0.F, 1.F, 0.F);
	D3DXVec3Cross(&vRight, &vUp, &vCurDir);
	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Cross(&vUp, &vCurDir, &vRight);
	D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &vCurDir, &vUp);
	D3DXMatrixTranspose(&matR, &matR);
}

void NS_UTILS::GetDistance(OUT float * pOutDistance, IN D3DXVECTOR3 vDstPos, IN D3DXVECTOR3 vSrcPos)
{
	D3DXVECTOR3 v = vDstPos - vSrcPos;
	(*pOutDistance) = D3DXVec3Length(&v);
}

void NS_UTILS::GetInterpolationT(OUT float * pOutT, IN float fStartTime, IN float fCurTime, IN float fEndTime)
{
	(*pOutT) = (fCurTime - fStartTime) / (fEndTime - fStartTime);
}
