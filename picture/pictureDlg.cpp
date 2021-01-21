
// pictureDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "picture.h"
#include "pictureDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
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


// CpictureDlg �Ի���




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


// CpictureDlg ��Ϣ�������

BOOL CpictureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	/*******����Ͽ��������Ƶ���ݶ��뷽�����ַ���*******/
	com_InputStyle.AddString(_T("���뱾����Ƶ"));
	com_InputStyle.AddString(_T("����ͼ��"));
	com_InputStyle.AddString(_T("����ͷ����"));
	com_InputStyle.AddString(_T("����Ҷ�ͼ��"));
	com_InputStyle.SetCurSel(1);
	inputType=emPICTURES_IN;
	/*******����Ͽ��������Ƶ���ݶ��뷽�����ַ���*******/

	/*******����Ͽ������ɫ��ת����ʽ���ַ���*******/
	com_ColorCov.AddString(_T("RGBת��Ϊ�Ҷ�ֵ"));
	com_ColorCov.AddString(_T("RGBת��ΪLAB"));
	com_ColorCov.AddString(_T("RGBת��ΪYCrCb"));
	com_ColorCov.AddString(_T("RGBת��ΪXYZ"));
	com_ColorCov.AddString(_T("RGBת��ΪHSV"));
	//com_ColorCov.SetCurSel(0);
	/*******����Ͽ������ɫ��ת����ʽ���ַ���*******/

	/*******����Ͽ�����ӱ�����ʽ���ַ���*******/
	com_PicTraversal.AddString(_T("at������������ɫ��"));
	com_PicTraversal.AddString(_T("��������ʽ��������ɫ��"));
	com_PicTraversal.AddString(_T("ָ�뷽ʽ��������ɫ��"));
	//com_ColorCov.SetCurSel(0);
	/*******����Ͽ�����ӱ�����ʽ���ַ���*******/

	/*******����Ͽ�����ӻҶȱ任��ʽ���ַ���*******/
	com_GreyTransform.AddString(_T("�Ҷ����Ա任"));
	com_GreyTransform.AddString(_T("�����任"));
	com_GreyTransform.AddString(_T("ָ���任"));
	com_GreyTransform.AddString(_T("���ɱ任"));
	com_GreyTransform.AddString(_T("ֱ��ͼ���⻯"));
	/*******����Ͽ�����ӻҶȱ任��ʽ���ַ���*******/

	com_ImageSmooth.AddString(_T("��������"));
	com_ImageSmooth.AddString(_T("����ƽ��"));
	com_ImageSmooth.AddString(_T("��ֵ�˲�"));

	com_GeometricTrans.AddString(_T("ͼ���������"));
	com_GeometricTrans.AddString(_T("ͼ��ƽ��"));
	com_GeometricTrans.AddString(_T("ͼ����"));
	com_GeometricTrans.AddString(_T("ͼ����ת"));
	com_GeometricTrans.AddString(_T("ͼ�񸴺ϱ任"));

	com_TwoValue.AddString(_T("��ʴ"));
	com_TwoValue.AddString(_T("����"));
	com_TwoValue.AddString(_T("������"));
	com_TwoValue.AddString(_T("������"));
	com_TwoValue.AddString(_T("�Ǽ���ȡ"));

	com_GrayValue.AddString(_T("��ֵ��ʴ"));
	com_GrayValue.AddString(_T("��ֵ����"));
	com_GrayValue.AddString(_T("��ֵ������"));
	com_GrayValue.AddString(_T("��ֵ������"));

	com_ImageCut.AddString(_T("����ʽ��ֵ��"));
	com_ImageCut.AddString(_T("�����ֵ��"));
	com_ImageCut.AddString(_T("����任ֱ�߼��"));
	com_ImageCut.AddString(_T("��ͨ��ʶ��"));
	com_ImageCut.AddString(_T("��Ե���"));

	//com_GeometricFeatures.AddString(_T("��ֵͼ����ͨ��ʶ��"));
	//com_GeometricFeatures.AddString(_T("��ͨ��߽�"));
	com_GeometricFeatures.AddString(_T("��ͨ������"));
	com_GeometricFeatures.AddString(_T("��ͨ�����"));
	com_GeometricFeatures.AddString(_T("��ͨ���ܳ�"));

	com_ShapeFeatures.AddString(_T("���ζ�"));
	com_ShapeFeatures.AddString(_T("Բ�ζ�"));

	com_TemplateMatching.AddString(_T("ģ��ƥ��"));
	com_TemplateMatching.AddString(_T("��С��Ӿ���"));

	/*******��OpenCV�еĴ�����ʾ��MFC��*******/
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
	UpdateData( FALSE );//���½���ؼ�
	/*******��OpenCV�еĴ�����ʾ��MFC��*******/

	//workDir = F_InitWorkDir();//�ж�Imgs��SaveFrame�ļ����Ƿ���ڣ������ڴ���(ww)

	// ��ʼ��ͼ����ʾ�ؼ���ͼ��
	CRect rect;
	GetDlgItem(IDC_STATIC_PICTURE) ->GetClientRect( &rect );
	image_in = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);
	GetDlgItem(IDC_STATIC_MEDIA) ->GetClientRect( &rect );
	image_out = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);

	((CButton *)GetDlgItem(IDC_RADIO_ORIGIN))->SetCheck(TRUE);//ԭͼ��Ĭ��ѡ��  
	((CButton *)GetDlgItem(IDC_RADIO_HISTOGRAM))->SetCheck(FALSE);//ֱ��ͼĬ�ϲ�ѡ��  

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CpictureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CpictureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//////////////////////////////////////////////////////////////////////////
/*----------------------------------
* ���� :	��ʼ������������������������ļ���
*----------------------------------
* ���� :	CDigImagProcDlg::F_InitWorkDir
* ���� :	private 
* ���� :	���������ļ��У�ԭʼͼ���ļ��У������ͼ���ļ��м���Ƶ�ļ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	StopCam();//ֹͣ�������
	CDialogEx::OnOK();
}


/*----------------------------
* ���� :�����û�ѡ��ķ�ʽ��ʾͼ�����Ƶ(ww)
*----------------------------
* ���� : CDigImagProcDlg::OnBnChoosePicture
* ���� : private 
* ���� : void
*
*/
void CpictureDlg::OnBnChoosePicture()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ����ѡ��ͬ���ֱ�������ͷ���룬��Ƶ���룬����ͼ�������뱳����ģ����-ww16/5/4
	if (inputType==emPICTURES_IN)//(1)��ѡ��ͼ������
	{
		StopCam();//ֹͣ�������
		string frmPath;
		frmPath = DoSelectFiles(
			_T("*.bmp"), 
			OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
			_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
			_T("ѡ��ͼ������"),
			workDir+"\Imgs");
		image_in=cv::imread(frmPath);//��ȡͼ��
		F_ShowImage(emVIEWBEF,image_in);
	}
	else if(inputType==emCAMERA_IN)//(2)��ѡ����Ƶ����
	{
		//����ͷ���룬��������ͷ��ʾ�ֱ���ww-6-14
		nImageWidth = 640;
		nImageHeight = 480;
		//�򿪵�һ������ͷ
		if ( !cap_VidCam.open(1) )
		{
			AfxMessageBox(_T("������ͷʧ�ܣ�"));
			return;
		}
		cap_VidCam.set(CV_CAP_PROP_FRAME_WIDTH,  nImageWidth); //cv������Ƶ����֡��ȣ�ֻ������ͷ��Ч��
		cap_VidCam.set(CV_CAP_PROP_FRAME_HEIGHT, nImageHeight);//cv������Ƶ����֡�߶ȣ�ֻ������ͷ��Ч��
		// ��������ͷ����ʾʵʱ����
		SetTimer(1, 10, NULL);	// 10ms ��ʱ��ʾ
	}
	else if(inputType == ememVIDEO_IN)//(3)��ѡ����Ƶ����
	{
		CStringA videoFiles;//�洢�ļ�������
		StopCam();//ֹͣ�������
		videoFiles = DoSelectFiles(
			_T("*.avi"), 
			OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
			_T("video files (*.avi) |*.avi| All Files (*.*) |*.*||"),
			_T("ѡ����Ƶ�ļ�"),
			workDir+"\Videos");
		cap_VidCam.open(LPCSTR(videoFiles));//���ļ�
		SetTimer(1, 10, NULL);	// 10ms ��ʱ��ʾ

	}
	else//(1)��ѡ��Ҷ�ͼ������
	{
		StopCam();//ֹͣ�������
		string frmPath;
		frmPath = DoSelectFiles(
			_T("*.bmp"), 
			OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
			_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
			_T("ѡ��ͼ������"),
			workDir+"\Imgs");
		image_in=cv::imread(frmPath,0);//��ȡ�Ҷ�ͼ��
		F_ShowImage(emVIEWBEF,image_in);
	}
	//DoShowOrigFrame();
	return;
}


/*----------------------------
* ���� : �ر�����ͷ
*----------------------------
* ���� : CDigImagProcDlg::StopCam
* ���� : private 
* ���� : void
*
*/
void CpictureDlg::StopCam()
{
	// TODO: Add your control notification handler code here
	if (cap_VidCam.isOpened())
	{
		KillTimer(1);//�ú����Ƴ���ǰ��SetTimer���õĶ�ʱ��,�ڶ�ʱ��ʹ����Ϻ��Ƴ���ʱ��ʱʹ��

		// ��ͼ����������
		image_in = Scalar(0);
		//F_ShowImage( frame, IDC_PicLfCam );
		cap_VidCam.release();//�ͷ�VideoCapture����


	}
	return;
}

/*----------------------------
* ���� : �������ļ��Ի���ѡ�񵥸��ļ���
�����������ļ�����
*----------------------------
* ���� : CDigImagProcDlg::DoSelectFiles
* ���� : private 
* ���� : selectedFiles	ѡ����ļ���·������
*
* ���� : lpszDefExt			[in]	�ļ�Ĭ�ϸ�ʽ
* ���� : dwFlags			[in]	�Ի���ѡ��
* ���� : lpszFilter			[in]	�ļ���ʽ��������
* ���� : lpstrTitle			[in]	�Ի������
* ���� : lpstrInitialDir	[in]	�Ի���ĳ�ʼ·��
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
		AfxMessageBox("������ѡ���ļ�����������ʾĬ��ͼƬ��");
	}

	return selectedFile;
}

//////////////////////////////////////////////////////////////////////////
/*----------------------------------
* ���� : ����ļ����Ƿ����
*----------------------------------
* ���� : CStereoVisionDlg::CheckDir
* ���� : private 
* ���� : 1 - �ļ��д��ڣ�0 - ������
*
* ���� : dir		[in]	�ļ���·��
* ���� : creatDir	[in]	�Ƿ񴴽��ļ���
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
* ���� : ��ʾͼ��
*		 ��Ҫ���Ƶ�ͼ�� src ���Ƶ� des��Ȼ����Ƶ��ؼ���Ϊ ID �� Picture �ؼ�
*----------------------------
* ���� : CDigImagProcDlg::F_ShowImage
* ���� : private 
* ���� : void
*
* ���� : src	[in]	����ʾͼ��
* ���� : des	[in]	����ͼ��
* ���� : ID		[in]	ͼ�񴰿ڿؼ�ID
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
* ���� : ���㴫��ͼ��ֱ��ͼ�����ǲ�ɫͼ�񣬼������ɫ����ֱ��ͼ������
*----------------------------
* ���� : CDigImagProcDlg::CreatHistogram
* ���� : public 
* ���� : vector<Mat>
*
* ���� : Mat& m_srcImg	����ȡֱ��ͼͼ��

*/
vector<Mat> CpictureDlg::CreatHistogram(Mat& m_srcImg)
{
	/**
	void calcHist(const Mat* images, int nimages, const int* channels,
	InputArray mask, OutputArray	hist,
	int dims, const int* histSize, const float** ranges,
	bool uniform=true, bool accumulate=false )
	* images - Դͼ������
	* nimages - Դͼ����Ŀ
	* channels - ���ڼ���ֱ��ͼ��ͨ���б���0��ʼ��ţ�
	* mask - ��ģͼ�����0Ԫ�ض�Ӧ��ͼ�����ؽ����ڼ���ֱ��ͼ��
	* hist - ֱ��ͼ��dimsά����
	* dims - ֱ��ͼ��ά�������ֵΪCV_MAX_DIMS��ĿǰΪ32��
	* histSize - ֱ��ͼ��ά�Ĵ�С���������
	* ranges - ֱ��ͼ��ά��������ֵ��Χ���������ȷֲ�����ÿάֻ������ֵ��
	* uniform - ֱ��ͼ����Ƿ���ȷֲ��ı�־
	* accumulate - �Ƿ��ۼ���ǰ��ֱ��ͼ
	*/

	//�����ʼ������
	vector<Mat> grayBGRImg;//ֱ��ͼ������,�Ҷȣ����̺����
	Mat bHist, gHist, rHist, grayHist;	// ֱ��ͼ����
	int histSize = 256;					// ֱ��ͼ�����������ֱ��ͼ������ȡֵ��С��һ��0��255
	float range[] = {0, 255};
	const float* histRange = {range};	// ֱ��ͼ��ά��������ֵ��Χ

	if (m_srcImg.channels()==1)//���ǻҶ�ͼ��
	{
		calcHist(&m_srcImg, 1, 0, Mat(), grayHist, 1, &histSize, &histRange, true, false);// ����ֱ��ͼ
		grayBGRImg.push_back(grayHist);

	} 
	else if(m_srcImg.channels()==3)
	{
		/// ת��Ϊ�Ҷ�ͼ��
		Mat grayImg;
		cvtColor(m_srcImg, grayImg, CV_BGR2GRAY);
		calcHist(&m_srcImg, 1, 0, Mat(), grayHist, 1, &histSize, &histRange, true, false);// ����ֱ��ͼ
		// Ҳ���������������졢�̡���ͨ����ֱ��ͼ���������ͨ��
		const int channels[] = {0, 1, 2}; // ����Ϊ�����̡������ɫͨ������
		calcHist(&m_srcImg, 1, &channels[0], Mat(), bHist, 1, &histSize, &histRange, true, false);	// ��ɫͨ��ֱ��ͼ
		calcHist(&m_srcImg, 1, &channels[1], Mat(), gHist, 1, &histSize, &histRange, true, false);	// ��ɫͨ��ֱ��ͼ
		calcHist(&m_srcImg, 1, &channels[2], Mat(), rHist, 1, &histSize, &histRange, true, false);	// ��ɫͨ��ֱ��ͼ
		//��ֱ��ͼһά������ջ
		grayBGRImg.push_back(grayHist);
		grayBGRImg.push_back(bHist);
		grayBGRImg.push_back(gHist);
		grayBGRImg.push_back(rHist);
	}
	else{}
	return grayBGRImg;

}


/*----------------------------
* ���� : ���浱ǰ�������image_outͼ��
*----------------------------
* ���� : CStereoVisionDlg::OnBnClickedSaveImage
* ���� : private 
* ���� : void
*
*/
void CpictureDlg::OnBnClickedSaveImage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//������Ա����ͼ�����ͺ�׺��
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

	CString defaultDir =  workDir+"\SaveFrame";   //Ĭ�ϴ򿪵��ļ�·��  
	CString fileName = "new.bmp";         //Ĭ�ϱ�����ļ��� 

	CFileDialog openFileDlg(false,".bmp", fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, csFilter, NULL);
	openFileDlg.m_ofn.lpstrInitialDir=defaultDir;//��ʼ��·��
	//  �ļ����̶Ի���
	if (openFileDlg.DoModal()==IDOK ) //  �������ļ���
	{        
		strFileName = openFileDlg.m_ofn.lpstrFile;
		if (openFileDlg.m_ofn.nFileExtension == 0) //  ���ļ���׺
		{  
			strExtension = name[openFileDlg.m_ofn.nFilterIndex];
			strFileName = strFileName + '.' + strExtension;
			//  ���ļ���׺
		}

		string s(strFileName.GetBuffer());
		imwrite(s,image_out);   //  ��ǰ�������  
	}
}


void CpictureDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (cap_VidCam.isOpened())//�������ͷ������Ƶ��
	{
		cap_VidCam >> image_in;//���ÿһ֡

		//�ڵ�picture�ؼ�������ʾÿһ֡ͼ��
		F_ShowImage(emVIEWBEF,image_in);

	}

	CDialogEx::OnTimer(nIDEvent);
}


/*----------------------------
* ���� : ѡ��ɫ��ת����ʽ,������ת��(ww)
*----------------------------
* ���� : CDigImagProcDlg::OnCbnSelchangeComcolorcov
* ���� : private 
* ���� : void
*
*/
void CpictureDlg::OnCbnSelchangeComcolorcov()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(flag) {
		image_out=obj_ImagBase.covertColor(image_in,com_ColorCov.GetCurSel());
		//�ڵ�2��picture��ɫת�����ͼ��
		F_ShowImage(emVIEWAFT,image_out);
	}
}



/*----------------------------
* ���� : ���ݲ�ͬѡ�����ͼ�񣬼���ɫ��(ww)
*----------------------------
* ���� : CDigImagProcDlg::OnCbnSelComPicTraversal
* ���� : private 
* ���� : void
*
*/
void CpictureDlg::OnCbnSelComPicTraversal()
{
	if(flag) {
		// ��ͼ����������
		image_out = Scalar(0);
		F_ShowImage(emVIEWAFT,image_out);

		double duration;
		duration = static_cast<double>(cv::getTickCount());//��ʼ��ʱ

		obj_ImagBase.colorReduce(image_in,image_out,64,com_PicTraversal.GetCurSel());

		duration = static_cast<double>(cv::getTickCount())-duration;
		duration /= cv::getTickFrequency(); // the elapsed time in m

		//��ʾ����ʱ��
		CString str;
		char buffer[20];
		sprintf_s(buffer,"%f",duration);
		str = buffer;

		CString words= "The picture traversal time is: " + str + " ��";  
		AfxMessageBox(words);

		//putText(image_out, words, Point(image_out.cols/2,image_out.rows/2),CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0), 3);  

		//�ڵ�2��picture��ʾɫ�׼��ٺ��ͼ�񣬲���ʾ����ʱ��
		F_ShowImage(emVIEWAFT,image_out);
	}
}


/*----------------------------
* ���� : ��Ƶͼ������ͷ����ѡ����Ӧ(ww)
*----------------------------
* ���� : CDigImagProcDlg::OnCbnSelInputStyle
* ���� : private 
* ���� : void
*
*/
void CpictureDlg::OnCbnSelInputStyle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	inputType = com_InputStyle.GetCurSel();
	return;
}


void CpictureDlg::OnCbnSelchangeGreyTransformation() //�Ҷȱ任
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(com_GreyTransform.GetCurSel() == 1) {//�Ҷ����Ա任
		CGreyDlg dlg;
		dlg.DoModal();
		grey_Tran.GreyLineTran(image_in, image_out, dlg.m_a, dlg.m_b, dlg.m_c, dlg.m_d);
		F_ShowImage(emVIEWAFT,image_out);
	}

	else if(com_GreyTransform.GetCurSel() == 0) {//�����任
		image_out = Scalar(0);

		CLogarithmDlg dlg;
		dlg.DoModal();
		grey_Tran.LogarithmTran(image_in, image_out, dlg.m_a, dlg.m_b, dlg.m_c);

		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GreyTransform.GetCurSel() == 2) {//�Ҷ����ɱ任
		image_out = Scalar(0);

		CGammaTranDlg dlg;
		dlg.DoModal();

		grey_Tran.MyGammaCorrection(image_in, image_out, dlg.m_c, dlg.m_y);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GreyTransform.GetCurSel() == 3) {//ֱ��ͼ���⻯
		image_out = Scalar(0);
		image_out = grey_Tran.EqualizeHist(image_in);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GreyTransform.GetCurSel() == 4) {//�Ҷ�ָ���任
		image_out = Scalar(0);

		CExpGrayTranDlg dlg;
		dlg.DoModal();

		grey_Tran.ExpGrayTransform(image_in, image_out, dlg.m_a, dlg.m_b, dlg.m_c);
		F_ShowImage(emVIEWAFT,image_out);
	}
}


void CpictureDlg::OnCbnSelchangeImageSmooth()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(com_ImageSmooth.GetCurSel() == 0) {//��������
		image_out = image_in;
		grey_Tran.salt(image_out, 300000);
		F_ShowImage(emVIEWAFT,image_out);
	}

	else if(com_ImageSmooth.GetCurSel() == 1) { 
		grey_Tran.AverFiltering(image_in, image_out);//����ƽ��

		F_ShowImage(emVIEWAFT,image_out);
	}

	else if(com_ImageSmooth.GetCurSel() == 2) {//��ֵ�˲�
		grey_Tran.MedianFlitering(image_in, image_out);

		F_ShowImage(emVIEWAFT,image_out);
	}
}


void CpictureDlg::OnBnClickedRadioHistogram()//��ʾֱ��ͼ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Mat temp;
	image_out = grey_Tran.EqualizeHist(image_in);
	image_out = grey_Tran.img_Hist(image_out);
	temp = grey_Tran.img_Hist(image_in);
	F_ShowImage(emVIEWBEF,temp);
	F_ShowImage(emVIEWAFT,image_out);
}


void CpictureDlg::OnBnClickedRadioOrigin()//��ʾԭͼ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	image_out = grey_Tran.EqualizeHist(image_in);
	F_ShowImage(emVIEWBEF,image_in);
	F_ShowImage(emVIEWAFT,image_out);
}


//���α任
void CpictureDlg::OnCbnSelchangeGeometricTrans()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(com_GeometricTrans.GetCurSel() == 0) {//ͼ������
		image_out = Scalar(0);
		CGeometricTranDlg dlg;
		dlg.DoModal();

		geometry_Trans.scaleIntervalSampling(image_in, image_out, dlg.m_a, dlg.m_d);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GeometricTrans.GetCurSel() == 1) {//ͼ��ƽ��
		CGeometricTranDlg dlg;
		dlg.DoModal();

		geometry_Trans.imgTranslate(image_in,image_out,dlg.m_p,dlg.m_q);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GeometricTrans.GetCurSel() == 2) {//ˮƽ����
		image_out = geometry_Trans.mirrorTranslate(image_in);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GeometricTrans.GetCurSel() == 3) {//ͼ����ת
		image_out = Scalar(0);

		CGeometricTranDlg dlg;
		dlg.DoModal();

		//image_out = geometry_Trans.imgTranslate(image_in,dlg.m_x,dlg.m_y);//ͼ��ƽ��
		//geometry_Trans.warpFfine (image_out,image_out, dlg.m_angle);//ͼ����ת
		geometry_Trans.warpFfine(image_in, image_out, dlg.m_x, dlg.m_y, dlg.m_angle);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GeometricTrans.GetCurSel() == 4) {//ͼ�θ��ϱ任
		image_out = Scalar(0);

		CGeometricTranDlg dlg;
		dlg.DoModal();

		geometry_Trans.compositeTransformation(image_in, image_out, dlg.a, dlg.b, dlg.p,
			dlg.c, dlg.d, dlg.q, dlg.e, dlg.h, dlg.s);
		F_ShowImage(emVIEWAFT,image_out);
	}
}


//��ֵ��̬ѧ
void CpictureDlg::OnCbnSelchangeTwoValueMorphology()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(com_TwoValue.GetCurSel() == 0) {	//��ʴ
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

	if(com_TwoValue.GetCurSel() == 1) {	//����
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

	if(com_TwoValue.GetCurSel() == 2) {//������
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

	if(com_TwoValue.GetCurSel() == 3) {//������
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

	if(com_TwoValue.GetCurSel() == 4) {//�Ǽ���ȡ
		Mat mid (image_in.size(), CV_8U);
		cvtColor(image_in, mid, CV_BGR2GRAY );

		//���ϸ��Ŀ��Ϊ��ɫ������תͼ��
		mid = 255 - mid;
		//��ֵ������
		threshold(mid,image_out, 100, 255, THRESH_BINARY);
		obj_Morphology.thinning(image_out, image_out);

		F_ShowImage(emVIEWAFT,image_out);
	}
}


//��ֵ��̬ѧ
void CpictureDlg::OnCbnSelchangeGrayValueMorphology()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(com_GrayValue.GetCurSel() == 0) {//��ֵ��ʴ
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

	if(com_GrayValue.GetCurSel() == 1) {//��ֵ����
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

	if(com_GrayValue.GetCurSel() == 2) {//��ֵ������
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

	if(com_GrayValue.GetCurSel() == 3) {//���Ʊ�����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(com_ImageCut.GetCurSel() == 0) {//��Сֵ��ֵ��
		obj_Segmentation.minThreshold(image_in, image_out);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_ImageCut.GetCurSel() == 1) {//�����ֵ
		//cvtColor(image_in,image_in,CV_RGB2GRAY);  
		obj_Segmentation.otsuGray(image_in, image_out);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_ImageCut.GetCurSel() == 2) {//����ֱ�߼��
		cvtColor(image_in,image_out,CV_RGB2GRAY); 
		image_in = image_out.clone();
		obj_Segmentation.hough(image_in, image_out);
		F_ShowImage(emVIEWAFT,image_out);
		/*Mat midImage;
		Canny(image_in, midImage, 50, 200, 3);
		cvtColor(midImage, image_out, CV_GRAY2BGR);

		vector<Vec4i> lines;
		//��HoughLines��ͬ���ǣ�HoughLinesP�õ�lines���Ǻ���ֱ���ϵ������ģ�����������л���ʱ�Ͳ�����Ҫ�Լ������������ȷ��Ψһ��ֱ����
		HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);//ע������������Ϊ��ֵ

		//���λ���ÿ���߶�
		for (size_t i = 0; i < lines.size(); i++)
		{
			Vec4i l = lines[i];

			line(image_out, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 1, 1); //Scalar�������ڵ����߶���ɫ

			F_ShowImage(emVIEWAFT,image_out);
		}*/
	}

	if(com_ImageCut.GetCurSel() == 3) {//��ͨ����
		obj_Segmentation.connectedDomain(image_in, image_out);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_ImageCut.GetCurSel() == 4) {//��Ե���
		obj_Segmentation.edgeDetection(image_in, image_out);
		F_ShowImage(emVIEWAFT,image_out);
	}
}

void CpictureDlg::OnCbnSelchangeGeometricFeatures()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(com_GeometricFeatures.GetCurSel() == 0) {//��ͨ�����ļ��
		obj_Features.centroidDetection(image_in, image_out);

		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GeometricFeatures.GetCurSel() == 1) {//��ͨ�����
		obj_Features.connectedArea(image_in, image_out);

		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_GeometricFeatures.GetCurSel() == 2) {//��ͨ���ܳ�
		obj_Features.connectedPerimeter(image_in, image_out);

		F_ShowImage(emVIEWAFT,image_out);
	}
}


void CpictureDlg::OnCbnSelchangeShapeFeatures()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(com_ShapeFeatures.GetCurSel() == 0) {//���ζ�
		cvtColor(image_in,image_out,CV_RGB2GRAY); 
		image_in = image_out.clone();
		obj_Features.myRectangle(image_in,image_out);
		F_ShowImage(emVIEWAFT,image_out);
	}

	if(com_ShapeFeatures.GetCurSel() == 1) {//Բ�ζ�
		cvtColor(image_in,image_out,CV_RGB2GRAY); 
		image_in = image_out.clone();
		obj_Features.myCircle(image_in,image_out);
		F_ShowImage(emVIEWAFT,image_out);
	}
}


void CpictureDlg::OnCbnSelchangeTemplateMatching()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(com_TemplateMatching.GetCurSel() == 0) {//ģ��ƥ��
		StopCam();//ֹͣ�������
		string frmPath;
		frmPath = DoSelectFiles(
			_T("*.bmp"), 
			OFN_ENABLESIZING |OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
			_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
			_T("ѡ��ͼ������"),
			workDir+"\Imgs");
		Mat mid = cv::imread(frmPath);//��ȡͼ��
		F_ShowImage(emVIEWAFT,mid);

		//��ʼģ��ƥ��
		obj_Features.templateMatching(image_in, mid, image_out);
		F_ShowImage(emVIEWBEF,image_out);
	}

	if(com_TemplateMatching.GetCurSel() == 1) {//��С��Ӿ���
		cvtColor(image_in,image_out,CV_RGB2GRAY); 
		image_in = image_out.clone();
		obj_Features.minMatrix(image_in,image_out);
		F_ShowImage(emVIEWAFT,image_out);
	}
}

