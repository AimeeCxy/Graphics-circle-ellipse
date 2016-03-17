// GOView.h : CGOView 类的接口
//


#pragma once
#include "atltypes.h"


class CGOView : public CView
{
protected: // 仅从序列化创建
	CGOView();
	DECLARE_DYNCREATE(CGOView)

// 属性
public:
	CGODoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CGOView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawellipse();
	afx_msg void OnDrawcircle();
	afx_msg void OnDrawmult();
	// 绘图类型
	int m_DrawType;
	// 是否正在绘图
	bool m_isDraw;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CPoint pointEnd;
	CPoint pointStart;
	// 中点画圆算法
	void midPointCircle(CDC* pDC, int x0, int y0, int R, COLORREF color);
	// Bresanham画椭圆算法
	void bresenhamEllipse(CDC* pDC, int x0, int y0, int a, int b, COLORREF color);
	CPoint pointCurrent;
	// 鼠标是否按下
	bool m_LButtonDown;
	// 光标资源句柄
	HCURSOR m_Cursor;
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	// 多边形顶点列表
	CArray<CPoint,CPoint> pointList;
	// 边标志法填充
	//void EdgeMarkFill(CArray<CPoint,CPoint> ptArray);
	// 用位图填充
	void PatternFill(int x, int y, COLORREF color);
	void EdgeMarkFill(void);
};


BOOL Polygon(LPPOINT lpPoints, int nCount);

#ifndef _DEBUG  // GOView.cpp 中的调试版本
inline CGODoc* CGOView::GetDocument() const
   { return reinterpret_cast<CGODoc*>(m_pDocument); }
#endif

