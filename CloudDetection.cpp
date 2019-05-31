// CloudDetection.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "vector"
#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>   
#include <opencv2/highgui/highgui.hpp>   
using namespace cv;
using namespace std;



void Detection(Mat M1, Mat M2) {

	int rows = M1.rows;
	int cols = M1.cols;

	Mat Mtemp1(rows, cols, CV_8UC1, Scalar(100));
	Mat Mtemp2(rows, cols, CV_8UC1, Scalar(100));
	Mat Mtemp3(rows, cols, CV_8UC1, Scalar(100));

	subtract(M1, M2, Mtemp1);//相减
	addWeighted(M1, 1, M2, 1,0., Mtemp2);//相加

	unsigned char *p1 = Mtemp1.data;
	unsigned char *p2 = Mtemp2.data;

	double result;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result = (double)p1[i*cols + j] / (double)p2[i*cols + j];
			result = result * 255;//线性拉伸
			Mtemp3.at<uchar>(i,j)= uchar(result * 1.0);
			Mtemp3.at<uchar>(i, j) = 255 - Mtemp3.at<uchar>(i, j);//反差变换
		}
	}
	threshold(Mtemp3, Mtemp3, 250, 255, THRESH_BINARY);

	namedWindow("Detection", 0);
	imshow("Detection", Mtemp3);
}


int main()
{

	//水体1-4 2-4   云 2-1(二值化)    4-1云和水体
	char imageName1[] = "cloudimage-2.tif";
	Mat M1 = imread(imageName1, IMREAD_GRAYSCALE);
	char imageName2[] = "cloudimage-1.tif";
	Mat M2 = imread(imageName2, IMREAD_GRAYSCALE);

	Detection(M1, M2);

	//namedWindow("win1",0);
	//imshow("win1", M1);
	waitKey();
	printf("\n\n");
    return 0;
}

