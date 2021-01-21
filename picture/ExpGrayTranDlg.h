#pragma once


// CExpGrayTranDlg 对话框

class CExpGrayTranDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExpGrayTranDlg)

public:
	CExpGrayTranDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExpGrayTranDlg();

// 对话框数据
	enum { IDD = IDD_EXPGRAYTRAN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_a;
	float m_b;
	float m_c;
};
