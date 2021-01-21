// ExpGrayTranDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "picture.h"
#include "ExpGrayTranDlg.h"
#include "afxdialogex.h"


// CExpGrayTranDlg 对话框

IMPLEMENT_DYNAMIC(CExpGrayTranDlg, CDialogEx)

CExpGrayTranDlg::CExpGrayTranDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExpGrayTranDlg::IDD, pParent)
	, m_a(2)
	, m_b(5)
	, m_c(1)
{

}

CExpGrayTranDlg::~CExpGrayTranDlg()
{
}

void CExpGrayTranDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_a);
	DDX_Text(pDX, IDC_EDIT2, m_b);
	DDX_Text(pDX, IDC_EDIT3, m_c);
}


BEGIN_MESSAGE_MAP(CExpGrayTranDlg, CDialogEx)
END_MESSAGE_MAP()


// CExpGrayTranDlg 消息处理程序
