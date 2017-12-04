/*!
 * \file Common_Macros.h
 * \date 2016/05/24 19:36
 *
 * \author 박정민
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 fail check or null check macro는 만들지 않습니다..
 귀찮아서 그런건 아니고 같은 에러가 발생해도 에러가 발생한 위치마다 그에 따른 대처가 매번 달라야 하는데
 매크로로 매번 메세지박스 띄우고 중단점만 걸어줘봐야 무슨 의미겠냐 싶어서..
 if문 안에 내용물이나 실하게 채워주는게 낫겠지요..
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