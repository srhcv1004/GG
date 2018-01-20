#include "stdafx.h"
#include "cAseLoadManager.h"
#include "cAseNode.h"
#include "cTexMtl.h"
#include "cAnimation.h"

cAseLoadManager::cAseLoadManager()
	: m_pFile(NULL)
	, m_pAseRoot(NULL)
	, m_pAseFolderName(NULL)
	, m_szToken()
{
}

cAseLoadManager::~cAseLoadManager()
{
}

void cAseLoadManager::Setup()
{

}

void cAseLoadManager::Release()
{

}

CHAR * cAseLoadManager::GetToken()
{
	int nIdx = 0;
	bool bIsQuote = false;

	while (true)
	{
		if (feof(m_pFile)) break;

		char ch = fgetc(m_pFile);
		if (ch == '\"')
		{
			if (bIsQuote) break;

			bIsQuote = true;
			continue;
		}

		if (!bIsQuote && this->IsWhite(ch))
		{
			if (nIdx == 0) continue;
			else break;
		}

		m_szToken[nIdx++] = ch;
	}

	if (nIdx == 0) return NULL;

	m_szToken[nIdx] = '\0';
	return m_szToken;
}

int cAseLoadManager::GetInt()
{
	return atoi(this->GetToken());
}

float cAseLoadManager::GetFloat()
{
	return (float)atof(this->GetToken());
}

bool cAseLoadManager::IsWhite(char ch)
{
	return ch < 33;
}

bool cAseLoadManager::IsEqual(const CHAR * pDst, const CHAR * pSrc)
{
	return !strcmp(pDst, pSrc);
}


cAseNode* cAseLoadManager::LoadAse(std::map<std::string, cAseNode*>& mapAseCharacter, 
	const CHAR* pAseFolderName, const CHAR* pAseFileName)
{
	m_pAseFolderName = pAseFolderName;

	std::string strFullName = std::string(pAseFolderName) +
		std::string("/") + std::string(pAseFileName);
	fopen_s(&m_pFile, strFullName.c_str(), "r");

	while (CHAR* pToken = this->GetToken())
	{
		if (this->IsEqual(pToken, ID_MATERIAL_LIST))
		{
			this->ProcessID_MATERIAL_LIST();
		}
		else if (this->IsEqual(pToken, ID_SCENE))
		{
			this->ProcessID_SCENE();
		}
		else if (this->IsEqual(pToken, ID_GEOMETRY))
		{

			cAseNode* pAseRoot = this->ProcessID_GEOMETRY(mapAseCharacter);
			if (!m_pAseRoot)
				m_pAseRoot = pAseRoot;
		}
	}

	fclose(m_pFile);
	return m_pAseRoot;
}

void cAseLoadManager::ProcessID_MATERIAL_LIST()
{
	int nLv = 0;
	do
	{
		CHAR* pToken = this->GetToken();
		if (this->IsEqual(pToken, "{"))
		{
			nLv++;
		}
		else if (this->IsEqual(pToken, "}"))
		{
			nLv--;
		}
		else if (this->IsEqual(pToken, ID_MATERIAL))
		{
			cTexMtl* pTexMtl = new cTexMtl();
			char szTexMtlKey[1024] = "";

			int nTexMtlIdx = this->GetInt();
			_itoa_s(nTexMtlIdx, szTexMtlKey, 10);

			D_TEXMTLMANAGER->AddTexMtl(szTexMtlKey, pTexMtl);

			this->ProcessID_MATERIAL(pTexMtl);
		}
	} while (nLv > 0);
}

void cAseLoadManager::ProcessID_MATERIAL(cTexMtl* pTexMtl)
{
	D3DMATERIAL9 sMtl;

	int nLv = 0;
	do
	{
		CHAR* pToken = this->GetToken();
		if (this->IsEqual(pToken, "{"))
		{
			nLv++;
		}
		else if (this->IsEqual(pToken, "}"))
		{
			nLv--;
		}
		else if (this->IsEqual(pToken, ID_AMBIENT))
		{
			sMtl.Ambient.r = this->GetFloat();
			sMtl.Ambient.g = this->GetFloat();
			sMtl.Ambient.b = this->GetFloat();
			sMtl.Ambient.a = 1.F;
		}
		else if (this->IsEqual(pToken, ID_DIFFUSE))
		{
			sMtl.Diffuse.r = this->GetFloat();
			sMtl.Diffuse.g = this->GetFloat();
			sMtl.Diffuse.b = this->GetFloat();
			sMtl.Diffuse.a = 1.F;
		}
		else if (this->IsEqual(pToken, ID_SPECULAR))
		{
			sMtl.Specular.r = this->GetFloat();
			sMtl.Specular.g = this->GetFloat();
			sMtl.Specular.b = this->GetFloat();
			sMtl.Specular.a = 1.F;
		}
		else if (this->IsEqual(pToken, ID_MAP_DIFFUSE))
		{
			this->ProcessID_MAP_DIFFUSE(pTexMtl);
		}
	} while (nLv > 0);

	pTexMtl->SetMtl(sMtl);
}

void cAseLoadManager::ProcessID_MAP_DIFFUSE(cTexMtl* pTexMtl)
{
	int nLv = 0;
	do
	{
		CHAR* pToken = this->GetToken();
		if (this->IsEqual(pToken, "{"))
		{
			nLv++;
		}
		else if (this->IsEqual(pToken, "}"))
		{
			nLv--;
		}
		else if (this->IsEqual(pToken, ID_BITMAP))
		{
			std::string strFullName = std::string(m_pAseFolderName) + 
				std::string(this->GetToken());

			pTexMtl->CreateTexture(strFullName.c_str());
		}
	} while (nLv > 0);
}

void cAseLoadManager::ProcessID_SCENE()
{
}

cAseNode* cAseLoadManager::ProcessID_GEOMETRY(std::map<std::string, cAseNode*>& mapAseCharacter)
{
	cAseNode* pAseNode = new cAseNode();
	cAnimation* pAnimation = new cAnimation();

	int nLv = 0;
	do
	{
		CHAR* pToken = this->GetToken();
		if (this->IsEqual(pToken, "{"))
		{
			nLv++;
		}
		else if (this->IsEqual(pToken, "}"))
		{
			nLv--;
		}
		else if (this->IsEqual(pToken, ID_NODE_NAME))
		{
			mapAseCharacter.insert(std::make_pair(this->GetToken(), pAseNode));
		}
		else if (this->IsEqual(pToken, ID_NODE_PARENT))
		{
			mapAseCharacter[this->GetToken()]->AddChild(pAseNode);
		}
		else if (this->IsEqual(pToken, ID_NODE_TM))
		{
			this->ProcessID_NODE_TM(pAseNode);
		}
		else if (this->IsEqual(pToken, ID_MESH))
		{
			this->ProcessID_MESH(pAseNode);
		}
		else if (this->IsEqual(pToken, ID_TM_ANIMATION))
		{
			this->ProcessID_TM_ANIMATION(pAseNode, pAnimation);
		}
		else if (this->IsEqual(pToken, ID_MATERIAL_REF))
		{	
			pAseNode->SetTexMtl(D_TEXMTLMANAGER->FindTexMtl(this->GetToken()));
		}
	} while (nLv > 0);
	
	pAseNode->SetAnimation(pAnimation);

	return pAseNode;
}

void cAseLoadManager::ProcessID_NODE_TM(cAseNode* pAseNode)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	int nLv = 0;
	do
	{
		CHAR* pToken = this->GetToken();
		if (this->IsEqual(pToken, "{"))
		{
			nLv++;
		}
		else if (this->IsEqual(pToken, "}"))
		{
			nLv--;
		}
		else if (this->IsEqual(pToken, ID_TM_ROW0))
		{
			matWorld._11 = this->GetFloat();
			matWorld._13 = this->GetFloat();
			matWorld._12 = this->GetFloat();
		}
		else if (this->IsEqual(pToken, ID_TM_ROW1))
		{
			matWorld._31 = this->GetFloat();
			matWorld._33 = this->GetFloat();
			matWorld._32 = this->GetFloat();
		}
		else if (this->IsEqual(pToken, ID_TM_ROW2))
		{
			matWorld._21 = this->GetFloat();
			matWorld._23 = this->GetFloat();
			matWorld._22 = this->GetFloat();
		}
		else if (this->IsEqual(pToken, ID_TM_ROW3))
		{
			matWorld._41 = this->GetFloat();
			matWorld._43 = this->GetFloat();
			matWorld._42 = this->GetFloat();
		}
	} while (nLv > 0);

	pAseNode->SetMatWorldTM(matWorld);
}

void cAseLoadManager::ProcessID_MESH(cAseNode* pAseNode)
{
	std::vector<ST_PNT_VERTEX> vecVertex;
	std::vector<D3DXVECTOR3>   vecV;
	std::vector<D3DXVECTOR2>   vecVT;
	std::vector<D3DXVECTOR3>   vecVN;

	int nLv = 0;
	do
	{
		CHAR* pToken = this->GetToken();
		if (this->IsEqual(pToken, "{"))
		{
			nLv++;
		}
		else if (this->IsEqual(pToken, "}"))
		{
			nLv--;
		}
		else if (this->IsEqual(pToken, ID_MESH_NUMVERTEX))
		{
			vecV.resize(this->GetInt());
		}
		else if (this->IsEqual(pToken, ID_MESH_NUMFACES))
		{
			vecVertex.resize(this->GetInt() * 3);
		}
		else if (this->IsEqual(pToken, ID_MESH_VERTEX_LIST))
		{
			this->ProcessID_MESH_VERTEX_LIST(vecV);
		}
		else if (this->IsEqual(pToken, ID_MESH_FACE_LIST))
		{
			this->ProcessID_MESH_FACE_LIST(vecVertex, vecV);
		}
		else if (this->IsEqual(pToken, ID_MESH_NUMTVERTEX))
		{
			vecVT.resize(this->GetInt());
		}
		else if (this->IsEqual(pToken, ID_MESH_TVERTLIST))
		{
			this->ProcessID_MESH_TVERTLIST(vecVT);
		}
		else if (this->IsEqual(pToken, ID_MESH_TFACELIST))
		{
			this->ProcessID_MESH_TFACELIST(vecVertex, vecVT);
		}
		else if (this->IsEqual(pToken, ID_MESH_NORMALS))
		{
			this->ProcessID_MESH_NORMALS(vecVertex);
		}
	} while (nLv > 0);

	pAseNode->SetVecVertex(vecVertex);
}

void cAseLoadManager::ProcessID_TM_ANIMATION(cAseNode * pAseNode, cAnimation* pAnimation)
{
	int nLv = 0;
	do
	{
		CHAR* pToken = this->GetToken();
		if (this->IsEqual(pToken, "{"))
		{
			nLv++;
		}
		else if (this->IsEqual(pToken, "}"))
		{
			nLv--;
		}
		else if (this->IsEqual(pToken, ID_POS_TRACK))
		{
			this->ProcessID_POS_TRACK(pAnimation);
		}
		else if (this->IsEqual(pToken, ID_ROT_TRACK))
		{
			this->ProcessID_ROT_TRACK(pAnimation);
		}
	} while (nLv > 0);
}

void cAseLoadManager::ProcessID_POS_TRACK(cAnimation* pAnimation)
{
	std::vector<cAnimation::ST_POS_TRACK>& vecPosTrack = pAnimation->GetVecPosTrack();

	int nLv = 0;
	do
	{
		CHAR* pToken = this->GetToken();
		if (this->IsEqual(pToken, "{"))
		{
			nLv++;
		}
		else if (this->IsEqual(pToken, "}"))
		{
			nLv--;
		}
		else if (this->IsEqual(pToken, ID_POS_SAMPLE))
		{
			cAnimation::ST_POS_TRACK sPosTrack;

			sPosTrack.ulFrame = this->GetInt();
			sPosTrack.vPosition.x = this->GetFloat();
			sPosTrack.vPosition.z = this->GetFloat();
			sPosTrack.vPosition.y = this->GetFloat();

			vecPosTrack.push_back(sPosTrack);
		}
	} while (nLv > 0);
}

void cAseLoadManager::ProcessID_ROT_TRACK(cAnimation* pAnimation)
{
	std::vector<cAnimation::ST_ROT_TRACK>& vecRotTrack = pAnimation->GetVecRotTrack();

	int nLv = 0;
	do
	{
		CHAR* pToken = this->GetToken();
		if (this->IsEqual(pToken, "{"))
		{
			nLv++;
		}
		else if (this->IsEqual(pToken, "}"))
		{
			nLv--;
		}
		else if (this->IsEqual(pToken, ID_ROT_SAMPLE))
		{
			cAnimation::ST_ROT_TRACK sRotTrack;
			D3DXVECTOR3 vAxis;
			float fAngle = 0.F;

			sRotTrack.ulFrame = this->GetInt();
			vAxis.x = this->GetFloat();
			vAxis.z = this->GetFloat();
			vAxis.y = this->GetFloat();
			fAngle = this->GetFloat();

			D3DXQuaternionRotationAxis(&sRotTrack.sQuarter, 
				&vAxis, fAngle);

			if (!vecRotTrack.empty())
			{
				sRotTrack.sQuarter = 
					vecRotTrack.back().sQuarter * sRotTrack.sQuarter;
			}

			vecRotTrack.push_back(sRotTrack);
		}
	} while (nLv > 0);
}

void cAseLoadManager::ProcessID_MESH_VERTEX_LIST(std::vector<D3DXVECTOR3>& vecV)
{
	int nLv = 0;
	do
	{
		CHAR* pToken = this->GetToken();
		if (this->IsEqual(pToken, "{"))
		{
			nLv++;
		}
		else if (this->IsEqual(pToken, "}"))
		{
			nLv--;
		}
		else if (this->IsEqual(pToken, ID_MESH_VERTEX))
		{
			int nIdx = this->GetInt();
			vecV[nIdx].x = this->GetFloat();
			vecV[nIdx].z = this->GetFloat();
			vecV[nIdx].y = this->GetFloat();
		}
	} while (nLv > 0);
}

void cAseLoadManager::ProcessID_MESH_FACE_LIST(std::vector<ST_PNT_VERTEX>& vecVertex, 
	std::vector<D3DXVECTOR3>& vecV)
{
	int nLv = 0;
	do
	{
		CHAR* pToken = this->GetToken();
		if (this->IsEqual(pToken, "{"))
		{
			nLv++;
		}
		else if (this->IsEqual(pToken, "}"))
		{
			nLv--;
		}
		else if (this->IsEqual(pToken, ID_MESH_FACE))
		{
			int nIdx = this->GetInt();

			this->GetToken();
			vecVertex[nIdx * 3 + 0].p = vecV[this->GetInt()];
			this->GetToken();
			vecVertex[nIdx * 3 + 2].p = vecV[this->GetInt()];
			this->GetToken();
			vecVertex[nIdx * 3 + 1].p = vecV[this->GetInt()];
		}
	} while (nLv > 0);
}

void cAseLoadManager::ProcessID_MESH_TVERTLIST(std::vector<D3DXVECTOR2>& vecVT)
{
	int nLv = 0;
	do
	{
		CHAR* pToken = this->GetToken();
		if (this->IsEqual(pToken, "{"))
		{
			nLv++;
		}
		else if (this->IsEqual(pToken, "}"))
		{
			nLv--;
		}
		else if (this->IsEqual(pToken, ID_MESH_TVERT))
		{
			int nIdx = this->GetInt();
			vecVT[nIdx].x = this->GetFloat();
			vecVT[nIdx].y = 1.F - this->GetFloat();
		}
	} while (nLv > 0);
}

void cAseLoadManager::ProcessID_MESH_TFACELIST(std::vector<ST_PNT_VERTEX>& vecVertex, std::vector<D3DXVECTOR2>& vecVT)
{
	int nLv = 0;
	do
	{
		CHAR* pToken = this->GetToken();
		if (this->IsEqual(pToken, "{"))
		{
			nLv++;
		}
		else if (this->IsEqual(pToken, "}"))
		{
			nLv--;
		}
		else if (this->IsEqual(pToken, ID_MESH_TFACE))
		{
			int nIdx = this->GetInt();

			vecVertex[nIdx * 3 + 0].t = vecVT[this->GetInt()];
			vecVertex[nIdx * 3 + 2].t = vecVT[this->GetInt()];
			vecVertex[nIdx * 3 + 1].t = vecVT[this->GetInt()];
		}
	} while (nLv > 0);
}

void cAseLoadManager::ProcessID_MESH_NORMALS(std::vector<ST_PNT_VERTEX>& vecVertex)
{
	int nIdx = 0;

	int nLv = 0;
	do
	{
		CHAR* pToken = this->GetToken();
		if (this->IsEqual(pToken, "{"))
		{
			nLv++;
		}
		else if (this->IsEqual(pToken, "}"))
		{
			nLv--;
		}
		else if (this->IsEqual(pToken, ID_MESH_FACENORMAL))
		{
			nIdx = this->GetInt();
		}
		else if (this->IsEqual(pToken, ID_MESH_FACENORMAL))
		{
			this->GetToken();

			D3DXVECTOR3 n;
			n.x = this->GetFloat();
			n.z = this->GetFloat();
			n.y = this->GetFloat();

			vecVertex[nIdx++].n = n;

			if (nIdx % 3 == 0)
			{
				D3DXVECTOR3 vTmp = vecVertex[nIdx - 1].n;
				vecVertex[nIdx - 1].n = vecVertex[nIdx - 2].n;
				vecVertex[nIdx - 2].n = vTmp;
			}
		}
	} while (nLv > 0);
}
