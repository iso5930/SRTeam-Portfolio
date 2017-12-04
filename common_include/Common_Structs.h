/*!
 * \file Common_Structs.h
 * \date 2016/05/31 20:59
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

#ifndef Common_Structs_h__
#define Common_Structs_h__

typedef struct tagVertexColor
{
	D3DXVECTOR3 vPos;
	DWORD dwColor;

	tagVertexColor(void)
		:vPos(0.f, 0.f, 0.f)
		,dwColor(0) { }
} VERTEX_COLOR;
const DWORD VERTEX_COLOR_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;

typedef struct tagVertextColorRHW
{
	D3DXVECTOR3 vPos;
	float fRHW;
	DWORD dwColor;
	tagVertextColorRHW(void)
		:vPos(0.f, 0.f, 0.f), fRHW(1.f), dwColor(0)
	{

	}

}VERTEX_COLOR_RHW;

const DWORD VERTEX_COLOR_RHW_FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX0;

typedef struct tagVertexTexture
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR2 vTex;

	tagVertexTexture(void)
		:vPos(0.f, 0.f, 0.f)
		,vTex(0.f, 0.f) { }
} VERTEX_TEXTURE;
const DWORD VERTEX_TEXTURE_FVF = D3DFVF_XYZ | D3DFVF_TEX1;

typedef struct tagVertexCube
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vTex;

	tagVertexCube(void)
		:vPos(0.f, 0.f, 0.f)
		,vTex(0.f, 0.f, 0.f) { }
} VERTEX_CUBE;
const DWORD VERTEX_CUBE_FVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

typedef struct tagIndex16
{
	WORD _1, _2, _3;

	tagIndex16(void)
		:_1(0), _2(0), _3(0) { }
} INDEX16;

typedef struct tagIndex32
{
	DWORD _1, _2, _3;

	tagIndex32(void)
		:_1(0), _2(0), _3(0) { }
} INDEX32;

typedef struct tagTexInfo
{	
	LPDIRECT3DTEXTURE9	pTexture;
	D3DXIMAGE_INFO		ImgInfo;

}TEXINFO;

typedef struct tagCharacterState
{

	int iLevel;
	int	iExp;
	int iNextExp;
	int	iBarrierPoint;
	int iMaxBarrierPoint;
	int iHitPoint;
	int iMaxHitPoint;
	int iRageGauge;
	int iMaxRageGauge;
	int iSTR;
	int iVIT;
	int iINT;
	int iAGI;
	int iLUK;
	int iATK;
	int iDEF;
	int iMAG;
	int iSPD;
	int iCRI;
	int iAbility1;
	int iAbility2;
	int iAbility3;
	int iMaxAbility1;
	int iMaxAbility2;
	int iMaxAbility3;

} CHARACTER_STATE;

typedef struct tagFrame
{
	float fStartFrame;
	float fCurFrame;
	float fEndFrame;
	float fFrameTime;
	
	tagFrame(void){}
	tagFrame(float _StartFrame, float _EndFrame, float _FrameTime)
		:fStartFrame(_StartFrame), fEndFrame(_EndFrame), fFrameTime(_FrameTime), fCurFrame(_StartFrame)
	{

	}
}FRAME;

typedef struct tagMemento
{
	eCharacterState eState;//저장된 스테이터스 값...
	D3DXVECTOR3		vPos; //저장된 캐릭터 위치값..
	D3DXVECTOR3		vDestPos; //저장된 목표 위치값 카메라가 회전했을 경우 스프라이트를 다시 골라야 하기 때문에.
	int				iCurFrame; //회전값을 다시 구한다면 필요가 없다...?
	int				iIndex; //다시 구해야 하므로 필요가 없다..

	tagMemento(void){}
	tagMemento(eCharacterState _eState, D3DXVECTOR3 _vPos, D3DXVECTOR3 _vDestPos, int _iCurFrame, int _iIndex)
		:eState(_eState), vPos(_vPos), vDestPos(_vDestPos), iCurFrame(_iCurFrame), iIndex(_iIndex)
	{

	}

}MEMENTO;

typedef struct tagMonsterState
{
	char	szName[20];
	int		iLevel;
	eMonsterType	eMonType;

	int		iHitPoint;
	int		iMaxHitPoint;
	int		iBarrierPoint;
	int		iMaxBarrierPoint;
	int		iATK;
	int		iSPD;
	int		iDEF;
	int		iEXP;
}MONSTER_STATE;

#endif // Common_Structs_h__