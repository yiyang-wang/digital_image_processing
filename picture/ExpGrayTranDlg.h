#pragma once


// CExpGrayTranDlg �Ի���

class CExpGrayTranDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExpGrayTranDlg)

public:
	CExpGrayTranDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExpGrayTranDlg();

// �Ի�������
	enum { IDD = IDD_EXPGRAYTRAN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_a;
	float m_b;
	float m_c;
};
