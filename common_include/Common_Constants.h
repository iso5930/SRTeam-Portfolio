/*!
 * \file Common_Constants.h
 * \date 2016/05/24 23:03
 *
 * \author 박정민
 * Contact: jmpark1125@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
 enum으로 정의된 친구들, 마침 정수라 가능해서 그렇게 한거임.
 상순데 이름으로 메모리 공간 주소 참조할 수 있는 데다가
 공간에 뭔짓을 할지 모름(const_cast)
*/

#ifndef Common_Constants_h__
#define Common_Constants_h__

enum
{
	FULL_STRING = 256,

	WINCX = 800,
	WINCY = 600
};

#endif // Common_Constants_h__