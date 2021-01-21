// GeometricTranDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "picture.h"
#include "GeometricTranDlg.h"
#include "afxdialogex.h"


// CGeometricTranDlg 对话框

IMPLEMENT_DYNAMIC(CGeometricTranDlg, CDialogEx)

CGeometricTranDlg::CGeometricTranDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGeometricTranDlg::IDD, pParent)
	, m_a(3)
	, m_d(2)
	, m_p(20)
	, m_q(30)
	, m_angle(30)
	, m_x(150)
	, m_y(100)
	, a(1)
	, b(0)
	, c(0)
	, d(1)
	, p(0)
	, q(0)
	, e(0)
	, h(0)
	, s(1)
{

}

CGeometricTranDlg::~CGeometricTranDlg()
{
}

void CGeometricTranDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_a);
	DDX_Text(pDX, IDC_EDIT2, m_d);
	DDX_Text(pDX, IDC_EDIT5, m_p);
	DDX_Text(pDX, IDC_EDIT6, m_q);
	DDX_Text(pDX, IDC_EDIT7, m_angle);
	DDX_Text(pDX, IDC_EDIT8, m_x);
	DDX_Text(pDX, IDC_EDIT9, m_y);
	DDX_Text(pDX, IDC_EDIT3, a);
	DDX_Text(pDX, IDC_EDIT10, b);
	DDX_Text(pDX, IDC_EDIT12, c);
	DDX_Text(pDX, IDC_EDIT13, d);
	DDX_Text(pDX, IDC_EDIT11, p);
	DDX_Text(pDX, IDC_EDIT14, q);
	DDX_Text(pDX, IDC_EDIT15, e);
	DDX_Text(pDX, IDC_EDIT16, h);
	DDX_Text(pDX, IDC_EDIT17, s);
}


BEGIN_MESSAGE_MAP(CGeometricTranDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGeometricTranDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGeometricTranDlg 消息处理程序


void CGeometricTranDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	CDialogEx::OnOK();
}
