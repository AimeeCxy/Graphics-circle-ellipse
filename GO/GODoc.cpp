// GODoc.cpp : CGODoc ���ʵ��
//

#include "stdafx.h"
#include "GO.h"

#include "GODoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGODoc

IMPLEMENT_DYNCREATE(CGODoc, CDocument)

BEGIN_MESSAGE_MAP(CGODoc, CDocument)
END_MESSAGE_MAP()


// CGODoc ����/����

CGODoc::CGODoc()
{
	// TODO: �ڴ����һ���Թ������

}

CGODoc::~CGODoc()
{
}

BOOL CGODoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CGODoc ���л�

void CGODoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CGODoc ���

#ifdef _DEBUG
void CGODoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGODoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGODoc ����
