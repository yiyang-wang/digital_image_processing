#pragma once
#include <iostream>
#include <math.h>
//#include "GreyDlg.h"
#include "opencv2/core/core.hpp"//����ģ�飬�����˻������ݽṹ���������ͺ��ڴ�����
#include "opencv2/imgproc/imgproc.hpp"//ͼ������ģ�飬����ͼ���˲���ͼ�񼸺α任��ɫ�ʿռ�ת�����ṹ����״������
using namespace cv;//���������ռ�cv,����cv::������(ww)
using namespace std;

class ImageMathematicalMorphology
{
public:
	ImageMathematicalMorphology(void);
	~ImageMathematicalMorphology(void);

	//��ֵ
	void twoValueErode(const Mat &src, Mat &dst, int a[5][5]);//��ʴ
	void twoValueDilate(const Mat &src, Mat &dst, int a[5][5]);//����
	void twoValueOpenOperation(const Mat &src, Mat &dst, int a[5][5]);//������
	void twoValueCloseOperation(const Mat &src, Mat &dst, int a[5][5]);//������
	//Mat thinImage(const cv::Mat & src, const int maxIterations);
	void thinning(const Mat &src, Mat &dst);//�Ǽ���ȡ

	//��ֵ
	void greyValueErode(const Mat &src, Mat &dst, int a[5][5]);//��ʴ
	void greyValueDilate(const Mat &src, Mat &dst, int a[5][5]);//����
	void greyValueOpenOperation(const Mat &src, Mat &dst, int a[5][5]);//������
	void greyValueCloseOperation(const Mat &src, Mat &dst, int a[5][5]);//������
	
};

