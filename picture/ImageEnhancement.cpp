#include "StdAfx.h"
#include "ImageEnhancement.h"

ImageEnhancement::ImageEnhancement(void)
{
}


ImageEnhancement::~ImageEnhancement(void)
{
}

/*----------------------------
 * 功能 : 灰度对数变换
 *----------------------------
 * 函数 : mageEnhancement::LogarithmTran
 * 访问 : private 
 * 返回 : void
 *
 */
void ImageEnhancement::LogarithmTran(const Mat &src, Mat& dst, float fA, float fB, float fC) {
	CV_Assert(src.data);  

	// accept only char type matrices  
	CV_Assert(src.depth() != sizeof(uchar));  

	// build look up table  
	unsigned char lut[256];  
	for( int i = 0; i < 256; i++ )  
	{  
		lut[i] = saturate_cast<uchar>(fA + logf((float)i/255.0 + 1.0f) / (fC * logf(fB))* 255.0f); 
		//lut[i] = saturate_cast<uchar>(fC*pow((float)(i/255.0), fGamma) * 255.0f);  
	}  

	dst = src.clone();  
	const int channels = dst.channels();  
	switch(channels)  
	{  
	case 1:  
		{  

			MatIterator_<uchar> it, end;  
			for( it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++ )  
				//*it = pow((float)(((*it))/255.0), fGamma) * 255.0;  
				*it = lut[(*it)];  

			break;  
		}  
	case 3:   
		{  

			MatIterator_<Vec3b> it, end;  
			for( it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++ )  
			{  
				//(*it)[0] = pow((float)(((*it)[0])/255.0), fGamma) * 255.0;  
				//(*it)[1] = pow((float)(((*it)[1])/255.0), fGamma) * 255.0;  
				//(*it)[2] = pow((float)(((*it)[2])/255.0), fGamma) * 255.0;  
				(*it)[0] = lut[((*it)[0])];  
				(*it)[1] = lut[((*it)[1])];  
				(*it)[2] = lut[((*it)[2])];  
			}  

			break;  

		}  
	}  
}

/*----------------------------
 * 功能 : 减少传入图像的色阶，采用at方式循环,减少倍数为div(ww)
 *此方法缺点为不适合表示行与列坐标
 *----------------------------
 * 函数 : ImageBase::colorReduceWithIterator
 * 访问 : private 
 *
 */
void ImageEnhancement::GreyLineTran(const Mat &src, Mat& dst, float fA, float fB, float fC, float fD){
	dst = Scalar(0);

	//CGreyDlg dlg;
	//dlg.DoModal();

	double k, b;  
	k = (fD - fC)/(fB - fA);
	b = fC- fA*(fD - fC)/(fB - fA);

	int RowsNum = src.rows;  
	int ColsNum = src.cols;  
	Mat img(src.size(), src.type());  
	//进行遍历图像像素,对每个像素进行相应的线性变换  
	for (int i = 0; i < RowsNum; i++)  
	{  
		for (int j = 0; j < ColsNum; j++)  
		{  
			//c为遍历图像的三个通道  
			for (int c = 0; c < 3; c++)  
			{  
				//使用at操作符，防止越界  
				img.at<Vec3b>(i, j)[c] = saturate_cast<uchar>  
					(k* (src.at<Vec3b>(i, j)[c]-fA) + b);  
			}  
		}  
	} 
	dst = img;
}

/*----------------------------
* 功能 : 减少传入图像的色阶，采用Iterator方式循环,减少倍数为div(ww)
*此方法缺点为不适合表示行与列坐标
*----------------------------
* 函数 : ImageBase::colorReduceWithIterator
* 访问 : private 
*
*/
void ImageEnhancement::MyGammaCorrection(const Mat &src, Mat& dst, float fC, float fGamma){
	CV_Assert(src.data);  

	// accept only char type matrices  
	CV_Assert(src.depth() != sizeof(uchar));  

	// build look up table  
	unsigned char lut[256];  
	for( int i = 0; i < 256; i++ )  
	{  
		lut[i] = saturate_cast<uchar>(fC*pow((float)(i/255.0), fGamma) * 255.0f);  
	}  

	dst = src.clone();  
	const int channels = dst.channels();  
	switch(channels)  
	{  
	case 1:  
		{  

			MatIterator_<uchar> it, end;  
			for( it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++ )  
				//*it = pow((float)(((*it))/255.0), fGamma) * 255.0;  
				*it = lut[(*it)];  

			break;  
		}  
	case 3:   
		{  

			MatIterator_<Vec3b> it, end;  
			for( it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++ )  
			{  
				//(*it)[0] = pow((float)(((*it)[0])/255.0), fGamma) * 255.0;  
				//(*it)[1] = pow((float)(((*it)[1])/255.0), fGamma) * 255.0;  
				//(*it)[2] = pow((float)(((*it)[2])/255.0), fGamma) * 255.0;  
				(*it)[0] = lut[((*it)[0])];  
				(*it)[1] = lut[((*it)[1])];  
				(*it)[2] = lut[((*it)[2])];  
			}  

			break;  

		}  
	}  
}

Mat ImageEnhancement::EqualizeHist(Mat &image) {
	Mat img_gray;  
	//GRAY  
	if(image.channels()==3)  
	{  
		cvtColor(image, img_gray, CV_BGR2GRAY);  
	}  
	else  
	{  
		image.copyTo(img_gray);  
	}  

	MatND hist;       // 在cv中用CvHistogram *hist = cvCreateHist  
	int dims = 1;  
	float hranges[] = {0, 255};  
	const float *ranges[] = {hranges};   // 这里需要为const类型  
	int size = 256;  
	int channels = 0;  
	// 计算图像的直方图  
	calcHist(&img_gray, 1, &channels, Mat(), hist, dims, &size, ranges);    // cv 中是cvCalcHist  
	int scale = 1;  
	Mat imageShow(size * scale, size, CV_8U, Scalar(0));  
	// 获取最大值和最小值  
	double minVal = 0;  
	double maxVal = 0;  
	minMaxLoc(hist,&minVal, &maxVal, 0, 0);  //  cv中用的是cvGetMinMaxHistValue  
	//显示直方图的图像  
	int hpt = saturate_cast<int>(0.9 * size);  

	for(int i = 0; i < 256; i++)  
	{  
		float value = hist.at<float>(i);           //   注意hist中是float类型    cv中用cvQueryHistValue_1D  
		int realValue = saturate_cast<int>(value * hpt/maxVal);  
		rectangle(imageShow,Point(i*scale, size - 1), Point((i+1)*scale - 1, size - realValue), Scalar(255));  
	}  

	Mat equalize_Hist;  
	cv::equalizeHist(img_gray,equalize_Hist);  

	return equalize_Hist;
}

void ImageEnhancement::ExpGrayTransform(const Mat &src, Mat& dst, float fA, float fB, float fC) {
	CV_Assert(src.data);  

	// accept only char type matrices  
	CV_Assert(src.depth() != sizeof(uchar));  

	// build look up table  
	unsigned char lut[256];  
	for( int i = 0; i < 256; i++ )  
	{  
		lut[i] = saturate_cast<uchar>((pow(fB, fC*((float)((i-fA)/255.0)))-1.0f) * 255.0f); 
	}  

	dst = src.clone();  
	const int channels = dst.channels();  
	switch(channels)  
	{  
	case 1:  
		{  

			MatIterator_<uchar> it, end;  
			for( it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++ )  
				//*it = pow((float)(((*it))/255.0), fGamma) * 255.0;  
				*it = lut[(*it)];  

			break;  
		}  
	case 3:   
		{  

			MatIterator_<Vec3b> it, end;  
			for( it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++ )  
			{  
				//(*it)[0] = pow((float)(((*it)[0])/255.0), fGamma) * 255.0;  
				//(*it)[1] = pow((float)(((*it)[1])/255.0), fGamma) * 255.0;  
				//(*it)[2] = pow((float)(((*it)[2])/255.0), fGamma) * 255.0;  
				(*it)[0] = lut[((*it)[0])];  
				(*it)[1] = lut[((*it)[1])];  
				(*it)[2] = lut[((*it)[2])];  
			}  

			break;  

		}  
	}  
}

Mat ImageEnhancement::img_Hist(Mat& image) {
	Mat img_gray;  
	//GRAY  
	if(image.channels()==3)  
	{  
		cvtColor(image, img_gray, CV_BGR2GRAY);  
	}  
	else  
	{  
		image.copyTo(img_gray);  
	}  

	MatND hist;       // 在cv中用CvHistogram *hist = cvCreateHist  
	int dims = 1;  
	float hranges[] = {0, 255};  
	const float *ranges[] = {hranges};   // 这里需要为const类型  
	int size = 256;  
	int channels = 0;  
	// 计算图像的直方图  
	calcHist(&img_gray, 1, &channels, Mat(), hist, dims, &size, ranges);    // cv 中是cvCalcHist  
	int scale = 1;  
	Mat imageShow(size * scale, size, CV_8U, Scalar(0));  
	// 获取最大值和最小值  
	double minVal = 0;  
	double maxVal = 0;  
	//minMaxLoc(hist,&minVal, &maxVal, 0, 0);  //  cv中用的是cvGetMinMaxHistValue  
	//显示直方图的图像  
	int hpt = saturate_cast<int>(0.9 * size);  

	// 计算图像的直方图  
	calcHist(&image, 1, &channels, Mat(), hist, dims, &size, ranges);    // cv 中是cvCalcHist  
	Mat imageShow_equal(size * scale, size, CV_8U, Scalar(0));  
	// 获取最大值和最小值  
	minMaxLoc(hist,&minVal, &maxVal, 0, 0);  //  cv中用的是cvGetMinMaxHistValue  
	//显示直方图的图像  
	hpt = saturate_cast<int>(0.9 * size);  
	for(int i = 0; i < 256; i++)  
	{  
		float value = hist.at<float>(i);           //   注意hist中是float类型    cv中用cvQueryHistValue_1D  
		int realValue = saturate_cast<int>(value * hpt/maxVal);  
		rectangle(imageShow_equal,Point(i*scale, size - 1), Point((i+1)*scale - 1, size - realValue), Scalar(255));  
	}  

	return imageShow_equal;
}

//添加椒盐噪声
void ImageEnhancement::salt(cv::Mat &image, int n) {
	int i,j;  
	for (int k=0; k<n/2; k++) {  

		// rand() is the random number generator  
		i = std::rand()%image.cols; // % 整除取余数运算符,rand=1022,cols=1000,rand%cols=22  
		j = std::rand()%image.rows;   

		if (image.type() == CV_8UC1) { // gray-level image  

			image.at<uchar>(j,i)= 255; //at方法需要指定Mat变量返回值类型,如uchar等  

		} else if (image.type() == CV_8UC3) { // color image  

			image.at<cv::Vec3b>(j,i)[0]= 255; //cv::Vec3b为opencv定义的一个3个值的向量类型  
			image.at<cv::Vec3b>(j,i)[1]= 255; //[]指定通道，B:0，G:1，R:2  
			image.at<cv::Vec3b>(j,i)[2]= 255;   
		}  
	}  
}

//邻域平均
void ImageEnhancement::AverFiltering(const Mat &src,Mat &dst) {  //Box模板
	if (!src.data) 
		return;  
	Mat _dst(src.size(), src.type()); 
	//at访问像素点  
	for (int i = 1; i<src.rows; ++i)  
		for (int j = 1; j < src.cols; ++j) {  
			if ((i - 1 >= 0) && (j - 1) >= 0 && (i + 1)<src.rows && (j + 1)<src.cols) {//边缘不进行处理  
				_dst.at<Vec3b>(i, j)[0] = (src.at<Vec3b>(i, j)[0] + src.at<Vec3b>(i - 1, j - 1)[0] + src.at<Vec3b>(i - 1, j)[0] + src.at<Vec3b>(i, j - 1)[0] +  
					src.at<Vec3b>(i - 1, j + 1)[0] + src.at<Vec3b>(i + 1, j - 1)[0] + src.at<Vec3b>(i + 1, j + 1)[0] + src.at<Vec3b>(i, j + 1)[0] +  
					src.at<Vec3b>(i + 1, j)[0]) / 9;  
				_dst.at<Vec3b>(i, j)[1] = (src.at<Vec3b>(i, j)[1] + src.at<Vec3b>(i - 1, j - 1)[1] + src.at<Vec3b>(i - 1, j)[1] + src.at<Vec3b>(i, j - 1)[1] +  
					src.at<Vec3b>(i - 1, j + 1)[1] + src.at<Vec3b>(i + 1, j - 1)[1] + src.at<Vec3b>(i + 1, j + 1)[1] + src.at<Vec3b>(i, j + 1)[1] +  
					src.at<Vec3b>(i + 1, j)[1]) / 9;  
				_dst.at<Vec3b>(i, j)[2] = (src.at<Vec3b>(i, j)[2] + src.at<Vec3b>(i - 1, j - 1)[2] + src.at<Vec3b>(i - 1, j)[2] + src.at<Vec3b>(i, j - 1)[2] +  
					src.at<Vec3b>(i - 1, j + 1)[2] + src.at<Vec3b>(i + 1, j - 1)[2] + src.at<Vec3b>(i + 1, j + 1)[2] + src.at<Vec3b>(i, j + 1)[2] +  
					src.at<Vec3b>(i + 1, j)[2]) / 9;  
			}  
			else {//边缘赋值  
				_dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i, j)[0];  
				_dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i, j)[1];  
				_dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i, j)[2];  
			}  
		}  
		_dst.copyTo(dst);//拷贝 
} 

//求九个数的中值  
uchar ImageEnhancement::Median(uchar n1, uchar n2, uchar n3, uchar n4, uchar n5,  
	uchar n6, uchar n7, uchar n8, uchar n9) {  
		uchar arr[9];  
		arr[0] = n1;  
		arr[1] = n2;  
		arr[2] = n3;  
		arr[3] = n4;  
		arr[4] = n5;  
		arr[5] = n6;  
		arr[6] = n7;  
		arr[7] = n8;  
		arr[8] = n9;  
		for (int gap = 9 / 2; gap > 0; gap /= 2)//希尔排序  
			for (int i = gap; i < 9; ++i)  
				for (int j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap)  
					swap(arr[j], arr[j + gap]);  
		return arr[4];//返回中值  
} 

//中值滤波
void ImageEnhancement::MedianFlitering(const Mat &src, Mat &dst) {  
	if (!src.data)
		return;  
	Mat _dst(src.size(), src.type());  
	for(int i=0;i<src.rows;++i)  
		for (int j=0; j < src.cols; ++j) {  
			if ((i - 1) > 0 && (i + 1) < src.rows && (j - 1) > 0 && (j + 1) < src.cols) {  
				_dst.at<Vec3b>(i, j)[0] = Median(src.at<Vec3b>(i, j)[0], src.at<Vec3b>(i + 1, j + 1)[0],  
					src.at<Vec3b>(i + 1, j)[0], src.at<Vec3b>(i, j + 1)[0], src.at<Vec3b>(i + 1, j - 1)[0],  
					src.at<Vec3b>(i - 1, j + 1)[0], src.at<Vec3b>(i - 1, j)[0], src.at<Vec3b>(i, j - 1)[0],  
					src.at<Vec3b>(i - 1, j - 1)[0]);  
				_dst.at<Vec3b>(i, j)[1] = Median(src.at<Vec3b>(i, j)[1], src.at<Vec3b>(i + 1, j + 1)[1],  
					src.at<Vec3b>(i + 1, j)[1], src.at<Vec3b>(i, j + 1)[1], src.at<Vec3b>(i + 1, j - 1)[1],  
					src.at<Vec3b>(i - 1, j + 1)[1], src.at<Vec3b>(i - 1, j)[1], src.at<Vec3b>(i, j - 1)[1],  
					src.at<Vec3b>(i - 1, j - 1)[1]);  
				_dst.at<Vec3b>(i, j)[2] = Median(src.at<Vec3b>(i, j)[2], src.at<Vec3b>(i + 1, j + 1)[2],  
					src.at<Vec3b>(i + 1, j)[2], src.at<Vec3b>(i, j + 1)[2], src.at<Vec3b>(i + 1, j - 1)[2],  
					src.at<Vec3b>(i - 1, j + 1)[2], src.at<Vec3b>(i - 1, j)[2], src.at<Vec3b>(i, j - 1)[2],  
					src.at<Vec3b>(i - 1, j - 1)[2]);  
			}  
			else  
				_dst.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);  
		}  
		_dst.copyTo(dst);//拷贝  
} 