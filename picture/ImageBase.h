#pragma once
#include <iostream>
#include "opencv2/core/core.hpp"//核心模块，定义了基本数据结构、数据类型和内存管理等
#include "opencv2/imgproc/imgproc.hpp"//图像处理函数模块，包括图像滤波、图像几何变换、色彩空间转换、结构和形状分析等
using namespace cv;//导入命名空间cv,不用cv::来修饰(ww)

class ImageBase
{
public:
	ImageBase(void);
	~ImageBase(void);

	cv::Mat covertColor(const cv::Mat &m_Input, int covType);//根据传递的参数实现颜色相互转换
	void colorReduce(cv::Mat &inputImage, cv::Mat &outputImage, int div, int type);//根据传递的参数实现颜色相互转换
};

