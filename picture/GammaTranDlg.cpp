// GammaTranDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "picture.h"
#include "GammaTranDlg.h"
#include "afxdialogex.h"


// CGammaTranDlg 对话框

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


// CGammaTranDlg 消息处理程序


void CGammaTranDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	CDialogEx::OnOK();
}
