
// pictureDlg.h : 头文件
//
#pragma once

#include "cv.h"  
#include "highgui.h"  
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include "CvvImage.h"
//包含Opencv库函数
#include <vector>//(ww)
#include <io.h>
#include <direct.h>
#include <stdio.h>
#include <afxwin.h>

#include "opencv2/imgproc/imgproc.hpp"//图像处理函数基本模块，包括图像滤波、图像几何变换、色彩空间转换等(ww)
#include "opencv2/highgui/highgui.hpp"//视频捕捉，图像视频读取解码，图形交互(ww)
#include "afxwin.h"

#include "ImageBase.h"//包含第二章类头文件
#include "ImageEnhancement.h"//第三章头文件
#include "ImageGeometry.h"//第四章头文件
#include "ImageMathematicalMorphology.h"//第六章头文件
#include "ImageSegmentation.h"//第七章头文件
#include "ImageFeatures.h"//第八章头文件
#include "GreyDlg.h"//灰度变换对话框
#include "LogarithmDlg.h"//对数变换
#include "GammaTranDlg.h"//幂律变换
#include "ExpGrayTranDlg.h"//指数变换
#include "GeometricTranDlg.h"//图像几何变换
#include "MorphologyDlg.h"//数学形态学处理
#include "MinThresholdDlg.h"//图像分割对话框
#include <cmath>

using namespace std;//导入命名空间std,不用std::来修饰(ww)
using namespace cv;//导入命名空间cv,不用cv::来修饰(ww)


// CpictureDlg 对话框
class CpictureDlg : public CDialogEx
{
	// 构造
public:
	CpictureDlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_PICTURE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnChoosePicture();
	afx_msg void OnBnClickedSaveImage();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCbnSelchangeComcolorcov();
	afx_msg void OnCbnSelComPicTraversal();
	afx_msg void OnCbnSelInputStyle();

	CComboBox com_ColorCov;
	CComboBox com_PicTraversal;
	CComboBox com_InputStyle;//图像输入方式下拉框关联变量
	CComboBox com_GreyTransform;// 灰度变换选择框变量
	CComboBox com_GeometricTrans;//几何变换选择框变量
	CComboBox com_TwoValue;//数字形态学二值形态学
	CComboBox com_GrayValue;//灰值形态学
	CComboBox com_ImageCut;//图像分割
	CComboBox com_GeometricFeatures;//几何特征
	CComboBox com_ShapeFeatures;//形状特征
	CComboBox com_TemplateMatching;// 模板匹配

public:
	vector<Mat> CreatHistogram(Mat& m_srcImg);//计算传入图像直方图，若是彩色图像，计算各颜色分量直方图并返回

private:
	//定义枚举类型(ww)
	typedef enum {ememVIDEO_IN, emPICTURES_IN,emCAMERA_IN } READ_METHOD;//读入方式，图像0，分为相机1，视频2读入
	typedef enum {emVIEWBEF, emVIEWAFT } SHOW_WINDOW;//读入方式，图像0，分为相机1，视频2读入
	typedef enum {emCV_BGR2GRAY, emCV_BGR2Lab,emCV_BGR2YCrCb,emCV_BGR2XYZ,emCV_BGR2HSV } COV_TYPE;//读入方式，图像0，分为相机1，视频2读入

	//全局私有变量(ww)
	VideoCapture cap_VidCam;//获取相机输入或者本地视频
	cv::Mat image_in;//原图像
	cv::Mat image_out;//处理后的图像
    int inputType;//选择的数据输入方式
	int nImageChannels;//记录图像通道数，1-灰度，3-彩色
	int nImageWidth;//记录或设置的图像宽度
	int nImageHeight;//记录或设置的图像高度
	CString workDir;//图像初始默认文件夹
	ImageBase obj_ImagBase;//数字图像处理基础类
	ImageEnhancement grey_Tran;//灰度变换处理基础类
	ImageGeometry geometry_Trans;//图像几何变换处理基础类
	ImageSegmentation obj_Segmentation;//图像分割处理基础类
	ImageMathematicalMorphology obj_Morphology;//数字形态学处理基础类
	ImageFeatures obj_Features;//图像特征与理解

	bool flag;

	void StopCam();//停止相机工作
	//选择用户选中的文件，并可以限制文件类型
	CStringA DoSelectFiles(LPCTSTR lpszDefExt,DWORD dwFlags,LPCTSTR	lpszFilter,	LPCSTR	lpstrTitle,	LPCSTR	lpstrInitialDir);
	//CString F_InitWorkDir();//初始化文件夹，并返回路径
	bool F_CheckDir(const string dir, bool creatDir /* = false */);//检查文件夹是否存在
	void F_ShowImage(int type,Mat& src);//显示图像至ID图像控件中

public:
	afx_msg void OnCbnSelchangeGreyTransformation();
	afx_msg void OnCbnSelchangeImageSmooth();
	afx_msg void OnCbnSelchangeTwoValueMorphology();
	CComboBox com_ImageSmooth;//图像平滑

	afx_msg void OnBnClickedRadioHistogram();
	afx_msg void OnBnClickedRadioOrigin();
	afx_msg void OnCbnSelchangeGeometricTrans();
	afx_msg void OnCbnSelchangeGrayValueMorphology();
	afx_msg void OnCbnSelchangeImageSegmentation();//大津阈值
	
	afx_msg void OnCbnSelchangeGeometricFeatures();
	afx_msg void OnCbnSelchangeTemplateMatching();
	afx_msg void OnCbnSelchangeShapeFeatures();
};
