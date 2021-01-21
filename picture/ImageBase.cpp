#include "StdAfx.h"
#include "ImageBase.h"


ImageBase::ImageBase(void)
{
}


ImageBase::~ImageBase(void)
{
}

/*----------------------------
 * 功能 : 根据传递的参数实现颜色相互转换(ww)
  *此方法缺点为遍历速度比较慢
 *----------------------------
 * 函数 : ImageBase::covertColor
 * 访问 : private 
 * 返回 : Mat
 *
 */
cv::Mat ImageBase::covertColor(const cv::Mat &m_Input, int covType)
{
	cv::Mat m_Output;
	switch (covType)
	{
	    case 0:
		  cv::cvtColor(m_Input,m_Output,CV_BGR2GRAY);
		  break;
		case 1:
			cv::cvtColor(m_Input,m_Output,CV_BGR2Lab);
			break;
		case 2:
			cv::cvtColor(m_Input,m_Output,CV_BGR2YCrCb);
			break;
		case 3:
			cv::cvtColor(m_Input,m_Output,CV_BGR2XYZ);
			break;
		case 4:
			cv::cvtColor(m_Input,m_Output,CV_BGR2HSV);
			break;
	}
	return m_Output;
}

/*----------------------------
 * 功能 : 减少传入图像的色阶，采用at方式循环,减少倍数为div(ww)
 *此方法缺点为不适合表示行与列坐标
 *----------------------------
 * 函数 : ImageBase::colorReduceWithIterator
 * 访问 : private 
 *
 */
void colorReduceWithAt(cv::Mat &inputImage, cv::Mat &outputImage, int div)
{
	outputImage = inputImage.clone();
	int rows = outputImage.rows;
	int cols = outputImage.cols;
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			outputImage.at<Vec3b>(i,j)[0] = outputImage.at<Vec3b>(i,j)[0]/div*div + div/2;
			outputImage.at<Vec3b>(i,j)[1] = outputImage.at<Vec3b>(i,j)[1]/div*div + div/2;
			outputImage.at<Vec3b>(i,j)[2] = outputImage.at<Vec3b>(i,j)[2]/div*div + div/2;
		}
	}
}

/*----------------------------
 * 功能 : 减少传入图像的色阶，采用Iterator方式循环,减少倍数为div(ww)
 *此方法缺点为不适合表示行与列坐标
 *----------------------------
 * 函数 : ImageBase::colorReduceWithIterator
 * 访问 : private 
 *
 */
void colorReduceWithIterator(cv::Mat &inputImage, cv::Mat &outputImage, int div)
{
	outputImage = inputImage.clone();
	//模板必须指明数据类型
	Mat_<Vec3b>::iterator it = inputImage.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = inputImage.end<Vec3b>();
	//也可以通过指明cimage类型的方法不写begin和end的类型
	Mat_<Vec3b> cimage= outputImage;
	Mat_<Vec3b>::iterator itout = cimage.begin();
	Mat_<Vec3b>::iterator itoutend = cimage.end();
	for(; it != itend; it++,itout++)
	{
		(*itout)[0] = (*it)[0]/div*div + div/2;
		(*itout)[1] = (*it)[1]/div*div + div/2;
		(*itout)[2] = (*it)[2]/div*div + div/2;
	}
}

/*----------------------------
 * 功能 : 减少传入图像的色阶，采用Ptr方式循环,减少倍数为div(ww)
 *----------------------------
 * 函数 : ImageBase::colorReduceWithIterator
 * 访问 : private 
 * 返回 : Mat
 *
 */
void colorReduceWithPtr(cv::Mat &inputImage, cv::Mat &outputImage, int div)
{
	outputImage = inputImage.clone();
	int rows = outputImage.rows;
	int cols = outputImage.cols*outputImage.channels();

	for(int i = 0; i < rows; i++)
	{
		uchar* dataout = outputImage.ptr<uchar>(i);
		for(int j = 0; j < cols; j++)
		{
			dataout[j] = dataout[j]/div*div + div/2;
		}
	}
}

/*----------------------------
 * 功能 : 减少传入图像的色阶，根据type采用不同遍历方式,减少倍数为div(ww)
 *----------------------------
 * 函数 : ImageBase::colorReduceWithIterator
 * 访问 : private 
 * 返回 : Mat
 *
 */
void ImageBase::colorReduce(cv::Mat &inputImage, cv::Mat &outputImage, int div, int type)
{
	switch (type)
	{
	  case 0:
		colorReduceWithAt(inputImage, outputImage, div);
		break;
	  case 1:
		colorReduceWithIterator(inputImage, outputImage, div);
		break;
	  case 2:
		colorReduceWithPtr(inputImage, outputImage, div);
		break;
	}
}