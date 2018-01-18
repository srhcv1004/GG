#pragma once
#include "cSingletonBase.h"

struct ST_PNT_VERTEX;

class cAseNode;
class cTexMtl;
class cAnimation;

class cAseLoadManager : public cSingletonBase<cAseLoadManager>
{
private:
	FILE*													m_pFile;

private:
	char													m_szToken[1024];
	const CHAR*												m_pAseFolderName;

private:
	cAseNode*												m_pAseRoot;

private:
	CHAR* GetToken();
	int GetInt();
	float GetFloat();
	bool IsWhite(char ch);
	bool IsEqual(const CHAR* pDst, const CHAR* pSrc);

private:
	void ProcessID_MATERIAL_LIST();
	void ProcessID_MATERIAL(cTexMtl* pTexMtl);
	void ProcessID_MAP_DIFFUSE(cTexMtl* pTexMtl);

	void ProcessID_SCENE();

	cAseNode* ProcessID_GEOMETRY(std::map<std::string, cAseNode*>& mapAseCharacter);
	void ProcessID_NODE_TM(cAseNode* pAseNode);
	void ProcessID_MESH(cAseNode* pAseNode);
	void ProcessID_TM_ANIMATION(cAseNode* pAseNode, cAnimation* pAnimation);
	void ProcessID_POS_TRACK(cAnimation* pAnimation);
	void ProcessID_ROT_TRACK(cAnimation* pAnimation);

	void ProcessID_MESH_VERTEX_LIST(std::vector<D3DXVECTOR3>& vecV);
	void ProcessID_MESH_FACE_LIST(std::vector<ST_PNT_VERTEX>& vecVertex, std::vector<D3DXVECTOR3>& vecV);
	void ProcessID_MESH_TVERTLIST(std::vector<D3DXVECTOR2>& vecVT);
	void ProcessID_MESH_TFACELIST(std::vector<ST_PNT_VERTEX>& vecVertex, std::vector<D3DXVECTOR2>& vecVT);
	void ProcessID_MESH_NORMALS(std::vector<ST_PNT_VERTEX>& vecVertex);

public:
	cAseLoadManager();
	virtual ~cAseLoadManager();

	void Setup();
	void Release();

	cAseNode* LoadAse(std::map<std::string, cAseNode*>& mapAseCharacter, 
		const CHAR* pAseFolderName, const CHAR* pAseFileName);
};

