#pragma once

class cAction;

class iDelegate
{
public:
	virtual void ActionFinish() = 0;
};

class cAction
{
protected:
	D_SYNTHESIZE(iDelegate*, m_pDelegate, Delegate);

public:
	cAction()
		: m_pDelegate(NULL)
	{
	}
	virtual ~cAction() {}

	virtual void Start() = 0;
	virtual void Update() = 0;
};

