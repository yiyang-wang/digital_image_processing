#pragma once
#include "afxwin.h"


// CGreyDlg 对话框

class CGreyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGreyDlg)

public:
	CGreyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGreyDlg();

// 对话框数据
	enum { IDD = IDD_GREY_TRANSFORMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL OnInitDialog();
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	afx_msg void OnBnClickedOk();
};
