/*!
 * \file InfoSubject.h
 * \date 2016/06/04 21:48
 *
 * \author 박정민
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
//! 옵저버의 구조?

#ifndef InfoSubject_h__
#define InfoSubject_h__

#include "Engine_Include.h"
#include "Subject.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CInfoSubject : public CSubject
{
	DECLARE_SINGLETON(CInfoSubject)

public:
	//! 근데 이러면 포인터가 넘어가는 셈이라, 결국 원래 자료를 수정하는 꼴이..
	// 최소한 const 포인터라도 넘겨야 되는거 아닌가?
	typedef list<void*> DATA_LIST;
private:
	typedef map<int, DATA_LIST> DATA_LIST_MAP;

	// member variable
private:
	DATA_LIST_MAP m_DataListMap;

	// member function
public:
	void AddData(int _iMessage, void* _pData);
	void RemoveData(int _iMessage, void* _pData);

	const DATA_LIST* GetDataList(int _iMessage);
private:
	void Release(void);

	// getter & setter
public:
	// -

	// constructor & destructor
private:
	explicit CInfoSubject(void);
	virtual ~CInfoSubject(void);
};
END_NAMESPACE

#endif // InfoSubject_h__