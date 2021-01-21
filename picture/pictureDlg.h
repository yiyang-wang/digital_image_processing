
// pictureDlg.h : ͷ�ļ�
//
#pragma once

#include "cv.h"  
#include "highgui.h"  
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include "CvvImage.h"
//����Opencv�⺯��
#include <vector>//(ww)
#include <io.h>
#include <direct.h>
#include <stdio.h>
#include <afxwin.h>

#include "opencv2/imgproc/imgproc.hpp"//ͼ����������ģ�飬����ͼ���˲���ͼ�񼸺α任��ɫ�ʿռ�ת����(ww)
#include "opencv2/highgui/highgui.hpp"//��Ƶ��׽��ͼ����Ƶ��ȡ���룬ͼ�ν���(ww)
#include "afxwin.h"

#include "ImageBase.h"//�����ڶ�����ͷ�ļ�
#include "ImageEnhancement.h"//������ͷ�ļ�
#include "ImageGeometry.h"//������ͷ�ļ�
#include "ImageMathematicalMorphology.h"//������ͷ�ļ�
#include "ImageSegmentation.h"//������ͷ�ļ�
#include "ImageFeatures.h"//�ڰ���ͷ�ļ�
#include "GreyDlg.h"//�Ҷȱ任�Ի���
#include "LogarithmDlg.h"//�����任
#include "GammaTranDlg.h"//���ɱ任
#include "ExpGrayTranDlg.h"//ָ���任
#include "GeometricTranDlg.h"//ͼ�񼸺α任
#include "MorphologyDlg.h"//��ѧ��̬ѧ����
#include "MinThresholdDlg.h"//ͼ��ָ�Ի���
#include <cmath>

using namespace std;//���������ռ�std,����std::������(ww)
using namespace cv;//���������ռ�cv,����cv::������(ww)


// CpictureDlg �Ի���
class CpictureDlg : public CDialogEx
{
	// ����
public:
	CpictureDlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_PICTURE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	CComboBox com_InputStyle;//ͼ�����뷽ʽ�������������
	CComboBox com_GreyTransform;// �Ҷȱ任ѡ������
	CComboBox com_GeometricTrans;//���α任ѡ������
	CComboBox com_TwoValue;//������̬ѧ��ֵ��̬ѧ
	CComboBox com_GrayValue;//��ֵ��̬ѧ
	CComboBox com_ImageCut;//ͼ��ָ�
	CComboBox com_GeometricFeatures;//��������
	CComboBox com_ShapeFeatures;//��״����
	CComboBox com_TemplateMatching;// ģ��ƥ��

public:
	vector<Mat> CreatHistogram(Mat& m_srcImg);//���㴫��ͼ��ֱ��ͼ�����ǲ�ɫͼ�񣬼������ɫ����ֱ��ͼ������

private:
	//����ö������(ww)
	typedef enum {ememVIDEO_IN, emPICTURES_IN,emCAMERA_IN } READ_METHOD;//���뷽ʽ��ͼ��0����Ϊ���1����Ƶ2����
	typedef enum {emVIEWBEF, emVIEWAFT } SHOW_WINDOW;//���뷽ʽ��ͼ��0����Ϊ���1����Ƶ2����
	typedef enum {emCV_BGR2GRAY, emCV_BGR2Lab,emCV_BGR2YCrCb,emCV_BGR2XYZ,emCV_BGR2HSV } COV_TYPE;//���뷽ʽ��ͼ��0����Ϊ���1����Ƶ2����

	//ȫ��˽�б���(ww)
	VideoCapture cap_VidCam;//��ȡ���������߱�����Ƶ
	cv::Mat image_in;//ԭͼ��
	cv::Mat image_out;//������ͼ��
    int inputType;//ѡ����������뷽ʽ
	int nImageChannels;//��¼ͼ��ͨ������1-�Ҷȣ�3-��ɫ
	int nImageWidth;//��¼�����õ�ͼ����
	int nImageHeight;//��¼�����õ�ͼ��߶�
	CString workDir;//ͼ���ʼĬ���ļ���
	ImageBase obj_ImagBase;//����ͼ���������
	ImageEnhancement grey_Tran;//�Ҷȱ任���������
	ImageGeometry geometry_Trans;//ͼ�񼸺α任���������
	ImageSegmentation obj_Segmentation;//ͼ��ָ�������
	ImageMathematicalMorphology obj_Morphology;//������̬ѧ���������
	ImageFeatures obj_Features;//ͼ�����������

	bool flag;

	void StopCam();//ֹͣ�������
	//ѡ���û�ѡ�е��ļ��������������ļ�����
	CStringA DoSelectFiles(LPCTSTR lpszDefExt,DWORD dwFlags,LPCTSTR	lpszFilter,	LPCSTR	lpstrTitle,	LPCSTR	lpstrInitialDir);
	//CString F_InitWorkDir();//��ʼ���ļ��У�������·��
	bool F_CheckDir(const string dir, bool creatDir /* = false */);//����ļ����Ƿ����
	void F_ShowImage(int type,Mat& src);//��ʾͼ����IDͼ��ؼ���

public:
	afx_msg void OnCbnSelchangeGreyTransformation();
	afx_msg void OnCbnSelchangeImageSmooth();
	afx_msg void OnCbnSelchangeTwoValueMorphology();
	CComboBox com_ImageSmooth;//ͼ��ƽ��

	afx_msg void OnBnClickedRadioHistogram();
	afx_msg void OnBnClickedRadioOrigin();
	afx_msg void OnCbnSelchangeGeometricTrans();
	afx_msg void OnCbnSelchangeGrayValueMorphology();
	afx_msg void OnCbnSelchangeImageSegmentation();//�����ֵ
	
	afx_msg void OnCbnSelchangeGeometricFeatures();
	afx_msg void OnCbnSelchangeTemplateMatching();
	afx_msg void OnCbnSelchangeShapeFeatures();
};
