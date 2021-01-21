#pragma once
#include <iostream>
//#include "GreyDlg.h"
#include "opencv2/core/core.hpp"//核心模块，定义了基本数据结构、数据类型和内存管理等
#include "opencv2/imgproc/imgproc.hpp"//图像处理函数模块，包括图像滤波、图像几何变换、色彩空间转换、结构和形状分析等
using namespace cv;//导入命名空间cv,不用cv::来修饰(ww)
using namespace std;

class ImageGeometry
{
public:
	ImageGeometry(void);
	~ImageGeometry(void);

	void imgTranslate(const Mat& src, Mat& dst,int xOffset,int yOffset);/*图像平移*/
	Mat mirrorTranslate(const Mat &src);//水平镜像
	void scaleIntervalSampling(const Mat &src, Mat &dst, double x, double y);//比例缩放
	void compositeTransformation(const Mat &src, Mat &dst, double a, double b, double p,
		double c, double d, double q, double e, double h, double s);//复合变换
	void warpFfine(Mat &src,Mat &dst,double m_x, double m_y, double m_angle);//图像旋转
};

