#include "stdafx.h"
#include "cXFileObj.h"
#include "cAllocateHierarchy.h"

cXFileObj::cXFileObj()
	: m_pRootBone(NULL)
	, m_pAnimationController(NULL)
	, m_pMeshSphereBone(NULL)
{
}

cXFileObj::~cXFileObj()
{
}

void cXFileObj::Setup(const CHAR * pXFileName)
{
	cCharacter::Setup();

	cAllocateHierarchy cAHier;

	D3DXLoadMeshHierarchyFromX(pXFileName,
		D3DXMESH_MANAGED,
		D_DEVICE,
		&cAHier,
		NULL,
		&m_pRootBone,
		&m_pAnimationController);

	this->SetupMeshes((ST_BONE*)m_pRootBone);

	D3DXCreateSphere(D_DEVICE, 1.F, 10, 10, &m_pMeshSphereBone, NULL);
}

void cXFileObj::Release()
{
	this->DestroyAll((ST_BONE*)m_pRootBone);

	D_SAFE_RELEASE(m_pAnimationController);
	D_SAFE_RELEASE(m_pMeshSphereBone);
}

void cXFileObj::Update()
{
	this->UpdateMatWorldTM((ST_BONE*)m_pRootBone, &m_matWorldTM);
}

void cXFileObj::Render()
{
	this->RenderMeshes((ST_BONE*)m_pRootBone);
	//this->RenderBones((ST_BONE*)m_pRootBone);
}

void cXFileObj::SetupMeshes(ST_BONE* pBone)
{
	if (pBone->pMeshContainer)
	{
		ST_BONEMESH* pBoneMesh = (ST_BONEMESH*)pBone->pMeshContainer;

		if (pBoneMesh->pSkinInfo)
		{
			int nBoneCount = pBoneMesh->pSkinInfo->GetNumBones();

			pBoneMesh->ppMat = new D3DXMATRIXA16*[nBoneCount]();
			for (int i = 0; i < nBoneCount; i++)
			{
				ST_BONE* pTmpBone = (ST_BONE*)D3DXFrameFind(m_pRootBone, 
					pBoneMesh->pSkinInfo->GetBoneName(i));

				if (pTmpBone) pBoneMesh->ppMat[i] = &pTmpBone->matWorldTM;
				else pBoneMesh->ppMat[i] = NULL;
			}
		}
	}

	if (pBone->pFrameSibling)
		SetupMeshes((ST_BONE*)pBone->pFrameSibling);

	if (pBone->pFrameFirstChild)
		SetupMeshes((ST_BONE*)pBone->pFrameFirstChild);
}

void cXFileObj::UpdateMatWorldTM(ST_BONE* pBone, D3DXMATRIXA16* pMatParentWorldTM)
{
	if (!pBone) return;
	CalculateMatWorldTM(pBone, pMatParentWorldTM);
}

void cXFileObj::RenderMeshes(ST_BONE* pBone)
{
	if (!pBone) pBone = (ST_BONE*)m_pRootBone;

	if (pBone->pMeshContainer)
	{
		ST_BONEMESH* pBoneMesh = (ST_BONEMESH*)pBone->pMeshContainer;

		if (pBoneMesh->pSkinInfo)
		{
			int nBoneCount = pBoneMesh->pSkinInfo->GetNumBones();
			for (int i = 0; i < nBoneCount; i++)
			{
				D3DXMatrixMultiply(&pBoneMesh->pMatCurrent[i],
					&pBoneMesh->pMatOffset[i], pBoneMesh->ppMat[i]);
			}

			BYTE* pDst = NULL;
			BYTE* pSrc = NULL;

			pBoneMesh->pMeshOrigin->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pSrc);
			pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (LPVOID*)&pDst);

			pBoneMesh->pSkinInfo->UpdateSkinnedMesh(pBoneMesh->pMatCurrent,
				NULL,
				pSrc,
				pDst);

			pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
			pBoneMesh->pMeshOrigin->UnlockVertexBuffer();

			for (DWORD i = 0; i < pBoneMesh->ulAttributeCount; i++)
			{
				DWORD nAttributeID = pBoneMesh->pAttributeInfo[i].AttribId;
				
				D_DEVICE->SetMaterial(&pBoneMesh->vecMaterial[nAttributeID]);
				D_DEVICE->SetTexture(0, pBoneMesh->vecTexture[nAttributeID]);

				pBoneMesh->MeshData.pMesh->DrawSubset(nAttributeID);
			}
		}
	}

	if (pBone->pFrameSibling)
		RenderMeshes((ST_BONE*)pBone->pFrameSibling);

	if (pBone->pFrameFirstChild)
		RenderMeshes((ST_BONE*)pBone->pFrameFirstChild);
}

void cXFileObj::RenderBones(ST_BONE* pBone)
{
	if (!pBone) return;

	D_DEVICE->SetTransform(D3DTS_WORLD, &pBone->matWorldTM);
	D_DEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pMeshSphereBone->DrawSubset(0);

	if (pBone->pFrameSibling)
		RenderBones((ST_BONE*)pBone->pFrameSibling);

	if (pBone->pFrameFirstChild)
		RenderBones((ST_BONE*)pBone->pFrameFirstChild);
}

void cXFileObj::DestroyAll(ST_BONE* pBone)
{
	cAllocateHierarchy cAHier;

	if (pBone->pFrameSibling)
		DestroyAll((ST_BONE*)pBone->pFrameSibling);

	if (pBone->pFrameFirstChild)
		DestroyAll((ST_BONE*)pBone->pFrameFirstChild);

	cAHier.DestroyMeshContainer(pBone->pMeshContainer);
	cAHier.DestroyFrame(pBone);
}
