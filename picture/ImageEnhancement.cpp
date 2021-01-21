#include "StdAfx.h"
#include "ImageEnhancement.h"

ImageEnhancement::ImageEnhancement(void)
{
}


ImageEnhancement::~ImageEnhancement(void)
{
}

/*----------------------------
 * ���� : �Ҷȶ����任
 *----------------------------
 * ���� : mageEnhancement::LogarithmTran
 * ���� : private 
 * ���� : void
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
 * ���� : ���ٴ���ͼ���ɫ�ף�����at��ʽѭ��,���ٱ���Ϊdiv(ww)
 *�˷���ȱ��Ϊ���ʺϱ�ʾ����������
 *----------------------------
 * ���� : ImageBase::colorReduceWithIterator
 * ���� : private 
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
	//���б���ͼ������,��ÿ�����ؽ�����Ӧ�����Ա任  
	for (int i = 0; i < RowsNum; i++)  
	{  
		for (int j = 0; j < ColsNum; j++)  
		{  
			//cΪ����ͼ�������ͨ��  
			for (int c = 0; c < 3; c++)  
			{  
				//ʹ��at����������ֹԽ��  
				img.at<Vec3b>(i, j)[c] = saturate_cast<uchar>  
					(k* (src.at<Vec3b>(i, j)[c]-fA) + b);  
			}  
		}  
	} 
	dst = img;
}

/*----------------------------
* ���� : ���ٴ���ͼ���ɫ�ף�����Iterator��ʽѭ��,���ٱ���Ϊdiv(ww)
*�˷���ȱ��Ϊ���ʺϱ�ʾ����������
*----------------------------
* ���� : ImageBase::colorReduceWithIterator
* ���� : private 
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

	MatND hist;       // ��cv����CvHistogram *hist = cvCreateHist  
	int dims = 1;  
	float hranges[] = {0, 255};  
	const float *ranges[] = {hranges};   // ������ҪΪconst����  
	int size = 256;  
	int channels = 0;  
	// ����ͼ���ֱ��ͼ  
	calcHist(&img_gray, 1, &channels, Mat(), hist, dims, &size, ranges);    // cv ����cvCalcHist  
	int scale = 1;  
	Mat imageShow(size * scale, size, CV_8U, Scalar(0));  
	// ��ȡ���ֵ����Сֵ  
	double minVal = 0;  
	double maxVal = 0;  
	minMaxLoc(hist,&minVal, &maxVal, 0, 0);  //  cv���õ���cvGetMinMaxHistValue  
	//��ʾֱ��ͼ��ͼ��  
	int hpt = saturate_cast<int>(0.9 * size);  

	for(int i = 0; i < 256; i++)  
	{  
		float value = hist.at<float>(i);           //   ע��hist����float����    cv����cvQueryHistValue_1D  
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

	MatND hist;       // ��cv����CvHistogram *hist = cvCreateHist  
	int dims = 1;  
	float hranges[] = {0, 255};  
	const float *ranges[] = {hranges};   // ������ҪΪconst����  
	int size = 256;  
	int channels = 0;  
	// ����ͼ���ֱ��ͼ  
	calcHist(&img_gray, 1, &channels, Mat(), hist, dims, &size, ranges);    // cv ����cvCalcHist  
	int scale = 1;  
	Mat imageShow(size * scale, size, CV_8U, Scalar(0));  
	// ��ȡ���ֵ����Сֵ  
	double minVal = 0;  
	double maxVal = 0;  
	//minMaxLoc(hist,&minVal, &maxVal, 0, 0);  //  cv���õ���cvGetMinMaxHistValue  
	//��ʾֱ��ͼ��ͼ��  
	int hpt = saturate_cast<int>(0.9 * size);  

	// ����ͼ���ֱ��ͼ  
	calcHist(&image, 1, &channels, Mat(), hist, dims, &size, ranges);    // cv ����cvCalcHist  
	Mat imageShow_equal(size * scale, size, CV_8U, Scalar(0));  
	// ��ȡ���ֵ����Сֵ  
	minMaxLoc(hist,&minVal, &maxVal, 0, 0);  //  cv���õ���cvGetMinMaxHistValue  
	//��ʾֱ��ͼ��ͼ��  
	hpt = saturate_cast<int>(0.9 * size);  
	for(int i = 0; i < 256; i++)  
	{  
		float value = hist.at<float>(i);           //   ע��hist����float����    cv����cvQueryHistValue_1D  
		int realValue = saturate_cast<int>(value * hpt/maxVal);  
		rectangle(imageShow_equal,Point(i*scale, size - 1), Point((i+1)*scale - 1, size - realValue), Scalar(255));  
	}  

	return imageShow_equal;
}

//��ӽ�������
void ImageEnhancement::salt(cv::Mat &image, int n) {
	int i,j;  
	for (int k=0; k<n/2; k++) {  

		// rand() is the random number generator  
		i = std::rand()%image.cols; // % ����ȡ���������,rand=1022,cols=1000,rand%cols=22  
		j = std::rand()%image.rows;   

		if (image.type() == CV_8UC1) { // gray-level image  

			image.at<uchar>(j,i)= 255; //at������Ҫָ��Mat��������ֵ����,��uchar��  

		} else if (image.type() == CV_8UC3) { // color image  

			image.at<cv::Vec3b>(j,i)[0]= 255; //cv::Vec3bΪopencv�����һ��3��ֵ����������  
			image.at<cv::Vec3b>(j,i)[1]= 255; //[]ָ��ͨ����B:0��G:1��R:2  
			image.at<cv::Vec3b>(j,i)[2]= 255;   
		}  
	}  
}

//����ƽ��
void ImageEnhancement::AverFiltering(const Mat &src,Mat &dst) {  //Boxģ��
	if (!src.data) 
		return;  
	Mat _dst(src.size(), src.type()); 
	//at�������ص�  
	for (int i = 1; i<src.rows; ++i)  
		for (int j = 1; j < src.cols; ++j) {  
			if ((i - 1 >= 0) && (j - 1) >= 0 && (i + 1)<src.rows && (j + 1)<src.cols) {//��Ե�����д���  
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
			else {//��Ե��ֵ  
				_dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i, j)[0];  
				_dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i, j)[1];  
				_dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i, j)[2];  
			}  
		}  
		_dst.copyTo(dst);//���� 
} 

//��Ÿ�������ֵ  
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
		for (int gap = 9 / 2; gap > 0; gap /= 2)//ϣ������  
			for (int i = gap; i < 9; ++i)  
				for (int j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap)  
					swap(arr[j], arr[j + gap]);  
		return arr[4];//������ֵ  
} 

//��ֵ�˲�
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
		_dst.copyTo(dst);//����  
} 