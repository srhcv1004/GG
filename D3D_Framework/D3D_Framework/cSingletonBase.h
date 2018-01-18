#pragma once

template <typename T>
class cSingletonBase
{
protected:
	static T*												m_pSingleton;

protected:
	cSingletonBase() {}
	~cSingletonBase() {}

public:
	static T* GetSingleton();
	void ReleaseSingleton();
};

template <typename T>
T* cSingletonBase<T>::m_pSingleton = NULL;

template <typename T>
inline T * cSingletonBase<T>::GetSingleton()
{
	if (!m_pSingleton) m_pSingleton = new T();
	return m_pSingleton;
}

template <typename T>
inline void cSingletonBase<T>::ReleaseSingleton()
{
	if (m_pSingleton)
	{
		delete m_pSingleton;
		m_pSingleton = NULL;
	}
}
