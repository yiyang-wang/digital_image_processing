#pragma once
#include <iostream>
#include "opencv2/core/core.hpp"//����ģ�飬�����˻������ݽṹ���������ͺ��ڴ�����
#include "opencv2/imgproc/imgproc.hpp"//ͼ������ģ�飬����ͼ���˲���ͼ�񼸺α任��ɫ�ʿռ�ת�����ṹ����״������
using namespace cv;//���������ռ�cv,����cv::������(ww)

class ImageBase
{
public:
	ImageBase(void);
	~ImageBase(void);

	cv::Mat covertColor(const cv::Mat &m_Input, int covType);//���ݴ��ݵĲ���ʵ����ɫ�໥ת��
	void colorReduce(cv::Mat &inputImage, cv::Mat &outputImage, int div, int type);//���ݴ��ݵĲ���ʵ����ɫ�໥ת��
};

