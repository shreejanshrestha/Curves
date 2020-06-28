#include "stdafx.h"
#include "Curves.h"
#include "CurvesDlg.h"
#include "afxdialogex.h"
#include <Eigen/Dense>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

CCurvesDlg::CCurvesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CURVES_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCurvesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCurvesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

BOOL CCurvesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	this->SetCoordinateRange(-1, 1, -1, 1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCurvesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCurvesDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting

		CPen blackPen;
		blackPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

		auto oldPen = dc.SelectObject(&blackPen);

		dc.Rectangle(this->m_rectGraph);

		CBrush greenBrush;
		greenBrush.CreateSolidBrush(RGB(0, 255, 0));

		auto oldBrush = dc.SelectObject(&greenBrush);

		Point origin = this->ConvertToWindows(Point(0, 0));

		dc.Ellipse(origin.x() - this->m_pointRadius, origin.y() - this->m_pointRadius, origin.x() + this->m_pointRadius, origin.y() + this->m_pointRadius);

		CBrush redBrush;
		redBrush.CreateSolidBrush(RGB(255, 0, 0));

		dc.SelectObject(&redBrush);

		this->DrawPolynomial(&dc);

		for(const auto& pt : this->m_points)
		{
			Point temp = this->ConvertToWindows(pt);
			dc.Ellipse(temp.x() - this->m_pointRadius, temp.y() - this->m_pointRadius, temp.x() + this->m_pointRadius, temp.y() + this->m_pointRadius);
		}

		dc.SelectObject(oldPen);
		dc.SelectObject(oldBrush);

		blackPen.DeleteObject();
		greenBrush.DeleteObject();
		redBrush.DeleteObject();

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCurvesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCurvesDlg::OnSize(UINT nType, int cx, int cy)
{
	Inherit::OnSize(nType, cx, cy);

	this->m_rectGraph.bottom = cy - this->m_margin;
	this->m_rectGraph.right = cx - this->m_margin;
	this->m_rectGraph.top = this->m_margin;
	this->m_rectGraph.left = this->m_margin;

	this->Invalidate();
	this->UpdateWindow();
}

void CCurvesDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	Inherit::OnLButtonDown(nFlags, point);

	if(this->m_points.size() == 4)
	{
		return;
	}

	Point pt = this->ConvertToCoordinate(Point(point.x, point.y));

	this->m_points.push_back(pt);

	this->Solve();

	this->Invalidate();
	this->UpdateWindow();
}

void CCurvesDlg::SetCoordinateRange(double left, double right, double bottom, double top)
{
	left *= m_zoom;
	right *= m_zoom;
	bottom *= m_zoom;
	top *= m_zoom;

	m_transform(0, 0) = 2.0 / (right - left);
	m_transform(0, 1) = 0.0;
	m_transform(0, 2) = -1.0 * ((right + left) / (right - left));
	m_transform(1, 0) = 0.0;
	m_transform(1, 1) = 2.0 / (top - bottom);
	m_transform(1, 2) = -1.0 * ((top + bottom) / (top - bottom));
	m_transform(2, 0) = 0.0;
	m_transform(2, 1) = 0.0;
	m_transform(2, 2) = 1.0;
}

auto CCurvesDlg::ConvertToCoordinate(const Point& ptWin) const -> Point
{
	Point3d pt;
	pt.x() = (ptWin.x() - m_rectGraph.left) / (double)m_rectGraph.Width() * 2.0 - 1.0;
	pt.y() = 1.0 - 2.0 * (ptWin.y() - m_rectGraph.top) / (double)m_rectGraph.Height();
	pt.z() = 1.0;

	Matrix3d mInv = this->m_transform.inverse();

	Point3d ptRet = mInv * pt;

	return Point(ptRet.x(), ptRet.y());
}

auto CCurvesDlg::ConvertToWindows(const Point& ptCoord) const -> Point
{
	Point3d ptTemp(ptCoord.x(), ptCoord.y(), 1);

	Point3d ret3d = this->m_transform * ptTemp;

	Point ret;
	ret.x() = (ret3d.x() * 0.5 + 0.5) * m_rectGraph.Width() + m_rectGraph.left;
	//ret.y() = (ret3d.y() * 0.5 + 0.5) * m_rectGraph.Height() + m_rectGraph.top;
	ret.y() = (m_rectGraph.Height() - (ret3d.y() * 0.5 + 0.5) * m_rectGraph.Height()) + m_rectGraph.top;

	return ret;
}

void CCurvesDlg::Solve()
{
	if(this->m_points.size() != 4)
	{
		return;
	}

	Eigen::Matrix4d mat;
	Eigen::Vector4d y;

	double a, b, c, d, v;
	this->Evaluate(m_points[0], a, b, c, d, v);
	mat(0, 0) = a; mat(0, 1) = b; mat(0, 2) = c; mat(0, 3) = d; y[0] = v;

	this->Evaluate(m_points[1], a, b, c, d, v);
	mat(1, 0) = a; mat(1, 1) = b; mat(1, 2) = c; mat(1, 3) = d; y[1] = v;

	this->Evaluate(m_points[2], a, b, c, d, v);
	mat(2, 0) = a; mat(2, 1) = b; mat(2, 2) = c; mat(2, 3) = d; y[2] = v;

	this->Evaluate(m_points[3], a, b, c, d, v);
	mat(3, 0) = a; mat(3, 1) = b; mat(3, 2) = c; mat(3, 3) = d; y[3] = v;

	Eigen::Vector4d coeffs = mat.inverse() * y;

	m_a = coeffs[0];
	m_b = coeffs[1];
	m_c = coeffs[2];
	m_d = coeffs[3];

	this->m_isSolved = true;
}

void CCurvesDlg::DrawPolynomial(CDC* dc)
{
	if(this->m_isSolved == false)
	{
		return;
	}

	CPen blackPen;
	blackPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	auto oldPen = dc->SelectObject(&blackPen);

	double dMin = -1.0 * m_zoom;
	double dMax = +1.0 * m_zoom;

	Point ptCoordPrev;
	ptCoordPrev.x() = dMin;
	ptCoordPrev.y() = m_a + m_b * -1.0 + m_c * -1.0 * -1.0 + m_d * -1.0 * -1.0 * -1.0;

	Point ptWinPrev = this->ConvertToWindows(ptCoordPrev);

	dc->MoveTo(ptWinPrev.x(), ptWinPrev.y());

	for(double d = dMin; d <= dMax; d += 0.01)
	{
		Point ptCoord(d, m_a + m_b * d + m_c * d * d + m_d * d * d * d);
		Point ptWin = this->ConvertToWindows(ptCoord);
		dc->LineTo(ptWin.x(), ptWin.y());
	}

	dc->SelectObject(oldPen);
	blackPen.DeleteObject();
}

void CCurvesDlg::Evaluate(const Point& pt, double& a, double& b, double& c, double&d, double& v)
{
	a = 1.0;
	b = pt.x();
	c = pt.x() * pt.x();
	d = pt.x() * pt.x() * pt.x();
	v = pt.y();
}

BOOL CCurvesDlg::OnMouseWheel(UINT nFlgs, short zDelta, CPoint pt)
{
	Inherit::OnMouseWheel(nFlgs, zDelta, pt);
	double f = zDelta > 0 ? 1 : -1;
	m_zoom *= (1 + f * 0.1);
	this->SetCoordinateRange(-1, 1, -1, 1);
	this->Invalidate();
	this->UpdateWindow();

	return TRUE;
}


