#include "StdAfx.h"
#include "ImageMathematicalMorphology.h"

ImageMathematicalMorphology::ImageMathematicalMorphology(void)
{
}


ImageMathematicalMorphology::~ImageMathematicalMorphology(void)
{
}


//膨胀
void ImageMathematicalMorphology::twoValueDilate(const Mat &src, Mat &dst, int a[5][5]) {
	//将输入图像二值化
	Mat grayImg(src.size(),CV_8U);
	cvtColor(src,grayImg,CV_BGR2GRAY);
	Mat binaryImg(grayImg.size(),grayImg.type());
	threshold(grayImg,binaryImg,100,255,THRESH_BINARY);

	dst =Mat::zeros(src.rows,src.cols,CV_8U);

	int judge;
	for(int i=0; i<binaryImg.rows; i++) {
		for(int j=0; j<binaryImg.cols; j++){
			judge = 0;
			for(int m = 2; m >= -2; m--){
				for(int n = 2; n >= -2; n--){
					if(a[m+2][n+2]){
						if(*(binaryImg.data + (i+m)* binaryImg.step + j+n)==255){
							judge = 1;
						}
					}
				}
			}

			if(judge)
				*(dst.data + i* dst.step + j) = 255;
			else
				*(dst.data + i* dst.step + j) = 0;
		}
	}
}


//腐蚀
void ImageMathematicalMorphology::twoValueErode(const Mat &src, Mat &dst, int a[5][5]) {
	//将输入图像二值化
	Mat grayImg(src.size(),CV_8U);
	cvtColor(src,grayImg,CV_BGR2GRAY);
	Mat binaryImg(grayImg.size(),grayImg.type());
	threshold(grayImg,binaryImg,100,255,THRESH_BINARY);

	dst =Mat::zeros(src.rows,src.cols,CV_8U);

	int judge;
	for(int i = 2; i < binaryImg.rows - 2; i++){
		for(int j = 2; j < binaryImg.cols - 2; j++){
			judge = 1;
			for(int m = -2; m <= 2; m++){
				for(int n = -2; n <= 2; n++){
					if(a[m+2][n+2]){
						if(*(binaryImg.data + (i+m)* binaryImg.step + j+n) == 0){//step 为图象像素行的实际宽度
							judge = 0;
						}
					}
				}
			}

			if(judge)
				*(dst.data + i* dst.step + j) = 255;
			else
				*(dst.data + i* dst.step + j) = 0;
		}
	}
}


//开运算
void ImageMathematicalMorphology::twoValueOpenOperation(const Mat &src, Mat &dst, int a[5][5]) {
	//将输入图像二值化
	Mat grayImg(src.size(),CV_8U);
	cvtColor(src,grayImg,CV_BGR2GRAY);
	Mat binaryImg(grayImg.size(),grayImg.type());
	threshold(grayImg,binaryImg,100,255,THRESH_BINARY);
	//inputImage = binaryImg.clone();
	dst =Mat::zeros(src.rows,src.cols,CV_8U);

	int judge;
	for(int i = 2; i < binaryImg.rows - 2; i++){
		for(int j = 2; j < binaryImg.cols - 2; j++){
			judge = 1;
			for(int m = -2; m <= 2; m++){
				for(int n = -2; n <= 2; n++){
					if(a[m+2][n+2]){
						if(!*(binaryImg.data + (i+m)* binaryImg.step + j+n)){
							judge = 0;
						}
					}
				}
			}

			if(judge)
				*(dst.data + i* dst.step + j) = 255;
			else
				*(dst.data + i* dst.step + j) = 0;
		}
	}

	Mat Image = dst.clone();
	for(int i=0; i<Image.rows; i++) {
		for(int j=0; j<Image.cols; j++){
			judge = 0;
			for(int m = -2; m <= 2; m++){
				for(int n = -2; n <= 2; n++){
					if(a[m+2][n+2]){
						if(*(Image.data + (i+m)* Image.step + j+n)==255){
							judge = 1;
						}
					}
				}
			}

			if(judge)
				*(dst.data + i* dst.step + j) = 255;
			else
				*(dst.data + i* dst.step + j) = 0;
		}
	}
}

//闭运算
void ImageMathematicalMorphology::twoValueCloseOperation(const Mat &src, Mat &dst, int a[5][5]) {
	//将输入图像二值化
	Mat grayImg(src.size(),CV_8U);
	cvtColor(src,grayImg,CV_BGR2GRAY);
	Mat binaryImg(grayImg.size(),grayImg.type());
	threshold(grayImg,binaryImg,100,255,THRESH_BINARY);

	dst =Mat::zeros(src.rows,src.cols,CV_8U);

	int judge;
	for(int i=0; i<binaryImg.rows; i++) {
		for(int j=0; j<binaryImg.cols; j++){
			judge = 0;
			for(int m = -2; m <= 2; m++){
				for(int n = -2; n <= 2; n++){
					if(a[m+2][n+2]){
						if(*(binaryImg.data + (i+m)* binaryImg.step + j+n)==255){
							judge = 1;
						}
					}
				}
			}

			if(judge)
				*(dst.data + i* dst.step + j) = 255;
			else
				*(dst.data + i* dst.step + j) = 0;
		}
	}

	Mat Image = dst.clone();
	for(int i=0; i<Image.rows; i++) {
		for(int j=0; j<Image.cols; j++){
			judge = 0;
			for(int m = -2; m <= 2; m++){
				for(int n = -2; n <= 2; n++){
					if(a[m+2][n+2]){
						if(*(Image.data + (i+m)* Image.step + j+n)==255){
							judge = 1;
						}
					}
				}
			}

			if(judge)
				*(dst.data + i* dst.step + j) = 255;
			else
				*(dst.data + i* dst.step + j) = 0;
		}
	}
}

//骨架提取
//*************************************************************************************
//函数名称：Mat thinning()
//基本功能：对二值图像进行细化运算
//参数说明：待细化二值图像，该图像中背景色为0，前景色（目标）为255
//返 回 值：返回细化后二值图像
//*************************************************************************************
void ImageMathematicalMorphology::thinning(const Mat &src, Mat &dst)
{
	int i, j, k;
	uchar p[11];
	int pos[9][2] = {{0,0}, {-1,0} , {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};
	int cond1, cond2, cond3, cond4, counter=0;
	bool pointsDeleted = true;
	Mat mask;

	
	//转化为0,1二值图像
	dst = src / 255;
	//若没有可删除像素点
	while (pointsDeleted)
	{
		mask = Mat::zeros(dst.size(), CV_8UC1);//初始化模板为全0
		pointsDeleted = false;
		for (i=1; i<dst.rows-1; i++)
		{
			for (j=1; j<dst.cols-1; j++)
			{
				//获取3*3结构元素p1~p9对应像素值, 其中p1为中心点
				for (k=1; k<10; k++)
					p[k] = dst.at<uchar>(i+pos[k-1][0], j+pos[k-1][1]);

				//若中心点为背景色，跳过
				if(p[1]==0) continue;

				//计算中心点周围所有像素值之和
				cond1 = 0;
				for (k=2; k<10; k++) cond1 += p[k];

				//计算p2~p9从0到1变化的次数
				cond2 = 0;
				p[10] = p[2]; //用于处理k=8时, p[k+2]越界情况
				for (k=2; k<10; k+=2)
					cond2 += ((p[k]==0 && p[k+1]==1) + (p[k+1]==0 && p[k+2]==1));

				if(counter%2==0)//偶数次迭代判断条件
				{
					cond3 = p[2] * p[4] * p[6];
					cond4 = p[4] * p[6] * p[8];
				}
				else//奇数次迭代判断条件
				{
					cond3 = p[2] * p[4] * p[8];
					cond4 = p[2] * p[6] * p[8];
				}
				//若同时满足条件1~条件4
				if ((2<=cond1 && cond1<= 6) && (cond2==1) && (cond3==0) && (cond4==0))
				{
					pointsDeleted = true;
					mask.at<uchar>(i, j) = 1; //写入待删除的像素点至模板
				}
			}
		}
		dst &= ~mask; //通过逻辑与操作删除目标像素点
		counter++;
	}
	//恢复为0, 255二值图像
	dst *= 255;
}


//灰值腐蚀
void ImageMathematicalMorphology::greyValueErode(const Mat &src, Mat &dst, int a[5][5]) {
	Mat grayImg(src.size(),CV_8U);
	cvtColor(src,dst,CV_BGR2GRAY);
	grayImg = dst.clone();

	int Num,tep;
	for(int i = 2; i < grayImg.rows-2 ; i++){
		for(int j = 2; j < grayImg.cols-2 ; j++){
			Num = 255;
			for(int m = -2; m <3; m++){
				for(int n = -2; n <3; n++){
					if(a[m+2][n+2]){
						tep=*(grayImg.data + (i+m)* grayImg.step + j+n)-a[m+2][n+2];
						if(tep < Num){
							Num = tep;
						}
					}
				}
			}
			if(Num < 0)
				*(dst.data + (i-2)* dst.step + j-2) = 0;
			else
				*(dst.data + (i-2)* dst.step + j-2) = Num;
		}
	}
}


//灰值膨胀
void ImageMathematicalMorphology::greyValueDilate(const Mat &src, Mat &dst, int a[5][5]) {
	Mat grayImg(src.size(),CV_8U);
	cvtColor(src,dst,CV_BGR2GRAY);
	grayImg = dst.clone();

	int Num,tep;
	for(int i = 2; i < grayImg.rows-2 ; i++){
		for(int j = 2; j < grayImg.cols-2 ; j++){
			Num = 0;
			for(int m = -2; m <3; m++){
				for(int n = -2; n <3; n++){
					if(a[m+2][n+2]){
						tep=*(grayImg.data + (i+m)* grayImg.step + j+n)+a[m+2][n+2];
						if(tep > Num){
							Num = tep;
						}
					}
				}
			}
			if(Num > 255)
				*(dst.data + (i-2)* dst.step + j-2) = 255;
			else
				*(dst.data + (i-2)* dst.step + j-2) = Num;
		}
	}
}


//灰值开运算
void ImageMathematicalMorphology::greyValueOpenOperation(const Mat &src, Mat &dst, int a[5][5]) {
	Mat grayImg(src.size(),CV_8U);
	cvtColor(src,dst,CV_BGR2GRAY);
	grayImg = dst.clone();

	int Num,tep;
	for(int i = 2; i < grayImg.rows-2 ; i++){
		for(int j = 2; j < grayImg.cols-2 ; j++){
			Num = 255;
			for(int m = -2; m <3; m++){
				for(int n = -2; n <3; n++){
					if(a[m+2][n+2]){
						tep=*(grayImg.data + (i+m)* grayImg.step + j+n)-a[m+2][n+2];
						if(tep < Num){
							Num = tep;
						}
					}
				}
			}
			if(Num < 0)
				*(dst.data + (i-2)* dst.step + j-2) = 0;
			else
				*(dst.data + (i-2)* dst.step + j-2) = Num;
		}
	}

	Mat Image = dst.clone();
	for(int i = 2; i < Image.rows-2 ; i++){
		for(int j = 2; j < Image.cols-2 ; j++){
			Num = 0;
			for(int m = -2; m <3; m++){
				for(int n = -2; n <3; n++){
					if(a[m+2][n+2]){
						tep=*(Image.data + (i+m)* Image.step + j+n)+a[m+2][n+2];
						if(tep > Num){
							Num = tep;
						}
					}
				}
			}
			if(Num > 255)
				*(dst.data + (i-2)* dst.step + j-2) = 255;
			else
				*(dst.data + (i-2)* dst.step + j-2) = Num;
		}
	}
}


//灰值闭运算
void ImageMathematicalMorphology::greyValueCloseOperation(const Mat &src, Mat &dst, int a[5][5]) {
	Mat grayImg(src.size(),CV_8U);
	grayImg = dst.clone();

	int Num,tep;

	for(int i = 2; i < grayImg.rows-2 ; i++){
		for(int j = 2; j < grayImg.cols-2 ; j++){
			Num = 0;
			for(int m = -2; m <3; m++){
				for(int n = -2; n <3; n++){
					if(a[m+2][n+2]){
						tep=*(grayImg.data + (i+m)* grayImg.step + j+n)+a[m+2][n+2];
						if(tep > Num){
							Num = tep;
						}
					}
				}
			}
			if(Num > 255)
				*(dst.data + (i-2)* dst.step + j-2) = 255;
			else
				*(dst.data + (i-2)* dst.step + j-2) = Num;
		}
	}

	Mat Image = dst.clone();
	for(int i = 2; i < Image.rows-2 ; i++){
		for(int j = 2; j < Image.cols-2 ; j++){
			Num = 255;
			for(int m = -2; m <3; m++){
				for(int n = -2; n <3; n++){
					if(a[m+2][n+2]){
						tep=*(Image.data + (i+m)* Image.step + j+n)-a[m+2][n+2];
						if(tep < Num){
							Num = tep;
						}
					}
				}
			}
			if(Num < 0)
				*(dst.data + (i-2)* dst.step + j-2) = 0;
			else
				*(dst.data + (i-2)* dst.step + j-2) = Num;
		}
	}
}