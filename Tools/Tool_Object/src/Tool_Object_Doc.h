
// Tool_Object_Doc.h : CTool_Object_Doc Ŭ������ �������̽�
//


#pragma once


class CTool_Object_Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CTool_Object_Doc();
	DECLARE_DYNCREATE(CTool_Object_Doc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CTool_Object_Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


