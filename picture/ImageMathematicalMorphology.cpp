#include "StdAfx.h"
#include "ImageMathematicalMorphology.h"

ImageMathematicalMorphology::ImageMathematicalMorphology(void)
{
}


ImageMathematicalMorphology::~ImageMathematicalMorphology(void)
{
}


//����
void ImageMathematicalMorphology::twoValueDilate(const Mat &src, Mat &dst, int a[5][5]) {
	//������ͼ���ֵ��
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


//��ʴ
void ImageMathematicalMorphology::twoValueErode(const Mat &src, Mat &dst, int a[5][5]) {
	//������ͼ���ֵ��
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
						if(*(binaryImg.data + (i+m)* binaryImg.step + j+n) == 0){//step Ϊͼ�������е�ʵ�ʿ��
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


//������
void ImageMathematicalMorphology::twoValueOpenOperation(const Mat &src, Mat &dst, int a[5][5]) {
	//������ͼ���ֵ��
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

//������
void ImageMathematicalMorphology::twoValueCloseOperation(const Mat &src, Mat &dst, int a[5][5]) {
	//������ͼ���ֵ��
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

//�Ǽ���ȡ
//*************************************************************************************
//�������ƣ�Mat thinning()
//�������ܣ��Զ�ֵͼ�����ϸ������
//����˵������ϸ����ֵͼ�񣬸�ͼ���б���ɫΪ0��ǰ��ɫ��Ŀ�꣩Ϊ255
//�� �� ֵ������ϸ�����ֵͼ��
//*************************************************************************************
void ImageMathematicalMorphology::thinning(const Mat &src, Mat &dst)
{
	int i, j, k;
	uchar p[11];
	int pos[9][2] = {{0,0}, {-1,0} , {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};
	int cond1, cond2, cond3, cond4, counter=0;
	bool pointsDeleted = true;
	Mat mask;

	
	//ת��Ϊ0,1��ֵͼ��
	dst = src / 255;
	//��û�п�ɾ�����ص�
	while (pointsDeleted)
	{
		mask = Mat::zeros(dst.size(), CV_8UC1);//��ʼ��ģ��Ϊȫ0
		pointsDeleted = false;
		for (i=1; i<dst.rows-1; i++)
		{
			for (j=1; j<dst.cols-1; j++)
			{
				//��ȡ3*3�ṹԪ��p1~p9��Ӧ����ֵ, ����p1Ϊ���ĵ�
				for (k=1; k<10; k++)
					p[k] = dst.at<uchar>(i+pos[k-1][0], j+pos[k-1][1]);

				//�����ĵ�Ϊ����ɫ������
				if(p[1]==0) continue;

				//�������ĵ���Χ��������ֵ֮��
				cond1 = 0;
				for (k=2; k<10; k++) cond1 += p[k];

				//����p2~p9��0��1�仯�Ĵ���
				cond2 = 0;
				p[10] = p[2]; //���ڴ���k=8ʱ, p[k+2]Խ�����
				for (k=2; k<10; k+=2)
					cond2 += ((p[k]==0 && p[k+1]==1) + (p[k+1]==0 && p[k+2]==1));

				if(counter%2==0)//ż���ε����ж�����
				{
					cond3 = p[2] * p[4] * p[6];
					cond4 = p[4] * p[6] * p[8];
				}
				else//�����ε����ж�����
				{
					cond3 = p[2] * p[4] * p[8];
					cond4 = p[2] * p[6] * p[8];
				}
				//��ͬʱ��������1~����4
				if ((2<=cond1 && cond1<= 6) && (cond2==1) && (cond3==0) && (cond4==0))
				{
					pointsDeleted = true;
					mask.at<uchar>(i, j) = 1; //д���ɾ�������ص���ģ��
				}
			}
		}
		dst &= ~mask; //ͨ���߼������ɾ��Ŀ�����ص�
		counter++;
	}
	//�ָ�Ϊ0, 255��ֵͼ��
	dst *= 255;
}


//��ֵ��ʴ
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


//��ֵ����
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


//��ֵ������
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


//��ֵ������
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