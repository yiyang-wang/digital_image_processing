// MinThresholdDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "picture.h"
#include "MinThresholdDlg.h"
#include "afxdialogex.h"


// CMinThresholdDlg �Ի���

IMPLEMENT_DYNAMIC(CMinThresholdDlg, CDialogEx)

	CMinThresholdDlg::CMinThresholdDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMinThresholdDlg::IDD, pParent)
	, m_average(0)
	, m_variance(0)
	, m_display(0)
{

}

CMinThresholdDlg::~CMinThresholdDlg()
{
}

void CMinThresholdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_average);
	DDX_Text(pDX, IDC_EDIT2, m_variance);
	DDX_Text(pDX, IDC_EDIT3, m_display);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
}


BEGIN_MESSAGE_MAP(CMinThresholdDlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CMinThresholdDlg::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDOK, &CMinThresholdDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMinThresholdDlg ��Ϣ�������



void CMinThresholdDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);

	CDialogEx::OnOK();
}


BOOL CMinThresholdDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	//��������ʼ��
	m_slider.SetRange(0,255,FALSE);
	m_slider.SetTicFreq(1);

	/*******��OpenCV�еĴ�����ʾ��MFC��*******/
	namedWindow("aa", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND) cvGetWindowHandle("aa");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_HISTOGRAM)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	UpdateData( FALSE );//���½���ؼ�

	/*******��OpenCV�еĴ�����ʾ��MFC��*******/
	//��ʾֱ��ͼ
	cv::Mat m_outputImage;
	CRect rect;
	GetDlgItem(IDC_HISTOGRAM)->GetClientRect(&rect);
	cv::Rect outputImage(rect.left,rect.top,rect.right,rect.bottom);
	cv::resize(m_histogram,m_outputImage,cv::Size(rect.Width(),rect.Height())); 
	imshow("aa", m_outputImage);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CMinThresholdDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	int num;
	//��ȡѡȡ�ĻҶ�ֵ
	num = m_slider.GetPos();

	//�����ֵ�ͷ���
	int height = m_image.rows;  
	int width  = m_image.cols;  
	int step   = m_image.step;   
	uchar* data  = m_image.data;  
	float gSum0;//��һ��Ҷ���ֵ  
	float gSum1;//�ڶ���Ҷ���ֵ  
	float N0 = 0;//ǰ��������  
	float N1 = 0;//����������  
	float u0 = 0;//ǰ������ƽ���Ҷ�  
	float u1 = 0;//��������ƽ���Ҷ�  
	float w0 = 0;//ǰ�����ص���ռ����ͼ��ı���Ϊ��0  
	float w1 = 0;//�������ص���ռ����ͼ��ı���Ϊ��1  
	float u = 0;//��ƽ���Ҷ�   
	float g = 0;//��䷽��  
	int Histogram[256]={0};//�Ҷ�ֱ��ͼ  
	int N = width*height;//��������  
	for(int i=0;i<height;i++)  {//����ֱ��ͼ  
		for(int j=0;j<width;j++)  {  
			double temp =data[i*step + j * 3] * 0.114 + data[i*step + j * 3+1] * 0.587 + data[i*step + j * 3+2] * 0.299;  
			temp = temp<0? 0:temp;  
			temp = temp>255? 255:temp;  
			Histogram[(int)temp]++;  
		}   
	}  

	gSum0 = 0;  
	gSum1 = 0;   
	for (int j = 0;j<=num;j++)   { 
		N0 += Histogram[j]; //ǰ��������
		gSum0 += j*Histogram[j];  //��һ��Ҷ���ֵ
	}  
	u0 = gSum0/N0;  //ǰ������ƽ���Ҷ�

	for(int k = num+1;k<256;k++)  { 
		N1 = N-N0;
		gSum1 += k*Histogram[k];  
	}   
	u1 = gSum1/N1;

	w0 = N0/N; //ǰ�����ص���ռ����ͼ��ı���Ϊ��0 
	w1 = 1-w0;

	u = w0*u0 + w1*u1;  //��ƽ���Ҷ�  
	g = w0*w1*(u0-u1)*(u0-u1);  //��䷽��


	//�༭����ʾ�Ҷ�ֵ����ֵ������
	SetDlgItemInt(IDC_EDIT3,num,TRUE);
	SetDlgItemInt(IDC_EDIT1,u,TRUE);
	SetDlgItemInt(IDC_EDIT2,g,TRUE);

	Mat Image;
	Image = m_histogram.clone();

	for(int i = 0; i < Image.rows;i++){
		if(*(Image.data + i*Image.cols + num) ==255){
			*(Image.data + i*Image.cols + num) = 180;
		}
	}
	cv::Mat m_outputImage;
	CRect rect;
	GetDlgItem(IDC_HISTOGRAM)->GetClientRect(&rect);
	cv::Rect outputImage(rect.left,rect.top,rect.right,rect.bottom);
	cv::resize(Image,m_outputImage,cv::Size(rect.Width(),rect.Height())); 
	imshow("aa", m_outputImage);
}