#pragma once
#include "cAction.h"

class cActionSequence : public cAction, public iDelegate
{
protected:
	typedef std::vector<cAction*>							vecAction;
	typedef std::vector<cAction*>::iterator					vecActionIter;

protected:
	vecAction												m_vecActions;
	vecActionIter											m_vecActionsIter;

public:
	cActionSequence();
	virtual ~cActionSequence();

	virtual void Start();
	virtual void Update();
	virtual void ActionFinish();
	
	void AddAction(cAction* pAction);
};

