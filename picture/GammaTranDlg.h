#pragma once


// CGammaTranDlg �Ի���

class CGammaTranDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGammaTranDlg)

public:
	CGammaTranDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGammaTranDlg();

// �Ի�������
	enum { IDD = IDD_GAMMATRAN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_c;
	float m_y;
	afx_msg void OnBnClickedOk();
};
