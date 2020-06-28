#pragma once

#include <vector>
#include <Eigen/Core>

class CCurvesDlg : public CDialogEx
{
	using Inherit = CDialogEx;
	using Point = Eigen::Vector2d;
	using Points = std::vector<Point>;
	using Matrix3d = Eigen::Matrix3d;
	using Point3d = Eigen::Vector3d;
public:
	CCurvesDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CURVES_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlgs, short zDelta, CPoint pt);
	DECLARE_MESSAGE_MAP()

private:
	void SetCoordinateRange(double left, double right, double bottom, double top);
	Point ConvertToCoordinate(const Point& ptWin) const;
	Point ConvertToWindows(const Point& ptCoord) const;
	void DrawPolynomial(CDC* dc);
	void Solve();
	void Evaluate(const Point& pt, double& a, double& b, double& c, double&d, double& v);

private:
	const int m_margin = 10;
	const int m_pointRadius = 5;
	CRect m_rectGraph;
	Points m_points;

	Matrix3d m_transform;

	double m_a, m_b, m_c, m_d;
	bool m_isSolved = false;
	double m_zoom = 1.0;
};

