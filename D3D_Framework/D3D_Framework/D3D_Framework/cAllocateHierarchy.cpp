#include "stdafx.h"
#include "cAllocateHierarchy.h"

cAllocateHierarchy::cAllocateHierarchy()
{
}

cAllocateHierarchy::~cAllocateHierarchy()
{
}

HRESULT cAllocateHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME* ppNewFrame)
{
	ST_BONE* pNewBone = new ST_BONE();
	ZeroMemory(pNewBone, sizeof(ST_BONE));

	D3DXMatrixIdentity(&pNewBone->matWorldTM);
	D3DXMatrixIdentity(&pNewBone->TransformationMatrix);

	if (Name)
	{
		int nNameLength = strlen(Name) + 1;
		pNewBone->Name = new CHAR[nNameLength]();
		strncpy_s(pNewBone->Name, nNameLength,
			Name, nNameLength);
	}

	(*ppNewFrame) = pNewBone;
	return S_OK;
}

HRESULT cAllocateHierarchy::CreateMeshContainer(LPCSTR Name,
	CONST D3DXMESHDATA* pMeshData,
	CONST D3DXMATERIAL* pMaterials,
	CONST D3DXEFFECTINSTANCE* pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD* pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER* ppNewMeshContainer)
{
	ST_BONEMESH* pNewBoneMesh = new ST_BONEMESH();
	ZeroMemory(pNewBoneMesh, sizeof(ST_BONEMESH));

	for (DWORD i = 0; i < NumMaterials; i++)
	{
		pNewBoneMesh->vecMaterial.push_back(pMaterials->MatD3D);

		IDirect3DTexture9* pNewTexture = NULL;
		if (pMaterials->pTextureFilename)
		{
			std::string strFullName = std::string(m_strFolderName);
			strFullName = strFullName + std::string("/")
				+ std::string("Texture")
				+ std::string("/")
				+ std::string(pMaterials->pTextureFilename);

			D3DXCreateTextureFromFile(D_DEVICE,
				strFullName.c_str(),
				&pNewTexture);
		}
		pNewBoneMesh->vecTexture.push_back(pNewTexture);
	}

	pMeshData->pMesh->AddRef();
	pNewBoneMesh->MeshData.pMesh = pMeshData->pMesh;
	pMeshData->pMesh->CloneMeshFVF(
		pMeshData->pMesh->GetOptions(),
		pMeshData->pMesh->GetFVF(),
		D_DEVICE,
		&pNewBoneMesh->pMeshOrigin);

	pMeshData->pMesh->GetAttributeTable(NULL, &pNewBoneMesh->dwAttributeCount);
	pNewBoneMesh->pAttribute = new D3DXATTRIBUTERANGE[pNewBoneMesh->dwAttributeCount]();
	pMeshData->pMesh->GetAttributeTable(pNewBoneMesh->pAttribute, NULL);

	if (pSkinInfo)
	{
		pSkinInfo->AddRef();
		pNewBoneMesh->pSkinInfo = pSkinInfo;

		DWORD dwBoneCount = pSkinInfo->GetNumBones();
		pNewBoneMesh->ppMat = new D3DXMATRIXA16*[dwBoneCount]();
		pNewBoneMesh->pMatOffset = new D3DXMATRIXA16[dwBoneCount]();
		pNewBoneMesh->pMatCurrent = new D3DXMATRIXA16[dwBoneCount]();

		for (DWORD i = 0; i < dwBoneCount; i++)
		{
			pNewBoneMesh->pMatOffset[i] =
				(*pSkinInfo->GetBoneOffsetMatrix(i));
		}
	}

	(*ppNewMeshContainer) = pNewBoneMesh;
	return S_OK;
}

HRESULT cAllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	ST_BONE* pBone = (ST_BONE*)pFrameToFree;

	D_SAFE_DELETE_ARR(pBone->Name);
	D_SAFE_DELETE(pFrameToFree);

	return S_OK;
}

HRESULT cAllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	ST_BONEMESH* pBoneMesh = (ST_BONEMESH*)pMeshContainerToFree;

	D_SAFE_RELEASE(pBoneMesh->pSkinInfo);
	D_SAFE_RELEASE(pBoneMesh->pMeshOrigin);
	D_SAFE_RELEASE(pBoneMesh->MeshData.pMesh);

	D_SAFE_DELETE_ARR(pBoneMesh->pAttribute);
	D_SAFE_DELETE_ARR(pBoneMesh->ppMat);
	D_SAFE_DELETE_ARR(pBoneMesh->pMatOffset);
	D_SAFE_DELETE_ARR(pBoneMesh->pMatCurrent);

	for (size_t i = 0; i < pBoneMesh->vecTexture.size(); i++)
	{
		D_SAFE_RELEASE(pBoneMesh->vecTexture[i]);
	}
	pBoneMesh->vecMaterial.clear();
	pBoneMesh->vecTexture.clear();

	D_SAFE_DELETE(pMeshContainerToFree);

	return S_OK;
}
