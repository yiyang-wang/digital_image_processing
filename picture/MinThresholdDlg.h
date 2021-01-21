#pragma once
#include "afxcmn.h"

#include <iostream>
#include "resource.h"
#include "cv.h"  
#include "highgui.h"  
#include "opencv2/core/core.hpp"//核心模块，定义了基本数据结构、数据类型和内存管理等
#include "opencv2/imgproc/imgproc.hpp"//图像处理函数模块，包括图像滤波、图像几何变换、色彩空间转换、结构和形状分析等
using namespace cv;//导入命名空间cv,不用cv::来修饰(ww)
using namespace std;

// CMinThresholdDlg 对话框

class CMinThresholdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMinThresholdDlg)

public:
	CMinThresholdDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMinThresholdDlg();

// 对话框数据
	enum { IDD = IDD_OTSU_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_average;
	double m_variance;
	double m_display;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slider;
	Mat m_histogram;
	Mat m_image;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
