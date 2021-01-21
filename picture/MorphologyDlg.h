#pragma once


// CMorphologyDlg 对话框

class CMorphologyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMorphologyDlg)

public:
	CMorphologyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMorphologyDlg();

// 对话框数据
	enum { IDD = IDD_MORPHOLOGY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m1;
	double m2;
	double m3;
	double m4;
	double m5;
	double m6;
	double m7;
	double m8;
	double m9;
	double m10;
	double m11;
	double m12;
	double m13;
	double m14;
	double m15;
	double m16;
	double m17;
	double m18;
	double m19;
	double m20;
	double m21;
	double m22;
	double m23;
	double m24;
	double m25;
	afx_msg void OnBnClickedOk();
};
