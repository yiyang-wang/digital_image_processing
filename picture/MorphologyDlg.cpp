// MorphologyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "picture.h"
#include "MorphologyDlg.h"
#include "afxdialogex.h"


// CMorphologyDlg 对话框

IMPLEMENT_DYNAMIC(CMorphologyDlg, CDialogEx)

CMorphologyDlg::CMorphologyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMorphologyDlg::IDD, pParent)
	, m1(0)
	, m2(0)
	, m3(0)
	, m4(0)
	, m5(0)
	, m6(0)
	, m7(1)
	, m8(1)
	, m9(1)
	, m10(0)
	, m11(0)
	, m12(1)
	, m13(1)
	, m14(1)
	, m15(0)
	, m16(0)
	, m17(1)
	, m18(1)
	, m19(1)
	, m20(0)
	, m21(0)
	, m22(0)
	, m23(0)
	, m24(0)
	, m25(0)
{

}

CMorphologyDlg::~CMorphologyDlg()
{
}

void CMorphologyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m1);
	DDX_Text(pDX, IDC_EDIT3, m2);
	DDX_Text(pDX, IDC_EDIT2, m3);
	DDX_Text(pDX, IDC_EDIT4, m4);
	DDX_Text(pDX, IDC_EDIT18, m5);
	DDX_Text(pDX, IDC_EDIT19, m6);
	DDX_Text(pDX, IDC_EDIT6, m7);
	DDX_Text(pDX, IDC_EDIT5, m8);
	DDX_Text(pDX, IDC_EDIT7, m9);
	DDX_Text(pDX, IDC_EDIT20, m10);
	DDX_Text(pDX, IDC_EDIT9, m11);
	DDX_Text(pDX, IDC_EDIT11, m12);
	DDX_Text(pDX, IDC_EDIT10, m13);
	DDX_Text(pDX, IDC_EDIT12, m14);
	DDX_Text(pDX, IDC_EDIT21, m15);
	DDX_Text(pDX, IDC_EDIT14, m16);
	DDX_Text(pDX, IDC_EDIT23, m17);
	DDX_Text(pDX, IDC_EDIT22, m18);
	DDX_Text(pDX, IDC_EDIT24, m19);
	DDX_Text(pDX, IDC_EDIT25, m20);
	DDX_Text(pDX, IDC_EDIT26, m21);
	DDX_Text(pDX, IDC_EDIT15, m22);
	DDX_Text(pDX, IDC_EDIT27, m23);
	DDX_Text(pDX, IDC_EDIT16, m24);
	DDX_Text(pDX, IDC_EDIT28, m25);
}


BEGIN_MESSAGE_MAP(CMorphologyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMorphologyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMorphologyDlg 消息处理程序


void CMorphologyDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	CDialogEx::OnOK();
}
