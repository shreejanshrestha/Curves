// CurveApplicationDoc.cpp : implementation of the CCurveApplicationDoc class
//

#include "stdafx.h"
#include "CurveApplication.h"

#include "CurveApplicationDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveApplicationDoc

IMPLEMENT_DYNCREATE(CCurveApplicationDoc, CDocument)

BEGIN_MESSAGE_MAP(CCurveApplicationDoc, CDocument)
	//{{AFX_MSG_MAP(CCurveApplicationDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveApplicationDoc construction/destruction

CCurveApplicationDoc::CCurveApplicationDoc()
{
	// TODO: add one-time construction code here

}

CCurveApplicationDoc::~CCurveApplicationDoc()
{
}

BOOL CCurveApplicationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCurveApplicationDoc serialization

void CCurveApplicationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCurveApplicationDoc diagnostics

#ifdef _DEBUG
void CCurveApplicationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCurveApplicationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCurveApplicationDoc commands
