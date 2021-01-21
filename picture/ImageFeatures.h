#pragma once
#include <iostream>
#include "ImageSegmentation.h"
#include "ImageGeometry.h"
//#include "GreyDlg.h"
#include "opencv2/core/core.hpp"//����ģ�飬�����˻������ݽṹ���������ͺ��ڴ�����
#include "opencv2/imgproc/imgproc.hpp"//ͼ������ģ�飬����ͼ���˲���ͼ�񼸺α任��ɫ�ʿռ�ת�����ṹ����״������
using namespace cv;//���������ռ�cv,����cv::������(ww)
using namespace std;

class ImageFeatures
{
public:
	ImageFeatures(void);
	~ImageFeatures(void);

	void centroidDetection(const Mat& src, Mat& dst);//���ļ��
	void connectedArea(Mat &inputImage, Mat &outputImage);//��ͨ���������
	void templateMatching(const Mat& src, Mat& mid, Mat& dst);//ģ��ƥ��
	void connectedPerimeter(Mat &inputImage, Mat &outputImage);//��ͨ���ܳ�����
	void minMatrix(Mat &src, Mat &dst);//��С��Ӿ���
	void myRectangle(Mat &src, Mat &dst);//���ζ�
	void myCircle(Mat &src, Mat &dst);//Բ�ζ�

	ImageSegmentation obj_Segmentation;
	ImageGeometry geometry_Trans;
};

