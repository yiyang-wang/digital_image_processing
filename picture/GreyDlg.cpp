// GreyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "picture.h"
#include "GreyDlg.h"
#include "afxdialogex.h"


// CGreyDlg 对话框

IMPLEMENT_DYNAMIC(CGreyDlg, CDialogEx)

CGreyDlg::CGreyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGreyDlg::IDD, pParent)
	, m_a(2)
	, m_b(255)
	, m_c(255)
	, m_d(0)
{

}

CGreyDlg::~CGreyDlg()
{
}

void CGreyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_GREY_EQUATION, m_ctrlPicture);
	//  DDX_Control(pDX, IDC_GREY_EQUATION, m_picture);
	DDX_Text(pDX, IDC_EDIT1, m_a);
	DDX_Text(pDX, IDC_EDIT2, m_b);
	DDX_Text(pDX, IDC_EDIT3, m_c);
	DDX_Text(pDX, IDC_EDIT4, m_d);
}


BEGIN_MESSAGE_MAP(CGreyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGreyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGreyDlg 消息处理程序

//BOOL CGreyDlg::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	// TODO:  在此添加额外的初始化
//	int cx, cy;  
//	CImage  image;  
//	CRect   rect;  
//
//	//根据路径载入图片  
//	image.Load(_T("grey_line.bmp"));  
//	//获取图片的宽 高度  
//	cx  = image.GetWidth();  
//	cy  = image.GetHeight();  
//
//	//获取Picture Control控件的大小  
//	GetDlgItem(IDC_GREY_LINEAR)->GetWindowRect(&rect);  
//	//将客户区选中到控件表示的矩形区域内  
//	ScreenToClient(&rect);  
//	//窗口移动到控件表示的区域  
//	GetDlgItem(IDC_GREY_LINEAR)->MoveWindow(rect.left, rect.top, cx, cy, TRUE);  
//	CWnd *pWnd = NULL;  
//	pWnd    = GetDlgItem(IDC_GREY_LINEAR);//获取控件句柄  
//	pWnd->GetClientRect(&rect);//获取句柄指向控件区域的大小  
//
//	CDC *pDc = NULL;  
//	pDc = pWnd->GetDC();//获取picture的DC  
//
//	image.Draw(pDc->m_hDC, rect);//将图片绘制到picture表示的区域内  
//
//	//ReleaseDC(pDc);  
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//	// 异常: OCX 属性页应返回 FALSE
//}


void CGreyDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	CDialogEx::OnOK();
}
