/*
#pragma warning (disable:4996)
#pragma warning (disable:4819)
#include <iostream>
#include <opencv2/opencv.hpp>
#include<windows.h>
#include<math.h>
using namespace std;
using namespace cv;
int **generateBlock(Mat src,int x,int y,int width, int height)
{
	int **result;
	result = (int**)malloc(sizeof(int*)*width);
	for (int i = 0; i < width; i++)
		result[i] = (int*)malloc(sizeof(int)*height);

	for (int i = 0; i < width ; i++)
	{
		for (int j = 0 ; j < height; j++)
		{
			result[i][j] = src.at<uchar>(y+j, x+i);
		}
	}
	return result;
}
int getMAD(int **bolck1, int **block2,int width,int height)
{
	int total = 0;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			total += (bolck1[i][j] - block2[i][j])*(bolck1[i][j]-block2[i][j]);
		}
	}
	total = total;

	return total;
}
int main(int argc, char** argv) {



	String openImagePath = "right.png";
	String openImagePath2 = "left.png";// Image Path That You Want To Open.
	String originalName = "Original Image";
	double scaleWidth = 3.0;								// scale Width and Height 
	double scaleHeight = 1.5;
	//int block[32][32];

	Mat src = imread(openImagePath, IMREAD_GRAYSCALE);			// Read Image
	Mat src2 = imread(openImagePath2, IMREAD_GRAYSCALE);														//if scale vectors are not bigger than 1.0, then original image is filtered gaussian blurring.
	int width;
	int height;
	if (src.empty())
	{
		cerr << "NO FILE PATH" << endl;
		return 0;
	}
	width = src.size().width;
	height = src.size().height;
	int mask = 5;
	int padding = mask / 2;
	Mat dst = Mat(height - padding, width - padding, CV_8UC1);
	for (int i = padding; i < width- padding; i++)
	{
		for (int j = padding; j < height- padding; j++)
		{
			int **orgBlock = generateBlock(src, i - padding, j - padding, mask, mask);
			int minIndex = -1;
			int min = 1000;
			for (int k = 0; k < 16 && k + i < width-padding; k++)
			{
				int **comBlock = generateBlock(src2, i + k - padding, j - padding, mask, mask);
				int result = getMAD(comBlock, orgBlock, mask, mask);
				if (min > result )
				{
					minIndex = k+1;
					min = result;
				}
			}
			//printf("--\n");
			dst.at<uchar>(j - padding, i - padding) = minIndex * 16;
			//printf("%d %d\n",j,i);
		}
	}

	imshow("right",src);
	imshow("left", src2);
	imshow("result", dst);

	waitKey();
	return 0;
}

*/