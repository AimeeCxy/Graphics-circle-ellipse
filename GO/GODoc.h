// GODoc.h : CGODoc ��Ľӿ�
//


#pragma once


class CGODoc : public CDocument
{
protected: // �������л�����
	CGODoc();
	DECLARE_DYNCREATE(CGODoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CGODoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


