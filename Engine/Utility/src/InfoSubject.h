/*!
 * \file InfoSubject.h
 * \date 2016/06/04 21:48
 *
 * \author ������
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
//! �������� ����?

#ifndef InfoSubject_h__
#define InfoSubject_h__

#include "Engine_Include.h"
#include "Subject.h"

BEGIN_NAMESPACE(ENGINE)
class ENGINE_DLL_SPECIFIER CInfoSubject : public CSubject
{
	DECLARE_SINGLETON(CInfoSubject)

public:
	//! �ٵ� �̷��� �����Ͱ� �Ѿ�� ���̶�, �ᱹ ���� �ڷḦ �����ϴ� ����..
	// �ּ��� const �����Ͷ� �Ѱܾ� �Ǵ°� �ƴѰ�?
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