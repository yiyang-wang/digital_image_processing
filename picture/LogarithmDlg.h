#pragma once


// CLogarithmDlg �Ի���

class CLogarithmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogarithmDlg)

public:
	CLogarithmDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogarithmDlg();

// �Ի�������
	enum { IDD = IDD_LOGARITHM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_a;
	int m_b;
	int m_c;
	afx_msg void OnBnClickedOk();
};
