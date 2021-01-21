#pragma once
#include "afxcmn.h"

#include <iostream>
#include "resource.h"
#include "cv.h"  
#include "highgui.h"  
#include "opencv2/core/core.hpp"//����ģ�飬�����˻������ݽṹ���������ͺ��ڴ�����
#include "opencv2/imgproc/imgproc.hpp"//ͼ������ģ�飬����ͼ���˲���ͼ�񼸺α任��ɫ�ʿռ�ת�����ṹ����״������
using namespace cv;//���������ռ�cv,����cv::������(ww)
using namespace std;

// CMinThresholdDlg �Ի���

class CMinThresholdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMinThresholdDlg)

public:
	CMinThresholdDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMinThresholdDlg();

// �Ի�������
	enum { IDD = IDD_OTSU_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
