#pragma once
#include <iostream>
//#include "GreyDlg.h"
#include "opencv2/core/core.hpp"//����ģ�飬�����˻������ݽṹ���������ͺ��ڴ�����
#include "opencv2/imgproc/imgproc.hpp"//ͼ������ģ�飬����ͼ���˲���ͼ�񼸺α任��ɫ�ʿռ�ת�����ṹ����״������
using namespace cv;//���������ռ�cv,����cv::������(ww)
using namespace std;

class ImageEnhancement
{
public:
	ImageEnhancement(void);
	~ImageEnhancement(void);

	void LogarithmTran(const Mat &src, Mat& dst, float fA, float fB, float fC);//�Ҷȶ����任
	void GreyLineTran(const Mat &src, Mat& dst, float fA, float fB, float fC, float fD);//�Ҷ����Ա任
	void MyGammaCorrection(const Mat &src, Mat& dst, float fC, float fGamma);//�Ҷ����ɱ任
	Mat EqualizeHist(Mat &image);//ֱ��ͼ�任
	void ExpGrayTransform(const Mat &src, Mat& dst, float fA, float fB, float fC);//�Ҷ�ָ���任
	Mat img_Hist(Mat& image);

	void salt(cv::Mat &image, int n);//��������
	void AverFiltering(const Mat &src,Mat &dst);//����ƽ��
	uchar Median(uchar n1, uchar n2, uchar n3, uchar n4, uchar n5, uchar n6, uchar n7, uchar n8, uchar n9);//��Ÿ�������ֵ 
	void MedianFlitering(const Mat &src, Mat &dst);//��ֵ�˲�

};

