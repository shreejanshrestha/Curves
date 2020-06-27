// CurveApplicationView.h : interface of the CCurveApplicationView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVEAPPLICATIONVIEW_H__59A5A5BF_8DF0_41AD_854F_829048D751F1__INCLUDED_)
#define AFX_CURVEAPPLICATIONVIEW_H__59A5A5BF_8DF0_41AD_854F_829048D751F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCurveApplicationView : public CView
{
protected: // create from serialization only
	CCurveApplicationView();
	DECLARE_DYNCREATE(CCurveApplicationView)

// Attributes
public:
	CCurveApplicationDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveApplicationView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCurveApplicationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCurveApplicationView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CurveApplicationView.cpp
inline CCurveApplicationDoc* CCurveApplicationView::GetDocument()
   { return (CCurveApplicationDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEAPPLICATIONVIEW_H__59A5A5BF_8DF0_41AD_854F_829048D751F1__INCLUDED_)
