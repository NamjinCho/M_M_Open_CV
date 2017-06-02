#pragma warning (disable:4996)
#pragma warning (disable:4819)
#include <iostream>
#include <opencv2/opencv.hpp>
#include<windows.h>
#include<math.h>
using namespace std;
using namespace cv;
int main(int argc, char** argv) {



	String openImagePath = "Girl_in_front_of_a_green_background.jpg";
	String openImagePath2 = "back.jpg";// Image Path That You Want To Open.

	Mat src = imread(openImagePath, IMREAD_COLOR);			// Read Image
	Mat src2 = imread(openImagePath2, IMREAD_COLOR);														//if scale vectors are not bigger than 1.0, then original image is filtered gaussian blurring.
	Mat temp, temp2;

	cvtColor(src, temp, CV_BGR2YCrCb);
	
	int width = src.size().width;
	int height = src.size().height;


	resize(src2, src2, Size(width, height));
	cvtColor(src2, temp2, CV_BGR2YCrCb);

	//71 ~ 95 , 62 ~ 49
	//key 62 , 52 // 70 54 / 94 10
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (temp.at<Vec3b>(y, x)[1] >= 40 && temp.at<Vec3b>(y, x)[1] <= 90)
			{
				if (temp.at<Vec3b>(y, x)[2] >= 40&& temp.at<Vec3b>(y, x)[2] <= 110)
				{
					src.at<Vec3b>(y, x)[0] = src2.at<Vec3b>(y, x)[0];
					src.at<Vec3b>(y, x)[1] = src2.at<Vec3b>(y, x)[1];
					src.at<Vec3b>(y, x)[2] = src2.at<Vec3b>(y, x)[2];
				}
			}
		}
	}

	printf("%d %d \n",temp.at<Vec3b>(110,167)[1], temp.at<Vec3b>(110, 167)[2]);
	printf("%d %d \n",temp.at<Vec3b>(417,584)[2], temp.at<Vec3b>(417, 584)[2]);
	imshow("ycbcr", src);
	waitKey();
	return 0;
}