/*!
 * \file Common_Macros.h
 * \date 2016/05/24 19:36
 *
 * \author ������
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 fail check or null check macro�� ������ �ʽ��ϴ�..
 �����Ƽ� �׷��� �ƴϰ� ���� ������ �߻��ص� ������ �߻��� ��ġ���� �׿� ���� ��ó�� �Ź� �޶�� �ϴµ�
 ��ũ�η� �Ź� �޼����ڽ� ���� �ߴ����� �ɾ������ ���� �ǹ̰ڳ� �;..
 if�� �ȿ� ���빰�̳� ���ϰ� ä���ִ°� ��������..
*/

#ifndef Common_Macros_h__
#define Common_Macros_h__

#define MAKE_UNCOPYABLE(_ClassName)					\
private:											\
	_ClassName(_ClassName& _Other);					\
	_ClassName& operator =(_ClassName& _Other);		\


#define DECLARE_SINGLETON(_ClassName)				\
	MAKE_UNCOPYABLE(_ClassName)						\
private:											\
	static _ClassName* m_pInstance;					\
public:												\
	static _ClassName* GetInstance(void);			\
	static void DestroyInstance(void);				\


#define IMPLEMENT_SINGLETON(_ClassName)				\
	_ClassName* _ClassName::m_pInstance = NULL;		\
	_ClassName* _ClassName::GetInstance(void)		\
	{												\
		if (!m_pInstance)							\
		m_pInstance = new _ClassName;				\
		return m_pInstance;							\
	}												\
	void _ClassName::DestroyInstance(void)			\
	{												\
		delete m_pInstance;							\
		m_pInstance = NULL;							\
	}												\


#endif // Common_Macros_h__