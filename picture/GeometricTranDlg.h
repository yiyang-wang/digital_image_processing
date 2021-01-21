#pragma once


// CGeometricTranDlg 对话框

class CGeometricTranDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGeometricTranDlg)

public:
	CGeometricTranDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGeometricTranDlg();

// 对话框数据
	enum { IDD = IDD_GEOMETRIC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_a;
	double m_d;
	afx_msg void OnBnClickedOk();
	double m_p;
	double m_q;
	double m_angle;
	double m_x;
	double m_y;
	double a;
	double b;
	double c;
	double d;
	double p;
	double q;
	double e;
	double h;
	double s;
};
