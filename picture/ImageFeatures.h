#pragma once
#include <iostream>
#include "ImageSegmentation.h"
#include "ImageGeometry.h"
//#include "GreyDlg.h"
#include "opencv2/core/core.hpp"//核心模块，定义了基本数据结构、数据类型和内存管理等
#include "opencv2/imgproc/imgproc.hpp"//图像处理函数模块，包括图像滤波、图像几何变换、色彩空间转换、结构和形状分析等
using namespace cv;//导入命名空间cv,不用cv::来修饰(ww)
using namespace std;

class ImageFeatures
{
public:
	ImageFeatures(void);
	~ImageFeatures(void);

	void centroidDetection(const Mat& src, Mat& dst);//质心检测
	void connectedArea(Mat &inputImage, Mat &outputImage);//连通域面积计算
	void templateMatching(const Mat& src, Mat& mid, Mat& dst);//模板匹配
	void connectedPerimeter(Mat &inputImage, Mat &outputImage);//连通域周长计算
	void minMatrix(Mat &src, Mat &dst);//最小外接矩阵
	void myRectangle(Mat &src, Mat &dst);//矩形度
	void myCircle(Mat &src, Mat &dst);//圆形度

	ImageSegmentation obj_Segmentation;
	ImageGeometry geometry_Trans;
};

