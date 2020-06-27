// CurveApplicationView.cpp : implementation of the CCurveApplicationView class
//

#include "stdafx.h"
#include "CurveApplication.h"

#include "CurveApplicationDoc.h"
#include "CurveApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveApplicationView

IMPLEMENT_DYNCREATE(CCurveApplicationView, CView)

BEGIN_MESSAGE_MAP(CCurveApplicationView, CView)
	//{{AFX_MSG_MAP(CCurveApplicationView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveApplicationView construction/destruction

#define FUNCTION_X(x) (0.00001f * (float)x * (float)x * (float)x)

#define DERIVATIVE_X(x) (0.00003f * (float)x * (float)x)

CCurveApplicationView::CCurveApplicationView()
{
	// TODO: add construction code here

}

CCurveApplicationView::~CCurveApplicationView()
{
}

BOOL CCurveApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCurveApplicationView drawing

typedef struct tagfPoint
{
	float x;
	float y;
}fPoint;

void CCurveApplicationView::OnDraw(CDC* pDC)
{
	CCurveApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	const int nCount = 600;
	fPoint vertices[nCount];

	int nIndex = 0;
	for(int x = 0; x < nCount; x++)
	{
		vertices[nIndex].x = (float)x;
		vertices[nIndex].y = FUNCTION_X((float)x);

		nIndex++;
	}

	CPen cPenRed;
	cPenRed.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	CPen* pPenOld = pDC->SelectObject(&cPenRed);

	for(x = 0; x < nCount; x++)
	{
	}

	pDC->SelectObject(pPenOld);
	cPenRed.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// CCurveApplicationView printing

BOOL CCurveApplicationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCurveApplicationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCurveApplicationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCurveApplicationView diagnostics

#ifdef _DEBUG
void CCurveApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CCurveApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCurveApplicationDoc* CCurveApplicationView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCurveApplicationDoc)));
	return (CCurveApplicationDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCurveApplicationView message handlers
