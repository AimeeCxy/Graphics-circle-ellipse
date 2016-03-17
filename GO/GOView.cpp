// GOView.cpp : CGOView 类的实现
//

#include "stdafx.h"
#include "GO.h"

#include "GODoc.h"
#include "GOView.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGOView

IMPLEMENT_DYNCREATE(CGOView, CView)

BEGIN_MESSAGE_MAP(CGOView, CView)
	ON_COMMAND(ID_DRAWELLIPSE, &CGOView::OnDrawellipse)
	ON_COMMAND(ID_DRAWCIRCLE, &CGOView::OnDrawcircle)
	ON_COMMAND(ID_DRAWMULT, &CGOView::OnDrawmult)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CGOView 构造/析构

CGOView::CGOView()
: m_DrawType(0)
, m_isDraw(false)
, pointEnd(0)
, pointStart(0)
, pointCurrent(0)
, m_LButtonDown(false)
{
	// TODO: 在此处添加构造代码
	m_LButtonDown = false;
}



CGOView::~CGOView()
{
}

BOOL CGOView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGOView 绘制

void CGOView::OnDraw(CDC* pDC)
{
	CGODoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CGOView 诊断

#ifdef _DEBUG
void CGOView::AssertValid() const
{
	CView::AssertValid();
}

void CGOView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGODoc* CGOView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGODoc)));
	return (CGODoc*)m_pDocument;
}
#endif //_DEBUG


// CGOView 消息处理程序

void CGOView::OnDrawellipse()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = 2;//2表示绘制椭圆
	m_Cursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	m_isDraw = true;//当前处于绘图状态

}

void CGOView::OnDrawcircle()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = 1;//1表示绘制圆
	m_Cursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	m_isDraw = true;//当前处于绘图状态

}

void CGOView::OnDrawmult()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = 3;//3表示绘制多边形并填充
	m_Cursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	m_isDraw = true;//当前处于绘图状态
}

void CGOView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCursor(m_Cursor);//设置使用光标资源
	ReleaseCapture();//释放鼠标
	CDC* cdc = this->GetDC();
	pointEnd = point;
	if ((m_DrawType == 1))
	{
		int radius = (int)sqrt(1.0*(pointEnd.x - pointStart.x)*( pointEnd.x - pointStart.x) + (pointEnd.y - pointStart.y)*( pointEnd.y - pointStart.y));
		midPointCircle(cdc,(int) pointStart.x,(int) pointStart.y, radius, RGB(255, 0, 0));
	}
	else if((m_DrawType==2))
	{
		bresenhamEllipse(cdc, (int)pointStart.x, (int)pointStart.y, (int)abs(pointEnd.x - pointStart.y), (int)abs(pointEnd.y - pointStart.y), RGB(0, 255, 0));
	}
	else
	{
	}
	m_LButtonDown = false;//设置鼠标左键按下
	CView::OnLButtonUp(nFlags, point);
}

void CGOView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCursor(m_Cursor);//设置使用光标资源
	pointCurrent=point;
	CDC* cdc = this->GetDC();
	if ((m_LButtonDown && m_DrawType == 1))
	{
		int radius = (int)sqrt(1.0*(pointEnd.x - pointStart.x)*( pointEnd.x - pointStart.x) + (pointEnd.y - pointStart.y)*( pointEnd.y - pointStart.y));
		midPointCircle(cdc,(int) pointStart.x,(int) pointStart.y, radius, RGB(255, 255, 255));
	
		radius = (int)sqrt(1.0*(pointCurrent.x - pointStart.x)*( pointCurrent.x - pointStart.x) + (pointCurrent.y - pointStart.y)*( pointCurrent.y - pointStart.y));
		midPointCircle(cdc,(int) pointStart.x,(int) pointStart.y, radius, RGB(255, 0, 0));

		pointEnd = pointCurrent;
	}
	if ((m_LButtonDown && m_DrawType==2))
	{
		bresenhamEllipse(cdc, (int)pointStart.x, (int)pointStart.y, (int)abs(pointEnd.x - pointStart.y), (int)abs(pointEnd.y - pointStart.y), RGB(255, 255, 255));
	
		bresenhamEllipse(cdc, (int)pointStart.x, (int)pointStart.y, (int)abs(pointCurrent.x - pointStart.y), (int)abs(pointCurrent.y - pointStart.y), RGB(0, 255, 0));
	
		pointEnd = pointCurrent;
	}
	
	CView::OnMouseMove(nFlags, point);
}

void CGOView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCursor(m_Cursor);//设置使用光标资源
	this->SetCapture();//捕捉鼠标
	//设置开始点和终止点，此时为同一点
	pointStart = point;
	pointEnd = point;
	m_LButtonDown = true;//设置鼠标左键按下
	
	if(m_DrawType==3)
	{
		CDC *pDC = GetDC();
		pointList.Add(point);
		pDC->SetPixel(point.x,point.y,RGB(0,0,0));
	}
	CView::OnLButtonDown(nFlags, point);
}

// 中点画圆算法
void CGOView::midPointCircle(CDC* pDC, int x0, int y0, int R, COLORREF color)
{
	int x, y, dx, dy, d;
	x = 0; y = R; d = 1 - R;
	dx = 3; dy = 5 - (R << 1);
	while (x < y){
		pDC->SetPixel(x + x0,y + y0, color);
		pDC->SetPixel(-x + x0, y + y0, color);
		pDC->SetPixel(x + x0, -y + y0, color);
		pDC->SetPixel(-x + x0, -y + y0, color);
		pDC->SetPixel(y + x0, x + y0, color);	
		pDC->SetPixel(-y + x0, x + y0, color);
		pDC->SetPixel(y + x0, -x + y0, color);
		pDC->SetPixel(-y+ x0, -x + y0, color);
		if (d < 0){
			d += dx;
			dx += 2;
			x++;
		}
		else
		{
			d += dx + dy;
			dx += 2;
			dy += 2;
			x++;
			y--;
		}
	}
}

// Bresanham画椭圆算法
void CGOView::bresenhamEllipse(CDC* pDC, int x0, int y0, int a, int b, COLORREF color)
{
	int x, y, p;
	int aa = a*a;
	int bb = b*b;
	//绘制第一部分
	x = 0; y = b; p = 2 * bb + aa*(1 - 2 * b);
	while (bb*x <= aa*y){
		//绘制对称的四个点
		pDC->SetPixel(x + x0, y + y0, color);
		pDC->SetPixel(-x + x0, y + y0, color);
		pDC->SetPixel(x + x0, -y + y0, color);
		pDC->SetPixel(-x + x0, -y + y0, color);
		if (p >= 0){
			p += 4 * aa*(1 - y) + bb*(4 * x + 6);
			y--;
		}
		else{
			p += bb*(4 * x + 6);
		}
		x++;
	}
	//绘制第二部分
	x = a; y = 0; p = 2 * aa + bb*(1 - 2 * a);
	while (bb*x > aa*y){
		//绘制四个对称点
		pDC->SetPixel(x + x0, y + y0, color);
		pDC->SetPixel(-x + x0, y + y0, color);
		pDC->SetPixel(x + x0, -y + y0, color);
		pDC->SetPixel(-x + x0, -y + y0, color);
		if (p > 0){
			p += 4 * bb*(1 - x) + aa*(4 * y + 6);
			x--;
		}
		else
		{
			p += aa*(4 * y + 6);
		}
		y++;
	}
}



void CGOView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	pointList.Add(point);
	//CGODoc * pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	CDC *cdc = GetDC();

	POINT p[20];
	for(int i=0;i<pointList.GetSize();i++)
	{
		p[i] = pointList.GetAt(i);
	}
	//CBrush brush1(RGB(255,0,0));
	//cdc->SelectObject(&brush1);
	cdc->Polygon(p,pointList.GetSize());
	EdgeMarkFill();
	pointList.RemoveAll();
	CView::OnLButtonDblClk(nFlags, point);
}

// 边标志法填充
//void CGOView::EdgeMarkFill(CArray<CPoint,CPoint>)
//{
//}

// 用位图填充
static int NumPicture[8][24] = {
	{0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0},
	{0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0},
	{0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0},
	{0,1,0,0,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,0,0},
	{0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
	{0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0},
	{0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,0,0,0,0}
};
void CGOView::PatternFill(int x, int y, COLORREF color)
{
	CDC* pDC = GetDC();
	if(NumPicture[y%8][x%24]==1)
	{
		pDC->SetPixel(x,y,color);
	}
}

void CGOView::EdgeMarkFill(void)
{
	
	int x2=0,x1=10000,y2=0,y1=10000,x,y;
	
	for(int i=0;i < pointList.GetSize();i++){
		if(pointList.GetAt(i).x<x1)
			x1 = pointList.GetAt(i).x;
		if(pointList.GetAt(i).x>x2)
			x2 = pointList.GetAt(i).x;
		if(pointList.GetAt(i).y<y1)
			y1 = pointList.GetAt(i).y;
		if(pointList.GetAt(i).y>y2)
			y2 = pointList.GetAt(i).y;
	}
	/*
	bool MASK[1000][1000];
	for(y=y1;y<=y2;y++)//形成轮廓线
		for(x=x1;x<=x2;x++)
			MASK[y][x] = false;

	int xs,dxs,ys,Ixs;
	for(int i=0;i<pointList.GetSize()-1;i++)
	{
		xs = pointList.GetAt(i).x;
		if((pointList.GetAt(i+1).y - pointList.GetAt(i).y)!=0)
		{
			dxs = ( pointList.GetAt(i+1).x - pointList.GetAt(i).x) / ( pointList.GetAt(i+1).y - pointList.GetAt(i).y);
		}
		if(pointList.GetAt(i).y < pointList.GetAt(i+1).y)
			for(ys = pointList.GetAt(i).y;ys<= pointList.GetAt(i+1).y;ys++)
			{
				xs = xs + dxs;
				Ixs = (int)(xs + 0.5);
				MASK[ys][Ixs] =! MASK[ys][Ixs];
			}
		else
			for(ys = pointList.GetAt(i+1).y;ys<= pointList.GetAt(i).y;ys++)
			{
				xs = xs + dxs;
				Ixs = (int)(xs - 0.5);
				MASK[ys][Ixs] =! MASK[ys][Ixs];
			}
	}
	*/
	bool inside;
	COLORREF co = RGB(0,0,0);
	CDC* pDC = GetDC();
	for(y=y1;y<=y2;y++)
	{
		inside = false;
		for(x=x1;x<=x2;x++)
		{
			if(co==pDC->GetPixel(x,y))
				inside =! inside;
			if(inside)
			{
				PatternFill(x,y,RGB(128,64,32));
				
				//pDC->SetPixel(x,y,RGB(255,0,0));
			}
				
				
		}
	}
}
