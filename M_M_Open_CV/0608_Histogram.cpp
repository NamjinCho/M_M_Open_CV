#pragma warning (disable:4996)
#pragma warning (disable:4819)
#include <iostream>
#include <opencv2/opencv.hpp>
#include<windows.h>
#include<math.h>
using namespace std;
using namespace cv;
int main(int, char**)
{
	Mat gray = imread("lena.png", 0);
	// Initialize parameters
	int histSize = 256; // bin size
	float range[] = { 0, 255 };
	const float *ranges[] = { range };
	// Calculate histogram
	Mat hist;
	calcHist(&gray, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);
	// Plot the histogram
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
	// Normalize the result to [ 0, histImage.rows]
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	for (int i = 1; i< histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}
	int width = gray.cols;
	int height = gray.rows;

	int **newSize,**forImg;
	newSize = (int**)malloc(sizeof(int*)*width);
	forImg = (int**)malloc(sizeof(int*)*width);
	for (int i = 0; i < height; i++) {
		newSize[i] = (int*)malloc(sizeof(int)*height);
		forImg[i] = (int*)malloc(sizeof(int)*height);
	}
	Mat dst = Mat(height, width, CV_16SC1);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			printf("%d %d\n",x,y);
			if (x == 0)
			{
				dst.at<int>(y,x) = gray.at<uchar>(y,x);
				
			}
			else
			{
				dst.at<int>(y, x) = gray.at<uchar>(y, x)- gray.at<uchar>(y, x-1);
			}
		}
	}
	int min, max;
	min = 1000;
	max = -1000;
	
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (newSize[x][y] < min)
				min = newSize[x][y];
			if (newSize[x][y] > max)
				max = newSize[x][y];
		}
	}
	//(v-min)/(max-min)*(newMax-newMin)+newMin
	
	Mat hist2;
	calcHist(&dst, 1, 0, Mat(), hist2, 1, &histSize, ranges, true, false);
	// Plot the histogram
	Mat histImage2(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
	// Normalize the result to [ 0, histImage.rows]
	normalize(hist2, hist2, 0, histImage2.rows, NORM_MINMAX, -1, Mat());
	for (int i = 1; i< histSize; i++)
	{
		line(histImage2, Point(bin_w*(i - 1), hist_h - cvRound(hist2.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(hist2.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}
	
	printf("%d",sizeof(ranges));
	namedWindow("Result", 1);
	imshow("Result", histImage);
	
	imshow("Result2", dst);
	imshow("Histo", histImage2);
	waitKey(0);
	return 0;
}