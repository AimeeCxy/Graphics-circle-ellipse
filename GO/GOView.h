// GOView.h : CGOView ��Ľӿ�
//


#pragma once
#include "atltypes.h"


class CGOView : public CView
{
protected: // �������л�����
	CGOView();
	DECLARE_DYNCREATE(CGOView)

// ����
public:
	CGODoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CGOView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawellipse();
	afx_msg void OnDrawcircle();
	afx_msg void OnDrawmult();
	// ��ͼ����
	int m_DrawType;
	// �Ƿ����ڻ�ͼ
	bool m_isDraw;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CPoint pointEnd;
	CPoint pointStart;
	// �е㻭Բ�㷨
	void midPointCircle(CDC* pDC, int x0, int y0, int R, COLORREF color);
	// Bresanham����Բ�㷨
	void bresenhamEllipse(CDC* pDC, int x0, int y0, int a, int b, COLORREF color);
	CPoint pointCurrent;
	// ����Ƿ���
	bool m_LButtonDown;
	// �����Դ���
	HCURSOR m_Cursor;
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	// ����ζ����б�
	CArray<CPoint,CPoint> pointList;
	// �߱�־�����
	//void EdgeMarkFill(CArray<CPoint,CPoint> ptArray);
	// ��λͼ���
	void PatternFill(int x, int y, COLORREF color);
	void EdgeMarkFill(void);
};


BOOL Polygon(LPPOINT lpPoints, int nCount);

#ifndef _DEBUG  // GOView.cpp �еĵ��԰汾
inline CGODoc* CGOView::GetDocument() const
   { return reinterpret_cast<CGODoc*>(m_pDocument); }
#endif

