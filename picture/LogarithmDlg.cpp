// LogarithmDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "picture.h"
#include "LogarithmDlg.h"
#include "afxdialogex.h"


// CLogarithmDlg �Ի���

IMPLEMENT_DYNAMIC(CLogarithmDlg, CDialogEx)

CLogarithmDlg::CLogarithmDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogarithmDlg::IDD, pParent)
	, m_a(150)
	, m_b(10)
	, m_c(1)
{

}

CLogarithmDlg::~CLogarithmDlg()
{
}

void CLogarithmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_a);
	DDX_Text(pDX, IDC_EDIT3, m_b);
	DDX_Text(pDX, IDC_EDIT2, m_c);
}


BEGIN_MESSAGE_MAP(CLogarithmDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLogarithmDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLogarithmDlg ��Ϣ�������


void CLogarithmDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);

	CDialogEx::OnOK();
}
