/*
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <string>
#define RGB 0
#define YCbCr 1
#define CMY 2
#define HSV 3
using namespace cv;
using namespace std;
Mat cvtColorForIntensity(Mat original, int type);
int main(int argc, char ** argv)
{
	string imageName("lena.png");

	if (argc > 1)
	{
		imageName = argv[1];
	}
	Mat image;
	image = imread(imageName.c_str(), IMREAD_COLOR);
	Mat RGBImage,YCbCrImage, CMYImage, HSVImage;


	if (image.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	CMYImage = cvtColorForIntensity(image, CMY);
	RGBImage = cvtColorForIntensity(image, RGB);
	HSVImage = cvtColorForIntensity(image, HSV);
	YCbCrImage = cvtColorForIntensity(image, YCbCr);
	//rgb2hsv(image, &HSVImage);
	imshow("original", image);
	imshow("CMY", CMYImage);
	imshow("HSV", HSVImage);
	imshow("YCBCR", YCbCrImage);
	imshow("RGB", RGBImage);
	waitKey();
}

Mat cvtColorForIntensity(Mat original, int type)
{
	Mat result;
	result = original.clone();

	int row = original.size().height;
	int col = original.size().width;

	if (type == YCbCr) {
		

		cvtColor(original, result, CV_BGR2YCrCb);

		for (int x = 0; x < col; x++)
		{
			for (int y = 0; y < row; y++)
			{
				result.at<Vec3b>(y, x)[0] = result.at<Vec3b>(y, x)[0] * 0.7;
			}
		}
		Mat temp;
		cvtColor(result, temp, CV_YCrCb2BGR);
		result = temp;

	}
	else if (type == CMY) {
			
			for (int x = 0; x < col; x++)
			{
				for (int y = 0; y < row; y++)
				{
					//BGR

					uchar B, G, R;
					B = original.at<Vec3b>(y, x)[0];
					G = original.at<Vec3b>(y, x)[1];
					R = original.at<Vec3b>(y, x)[2];

					uchar C = 255 - R;
					uchar M = 255 - G;
					uchar Y = 255 - B;

					double Cprime = C*0.7 + 0.3*255;
					double Mprime = M*0.7 + 0.3*255;
					double Yprime = Y*0.7 + 0.3*255;

					double Rprime = 255 - Cprime;
					double Gprime = 255 - Mprime;
					double Bprime = 255 - Yprime;
					result.at<Vec3b>(y, x)[0] = (uchar)Bprime;
					result.at<Vec3b>(y, x)[1] = (uchar)Gprime;
					result.at<Vec3b>(y, x)[2] = (uchar)Rprime;

				}
			}
	}
	else if (type == HSV)
	{
		cvtColor(original, result, CV_BGR2HSV);
		for (int x = 0; x < col; x++)
		{
			for (int y = 0; y < row; y++)
			{
				result.at<Vec3b>(y, x)[2] = result.at<Vec3b>(y, x)[2] * 0.7;
			}
		}

		Mat temp;
		cvtColor(result, temp, CV_HSV2BGR);
		result = temp;
	}
	else if (type == RGB)
	{
		for (int x = 0; x < col; x++)
		{
			for (int y = 0; y < row; y++)
			{
				result.at<Vec3b>(y, x)[0] = result.at<Vec3b>(y, x)[0] * 0.7;
				result.at<Vec3b>(y, x)[1] = result.at<Vec3b>(y, x)[1] * 0.7;
				result.at<Vec3b>(y, x)[2] = result.at<Vec3b>(y, x)[2] * 0.7;
			}
		}
	}

	return result;
}
*/