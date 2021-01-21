#pragma once
#include <iostream>
#include <math.h>
//#include "GreyDlg.h"
#include "opencv2/core/core.hpp"//核心模块，定义了基本数据结构、数据类型和内存管理等
#include "opencv2/imgproc/imgproc.hpp"//图像处理函数模块，包括图像滤波、图像几何变换、色彩空间转换、结构和形状分析等
using namespace cv;//导入命名空间cv,不用cv::来修饰(ww)
using namespace std;

class ImageMathematicalMorphology
{
public:
	ImageMathematicalMorphology(void);
	~ImageMathematicalMorphology(void);

	//二值
	void twoValueErode(const Mat &src, Mat &dst, int a[5][5]);//腐蚀
	void twoValueDilate(const Mat &src, Mat &dst, int a[5][5]);//膨胀
	void twoValueOpenOperation(const Mat &src, Mat &dst, int a[5][5]);//开运算
	void twoValueCloseOperation(const Mat &src, Mat &dst, int a[5][5]);//闭运算
	//Mat thinImage(const cv::Mat & src, const int maxIterations);
	void thinning(const Mat &src, Mat &dst);//骨架提取

	//灰值
	void greyValueErode(const Mat &src, Mat &dst, int a[5][5]);//腐蚀
	void greyValueDilate(const Mat &src, Mat &dst, int a[5][5]);//膨胀
	void greyValueOpenOperation(const Mat &src, Mat &dst, int a[5][5]);//开运算
	void greyValueCloseOperation(const Mat &src, Mat &dst, int a[5][5]);//闭运算
	
};

