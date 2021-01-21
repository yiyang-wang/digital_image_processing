#pragma once


// CGammaTranDlg 对话框

class CGammaTranDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGammaTranDlg)

public:
	CGammaTranDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGammaTranDlg();

// 对话框数据
	enum { IDD = IDD_GAMMATRAN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_c;
	float m_y;
	afx_msg void OnBnClickedOk();
};
