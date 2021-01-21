#pragma once
#include <iostream>
#include <math.h>
//#include "GreyDlg.h"
#include "opencv2/core/core.hpp"//����ģ�飬�����˻������ݽṹ���������ͺ��ڴ�����
#include "opencv2/imgproc/imgproc.hpp"//ͼ������ģ�飬����ͼ���˲���ͼ�񼸺α任��ɫ�ʿռ�ת�����ṹ����״������
#include "MinThresholdDlg.h"
using namespace cv;//���������ռ�cv,����cv::������(ww)
using namespace std;

#define PI 3.1415926

class ImageSegmentation
{
public:
	ImageSegmentation(void);
	~ImageSegmentation(void);

	void otsuGray(const Mat &src, Mat &dst);//�����ֵ��
	void connectedDomain(cv::Mat &inputImage, cv::Mat &outputImage);//��ͨ�����
	void minThreshold(Mat &src, Mat &dst);//��Сֵ��ֵ��
	void edgeDetection(const Mat &src, Mat &dst);//��Ե���
	void hough(Mat &src, Mat &dst);//����ֱ�߼��
};

