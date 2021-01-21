// GreyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "picture.h"
#include "GreyDlg.h"
#include "afxdialogex.h"


// CGreyDlg �Ի���

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


// CGreyDlg ��Ϣ�������

//BOOL CGreyDlg::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
//	int cx, cy;  
//	CImage  image;  
//	CRect   rect;  
//
//	//����·������ͼƬ  
//	image.Load(_T("grey_line.bmp"));  
//	//��ȡͼƬ�Ŀ� �߶�  
//	cx  = image.GetWidth();  
//	cy  = image.GetHeight();  
//
//	//��ȡPicture Control�ؼ��Ĵ�С  
//	GetDlgItem(IDC_GREY_LINEAR)->GetWindowRect(&rect);  
//	//���ͻ���ѡ�е��ؼ���ʾ�ľ���������  
//	ScreenToClient(&rect);  
//	//�����ƶ����ؼ���ʾ������  
//	GetDlgItem(IDC_GREY_LINEAR)->MoveWindow(rect.left, rect.top, cx, cy, TRUE);  
//	CWnd *pWnd = NULL;  
//	pWnd    = GetDlgItem(IDC_GREY_LINEAR);//��ȡ�ؼ����  
//	pWnd->GetClientRect(&rect);//��ȡ���ָ��ؼ�����Ĵ�С  
//
//	CDC *pDc = NULL;  
//	pDc = pWnd->GetDC();//��ȡpicture��DC  
//
//	image.Draw(pDc->m_hDC, rect);//��ͼƬ���Ƶ�picture��ʾ��������  
//
//	//ReleaseDC(pDc);  
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//	// �쳣: OCX ����ҳӦ���� FALSE
//}


void CGreyDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);

	CDialogEx::OnOK();
}
