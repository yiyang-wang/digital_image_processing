#pragma once
#include <iostream>
//#include "GreyDlg.h"
#include "opencv2/core/core.hpp"//����ģ�飬�����˻������ݽṹ���������ͺ��ڴ�����
#include "opencv2/imgproc/imgproc.hpp"//ͼ������ģ�飬����ͼ���˲���ͼ�񼸺α任��ɫ�ʿռ�ת�����ṹ����״������
using namespace cv;//���������ռ�cv,����cv::������(ww)
using namespace std;

class ImageGeometry
{
public:
	ImageGeometry(void);
	~ImageGeometry(void);

	void imgTranslate(const Mat& src, Mat& dst,int xOffset,int yOffset);/*ͼ��ƽ��*/
	Mat mirrorTranslate(const Mat &src);//ˮƽ����
	void scaleIntervalSampling(const Mat &src, Mat &dst, double x, double y);//��������
	void compositeTransformation(const Mat &src, Mat &dst, double a, double b, double p,
		double c, double d, double q, double e, double h, double s);//���ϱ任
	void warpFfine(Mat &src,Mat &dst,double m_x, double m_y, double m_angle);//ͼ����ת
};

