#pragma once

namespace NS_UTILS
{
	void GetDirection(OUT D3DXMATRIXA16& matR, OUT D3DXVECTOR3& vCurDir, IN D3DXVECTOR3 vChangeDir);
	void GetDistance(OUT float* pOutDistance, IN D3DXVECTOR3 vDstPos, IN D3DXVECTOR3 vSrcPos);
	void GetInterpolationT(OUT float* pOutT, IN float fStartTime, IN float fCurTime, IN float fEndTime);
}



