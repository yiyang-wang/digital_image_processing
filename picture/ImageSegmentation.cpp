#include "StdAfx.h"
#include "ImageSegmentation.h"

ImageSegmentation::ImageSegmentation(void)
{
}


ImageSegmentation::~ImageSegmentation(void)
{
}


void ImageSegmentation::otsuGray(const Mat &src, Mat &dst){//�����ֵ
	Mat grayImg = Mat::zeros(src.rows,src.cols,CV_8U);
	cvtColor(src,dst,CV_BGR2GRAY);
	grayImg = dst.clone();

	int T = 0; //�����ֵ  
	int height = grayImg.rows;  
	int width = grayImg.cols;      
	uchar* data  = grayImg.data;  
	float gSum0; //��һ��Ҷ���ֵ  
	float gSum1; //�ڶ���Ҷ���ֵ  
	float N0 = 0; //ǰ��������  
	float N1 = 0; //����������  
	float u0 = 0; //ǰ������ƽ���Ҷ�  
	float u1 = 0; //��������ƽ���Ҷ�  
	float w0 = 0; //ǰ�����ص���ռ����ͼ��ı���Ϊ��0  
	float w1 = 0; //�������ص���ռ����ͼ��ı���Ϊ��1  
	float u = 0; //��ƽ���Ҷ�
	//��䷽�ʽ��g=��0(��0-��)^2+��1(��1-��)^2==��0��1(��0-��1)^2
	float tempg = 0; //��ʱ��䷽��  
	float g = 0; //��䷽��
	int Histogram[256] = {0}; //�Ҷ�ֱ��ͼ  
	int N = width*height; //��������

	//����ֱ��ͼ 
	for(int i = 0;i < height;i++)  {  
		for(int j = 0;j < width;j++)  {  
			double temp = data[i*grayImg.step + j * 3] * 0.114 
				+ data[i*grayImg.step + j * 3+1] * 0.587 + data[i*grayImg.step + j * 3+2] * 0.299;
			//�Ҷ�ֵ��ʽ��gray = 0.114*B + 0.587*G + 0.299*R,RGBΪ���ص������ͨ��������ֵ
			temp = temp < 0?  0:temp;  
			temp = temp > 255?  255:temp;  
			Histogram[(int)temp]++;  //ĳһ�Ҷ�ֵ�ĸ���
		}   
	}  

	//������ֵ  
	for (int i = 0;i < 256;i++)  {  
		gSum0 = 0;  
		gSum1 = 0;  
		N0 += Histogram[i]; //ǰ�����ظ���          
		N1 = N-N0; //�������ظ��� 
		if(N0 == 0)    break; //������ǰ�������ص�ʱ������ѭ��  
		w0 = N0/N;  
		w1 = 1-w0;  
		for (int j = 0;j <= i;j++){
			gSum0 += j*Histogram[j];  //ǰ���Ҷ���ֵ  
		}  
		u0 = gSum0/N0;  
		for(int k = i+1;k<256;k++){  
			gSum1 += k*Histogram[k];  //�����Ҷ���ֵ
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


void ImageSegmentation::connectedDomain(cv::Mat &inputImage, cv::Mat &outputImage){//��ͨ�����
	int count = 0;
	Mat Image;
	//���ô����ֵ�ָͼ��ָ�ɱ�����Ŀ��
	otsuGray(inputImage,outputImage);
	Image = outputImage.clone();
	Vector<Point> vector;
	for(int i = 0;i<outputImage.rows;i++){
		for(int j = 0;j<outputImage.cols;j++){
			//����õ���Ŀ��������ջ
			if(*(outputImage.data + i*outputImage.cols +j) == 255){
				count ++;

				Point a;
				a.x =i;
				a.y = j;
				vector.push_back(a);
				*(outputImage.data + i*outputImage.cols + j) = 0;
				//������ͨ��
				while(!vector.empty()){
					//��ջ
					Point b = vector.back();
					vector.pop_back();
					for(int m = -1;m<=1;m++){
						for(int n = -1;n<=1;n++){
							//���Ŀ���������Ƿ���Ŀ������ĵ�
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
	CString words= "��ͼ����ͨ��ĸ���Ϊ: " + str;

	AfxMessageBox(words);

	outputImage = Image.clone();

}



Mat Histogarm(cv::Mat &image){
	MatND hist;       // ��cv����CvHistogram *hist = cvCreateHist  
	int dims = 1;  
	float hranges[] = {0, 255};  
	const float *ranges[] = {hranges};   // ������ҪΪconst����  
	int size = 256;  
	int channels = 0;  
	// ����ͼ���ֱ��ͼ  
	calcHist(&image, 1, &channels, Mat(), hist, dims, &size, ranges);    // cv ����cvCalcHist  
	int scale = 1;  
	Mat imageShow(size * scale, size, CV_8U, Scalar(0));  
	// ��ȡ���ֵ����Сֵ  
	double minVal = 0;  
	double maxVal = 0;  
	minMaxLoc(hist,&minVal, &maxVal, 0, 0);  //  cv���õ���cvGetMinMaxHistValue  
	//��ʾֱ��ͼ��ͼ��  
	int hpt = saturate_cast<int>(0.9 * size);     
	for(int i = 0; i < 256; i++)  {  
		float value = hist.at<float>(i);           //   ע��hist����float����    cv����cvQueryHistValue_1D  
		int realValue = saturate_cast<int>(value * hpt/maxVal);  
		line(imageShow, Point(i, size - 1), Point(i, size - realValue), Scalar(255));  
		//rectangle(imageShow,Point(i*scale, size - 1), Point((i+1)*scale - 1, size - realValue), Scalar(255));  
	}  
	return imageShow;
}


void ImageSegmentation::minThreshold(Mat &src, Mat &dst){//����ʽ��ֵ
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

void ImageSegmentation::edgeDetection(const Mat &src, Mat &dst) {//��Ե���
	Canny(src, dst, 50, 150, 3, false);
}


void ImageSegmentation::hough(Mat &src, Mat &dst) { //����任ֱ�߼��
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