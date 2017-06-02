/*
#pragma warning (disable:4996)
#pragma warning (disable:4819)
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat Interpolation(const Mat src, const double scaleWidth, const double scaleHeight) {

	int x1, x2;
	int y1, y2;
	double rx, ry;
	double s1, s2;
	Vec3b r1, r2;

	Mat dst((int)(src.rows * scaleHeight + 0.5), (int)(src.cols * scaleWidth + 0.5), CV_8UC3);
	double srcX = 1 / scaleWidth;
	double srcY = 1 / scaleHeight;

	int  r = 0;

	for (int y = 0; y < dst.rows; y++)

	{

		int  r = 0;

		for (int x = 0; x < dst.cols; x++)
		{
			rx = srcX * x;
			ry = srcY * y;
			x1 = (int)floor(rx);
			y1 = (int)floor(ry);

#if 0
			x2 = x1 + 1; if (x2 == src.cols) x2 = x1;
			y2 = y1 + 1; if (y2 == src.rows) y2 = y1;
#else
			x2 = x1 + 1; if (x2 == src.cols) x2 = x1 - 1;
			y2 = y1 + 1; if (y2 == src.rows) y2 = y1 - 1;

#endif
			s1 = rx - x1;
			s2 = ry - y1;

			for (int i = 0; i < 3; i++) {
				r1[i] = saturate_cast<uchar>((1 - s1)* src.at<Vec3b>(y1, x1)[i] + s1 * src.at<Vec3b>(y1, x2)[i] + 0.5);
				r2[i] = saturate_cast<uchar>((1 - s1) *src.at<Vec3b>(y2, x1)[i] + s1 * src.at<Vec3b>(y2, x2)[i] + 0.5);
				dst.at<Vec3b>(y, x)[i] = saturate_cast<uchar>((1 - s2) * r1[i] + s2 * r2[i] + 0.5);
			}

		}

	}



	return dst;

}

int main(int argc, char** argv) {



	String openImagePath = "namjin.jpg";						// Image Path That You Want To Open.
	String originalName = "Original Image";
	double scaleWidth = 3.0;								// scale Width and Height 
	double scaleHeight = 1.5;
	if (argc > 2)
	{
		openImagePath = argv[1];
		scaleWidth = atof(argv[2]);
		scaleHeight = atof(argv[3]);

	}

	Mat src = imread(openImagePath, IMREAD_COLOR);			// Read Image
															//if scale vectors are not bigger than 1.0, then original image is filtered gaussian blurring.

	if (src.empty())
	{
		cerr << "NO FILE PATH" << endl;
		return 0;
	}


	Mat dst = Interpolation(src, scaleWidth, scaleHeight);
	imshow("Scaled", dst);
	imshow("original", src);
	waitKey();
	return 0;

}*/