#pragma once
#include <iostream>
#include <math.h>
//#include "GreyDlg.h"
#include "opencv2/core/core.hpp"//核心模块，定义了基本数据结构、数据类型和内存管理等
#include "opencv2/imgproc/imgproc.hpp"//图像处理函数模块，包括图像滤波、图像几何变换、色彩空间转换、结构和形状分析等
#include "MinThresholdDlg.h"
using namespace cv;//导入命名空间cv,不用cv::来修饰(ww)
using namespace std;

#define PI 3.1415926

class ImageSegmentation
{
public:
	ImageSegmentation(void);
	~ImageSegmentation(void);

	void otsuGray(const Mat &src, Mat &dst);//大津阈值法
	void connectedDomain(cv::Mat &inputImage, cv::Mat &outputImage);//连通域计数
	void minThreshold(Mat &src, Mat &dst);//最小值阈值法
	void edgeDetection(const Mat &src, Mat &dst);//边缘检测
	void hough(Mat &src, Mat &dst);//霍夫直线检测
};

