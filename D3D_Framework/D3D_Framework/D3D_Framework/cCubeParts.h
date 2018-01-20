#pragma once
#include "cCubeNode.h"

class cCubeParts : public cCubeNode
{
public:
	cCubeParts();
	virtual ~cCubeParts();
	
	void Setup(D3DXVECTOR3 vScale, D3DXVECTOR3 vAniLocal, D3DXVECTOR3 vLocalPos);
};

