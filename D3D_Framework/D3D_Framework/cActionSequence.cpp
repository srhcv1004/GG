#include "stdafx.h"
#include "cActionSequence.h"

cActionSequence::cActionSequence()
{
}

cActionSequence::~cActionSequence()
{
}

void cActionSequence::Start()
{
	if (m_vecActions.empty()) return;

	m_vecActionsIter = m_vecActions.begin();
	(*m_vecActionsIter)->Start();
}

void cActionSequence::Update()
{
	(*m_vecActionsIter)->Update();
}

void cActionSequence::ActionFinish()
{
	if (m_vecActionsIter + 1 == m_vecActions.end())
	{
		m_vecActionsIter = m_vecActions.begin();
		(*m_vecActionsIter)->Start();
	}
	else
	{
		m_vecActionsIter++;
		(*m_vecActionsIter)->Start();
	}
}

void cActionSequence::AddAction(cAction * pAction)
{
	m_vecActions.push_back(pAction);
}
