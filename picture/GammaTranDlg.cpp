// GammaTranDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "picture.h"
#include "GammaTranDlg.h"
#include "afxdialogex.h"


// CGammaTranDlg �Ի���

IMPLEMENT_DYNAMIC(CGammaTranDlg, CDialogEx)

CGammaTranDlg::CGammaTranDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGammaTranDlg::IDD, pParent)
	, m_c(2)
	, m_y(2)
{

}

CGammaTranDlg::~CGammaTranDlg()
{
}

void CGammaTranDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_c);
	DDX_Text(pDX, IDC_EDIT2, m_y);
}


BEGIN_MESSAGE_MAP(CGammaTranDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGammaTranDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGammaTranDlg ��Ϣ�������


void CGammaTranDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);

	CDialogEx::OnOK();
}
