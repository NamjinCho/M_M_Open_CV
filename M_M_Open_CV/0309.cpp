/*
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char ** argv)
{

	string imageName("ss.jpg");

	if (argc > 1)
	{
		imageName = argv[1];
	}
	Mat image;
	image = imread(imageName.c_str(), IMREAD_COLOR);
	if (image.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	float a = 2.2;
	int b = 100;
	for (int y = 0; y < 960; y++) {
		for (int x = 0; x < 720; x++) {
			image.at<Vec3b>(y, x)[0] = saturate_cast<uchar>(a*image.at<Vec3b>(y, x)[0] + b);

			image.at<Vec3b>(y, x)[1] = saturate_cast<uchar>(a*image.at<Vec3b>(y, x)[1] + b);

			image.at<Vec3b>(y, x)[2] = saturate_cast<uchar>(a*image.at<Vec3b>(y, x)[2] + b);
		}
	}

	//namedWindow("Display Window! " , WINDOW_AUTOSIZE);

	imshow("Display Window!",image);

	waitKey(0);

	return 0;
}
*/