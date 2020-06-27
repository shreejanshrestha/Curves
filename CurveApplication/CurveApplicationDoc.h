// CurveApplicationDoc.h : interface of the CCurveApplicationDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVEAPPLICATIONDOC_H__041BA02E_6F2A_4600_8041_6569CCBD29E2__INCLUDED_)
#define AFX_CURVEAPPLICATIONDOC_H__041BA02E_6F2A_4600_8041_6569CCBD29E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCurveApplicationDoc : public CDocument
{
protected: // create from serialization only
	CCurveApplicationDoc();
	DECLARE_DYNCREATE(CCurveApplicationDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveApplicationDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCurveApplicationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCurveApplicationDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEAPPLICATIONDOC_H__041BA02E_6F2A_4600_8041_6569CCBD29E2__INCLUDED_)
