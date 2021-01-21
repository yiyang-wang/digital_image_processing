#include "StdAfx.h"
#include "ImageFeatures.h"

ImageFeatures::ImageFeatures(void)
{
}


ImageFeatures::~ImageFeatures(void)
{
}


void ImageFeatures::centroidDetection(const Mat& src, Mat& dst) {//质心检测 
	ImageSegmentation seg;
	seg.otsuGray(src, dst);
	int rows = dst.rows;
	int cols = dst.cols;
	int xSum = 0;
	int ySum = 0;
	double ave_x = 0;
	double ave_y = 0;
	double num = 0;
	Mat Image = dst.clone();
	Vector<Point>vector;
	Vector<Point>centroid;

	for(int i = 0; i < rows; i++)
	{	
		for(int j = 0; j < cols; j++)
		{
			if(Image.at<uchar>(i,j) == 255)
			{
				vector.push_back(Point(i,j));
				Image.at<uchar>(i,j) = 0;
				//生长连通域
				while(!vector.empty())
				{
					Point p = vector.back();
					xSum += p.x;
					ySum += p.y;
					num ++;
					vector.pop_back();

					for(int m = -1; m <= 1; m++){
						for(int n = -1; n <= 1; n++)
						{
							//检测目标区域八连通域是否有目标点
							if((p.x + m) >= 0 && (p.x +m) < rows
								&& (p.y + n) >= 0 && (p.y + n) < cols
								&& (Image.at<uchar>(p.x + m, p.y + n) == 255)){

									Point q;
									q.x = p.x + m;
									q.y = p.y + n;
									vector.push_back(q);
									Image.at<uchar>(q.x, q.y) = 0;
							}
						}
					}
				}
				ave_x = xSum / num;
				ave_y = ySum / num;
				centroid.push_back(Point(ave_x, ave_y));
				num = 0;
				xSum = 0;
				ySum = 0;
			}
		}
	}

	for(int i = 0; i < centroid.size(); i++)
	{
		Point p = centroid[i];
		dst.at<uchar>(p.x, p.y) = 0;
	}

	/*Mat src_gray; 
	int thresh = 30; 
	int max_thresh = 255; 

	cvtColor( src, src_gray, CV_BGR2GRAY );//灰度化 	
	GaussianBlur( src, src, Size(3,3), 0.1, 0, BORDER_DEFAULT ); 	
	blur( src_gray, src_gray, Size(3,3) ); //滤波 	
	//定义Canny边缘检测图像 	
	Mat canny_output; 	
	vector<vector<Point> > contours; 	
	vector<Vec4i> hierarchy; 	
	//利用canny算法检测边缘 	
	Canny( src_gray, canny_output, thresh, thresh*3, 3 ); 	
	//查找轮廓 	
	findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) ); 	
	//计算轮廓矩 	
	vector<Moments> mu(contours.size() ); 	
	for( int i = 0; i < contours.size(); i++ ) 	
	{ 
	mu[i] = moments( contours[i], false ); 
	} 	
	//计算轮廓的质心 	
	vector<Point2f> mc( contours.size() ); 	
	for( int i = 0; i < contours.size(); i++ ) 	
	{ 
	mc[i] = Point2d( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); 
	}  	
	//画轮廓及其质心并显示 	
	Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 ); 		
	for( int i = 0; i< contours.size(); i++ ) 	
	{ 		
	Scalar color = Scalar( 255, 0, 0); 		
	drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() ); 		
	circle( drawing, mc[i], 5, Scalar( 0, 0, 255), -1, 8, 0 );		 		
	rectangle(drawing, boundingRect(contours.at(i)), cvScalar(0,255,0)); 			
	char tam[100]; 
	sprintf(tam, "(%0.0f,%0.0f)",mc[i].x,mc[i].y); 
	putText(drawing, tam, Point(mc[i].x, mc[i].y), FONT_HERSHEY_SIMPLEX, 0.4, cvScalar(255,0,255),1); 	
	}	
	dst = drawing;*/
}


void ImageFeatures::connectedArea(Mat &inputImage, Mat &outputImage){//连通域面积计算
	int count = 0;
	int array[100] = {0};//存储每个连通域的像素个数
	Mat Image;
	//利用大津阈值分割将图像分割成背景和目标
	obj_Segmentation.otsuGray(inputImage,outputImage);
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
					array[count]++;//像素计数
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
	CString str[100];
	char buffer[10];
	CString words;
	for(int i = 1; i <= count; i++) {
		sprintf_s(buffer,"%d",array[i]);
		str[i] = buffer;
		CString word1 = "个连通域的面积为:" + str[i];
		CString word2;
		word2.Format(_T("%d"),i);
		CString word3 = "第" + word2 + word1;
		words += word3 + "\r\n";
	}
	AfxMessageBox(words);

	outputImage = Image.clone();

}



void ImageFeatures::connectedPerimeter(Mat &inputImage, Mat &outputImage) {//连通域周长计算
	int count = 0;
	int array[100] = {0};//存储每个连通域的像素个数
	Mat Image;
	//利用大津阈值分割将图像分割成背景和目标
	obj_Segmentation.otsuGray(inputImage,Image);
	obj_Segmentation.edgeDetection(Image, outputImage);
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
					array[count]++;//像素计数
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
	CString str[100];
	char buffer[10];
	CString words;
	for(int i = 1; i <= count; i++) {
		sprintf_s(buffer,"%d",array[i]);
		str[i] = buffer;
		CString word1 = "个连通域的周长为:" + str[i];
		CString word2;
		word2.Format(_T("%d"),i);
		CString word3 = "第" + word2 + word1;
		words += word3 + "\r\n";
	}
	AfxMessageBox(words);
	/*CString str[100];
	char buffer[10];
	for(int i = 1; i <= count; i++) {
		sprintf_s(buffer,"%d",array[i]);
		str[i] = buffer;
		CString words= "连通域的周长为: " + str[i];
		AfxMessageBox(words);
	}*/

	outputImage = Image.clone();
}


void ImageFeatures::myRectangle(Mat &src, Mat &dst) {//矩形度
	int rows = src.rows;
	int cols = src.cols;
	int hypotenuse = sqrt(double(rows*rows+cols*cols));
	Mat mid = Mat::zeros(hypotenuse,hypotenuse,CV_8U);

	for(int i = (hypotenuse-rows)/2; i<(hypotenuse+rows)/2; i++) {
		for(int j = (hypotenuse-cols)/2; j<(hypotenuse+cols)/2; j++) {
			mid.at<uchar>(i,j) = src.at<uchar>(i-(hypotenuse-rows)/2,j-(hypotenuse-cols)/2);
		}
	}

	int s = 0;
	for(int i = 0; i<hypotenuse; i++) {
		for(int j = 0; j<hypotenuse; j++) {
			if(mid.at<uchar>(i,j) == 255) {
				s++;	
			}
		}
	}

	int sMin = hypotenuse*hypotenuse;
	int angle = 0;
	int x1;
	int y1;
	int x2;
	int y2;
	for(int k = 1; k<=30; k++) {
		geometry_Trans.warpFfine(mid, dst ,(int)hypotenuse/2, (int)hypotenuse/2, 3*k);//每次旋转3度
		int xMin = hypotenuse;
		int yMin = hypotenuse;
		int xMax = 0;
		int yMax = 0;
		for(int i = 0; i<hypotenuse; i++) {
			for(int j = 0; j<hypotenuse; j++) {
				if(dst.at<uchar>(i,j) == 255) {
					if(xMin > j)
						xMin = j;
					if(yMin > i)
						yMin = i;
					if(xMax < j)
						xMax = j;
					if(yMax <i)
						yMax = i;
				}
			}
		}

		if(abs(xMax-xMin)*abs(yMax-yMin) < sMin) {
			sMin = abs(xMax-xMin)*abs(yMax-yMin);
			angle = 3*k;
			x1 = xMax;
			y1 = yMax;
			x2 = xMin;
			y2 = yMin;
		}
	}

	geometry_Trans.warpFfine(mid, dst ,(int)hypotenuse/2, (int)hypotenuse/2, angle);//让图像转到最小外接矩阵产生时
	cv::rectangle(dst,cvPoint(x1,y1),cvPoint(x2,y2),Scalar(255,255,255),1,1,0); //打上矩形框

	Mat a = dst.clone();
	geometry_Trans.warpFfine(a, dst ,(int)hypotenuse/2, (int)hypotenuse/2, -angle);//矩形和原图一起转回

	Mat b = Mat::zeros(rows,cols,src.type());
	for(int i = 0; i<rows; i++) {
		for(int j = 0; j<cols; j++) {
			b.at<uchar>(i,j) = dst.at<uchar>(i+(hypotenuse-rows)/2,j+(hypotenuse-cols)/2);
		}
	}
	dst = b.clone();

	float x = s*1.0/sMin;
	CString str;
	char buffer[10];
	sprintf_s(buffer,"%.2f",x);
	str = buffer;
	CString words= "矩形度为: " + str;
	AfxMessageBox(words);
}


void ImageFeatures::myCircle(Mat &src, Mat &dst) {//圆形度
	int rows = src.rows;
	int cols = src.cols;
	int hypotenuse = sqrt(double(rows*rows+cols*cols));
	Mat mid = Mat::zeros(hypotenuse,hypotenuse,CV_8U);

	for(int i = (hypotenuse-rows)/2; i<(hypotenuse+rows)/2; i++) {
		for(int j = (hypotenuse-cols)/2; j<(hypotenuse+cols)/2; j++) {
			mid.at<uchar>(i,j) = src.at<uchar>(i-(hypotenuse-rows)/2,j-(hypotenuse-cols)/2);
		}
	}

	int s = 0;
	for(int i = 0; i<hypotenuse; i++) {
		for(int j = 0; j<hypotenuse; j++) {
			if(mid.at<uchar>(i,j) == 255) {
				s++;	
			}
		}
	}

	int sMin = hypotenuse*hypotenuse;
	int angle = 0;
	int x1;
	int y1;
	int x2;
	int y2;
	for(int k = 1; k<=30; k++) {
		geometry_Trans.warpFfine(mid, dst ,(int)hypotenuse/2, (int)hypotenuse/2, 3*k);
		int xMin = hypotenuse;
		int yMin = hypotenuse;
		int xMax = 0;
		int yMax = 0;
		for(int i = 0; i<hypotenuse; i++) {
			for(int j = 0; j<hypotenuse; j++) {
				if(dst.at<uchar>(i,j) == 255) {
					if(xMin > j)
						xMin = j;
					if(yMin > i)
						yMin = i;
					if(xMax < j)
						xMax = j;
					if(yMax <i)
						yMax = i;
				}
			}
		}

		if(abs(xMax-xMin)*abs(yMax-yMin) < sMin) {
			sMin = abs(xMax-xMin)*abs(yMax-yMin);
			angle = 3*k;
			x1 = xMax;
			y1 = yMax;
			x2 = xMin;
			y2 = yMin;
		}
	}

	geometry_Trans.warpFfine(mid, dst ,(int)hypotenuse/2, (int)hypotenuse/2, angle);
	cv::circle(dst,cvPoint((x1+x2)/2,(y1+y2)/2),sqrt(double((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)))/2.0,Scalar(255,255,255),1,1,0); 

	Mat a = dst.clone();
	geometry_Trans.warpFfine(a, dst ,(int)hypotenuse/2, (int)hypotenuse/2, -angle);

	Mat b = Mat::zeros(rows,cols,src.type());
	for(int i = 0; i<rows; i++) {
		for(int j = 0; j<cols; j++) {
			b.at<uchar>(i,j) = dst.at<uchar>(i+(hypotenuse-rows)/2,j+(hypotenuse-cols)/2);
		}
	}
	dst = b.clone();

	sMin = PI*double((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))/4.0;
	float x = s*1.0/sMin;
	CString str;
	char buffer[10];
	sprintf_s(buffer,"%.2f",x);
	str = buffer;
	CString words= "圆形度为: " + str;
	AfxMessageBox(words);
}


//模板匹配
void ImageFeatures::templateMatching(const Mat& src, Mat& mid, Mat& dst) {
	int rows=src.rows;
	int cols=src.cols;
	//dst=Mat::zeros(src.size(),src.type());
	dst = src;
	double a, temp = 10000;
	int x = 0,y = 0;
	//Vec<uchar,3> a[src.rows-mid.rows][src.cols-mid.cols];
	for(int i=0;i<src.rows-mid.rows;i++){
		for(int j=0;j<src.cols-mid.cols;j++){
			a = 0;
			for(int m=0;m<mid.rows;m++){
				for(int n=0;n<mid.cols;n++){
					//a(i,j) = src.at<Vec3b>(m+i,n+j)-mid.at<Vec3b>(m,n);
					a += abs(src.at<uchar>(m+i,n+j)-mid.at<uchar>(m,n));
				}
			}
			if(a < temp) {
				temp = a;
				y = i;
				x = j;
			};
		}
	}

	if(temp < 10000) {
		for (int i = y; i<y+mid.rows; i++) {
			dst.at<uchar>(i,x) = 255;
			dst.at<uchar>(i,x+mid.cols*dst.channels()) = 255;
			dst.at<uchar>(i,x+1) = 255;
			dst.at<uchar>(i,x+mid.cols*dst.channels()-1) = 255;
		}
		for(int j = x; j<x+mid.cols*dst.channels(); j++) {
			dst.at<uchar>(y,j) = 255;
			dst.at<uchar>(y+mid.rows,j) = 255;
			dst.at<uchar>(y+1,j) = 255;
			dst.at<uchar>(y+mid.rows-1,j) = 255;
		}
	}

	else {
		CString words= "未匹配成功！";
		AfxMessageBox(words);
	}

}

void ImageFeatures::minMatrix(Mat &src, Mat &dst) {//最小外接矩阵
	int rows = src.rows;
	int cols = src.cols;
	int hypotenuse = sqrt(double(rows*rows+cols*cols));
	Mat mid = Mat::zeros(hypotenuse,hypotenuse,CV_8U);

	for(int i = (hypotenuse-rows)/2; i<(hypotenuse+rows)/2; i++) {
		for(int j = (hypotenuse-cols)/2; j<(hypotenuse+cols)/2; j++) {
			mid.at<uchar>(i,j) = src.at<uchar>(i-(hypotenuse-rows)/2,j-(hypotenuse-cols)/2);
		}
	}

	int sMin = hypotenuse*hypotenuse;
	int angle = 0;
	int x1;
	int y1;
	int x2;
	int y2;
	for(int k = 1; k<=30; k++) {
		geometry_Trans.warpFfine(mid, dst ,(int)hypotenuse/2, (int)hypotenuse/2, 3*k);
		int xMin = hypotenuse;
		int yMin = hypotenuse;
		int xMax = 0;
		int yMax = 0;
		for(int i = 0; i<hypotenuse; i++) {
			for(int j = 0; j<hypotenuse; j++) {
				if(dst.at<uchar>(i,j) == 255) {
					if(xMin > j)
						xMin = j;
					if(yMin > i)
						yMin = i;
					if(xMax < j)
						xMax = j;
					if(yMax <i)
						yMax = i;
				}
			}
		}

		if(abs(xMax-xMin)*abs(yMax-yMin) < sMin) {
			sMin = abs(xMax-xMin)*abs(yMax-yMin);
			angle = 3*k;
			x1 = xMax;
			y1 = yMax;
			x2 = xMin;
			y2 = yMin;
		}
	}

	geometry_Trans.warpFfine(mid, dst ,(int)hypotenuse/2, (int)hypotenuse/2, angle);
	cv::rectangle(dst,cvPoint(x1,y1),cvPoint(x2,y2),Scalar(255,255,255),1,1,0); 

	Mat a = dst.clone();
	geometry_Trans.warpFfine(a, dst ,(int)hypotenuse/2, (int)hypotenuse/2, -angle);

	Mat b = Mat::zeros(rows,cols,src.type());
	for(int i = 0; i<rows; i++) {
		for(int j = 0; j<cols; j++) {
			b.at<uchar>(i,j) = dst.at<uchar>(i+(hypotenuse-rows)/2,j+(hypotenuse-cols)/2);
		}
	}
	dst = b.clone();
}