#pragma once
#include <iostream>
//#include "GreyDlg.h"
#include "opencv2/core/core.hpp"//核心模块，定义了基本数据结构、数据类型和内存管理等
#include "opencv2/imgproc/imgproc.hpp"//图像处理函数模块，包括图像滤波、图像几何变换、色彩空间转换、结构和形状分析等
using namespace cv;//导入命名空间cv,不用cv::来修饰(ww)
using namespace std;

class ImageEnhancement
{
public:
	ImageEnhancement(void);
	~ImageEnhancement(void);

	void LogarithmTran(const Mat &src, Mat& dst, float fA, float fB, float fC);//灰度对数变换
	void GreyLineTran(const Mat &src, Mat& dst, float fA, float fB, float fC, float fD);//灰度线性变换
	void MyGammaCorrection(const Mat &src, Mat& dst, float fC, float fGamma);//灰度幂律变换
	Mat EqualizeHist(Mat &image);//直方图变换
	void ExpGrayTransform(const Mat &src, Mat& dst, float fA, float fB, float fC);//灰度指数变换
	Mat img_Hist(Mat& image);

	void salt(cv::Mat &image, int n);//椒盐噪声
	void AverFiltering(const Mat &src,Mat &dst);//邻域平均
	uchar Median(uchar n1, uchar n2, uchar n3, uchar n4, uchar n5, uchar n6, uchar n7, uchar n8, uchar n9);//求九个数的中值 
	void MedianFlitering(const Mat &src, Mat &dst);//中值滤波

};

