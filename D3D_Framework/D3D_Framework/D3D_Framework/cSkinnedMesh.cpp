#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"

cSkinnedMesh::cSkinnedMesh()
	: m_pRootBone(NULL)
	, m_pAnimationController(NULL)
	, m_pSphere(NULL)
	, m_fPassedBlendTime(0.F)
	, m_fBlendTime(0.F)
	, m_fAniElapsedTime(0.F)
	, m_bIsBlend(false)
{
}

cSkinnedMesh::~cSkinnedMesh()
{
}

void cSkinnedMesh::Setup(const CHAR* pFolderName, const CHAR* pFileName)
{
	std::string strFullName = std::string(pFolderName);
	strFullName = strFullName + std::string("/")
		+ std::string(pFileName);

	cAllocateHierarchy cHierarchy;
	cHierarchy.SetFolderName(std::string(pFolderName));

	D3DXLoadMeshHierarchyFromX(strFullName.c_str(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		D_DEVICE,
		&cHierarchy,
		NULL,
		&m_pRootBone,
		&m_pAnimationController);

	this->SetupSkinnedMesh((ST_BONE*)m_pRootBone);

	D3DXCreateSphere(D_DEVICE,
		0.05F,
		10,
		10,
		&m_pSphere,
		NULL);
}

void cSkinnedMesh::Release()
{
	cAllocateHierarchy ah;
	D3DXFrameDestroy(m_pRootBone, &ah);

	D_SAFE_RELEASE(m_pSphere);
}

void cSkinnedMesh::Update()
{
	// Animation Code
	this->UpdateAnimation();

	// Frame & Mesh Code
	UpdateMatWorldTM((ST_BONE*)m_pRootBone, m_pMatWorldPtr);
	this->UpdateSkinnedMesh((ST_BONE*)m_pRootBone);
}

void cSkinnedMesh::Render()
{
	//this->RenderBones((ST_BONE*)m_pRootBone, NULL);
	this->RenderSkinnedMesh((ST_BONE*)m_pRootBone);

	D3DXMATRIXA16 matW;
	D3DXMatrixIdentity(&matW);

	//RenderBoneLines((ST_BONE*)m_pRootBone, NULL, &matW);
}

void cSkinnedMesh::SetupSkinnedMesh(ST_BONE* pBone)
{
	if (!pBone) return;

	if (pBone->pMeshContainer)
	{
		ST_BONEMESH* pBoneMesh = (ST_BONEMESH*)pBone->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			DWORD dwBoneCount = pBoneMesh->pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwBoneCount; i++)
			{
				ST_BONE* pTmpBone = (ST_BONE*)D3DXFrameFind(m_pRootBone,
					pBoneMesh->pSkinInfo->GetBoneName(i));

				if (pTmpBone)
				{
					pBoneMesh->ppMat[i] = &pTmpBone->matWorldTM;
				}
				else
				{
					pBoneMesh->ppMat[i] = NULL;
				}
			}
		}
	}

	if (pBone->pFrameSibling)
	{
		SetupSkinnedMesh((ST_BONE*)pBone->pFrameSibling);
	}
	if (pBone->pFrameFirstChild)
	{
		SetupSkinnedMesh((ST_BONE*)pBone->pFrameFirstChild);
	}
}

void cSkinnedMesh::UpdateSkinnedMesh(ST_BONE* pBone)
{
	if (pBone->pMeshContainer)
	{
		ST_BONEMESH* pBoneMesh = (ST_BONEMESH*)pBone->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			DWORD dwBoneCount = pBoneMesh->pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwBoneCount; i++)
			{
				D3DXMatrixMultiply(&pBoneMesh->pMatCurrent[i],
					&pBoneMesh->pMatOffset[i],
					pBoneMesh->ppMat[i]);
			}

			BYTE* pDst = NULL;
			BYTE* pSrc = NULL;

			pBoneMesh->pMeshOrigin->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pSrc);
			pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (LPVOID*)&pDst);

			pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
				pBoneMesh->pMatCurrent,
				NULL,
				pSrc,
				pDst);

			pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
			pBoneMesh->pMeshOrigin->UnlockVertexBuffer();
		}
	}

	if (pBone->pFrameSibling)
	{
		UpdateSkinnedMesh((ST_BONE*)pBone->pFrameSibling);
	}
	if (pBone->pFrameFirstChild)
	{
		UpdateSkinnedMesh((ST_BONE*)pBone->pFrameFirstChild);
	}
}

void cSkinnedMesh::RenderSkinnedMesh(ST_BONE* pBone)
{
	if (pBone->pMeshContainer)
	{
		ST_BONEMESH* pBoneMesh = (ST_BONEMESH*)pBone->pMeshContainer;

		if (pBoneMesh->pSkinInfo)
		{
			for (DWORD i = 0; i < pBoneMesh->vecMaterial.size(); i++)
			{
				D_DEVICE->SetMaterial(&pBoneMesh->vecMaterial[i]);
				D_DEVICE->SetTexture(0, pBoneMesh->vecTexture[i]);

				pBoneMesh->MeshData.pMesh->DrawSubset(i);
			}
		}
	}

	if (pBone->pFrameSibling)
	{
		RenderSkinnedMesh((ST_BONE*)pBone->pFrameSibling);
	}
	if (pBone->pFrameFirstChild)
	{
		RenderSkinnedMesh((ST_BONE*)pBone->pFrameFirstChild);
	}
}

void cSkinnedMesh::RenderBones(ST_BONE* pBone, D3DXMATRIXA16* pMatWorld)
{
	D_DEVICE->SetTransform(D3DTS_WORLD, &pBone->matWorldTM);
	m_pSphere->DrawSubset(0);

	if (pBone->pFrameSibling)
	{
		RenderBones((ST_BONE*)pBone->pFrameSibling, pMatWorld);
	}
	if (pBone->pFrameFirstChild)
	{
		RenderBones((ST_BONE*)pBone->pFrameFirstChild, pMatWorld);
	}
}

void cSkinnedMesh::RenderBoneLines(ST_BONE* pBone, ST_BONE* pParent, D3DXMATRIXA16* matWorld)
{
	if (!pBone) pBone = (ST_BONE*)m_pRootBone;

	D3DXMATRIXA16   r, s, t;
	D3DXMatrixRotationYawPitchRoll(&r, -D3DX_PI * 0.5f, 0.0f, 0.0f);

	if (pParent && pBone->Name && pParent->Name)
	{
		D_DEVICE->SetRenderState(D3DRS_LIGHTING, false);
		s = r * pBone->matWorldTM * (*matWorld);
		D3DXMatrixTranslation(&t, s(3, 0), s(3, 1), s(3, 2));
		D_DEVICE->SetTransform(D3DTS_WORLD, &t);
		m_pSphere->DrawSubset(0);

		D3DXMATRIXA16 w1 = pBone->matWorldTM;
		D3DXMATRIXA16 w2 = pParent->matWorldTM;

		D3DXVECTOR3 thisBone = D3DXVECTOR3(w1(3, 0), w1(3, 1), w1(3, 2));
		D3DXVECTOR3 parentBone = D3DXVECTOR3(w2(3, 0), w2(3, 1), w2(3, 2));

		D_DEVICE->SetTransform(D3DTS_WORLD, matWorld);

		ST_PC_VERTEX vertex[] = { ST_PC_VERTEX(parentBone, D3DXCOLOR(0.f, 0.f, 0.f, 1.0f)),
			ST_PC_VERTEX(thisBone, D3DXCOLOR(0.f, 0.f, 0.f, 1.0f)) };

		D_DEVICE->SetRenderState(D3DRS_LIGHTING, false);
		D_DEVICE->SetFVF(ST_PC_VERTEX::FVF);
		D_DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, &vertex[0], sizeof(ST_PC_VERTEX));
	}

	if (pBone->pFrameSibling)
	{
		RenderBoneLines((ST_BONE*)pBone->pFrameSibling, pParent, matWorld);
	}
	if (pBone->pFrameFirstChild)
	{
		RenderBoneLines((ST_BONE*)pBone->pFrameFirstChild, pBone, matWorld);
	}
}

void cSkinnedMesh::SetAnimationIndex(int nIndex)
{
	int nMax = m_pAnimationController->GetNumAnimationSets();
	if (nIndex > nMax)	nIndex = nIndex % nMax;

	LPD3DXANIMATIONSET	pAnimSet = NULL;
	m_pAnimationController->GetAnimationSet(nIndex, &pAnimSet);
	m_pAnimationController->SetTrackAnimationSet(0, pAnimSet);

	D_SAFE_RELEASE(pAnimSet);
}

void cSkinnedMesh::SetAnimationIndexBlend(int nIndex)
{
	m_bIsBlend = true;
	m_fPassedBlendTime = 0.0F;

	int nMax = m_pAnimationController->GetNumAnimationSets();
	if (nIndex > nMax)	nIndex = nIndex % nMax;

	LPD3DXANIMATIONSET	pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET	pNextAnimSet = NULL;

	D3DXTRACK_DESC stTrackDesc;

	m_pAnimationController->GetTrackDesc(0, &stTrackDesc);

	m_pAnimationController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pAnimationController->SetTrackAnimationSet(1, pPrevAnimSet);
	m_pAnimationController->SetTrackDesc(1, &stTrackDesc);

	m_pAnimationController->GetAnimationSet(nIndex, &pNextAnimSet);
	m_pAnimationController->SetTrackAnimationSet(0, pNextAnimSet);

	m_pAnimationController->SetTrackWeight(0, 0.0f);
	m_pAnimationController->SetTrackWeight(1, 1.0f);

	m_pAnimationController->SetTrackPosition(0, 0);

	D_SAFE_RELEASE(pPrevAnimSet);
	D_SAFE_RELEASE(pNextAnimSet);
}

void cSkinnedMesh::UpdateAnimation()
{
	if (m_pAnimationController)
	{
		if (m_bIsBlend)
		{
			m_fPassedBlendTime += D_TIMEMANAGER->GetElapsedTime();
			if (m_fPassedBlendTime >= m_fBlendTime)
			{
				m_pAnimationController->SetTrackWeight(0, 1.0f);
				m_pAnimationController->SetTrackEnable(1, false);
			}
			else
			{
				float fWeight = m_fPassedBlendTime / m_fBlendTime;
				m_pAnimationController->SetTrackWeight(0, fWeight);
				m_pAnimationController->SetTrackWeight(1, 1.0f - fWeight);
			}
		}

		m_pAnimationController->AdvanceTime(
			D_TIMEMANAGER->GetElapsedTime(), NULL);
	}
}
