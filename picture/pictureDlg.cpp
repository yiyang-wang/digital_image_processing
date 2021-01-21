
// pictureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "picture.h"
#include "pictureDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CpictureDlg 对话框




CpictureDlg::CpictureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CpictureDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	flag = false;
}

void CpictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, com_InputStyle);
	DDX_Control(pDX, IDC_COMCOLORCOV, com_ColorCov);
	DDX_Control(pDX, IDC_COMPICTRAVERSAL, com_PicTraversal);
	DDX_Control(pDX, IDC_GREY_TRANSFORMATION, com_GreyTransform);
	DDX_Control(pDX, IDC_IMAGE_SMOOTH, com_ImageSmooth);
	DDX_Control(pDX, IDC_GEOMETRIC_TRANS, com_GeometricTrans);
	DDX_Control(pDX, IDC_TWO_VALUE_MORPHOLOGY, com_TwoValue);
	DDX_Control(pDX, IDC_IMAGE_SEGMENTATION, com_ImageCut);
	DDX_Control(pDX, IDC_GRAY_VALUE_MORPHOLOGY, com_GrayValue);
	DDX_Control(pDX, IDC_GEOMETRIC_FEATURES, com_GeometricFeatures);
	DDX_Control(pDX, IDC_SHAPE_FEATURES, com_ShapeFeatures);
	DDX_Control(pDX, IDC_TEMPLATE_MATCHING, com_TemplateMatching);
}

BEGIN_MESSAGE_MAP(CpictureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CpictureDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCPIC, &CpictureDlg::OnBnChoosePicture)
	ON_BN_CLICKED(IDC_SAVE, &CpictureDlg::OnBnClickedSaveImage)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMCOLORCOV, &CpictureDlg::OnCbnSelchangeComcolorcov)
	ON_CBN_SELCHANGE(IDC_COMPICTRAVERSAL, &CpictureDlg::OnCbnSelComPicTraversal)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CpictureDlg::OnCbnSelInputStyle)
	ON_CBN_SELCHANGE(IDC_GREY_TRANSFORMATION, &CpictureDlg::OnCbnSelchangeGreyTransformation)
	ON_CBN_SELCHANGE(IDC_IMAGE_SMOOTH, &CpictureDlg::OnCbnSelchangeImageSmooth)
	ON_BN_CLICKED(IDC_RADIO_HISTOGRAM, &CpictureDlg::OnBnClickedRadioHistogram)
	ON_BN_CLICKED(IDC_RADIO_ORIGIN, &CpictureDlg::OnBnClickedRadioOrigin)
	ON_CBN_SELCHANGE(IDC_GEOMETRIC_TRANS, &CpictureDlg::OnCbnSelchangeGeometricTrans)
	ON_CBN_SELCHANGE(IDC_TWO_VALUE_MORPHOLOGY, &CpictureDlg::OnCbnSelchangeTwoValueMorphology)
	ON_CBN_SELCHANGE(IDC_IMAGE_SEGMENTATION, &CpictureDlg::OnCbnSelchangeImageSegmentation)
	ON_CBN_SELCHANGE(IDC_GRAY_VALUE_MORPHOLOGY, &CpictureDlg::OnCbnSelchangeGrayValueMorphology)
	ON_CBN_SELCHANGE(IDC_GEOMETRIC_FEATURES, &CpictureDlg::OnCbnSelchangeGeometricFeatures)
	ON_CBN_SELCHANGE(IDC_TEMPLATE_MATCHING, &CpictureDlg::OnCbnSelchangeTemplateMatching)
	ON_CBN_SELCHANGE(IDC_SHAPE_FEATURES, &CpictureDlg::OnCbnSelchangeShapeFeatures)
END_MESSAGE_MAP()


// CpictureDlg 消息处理程序

BOOL CpictureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	/*******在组合框中添加视频数据读入方法的字符串*******/
	com_InputStyle.AddString(_T("读入本地视频"));
	com_InputStyle.AddString(_T("读入图像"));
	com_InputStyle.AddString(_T("摄像头输入"));
	com_InputStyle.AddString(_T("读入灰度图像"));
	com_InputStyle.SetCurSel(1);
	inputType=emPICTURES_IN;
	/*******在组合框中添加视频数据读入方法的字符串*******/

	/*******在组合框中添加色彩转换方式的字符串*******/
	com_ColorCov.AddString(_T("RGB转换为灰度值"));
	com_ColorCov.AddString(_T("RGB转换为LAB"));
	com_ColorCov.AddString(_T("RGB转换为YCrCb"));
	com_ColorCov.AddString(_T("RGB转换为XYZ"));
	com_ColorCov.AddString(_T("RGB转换为HSV"));
	//com_ColorCov.SetCurSel(0);
	/*******在组合框中添加色彩转换方式的字符串*******/

	/*******在组合框中添加遍历方式的字符串*******/
	com_PicTraversal.AddString(_T("at方法遍历减少色阶"));
	com_PicTraversal.AddString(_T("迭代器方式遍历减少色阶"));
	com_PicTraversal.AddString(_T("指针方式遍历减少色阶"));
	//com_ColorCov.SetCurSel(0);
	/*******在组合框中添加遍历方式的字符串*******/

	/*******在组合框中添加灰度变换方式的字符串*******/
	com_GreyTransform.AddString(_T("灰度线性变换"));
	com_GreyTransform.AddString(_T("对数变换"));
	com_GreyTransform.AddString(_T("指数变换"));
	com_GreyTransform.AddString(_T("幂律变换"));
	com_GreyTransform.AddString(_T("直方图均衡化"));
	/*******在组合框中添加灰度变换方式的字符串*******/

	com_ImageSmooth.AddString(_T("椒盐噪声"));
	com_ImageSmooth.AddString(_T("领域平均"));
	com_ImageSmooth.AddString(_T("中值滤波"));

	com_GeometricTrans.AddString(_T("图像比例缩放"));
	com_GeometricTrans.AddString(_T("图像平移"));
	com_GeometricTrans.AddString(_T("图像镜像"));
	com_GeometricTrans.AddString(_T("图像旋转"));
	com_GeometricTrans.AddString(_T("图像复合变换"));

	com_TwoValue.AddString(_T("腐蚀"));
	com_TwoValue.AddString(_T("膨胀"));
	com_TwoValue.AddString(_T("开运算"));
	com_TwoValue.AddString(_T("闭运算"));
	com_TwoValue.AddString(_T("骨架提取"));

	com_GrayValue.AddString(_T("灰值腐蚀"));
	com_GrayValue.AddString(_T("灰值膨胀"));
	com_GrayValue.AddString(_T("灰值闭运算"));
	com_GrayValue.AddString(_T("灰值开运算"));

	com_ImageCut.AddString(_T("交互式阈值法"));
	com_ImageCut.AddString(_T("大津阈值法"));
	com_ImageCut.AddString(_T("霍夫变换直线检测"));
	com_ImageCut.AddString(_T("连通域识别"));
	com_ImageCut.AddString(_T("边缘检测"));

	//com_GeometricFeatures.AddString(_T("二值图像连通域识别"));
	//com_GeometricFeatures.AddString(_T("连通域边界"));
	com_GeometricFeatures.AddString(_T("连通域质心"));
	com_GeometricFeatures.AddString(_T("连通域面积"));
	com_GeometricFeatures.AddString(_T("连通域周长"));

	com_ShapeFeatures.AddString(_T("矩形度"));
	com_ShapeFeatures.AddString(_T("圆形度"));

	com_TemplateMatching.AddString(_T("模板匹配"));
	com_TemplateMatching.AddString(_T("最小外接矩形"));

	/*******将OpenCV中的窗口显示在MFC中*******/
	namedWindow("emVIEWBEF", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND) cvGetWindowHandle("emVIEWBEF");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_STATIC_PICTURE)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	namedWindow("emVIEWAFT", WINDOW_AUTOSIZE);
	HWND hWnd2 = (HWND) cvGetWindowHandle("emVIEWAFT");
	HWND hParent2 = ::GetParent(hWnd2);
	::SetParent(hWnd2, GetDlgItem(IDC_STATIC_MEDIA)->m_hWnd);
	::ShowWindow(hParent2, SW_HIDE);
	UpdateData( FALSE );//更新界面控件
	/*******将OpenCV中的窗口显示在MFC中*******/

	//workDir = F_InitWorkDir();//判断Imgs及SaveFrame文件夹是否存在，不存在创建(ww)

	// 初始化图像显示控件的图像
	CRect rect;
	GetDlgItem(IDC_STATIC_PICTURE) ->GetClientRect( &rect );
	image_in = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);
	GetDlgItem(IDC_STATIC_MEDIA) ->GetClientRect( &rect );
	image_out = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);

	((CButton *)GetDlgItem(IDC_RADIO_ORIGIN))->SetCheck(TRUE);//原图像默认选上  
	((CButton *)GetDlgItem(IDC_RADIO_HISTOGRAM))->SetCheck(FALSE);//直方图默认不选上  

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CpictureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CpictureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CpictureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//////////////////////////////////////////////////////////////////////////
/*----------------------------------
* 功能 :	初始化（创建）程序运行所需的文件夹
*----------------------------------
* 函数 :	CDigImagProcDlg::F_InitWorkDir
* 访问 :	private 
* 返回 :	创立三个文件夹，原始图像文件夹，处理后图像文件夹及视频文件夹
*/
//CString CpictureDlg::F_InitWorkDir()
//{
//	CStringA strPath;
// 	TCHAR path[_MAX_PATH];
//	TCHAR drive[_MAX_DRIVE];
//	TCHAR dir[_MAX_DIR];
//	TCHAR fname[_MAX_FNAME];
//	TCHAR ext[_MAX_EXT];
//	::GetModuleFileName(AfxGetApp()->m_hInstance, path, _MAX_PATH);
//	_tsplitpath(path, drive, dir, fname, ext);
//
//	strPath.Empty();
//	strPath += CString(drive);
//	strPath += CString(dir); 
//
//    string saveDir = strPath;
//    saveDir += "/Imgs";
//    F_CheckDir(saveDir, true);
//	saveDir = strPath;
//	saveDir += "/Videos";
//	F_CheckDir(saveDir, true);
//	saveDir = strPath;
//    saveDir += "/SaveFrame";
//    F_CheckDir(saveDir, true);
//
//	return CString(strPath);
//}

void CpictureDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	StopCam();//停止相机工作
	CDialogEx::OnOK();
}


/*----------------------------
* 功能 :根据用户选择的方式显示图像或视频(ww)
*----------------------------
* 函数 : CDigImagProcDlg::OnBnChoosePicture
* 访问 : private 
* 返回 : void
*
*/
void CpictureDlg::OnBnChoosePicture()
{
	// TODO: 在此添加控件通知处理程序代码
	// 根据选择不同，分别做摄像头输入，视频输入，本地图像组输入背景建模处理-ww16/5/4
	if (inputType==emPICTURES_IN)//(1)如选择图像输入
	{
		StopCam();//停止相机工作
		string frmPath;
		frmPath = DoSelectFiles(
			_T("*.bmp"), 
			OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
			_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
			_T("选择图像序列"),
			workDir+"\Imgs");
		image_in=cv::imread(frmPath);//读取图像
		F_ShowImage(emVIEWBEF,image_in);
	}
	else if(inputType==emCAMERA_IN)//(2)如选择视频输入
	{
		//摄像头输入，设置摄像头显示分辨率ww-6-14
		nImageWidth = 640;
		nImageHeight = 480;
		//打开第一个摄像头
		if ( !cap_VidCam.open(1) )
		{
			AfxMessageBox(_T("打开摄像头失败！"));
			return;
		}
		cap_VidCam.set(CV_CAP_PROP_FRAME_WIDTH,  nImageWidth); //cv设置视频流的帧宽度（只对摄像头有效）
		cap_VidCam.set(CV_CAP_PROP_FRAME_HEIGHT, nImageHeight);//cv设置视频流的帧高度（只对摄像头有效）
		// 启动摄像头后显示实时画面
		SetTimer(1, 10, NULL);	// 10ms 定时显示
	}
	else if(inputType == ememVIDEO_IN)//(3)如选择视频输入
	{
		CStringA videoFiles;//存储文件的名字
		StopCam();//停止相机工作
		videoFiles = DoSelectFiles(
			_T("*.avi"), 
			OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
			_T("video files (*.avi) |*.avi| All Files (*.*) |*.*||"),
			_T("选择视频文件"),
			workDir+"\Videos");
		cap_VidCam.open(LPCSTR(videoFiles));//打开文件
		SetTimer(1, 10, NULL);	// 10ms 定时显示

	}
	else//(1)如选择灰度图像输入
	{
		StopCam();//停止相机工作
		string frmPath;
		frmPath = DoSelectFiles(
			_T("*.bmp"), 
			OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
			_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
			_T("选择图像序列"),
			workDir+"\Imgs");
		image_in=cv::imread(frmPath,0);//读取灰度图像
		F_ShowImage(emVIEWBEF,image_in);
	}
	//DoShowOrigFrame();
	return;
}


/*----------------------------
* 功能 : 关闭摄像头
*----------------------------
* 函数 : CDigImagProcDlg::StopCam
* 访问 : private 
* 返回 : void
*
*/
void CpictureDlg::StopCam()
{
	// TODO: Add your control notification handler code here
	if (cap_VidCam.isOpened())
	{
		KillTimer(1);//该函数移除先前用SetTimer设置的定时器,在定时器使用完毕后移除定时器时使用

		// 对图像数据清零
		image_in = Scalar(0);
		//F_ShowImage( frame, IDC_PicLfCam );
		cap_VidCam.release();//释放VideoCapture对象


	}
	return;
}

/*----------------------------
* 功能 : 弹出打开文件对话框，选择单个文件，
并可以限制文件类型
*----------------------------
* 函数 : CDigImagProcDlg::DoSelectFiles
* 访问 : private 
* 返回 : selectedFiles	选择的文件的路径序列
*
* 参数 : lpszDefExt			[in]	文件默认格式
* 参数 : dwFlags			[in]	对话框选项
* 参数 : lpszFilter			[in]	文件格式过滤条件
* 参数 : lpstrTitle			[in]	对话框标题
* 参数 : lpstrInitialDir	[in]	对话框的初始路径
*/
CStringA CpictureDlg::DoSelectFiles(
	LPCTSTR	lpszDefExt,
	DWORD	dwFlags,
	LPCTSTR	lpszFilter,
	LPCSTR	lpstrTitle,
	LPCSTR	lpstrInitialDir )
{
	CStringA selectedFile;
	POSITION filePosition;

	CFileDialog dlg( TRUE, lpszDefExt, NULL, dwFlags, lpszFilter, NULL );	
	dlg.m_ofn.lpstrFile[0] = NULL; 
	dlg.m_ofn.lpstrTitle = lpstrTitle;
	dlg.m_ofn.lpstrInitialDir = lpstrInitialDir;

	if( dlg.DoModal() == IDOK )
	{
		selectedFile = dlg.GetPathName();
		flag = true;
	}

	else {
		selectedFile = "demo.jpg";
		AfxMessageBox("请重新选择文件！（即将显示默认图片）");
	}

	return selectedFile;
}

//////////////////////////////////////////////////////////////////////////
/*----------------------------------
* 功能 : 检查文件夹是否存在
*----------------------------------
* 函数 : CStereoVisionDlg::CheckDir
* 访问 : private 
* 返回 : 1 - 文件夹存在；0 - 不存在
*
* 参数 : dir		[in]	文件夹路径
* 参数 : creatDir	[in]	是否创建文件夹
*/
bool CpictureDlg::F_CheckDir(const string dir, bool creatDir /* = false */)
{
	bool RetVal = false;

	string fileName = dir;
	fileName += "\\*";

	_finddata_t FileInfo;
	long Handle = _findfirst(fileName.c_str(), &FileInfo);	

	if (Handle == -1L)
	{
		if (creatDir)
		{
			if(_mkdir(dir.c_str())==0)
			{
				RetVal = true;
			}
		}
	}
	else
	{
		RetVal = true;
		_findclose(Handle);
	}

	return RetVal;
}

/*----------------------------
* 功能 : 显示图像
*		 将要绘制的图像 src 复制到 des，然后绘制到控件号为 ID 的 Picture 控件
*----------------------------
* 函数 : CDigImagProcDlg::F_ShowImage
* 访问 : private 
* 返回 : void
*
* 参数 : src	[in]	待显示图像
* 参数 : des	[in]	窗口图像
* 参数 : ID		[in]	图像窗口控件ID
*/
void CpictureDlg::F_ShowImage(int type,Mat& src)
{
	cv::Mat m_dst;
	CRect rect;
	GetDlgItem(IDC_STATIC_PICTURE)->GetClientRect(&rect);
	cv::Rect dst(rect.left,rect.top,rect.right,rect.bottom);
	cv::resize(src,m_dst,cv::Size(rect.Width(),rect.Height())); 
	if (type==emVIEWBEF)
	{
		imshow("emVIEWBEF", m_dst);
	}
	else
	{
		imshow("emVIEWAFT", m_dst);
	}
}

/*----------------------------
* 功能 : 计算传入图像直方图，若是彩色图像，计算各颜色分量直方图并返回
*----------------------------
* 函数 : CDigImagProcDlg::CreatHistogram
* 访问 : public 
* 返回 : vector<Mat>
*
* 参数 : Mat& m_srcImg	待求取直方图图像

*/
vector<Mat> CpictureDlg::CreatHistogram(Mat& m_srcImg)
{
	/**
	void calcHist(const Mat* images, int nimages, const int* channels,
	InputArray mask, OutputArray	hist,
	int dims, const int* histSize, const float** ranges,
	bool uniform=true, bool accumulate=false )
	* images - 源图像数组
	* nimages - 源图像数目
	* channels - 用于计算直方图的通道列表（从0开始编号）
	* mask - 掩模图像（与非0元素对应的图像像素将用于计算直方图）
	* hist - 直方图（dims维矩阵）
	* dims - 直方图的维数（最大值为CV_MAX_DIMS，目前为32）
	* histSize - 直方图各维的大小（箱格数）
	* ranges - 直方图各维的箱格的数值范围（若箱格均匀分布，则每维只需两个值）
	* uniform - 直方图箱格是否均匀分布的标志
	* accumulate - 是否累加以前的直方图
	*/

	//申请初始化变量
	vector<Mat> grayBGRImg;//直方图向量组,灰度，蓝绿红分量
	Mat bHist, gHist, rHist, grayHist;	// 直方图数据
	int histSize = 256;					// 直方图的箱格数，及直方图横坐标取值大小，一般0至255
	float range[] = {0, 255};
	const float* histRange = {range};	// 直方图各维的箱格的数值范围

	if (m_srcImg.channels()==1)//若是灰度图像
	{
		calcHist(&m_srcImg, 1, 0, Mat(), grayHist, 1, &histSize, &histRange, true, false);// 亮度直方图
		grayBGRImg.push_back(grayHist);

	} 
	else if(m_srcImg.channels()==3)
	{
		/// 转换为灰度图像
		Mat grayImg;
		cvtColor(m_srcImg, grayImg, CV_BGR2GRAY);
		calcHist(&m_srcImg, 1, 0, Mat(), grayHist, 1, &histSize, &histRange, true, false);// 亮度直方图
		// 也可用下面的语句计算红、绿、蓝通道的直方图，无需分离通道
		const int channels[] = {0, 1, 2}; // 依次为蓝、绿、红的颜色通道索引
		calcHist(&m_srcImg, 1, &channels[0], Mat(), bHist, 1, &histSize, &histRange, true, false);	// 蓝色通道直方图
		calcHist(&m_srcImg, 1, &channels[1], Mat(), gHist, 1, &histSize, &histRange, true, false);	// 绿色通道直方图
		calcHist(&m_srcImg, 1, &channels[2], Mat(), rHist, 1, &histSize, &histRange, true, false);	// 红色通道直方图
		//各直方图一维矩阵入栈
		grayBGRImg.push_back(grayHist);
		grayBGRImg.push_back(bHist);
		grayBGRImg.push_back(gHist);
		grayBGRImg.push_back(rHist);
	}
	else{}
	return grayBGRImg;

}


/*----------------------------
* 功能 : 保存当前处理过的image_out图像
*----------------------------
* 函数 : CStereoVisionDlg::OnBnClickedSaveImage
* 访问 : private 
* 返回 : void
*
*/
void CpictureDlg::OnBnClickedSaveImage()
{
	// TODO: 在此添加控件通知处理程序代码
	//定义可以保存的图像类型后缀名
	CString csBMP="BMP Files(*.BMP)|*.BMP|";
	CString csJPG="JPG Files(*.JPG)|*.JPG|";
	CString csTIF="TIF Files(*.TIF)|*.TIF|";
	CString csPNG="PNG Files(*.PNG)|*.PNG|";
	CString csDIB="DIB Files(*.DIB)|*.DIB|";
	CString csPBM="PBM Files(*.PBM)|*.PBM|";
	CString csPGM="PGM Files(*.PGM)|*.PGM|";
	CString csPPM="PPM Files(*.PPM)|*.PPM|";
	CString csSR ="SR  Files(*.SR) |*.SR|";
	CString csRAS="RAS Files(*.RAS)|*.RAS||";

	CString csFilter=csBMP+csJPG+csTIF+csPNG+csDIB
		+csPBM+csPGM+csPPM+csSR+csRAS;

	CString name[]={"","bmp","jpg","tif","png","dib",
		"pbm","pgm","ppm","sr", "ras",""};

	CString strFileName;
	CString strExtension;

	CString defaultDir =  workDir+"\SaveFrame";   //默认打开的文件路径  
	CString fileName = "new.bmp";         //默认保存的文件名 

	CFileDialog openFileDlg(false,".bmp", fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, csFilter, NULL);
	openFileDlg.m_ofn.lpstrInitialDir=defaultDir;//初始化路径
	//  文件存盘对话框
	if (openFileDlg.DoModal()==IDOK ) //  输入了文件名
	{        
		strFileName = openFileDlg.m_ofn.lpstrFile;
		if (openFileDlg.m_ofn.nFileExtension == 0) //  无文件后缀
		{  
			strExtension = name[openFileDlg.m_ofn.nFilterIndex];
			strFileName = strFileName + '.' + strExtension;
			//  加文件后缀
		}

		string s(strFileName.GetBuffer());
		imwrite(s,image_out);   //  当前画面存盘  
	}
}


void CpictureDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (cap_VidCam.isOpened())//如果摄像头或者视频打开
	{
		cap_VidCam >> image_in;//输出每一帧

		//在第picture控件上面显示每一帧图像
		F_ShowImage(emVIEWBEF,image_in);

	}

	CDialogEx::OnTimer(nIDEvent);
}


/*----------------------------
* 功能 : 选择色彩转换方式,并进行转换(ww)
*----------------------------
* 函数 : CDigImagProcDlg::OnCbnSelchangeComcolorcov
* 访问 : private 
* 返回 : void
*
*/
void CpictureDlg::OnCbnSelchangeComcolorcov()
{
	// TODO: 在此添加控件通知处理程序代码
	if(flag) {
		image_out=obj_ImagBase.covertColor(image_in,com_ColorCov.GetCurSel());
		//在第2个picture颜色转换后的图像
		F_ShowImage(emVIEWAFT,image_out);
	}
}



/*----------------------------
* 功能 : 根据不同选择遍历图像，减少色阶(ww)
*----------------------------
* 函数 : CDigImagProcDlg::OnCbnSelComPicTraversal
* 访问 : private 
* 返回 : void
*
*/
void CpictureDlg::OnCbnSelComPicTraversal()
{
	if(flag) {
		// 对图像数据清零
		image_out = Scalar(0);
		F_ShowImage(emVIEWAFT,image_out);

		double duration;
		duration = static_cast<double>(cv::getTickCount());//开始记时

		obj_ImagBase.colorReduce(image_in,image_out,64,com_PicTraversal.GetCurSel());

		duration = static_cast<double>(cv::getTickCount())-duration;
		duration /= cv::getTickFrequency(); // the elapsed time in m

		//显示遍历时间
		CString str;
		char buffer[20];
		sprintf_s(buffer,"%f",duration);
		str = buffer;

		CString words= "The picture traversal time is: " + str + " 秒";  
		AfxMessageBox(words);

		//putText(image_out, words, Point(image_out.cols/2,image_out.rows/2),CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0), 3);  

		//在第2个picture显示色阶减少后的图像，并显示遍历时间
		F_ShowImage(emVIEWAFT,image_out);
	}
}


/*----------------------------
* 功能 : 视频图像摄像头输入选择响应(ww)
*----------------------------
* 函数 : CDigImagProcDlg::OnCbnSelInputStyle
* 访问 : private 
* 返回 : void
*
*/
void CpictureDlg::OnCbnSelInputStyle()
{
	// TODO: 在此添加控件通知处理程序代码
	inputType = com_InputStyle.GetCurSel();
	return;
}


void CpictureDlg::OnCbnSelchangeGreyTransformation() //灰度变换
{
	// TODO: 在此添加控件通知处理程序代码
	if(com_GreyTransform.GetCurSel() == 1) {//灰度线性变换
		CGreyDlg dlg;
		dlg.DoModal();
		grey_Tran.GreyLineTran(image_in, image_out, dlg.m_a, dlg.m_b, dlg.m_c, dlg.m_d);
		F_ShowImage(emVIEWAFT,image_out);
	}

	else if(com_GreyTransform.GetCurSel() == 0) {//对数变换
		image_out = Scalar(0);

		CLogarithmDlg dlg;
		dlg.DoModal();
		grey_Tran.LogarithmTran(image_in, image_out, dlg.m_a, dlg.m_b, dlg.m_c);

		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GreyTransform.GetCurSel() == 2) {//灰度幂律变换
		image_out = Scalar(0);

		CGammaTranDlg dlg;
		dlg.DoModal();

		grey_Tran.MyGammaCorrection(image_in, image_out, dlg.m_c, dlg.m_y);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GreyTransform.GetCurSel() == 3) {//直方图均衡化
		image_out = Scalar(0);
		image_out = grey_Tran.EqualizeHist(image_in);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GreyTransform.GetCurSel() == 4) {//灰度指数变换
		image_out = Scalar(0);

		CExpGrayTranDlg dlg;
		dlg.DoModal();

		grey_Tran.ExpGrayTransform(image_in, image_out, dlg.m_a, dlg.m_b, dlg.m_c);
		F_ShowImage(emVIEWAFT,image_out);
	}
}


void CpictureDlg::OnCbnSelchangeImageSmooth()
{
	// TODO: 在此添加控件通知处理程序代码
	if(com_ImageSmooth.GetCurSel() == 0) {//椒盐噪声
		image_out = image_in;
		grey_Tran.salt(image_out, 300000);
		F_ShowImage(emVIEWAFT,image_out);
	}

	else if(com_ImageSmooth.GetCurSel() == 1) { 
		grey_Tran.AverFiltering(image_in, image_out);//邻域平均

		F_ShowImage(emVIEWAFT,image_out);
	}

	else if(com_ImageSmooth.GetCurSel() == 2) {//中值滤波
		grey_Tran.MedianFlitering(image_in, image_out);

		F_ShowImage(emVIEWAFT,image_out);
	}
}


void CpictureDlg::OnBnClickedRadioHistogram()//显示直方图
{
	// TODO: 在此添加控件通知处理程序代码
	Mat temp;
	image_out = grey_Tran.EqualizeHist(image_in);
	image_out = grey_Tran.img_Hist(image_out);
	temp = grey_Tran.img_Hist(image_in);
	F_ShowImage(emVIEWBEF,temp);
	F_ShowImage(emVIEWAFT,image_out);
}


void CpictureDlg::OnBnClickedRadioOrigin()//显示原图像
{
	// TODO: 在此添加控件通知处理程序代码
	image_out = grey_Tran.EqualizeHist(image_in);
	F_ShowImage(emVIEWBEF,image_in);
	F_ShowImage(emVIEWAFT,image_out);
}


//几何变换
void CpictureDlg::OnCbnSelchangeGeometricTrans()
{
	// TODO: 在此添加控件通知处理程序代码

	if(com_GeometricTrans.GetCurSel() == 0) {//图像缩放
		image_out = Scalar(0);
		CGeometricTranDlg dlg;
		dlg.DoModal();

		geometry_Trans.scaleIntervalSampling(image_in, image_out, dlg.m_a, dlg.m_d);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GeometricTrans.GetCurSel() == 1) {//图像平移
		CGeometricTranDlg dlg;
		dlg.DoModal();

		geometry_Trans.imgTranslate(image_in,image_out,dlg.m_p,dlg.m_q);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GeometricTrans.GetCurSel() == 2) {//水平镜像
		image_out = geometry_Trans.mirrorTranslate(image_in);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GeometricTrans.GetCurSel() == 3) {//图像旋转
		image_out = Scalar(0);

		CGeometricTranDlg dlg;
		dlg.DoModal();

		//image_out = geometry_Trans.imgTranslate(image_in,dlg.m_x,dlg.m_y);//图像平移
		//geometry_Trans.warpFfine (image_out,image_out, dlg.m_angle);//图像旋转
		geometry_Trans.warpFfine(image_in, image_out, dlg.m_x, dlg.m_y, dlg.m_angle);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GeometricTrans.GetCurSel() == 4) {//图形复合变换
		image_out = Scalar(0);

		CGeometricTranDlg dlg;
		dlg.DoModal();

		geometry_Trans.compositeTransformation(image_in, image_out, dlg.a, dlg.b, dlg.p,
			dlg.c, dlg.d, dlg.q, dlg.e, dlg.h, dlg.s);
		F_ShowImage(emVIEWAFT,image_out);
	}
}


//二值形态学
void CpictureDlg::OnCbnSelchangeTwoValueMorphology()
{
	// TODO: 在此添加控件通知处理程序代码
	if(com_TwoValue.GetCurSel() == 0) {	//腐蚀
		//erode(image_in, image_out, Mat(5,5,CV_8U), Point(-1,-1),2);
		CMorphologyDlg dlg;
		dlg.DoModal();

		int a[5][5] = {dlg.m1, dlg.m2, dlg.m3, dlg.m4, dlg.m5,
			dlg.m6, dlg.m7, dlg.m8, dlg.m9, dlg.m10,
			dlg.m11, dlg.m12, dlg.m13, dlg.m14, dlg.m15,
			dlg.m16, dlg.m17, dlg.m18, dlg.m19, dlg.m20,
			dlg.m21, dlg.m22, dlg.m23, dlg.m24, dlg.m25};

		obj_Morphology.twoValueErode(image_in, image_out, a);

		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_TwoValue.GetCurSel() == 1) {	//膨胀
		//dilate(image_in, image_out, Mat(5,5,CV_8U), Point(-1,-1),2);
		CMorphologyDlg dlg;
		dlg.DoModal();

		int a[5][5] = {dlg.m1, dlg.m2, dlg.m3, dlg.m4, dlg.m5,
			dlg.m6, dlg.m7, dlg.m8, dlg.m9, dlg.m10,
			dlg.m11, dlg.m12, dlg.m13, dlg.m14, dlg.m15,
			dlg.m16, dlg.m17, dlg.m18, dlg.m19, dlg.m20,
			dlg.m21, dlg.m22, dlg.m23, dlg.m24, dlg.m25};

		obj_Morphology.twoValueDilate(image_in, image_out, a);

		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_TwoValue.GetCurSel() == 2) {//开运算
		CMorphologyDlg dlg;
		dlg.DoModal();

		int a[5][5] = {dlg.m1, dlg.m2, dlg.m3, dlg.m4, dlg.m5,
			dlg.m6, dlg.m7, dlg.m8, dlg.m9, dlg.m10,
			dlg.m11, dlg.m12, dlg.m13, dlg.m14, dlg.m15,
			dlg.m16, dlg.m17, dlg.m18, dlg.m19, dlg.m20,
			dlg.m21, dlg.m22, dlg.m23, dlg.m24, dlg.m25};

		obj_Morphology.twoValueOpenOperation(image_in, image_out, a);

		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_TwoValue.GetCurSel() == 3) {//闭运算
		CMorphologyDlg dlg;
		dlg.DoModal();

		int a[5][5] = {dlg.m1, dlg.m2, dlg.m3, dlg.m4, dlg.m5,
			dlg.m6, dlg.m7, dlg.m8, dlg.m9, dlg.m10,
			dlg.m11, dlg.m12, dlg.m13, dlg.m14, dlg.m15,
			dlg.m16, dlg.m17, dlg.m18, dlg.m19, dlg.m20,
			dlg.m21, dlg.m22, dlg.m23, dlg.m24, dlg.m25};

		obj_Morphology.twoValueCloseOperation(image_in, image_out, a);

		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_TwoValue.GetCurSel() == 4) {//骨架提取
		Mat mid (image_in.size(), CV_8U);
		cvtColor(image_in, mid, CV_BGR2GRAY );

		//如果细化目标为黑色区域，则反转图像
		mid = 255 - mid;
		//二值化处理
		threshold(mid,image_out, 100, 255, THRESH_BINARY);
		obj_Morphology.thinning(image_out, image_out);

		F_ShowImage(emVIEWAFT,image_out);
	}
}


//灰值形态学
void CpictureDlg::OnCbnSelchangeGrayValueMorphology()
{
	// TODO: 在此添加控件通知处理程序代码
	if(com_GrayValue.GetCurSel() == 0) {//灰值腐蚀
		CMorphologyDlg dlg;
		dlg.DoModal();

		int a[5][5] = {dlg.m1, dlg.m2, dlg.m3, dlg.m4, dlg.m5,
			dlg.m6, dlg.m7, dlg.m8, dlg.m9, dlg.m10,
			dlg.m11, dlg.m12, dlg.m13, dlg.m14, dlg.m15,
			dlg.m16, dlg.m17, dlg.m18, dlg.m19, dlg.m20,
			dlg.m21, dlg.m22, dlg.m23, dlg.m24, dlg.m25};

		obj_Morphology.greyValueErode(image_in, image_out, a);

		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GrayValue.GetCurSel() == 1) {//灰值膨胀
		CMorphologyDlg dlg;
		dlg.DoModal();

		int a[5][5] = {dlg.m1, dlg.m2, dlg.m3, dlg.m4, dlg.m5,
			dlg.m6, dlg.m7, dlg.m8, dlg.m9, dlg.m10,
			dlg.m11, dlg.m12, dlg.m13, dlg.m14, dlg.m15,
			dlg.m16, dlg.m17, dlg.m18, dlg.m19, dlg.m20,
			dlg.m21, dlg.m22, dlg.m23, dlg.m24, dlg.m25};

		obj_Morphology.greyValueDilate(image_in, image_out, a);

		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GrayValue.GetCurSel() == 2) {//灰值开运算
		CMorphologyDlg dlg;
		dlg.DoModal();

		int a[5][5] = {dlg.m1, dlg.m2, dlg.m3, dlg.m4, dlg.m5,
			dlg.m6, dlg.m7, dlg.m8, dlg.m9, dlg.m10,
			dlg.m11, dlg.m12, dlg.m13, dlg.m14, dlg.m15,
			dlg.m16, dlg.m17, dlg.m18, dlg.m19, dlg.m20,
			dlg.m21, dlg.m22, dlg.m23, dlg.m24, dlg.m25};

		obj_Morphology.greyValueOpenOperation(image_in, image_out, a);

		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GrayValue.GetCurSel() == 3) {//绘制闭运算
		CMorphologyDlg dlg;
		dlg.DoModal();

		int a[5][5] = {dlg.m1, dlg.m2, dlg.m3, dlg.m4, dlg.m5,
			dlg.m6, dlg.m7, dlg.m8, dlg.m9, dlg.m10,
			dlg.m11, dlg.m12, dlg.m13, dlg.m14, dlg.m15,
			dlg.m16, dlg.m17, dlg.m18, dlg.m19, dlg.m20,
			dlg.m21, dlg.m22, dlg.m23, dlg.m24, dlg.m25};

		obj_Morphology.greyValueCloseOperation(image_in, image_out, a);

		F_ShowImage(emVIEWAFT,image_out);
	}
}

void CpictureDlg::OnCbnSelchangeImageSegmentation()
{
	// TODO: 在此添加控件通知处理程序代码
	if(com_ImageCut.GetCurSel() == 0) {//极小值阈值法
		obj_Segmentation.minThreshold(image_in, image_out);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_ImageCut.GetCurSel() == 1) {//大津阈值
		//cvtColor(image_in,image_in,CV_RGB2GRAY);  
		obj_Segmentation.otsuGray(image_in, image_out);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_ImageCut.GetCurSel() == 2) {//霍夫直线检测
		cvtColor(image_in,image_out,CV_RGB2GRAY); 
		image_in = image_out.clone();
		obj_Segmentation.hough(image_in, image_out);
		F_ShowImage(emVIEWAFT,image_out);
		/*Mat midImage;
		Canny(image_in, midImage, 50, 200, 3);
		cvtColor(midImage, image_out, CV_GRAY2BGR);

		vector<Vec4i> lines;
		//与HoughLines不同的是，HoughLinesP得到lines的是含有直线上点的坐标的，所以下面进行划线时就不再需要自己求出两个点来确定唯一的直线了
		HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);//注意第五个参数，为阈值

		//依次画出每条线段
		for (size_t i = 0; i < lines.size(); i++)
		{
			Vec4i l = lines[i];

			line(image_out, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 1, 1); //Scalar函数用于调节线段颜色

			F_ShowImage(emVIEWAFT,image_out);
		}*/
	}

	if(com_ImageCut.GetCurSel() == 3) {//连通域检测
		obj_Segmentation.connectedDomain(image_in, image_out);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_ImageCut.GetCurSel() == 4) {//边缘检测
		obj_Segmentation.edgeDetection(image_in, image_out);
		F_ShowImage(emVIEWAFT,image_out);
	}
}

void CpictureDlg::OnCbnSelchangeGeometricFeatures()
{
	// TODO: 在此添加控件通知处理程序代码
	if(com_GeometricFeatures.GetCurSel() == 0) {//连通域质心检测
		obj_Features.centroidDetection(image_in, image_out);

		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GeometricFeatures.GetCurSel() == 1) {//连通域面积
		obj_Features.connectedArea(image_in, image_out);

		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GeometricFeatures.GetCurSel() == 2) {//连通域周长
		obj_Features.connectedPerimeter(image_in, image_out);

		F_ShowImage(emVIEWAFT,image_out);
	}
}


void CpictureDlg::OnCbnSelchangeShapeFeatures()
{
	// TODO: 在此添加控件通知处理程序代码
	if(com_ShapeFeatures.GetCurSel() == 0) {//矩形度
		cvtColor(image_in,image_out,CV_RGB2GRAY); 
		image_in = image_out.clone();
		obj_Features.myRectangle(image_in,image_out);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_ShapeFeatures.GetCurSel() == 1) {//圆形度
		cvtColor(image_in,image_out,CV_RGB2GRAY); 
		image_in = image_out.clone();
		obj_Features.myCircle(image_in,image_out);
		F_ShowImage(emVIEWAFT,image_out);
	}
}


void CpictureDlg::OnCbnSelchangeTemplateMatching()
{
	// TODO: 在此添加控件通知处理程序代码
	if(com_TemplateMatching.GetCurSel() == 0) {//模板匹配
		StopCam();//停止相机工作
		string frmPath;
		frmPath = DoSelectFiles(
			_T("*.bmp"), 
			OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
			_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
			_T("选择图像序列"),
			workDir+"\Imgs");
		Mat mid = cv::imread(frmPath);//读取图像
		F_ShowImage(emVIEWAFT,mid);

		//开始模板匹配
		obj_Features.templateMatching(image_in, mid, image_out);
		F_ShowImage(emVIEWBEF,image_out);
	}

	if(com_TemplateMatching.GetCurSel() == 1) {//最小外接矩阵
		cvtColor(image_in,image_out,CV_RGB2GRAY); 
		image_in = image_out.clone();
		obj_Features.minMatrix(image_in,image_out);
		F_ShowImage(emVIEWAFT,image_out);
	}
}

