// LogarithmDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "picture.h"
#include "LogarithmDlg.h"
#include "afxdialogex.h"


// CLogarithmDlg 对话框

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


// CLogarithmDlg 消息处理程序


void CLogarithmDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	CDialogEx::OnOK();
}
