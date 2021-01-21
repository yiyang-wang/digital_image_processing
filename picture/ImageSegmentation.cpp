#include "StdAfx.h"
#include "ImageSegmentation.h"

ImageSegmentation::ImageSegmentation(void)
{
}


ImageSegmentation::~ImageSegmentation(void)
{
}


void ImageSegmentation::otsuGray(const Mat &src, Mat &dst){//大津阈值
	Mat grayImg = Mat::zeros(src.rows,src.cols,CV_8U);
	cvtColor(src,dst,CV_BGR2GRAY);
	grayImg = dst.clone();

	int T = 0; //最大阈值  
	int height = grayImg.rows;  
	int width = grayImg.cols;      
	uchar* data  = grayImg.data;  
	float gSum0; //第一类灰度总值  
	float gSum1; //第二类灰度总值  
	float N0 = 0; //前景像素数  
	float N1 = 0; //背景像素数  
	float u0 = 0; //前景像素平均灰度  
	float u1 = 0; //背景像素平均灰度  
	float w0 = 0; //前景像素点数占整幅图像的比例为ω0  
	float w1 = 0; //背景像素点数占整幅图像的比例为ω1  
	float u = 0; //总平均灰度
	//类间方差公式：g=ω0(μ0-μ)^2+ω1(μ1-μ)^2==ω0ω1(μ0-μ1)^2
	float tempg = 0; //临时类间方差  
	float g = 0; //类间方差
	int Histogram[256] = {0}; //灰度直方图  
	int N = width*height; //总像素数

	//计算直方图 
	for(int i = 0;i < height;i++)  {  
		for(int j = 0;j < width;j++)  {  
			double temp = data[i*grayImg.step + j * 3] * 0.114 
				+ data[i*grayImg.step + j * 3+1] * 0.587 + data[i*grayImg.step + j * 3+2] * 0.299;
			//灰度值公式：gray = 0.114*B + 0.587*G + 0.299*R,RGB为像素点的三个通道的像素值
			temp = temp < 0?  0:temp;  
			temp = temp > 255?  255:temp;  
			Histogram[(int)temp]++;  //某一灰度值的个数
		}   
	}  

	//计算阈值  
	for (int i = 0;i < 256;i++)  {  
		gSum0 = 0;  
		gSum1 = 0;  
		N0 += Histogram[i]; //前景像素个数          
		N1 = N-N0; //背景像素个数 
		if(N0 == 0)    break; //当出现前景无像素点时，跳出循环  
		w0 = N0/N;  
		w1 = 1-w0;  
		for (int j = 0;j <= i;j++){
			gSum0 += j*Histogram[j];  //前景灰度总值  
		}  
		u0 = gSum0/N0;  
		for(int k = i+1;k<256;k++){  
			gSum1 += k*Histogram[k];  //背景灰度总值
		}  
		u1 = gSum1/N1;  
		//u = w0*u0 + w1*u1;  
		g = w0*w1*(u0-u1)*(u0-u1);  
		if (g > tempg){  
			tempg = g;  
			T = i;  
		}  
	} 

	for(int i = 0;i < dst.rows;i++){
		for(int j = 0;j < src.cols;j++){
			if(*(grayImg.data + i*grayImg.cols + j) < T)
				*(dst.data + i*dst.cols + j) = 0;
			else
				*(dst.data + i*dst.cols + j) = 255;
		}
	}

}


void ImageSegmentation::connectedDomain(cv::Mat &inputImage, cv::Mat &outputImage){//连通域计数
	int count = 0;
	Mat Image;
	//利用大津阈值分割将图像分割成背景和目标
	otsuGray(inputImage,outputImage);
	Image = outputImage.clone();
	Vector<Point> vector;
	for(int i = 0;i<outputImage.rows;i++){
		for(int j = 0;j<outputImage.cols;j++){
			//如果该点是目标区域，入栈
			if(*(outputImage.data + i*outputImage.cols +j) == 255){
				count ++;

				Point a;
				a.x =i;
				a.y = j;
				vector.push_back(a);
				*(outputImage.data + i*outputImage.cols + j) = 0;
				//生长连通域
				while(!vector.empty()){
					//出栈
					Point b = vector.back();
					vector.pop_back();
					for(int m = -1;m<=1;m++){
						for(int n = -1;n<=1;n++){
							//检测目标点八领域是否有目标区域的点
							if( (b.x +m)>=0 && (b.x + m)<outputImage.rows
								&& (n + b.y)>=0 && (n + b.y)<outputImage.cols
								&& *(outputImage.data + (b.x +m)*outputImage.cols + n + b.y) == 255){

									Point c;
									c.x =b.x +m;
									c.y =n + b.y;
									vector.push_back(c);
									*(outputImage.data + (b.x +m)*outputImage.cols + n + b.y)=0;
							}
						}
					}

				}
			}

		}
	}
	CString str;
	char buffer[10];
	sprintf_s(buffer,"%d",count);
	str = buffer;
	CString words= "该图像连通域的个数为: " + str;

	AfxMessageBox(words);

	outputImage = Image.clone();

}



Mat Histogarm(cv::Mat &image){
	MatND hist;       // 在cv中用CvHistogram *hist = cvCreateHist  
	int dims = 1;  
	float hranges[] = {0, 255};  
	const float *ranges[] = {hranges};   // 这里需要为const类型  
	int size = 256;  
	int channels = 0;  
	// 计算图像的直方图  
	calcHist(&image, 1, &channels, Mat(), hist, dims, &size, ranges);    // cv 中是cvCalcHist  
	int scale = 1;  
	Mat imageShow(size * scale, size, CV_8U, Scalar(0));  
	// 获取最大值和最小值  
	double minVal = 0;  
	double maxVal = 0;  
	minMaxLoc(hist,&minVal, &maxVal, 0, 0);  //  cv中用的是cvGetMinMaxHistValue  
	//显示直方图的图像  
	int hpt = saturate_cast<int>(0.9 * size);     
	for(int i = 0; i < 256; i++)  {  
		float value = hist.at<float>(i);           //   注意hist中是float类型    cv中用cvQueryHistValue_1D  
		int realValue = saturate_cast<int>(value * hpt/maxVal);  
		line(imageShow, Point(i, size - 1), Point(i, size - realValue), Scalar(255));  
		//rectangle(imageShow,Point(i*scale, size - 1), Point((i+1)*scale - 1, size - realValue), Scalar(255));  
	}  
	return imageShow;
}


void ImageSegmentation::minThreshold(Mat &src, Mat &dst){//交互式阈值
	Mat grayImg = Mat::zeros(src.rows,src.cols,CV_8U);
	cvtColor(src,dst,CV_BGR2GRAY);
	grayImg = dst.clone();

	CMinThresholdDlg dlg;
	dlg.m_image = dst.clone();
	dlg.m_histogram = Histogarm(grayImg);
	if(dlg.DoModal() == IDOK){
		for(int i = 0;i < src.rows;i++){
			for(int j = 0;j < src.cols;j++){
				if(*(grayImg.data + i*grayImg.cols + j) < dlg.m_display)
					*(dst.data + i*dst.cols + j) = 0;
				else
					*(dst.data + i*dst.cols + j) = 255;
			}
		}

	}
}

void ImageSegmentation::edgeDetection(const Mat &src, Mat &dst) {//边缘检测
	Canny(src, dst, 50, 150, 3, false);
}


void ImageSegmentation::hough(Mat &src, Mat &dst) { //哈夫变换直线检测
	Canny(src, src, 50, 150, 3, false);
	int rows = src.rows;
	int cols = src.cols;
	int n = int(sqrt(double(src.rows*src.rows+src.cols*src.cols)));
	int theta = 0;
	int rho = 0;
	dst = Mat::zeros(181,n+1,CV_8U);
	
	for(int i = 0; i<rows; i++) {
		for(int j = 0; j<cols; j++) {
			if(src.at<uchar>(i,j) == 255) {
				for(theta = -90; theta<=90; theta++) {
					rho = int(j*cos(theta/180.0*PI) + i*sin(theta/180.0*PI));
					for(int k = 0; k <= n; k++) {
						if(rho == k) {
							if(dst.at<uchar>(theta+90,rho) <= 255) {
								dst.at<uchar>(theta+90,rho)++;
							}
						}
					}
				}
			}
		}
	}
}