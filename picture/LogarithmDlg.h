#pragma once


// CLogarithmDlg 对话框

class CLogarithmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogarithmDlg)

public:
	CLogarithmDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogarithmDlg();

// 对话框数据
	enum { IDD = IDD_LOGARITHM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_a;
	int m_b;
	int m_c;
	afx_msg void OnBnClickedOk();
};
