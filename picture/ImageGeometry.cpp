#include "StdAfx.h"
#include "ImageGeometry.h"

ImageGeometry::ImageGeometry(void)
{
}


ImageGeometry::~ImageGeometry(void)
{
}


/*图像平移*/
void ImageGeometry::imgTranslate(const Mat& src, Mat& dst, int xOffset,int yOffset){
	int rows=src.rows;
	int cols=src.cols;
	dst=Mat::zeros(src.size(),src.type());
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			int x=i+yOffset;
			int y=j+xOffset;
			if(x>=0 && y>=0 && x<rows && y<cols){
				dst.at<Vec3b>(x,y)=src.at<Vec3b>(i,j);
			}
		}
	}
}

//水平镜像
Mat ImageGeometry::mirrorTranslate(const Mat &src) {
	Mat dst;  
	dst.create( src.size(), src.type());  
	Mat map_x;  
	Mat map_y;  
	map_x.create( src.size(), CV_32FC1);  
	map_y.create( src.size(), CV_32FC1);  
	for( int i = 0; i < src.rows; ++i)  
	{  
		for( int j = 0; j < src.cols; ++j)  
		{  
			map_x.at<float>(i, j) = (float) (src.cols - j) ;  
			map_y.at<float>(i, j) = (float) i;//(src.rows - i) ;  
		}  
	}  
	remap(src, dst, map_x, map_y, CV_INTER_LINEAR);  
	return dst;
}

//比例缩放
void ImageGeometry::scaleIntervalSampling(const Mat &src, Mat &dst, double x, double y){

	CV_Assert(src.depth() == CV_8U);

	const int rows = src.rows;
	const int cols = src.cols;

	dst.create(rows, cols, src.type());

	double m_translate1=x;
	double m_translate2=y;

	Vec3b *p;
	for (int i = 0; i < rows; i++)
	{
		p = dst.ptr<Vec3b>(i);
		for (int j = 0; j < cols; j++)
		{
			//平移后坐标映射到原图像
			int x = j / m_translate1;
			int y = i / m_translate2;

			//保证映射后的坐标在原图像范围内
			if (x >= 0 && y >= 0 && x < cols && y < rows)
				p[j] = src.ptr<Vec3b>(y)[x];
		}
	}
}


//复合变换
void ImageGeometry::compositeTransformation(const Mat &src, Mat &dst, double a, double b, double p,
										double c, double d, double q, double e, double h, double s)
{
	CV_Assert(src.depth() == CV_8U);

	const int rows = src.rows;
	const int cols = src.cols;

	dst.create(rows, cols, src.type());

	if(s != 1) {
		a = a*s;
		b = b*s;
		p = p*s;
		c = c*s;
		d = d*s;
		q = q*s;
		s = 1;
	}

	e = 0;
	h = 0;

	Vec3b *m_p;

	for (int i = 0; i < rows; i++)
	{
		m_p = dst.ptr<Vec3b>(i);
		for (int j = 0; j < cols; j++)
		{
			//平移后坐标映射到原图像
			int x = a*j+b*i+p;
			int y = c*j+d*i+q;

			//保证映射后的坐标在原图像范围内
			if (x >= 0 && y >= 0 && x < cols && y < rows)
				m_p[j] = src.ptr<Vec3b>(y)[x];
		}
	}
	/*int rows=src.rows;
	int cols=src.cols;
	dst = Mat::zeros(src.size(),src.type());

	if(s != 1) {
		a = a/s;
		b = b/s;
		p = p/s;
		c = c/s;
		d = d/s;
		q = q/s;
		s = 1;
	}

	e = 0;
	h = 0;

	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			int x = a*i+b*j+p;
			int y = c*i+d*j+q;
			if(x>=0 && y>=0 && x<rows && y<cols){
				dst.at<Vec3b>(x,y)=src.at<Vec3b>(i,j);
			}
		}
	}*/
}


//图像旋转
void ImageGeometry::warpFfine(Mat &src,Mat &dst,double m_x, double m_y, double m_angle)
{
	CV_Assert(src.depth() == CV_8U);

	const int rows = src.rows;
	const int cols = src.cols;

	m_angle = m_angle/180*3.1415926;

	//dst.create(rows, cols, src.type());
	dst = Mat::zeros(rows,cols,src.type());

	if(src.type() == CV_8U) {//灰度图像旋转
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				//平移后坐标映射到原图像
				int x = cos(m_angle)*(j-m_x)+sin(m_angle)*(i-m_y)+m_x;
				int y = -sin(m_angle)*(j-m_x)+cos(m_angle)*(i-m_y)+m_y;

				//保证映射后的坐标在原图像范围内
				if (x >= 0 && y >= 0 && x < cols && y < rows) {
					dst.at<uchar>(i,j) = src.at<uchar>(y,x);
				}

			}
		}
	}

	else {//三通道旋转
		Vec3b *p;
		for (int i = 0; i < rows; i++)
		{
			p = dst.ptr<Vec3b>(i);
			for (int j = 0; j < cols; j++)
			{
				//平移后坐标映射到原图像
				int x = cos(m_angle)*(j-m_x)+sin(m_angle)*(i-m_y)+m_x;
				int y = -sin(m_angle)*(j-m_x)+cos(m_angle)*(i-m_y)+m_y;

				//保证映射后的坐标在原图像范围内
				if (x >= 0 && y >= 0 && x < cols && y < rows) {
					p[j] = src.ptr<Vec3b>(y)[x];
				}

			}
		}
	}
}