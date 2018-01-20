#pragma once

//API 편의 함수.. D3D용으로 교체 예정임.
inline POINT PointMake(int nPosX, int nPosY)
{
	POINT sPos = { nPosX, nPosY };
	return sPos;
}

inline RECT RectMake(int nStartX, int nStartY, int nWidth, int nHeight)
{
	RECT sRc = { nStartX, nStartY, nStartX + nWidth, nStartY + nHeight };
	return sRc;
}

inline RECT RectMakeCenter(int nStartX, int nStartY, int nWidth, int nHeight)
{
	RECT sRc = { nStartX - (nWidth / 2), nStartY - (nHeight / 2), 
		nStartX + (nWidth / 2), nStartY + (nHeight / 2) };
	return sRc;
}

inline void RectDraw(HDC hdc, int nStartX, int nStartY, int nWidth, int nHeight)
{
	Rectangle(hdc, nStartX, nStartY, nStartX + nWidth, nStartY + nHeight);
}

void RectDrawCenter(HDC hdc, int nStartX, int nStartY, int nWidth, int nHeight)
{
	Rectangle(hdc, nStartX - (nWidth / 2), nStartY - (nHeight / 2),
		nStartX + (nWidth / 2), nStartY + (nHeight / 2));
}

inline void EllipseDraw(HDC hdc, int nStartX, int nStartY, int nWidth, int nHeight)
{
	Ellipse(hdc, nStartX, nStartY, nStartX + nWidth, nStartY + nHeight);
}

inline void EllipseDrawCenter(HDC hdc, int nStartX, int nStartY, int nWidth, int nHeight)
{
	Ellipse(hdc, nStartX - (nWidth / 2), nStartY - (nHeight / 2),
		nStartX + (nWidth / 2), nStartY + (nHeight / 2));
}

inline void LineDraw(HDC hdc, int nMoveX, int nMoveY, int nLineX, int nLineY)
{
	MoveToEx(hdc, nMoveX, nMoveY, NULL);
	LineTo(hdc, nLineX, nLineY);
}

inline void UpdateMatWorldTM(ST_BONE* pBone, D3DXMATRIXA16* pMatParentWorldTM)
{
	if (!pBone) return;

	D3DXMatrixMultiply(&pBone->matWorldTM,
		&pBone->TransformationMatrix, pMatParentWorldTM);

	if (pBone->pFrameSibling)
	{
		UpdateMatWorldTM((ST_BONE*)pBone->pFrameSibling, pMatParentWorldTM);
	}

	if (pBone->pFrameFirstChild)
	{
		UpdateMatWorldTM((ST_BONE*)pBone->pFrameFirstChild, &pBone->matWorldTM);
	}
}