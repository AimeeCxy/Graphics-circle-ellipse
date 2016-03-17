// GODoc.cpp : CGODoc 类的实现
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


// CGODoc 构造/析构

CGODoc::CGODoc()
{
	// TODO: 在此添加一次性构造代码

}

CGODoc::~CGODoc()
{
}

BOOL CGODoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CGODoc 序列化

void CGODoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CGODoc 诊断

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


// CGODoc 命令
