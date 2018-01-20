#pragma once

class cAnimation
{
public:
	struct ST_POS_TRACK
	{
		DWORD												ulFrame;
		D3DXVECTOR3											vPosition;
	};

	struct ST_ROT_TRACK
	{
		DWORD												ulFrame;
		D3DXQUATERNION										sQuarter;
	};

private:
	D3DXMATRIXA16											m_matLocalTM;

private:
	D_SYNTHESIZE_REF(std::vector<ST_POS_TRACK>, m_vecPosTrack, VecPosTrack);
	D_SYNTHESIZE_REF(std::vector<ST_ROT_TRACK>, m_vecRotTrack, VecRotTrack);

private:
	D_SYNTHESIZE_REF(D3DXMATRIXA16, m_matAnimation, MatAnimation);
	D3DXMATRIXA16											m_matAniR;
	D3DXMATRIXA16											m_matAniT;

private:
	void AnimationRotTrack(float* pFrame);
	void AnimationPosTrack(float* pFrame);

public:
	cAnimation();
	~cAnimation();

	void Setup();
	void Release();
	void Update(float* pFrame, D3DXMATRIXA16* pLocalTM);
};

