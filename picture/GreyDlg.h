#pragma once
#include "afxwin.h"


// CGreyDlg �Ի���

class CGreyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGreyDlg)

public:
	CGreyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGreyDlg();

// �Ի�������
	enum { IDD = IDD_GREY_TRANSFORMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL OnInitDialog();
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	afx_msg void OnBnClickedOk();
};
