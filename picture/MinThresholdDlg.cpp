// MinThresholdDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "picture.h"
#include "MinThresholdDlg.h"
#include "afxdialogex.h"


// CMinThresholdDlg 对话框

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


// CMinThresholdDlg 消息处理程序



void CMinThresholdDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	CDialogEx::OnOK();
}


BOOL CMinThresholdDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// IDM_ABOUTBOX 必须在系统命令范围内。
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
	//滑动条初始化
	m_slider.SetRange(0,255,FALSE);
	m_slider.SetTicFreq(1);

	/*******将OpenCV中的窗口显示在MFC中*******/
	namedWindow("aa", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND) cvGetWindowHandle("aa");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_HISTOGRAM)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	UpdateData( FALSE );//更新界面控件

	/*******将OpenCV中的窗口显示在MFC中*******/
	//显示直方图
	cv::Mat m_outputImage;
	CRect rect;
	GetDlgItem(IDC_HISTOGRAM)->GetClientRect(&rect);
	cv::Rect outputImage(rect.left,rect.top,rect.right,rect.bottom);
	cv::resize(m_histogram,m_outputImage,cv::Size(rect.Width(),rect.Height())); 
	imshow("aa", m_outputImage);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CMinThresholdDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int num;
	//获取选取的灰度值
	num = m_slider.GetPos();

	//计算均值和方差
	int height = m_image.rows;  
	int width  = m_image.cols;  
	int step   = m_image.step;   
	uchar* data  = m_image.data;  
	float gSum0;//第一类灰度总值  
	float gSum1;//第二类灰度总值  
	float N0 = 0;//前景像素数  
	float N1 = 0;//背景像素数  
	float u0 = 0;//前景像素平均灰度  
	float u1 = 0;//背景像素平均灰度  
	float w0 = 0;//前景像素点数占整幅图像的比例为ω0  
	float w1 = 0;//背景像素点数占整幅图像的比例为ω1  
	float u = 0;//总平均灰度   
	float g = 0;//类间方差  
	int Histogram[256]={0};//灰度直方图  
	int N = width*height;//总像素数  
	for(int i=0;i<height;i++)  {//计算直方图  
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
		N0 += Histogram[j]; //前景像素数
		gSum0 += j*Histogram[j];  //第一类灰度总值
	}  
	u0 = gSum0/N0;  //前景像素平均灰度

	for(int k = num+1;k<256;k++)  { 
		N1 = N-N0;
		gSum1 += k*Histogram[k];  
	}   
	u1 = gSum1/N1;

	w0 = N0/N; //前景像素点数占整幅图像的比例为ω0 
	w1 = 1-w0;

	u = w0*u0 + w1*u1;  //总平均灰度  
	g = w0*w1*(u0-u1)*(u0-u1);  //类间方差


	//编辑框显示灰度值、均值、方差
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