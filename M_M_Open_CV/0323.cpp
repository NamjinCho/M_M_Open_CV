/*
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;
int mask[5][5] = {
	{ 1,1,1,1,1 },{ 1,1,1,1,1 },{ 1,1,1,1,1 },{ 1,1,1,1,1 },{ 1,1,1,1,1 }
};

Mat gaussian_filter(Mat img, float sigma, int size) {
	Mat convolution(Mat, Mat);
	Mat kernel(size, size, CV_32F);
	//calculate mask
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			float temp_x = x - size / 2;
			float temp_y = y - size / 2;
			kernel.at<float>(y, x) = pow(2, -(temp_x*temp_x + temp_y*temp_y) / 2 * sigma*sigma) / (2 * 3.14*sigma*sigma);
		}
	}

	return convolution(img, kernel);
}

Mat convolution(Mat img, Mat mask) {
	int mask_size = mask.size().width;
	copyMakeBorder(img, img, mask_size, mask_size, mask_size, mask_size, 0, 0);
	Mat result = img.clone();

	int half = mask_size / 2;

	for (int y = half; y < img.size().height - half; y++)
		for (int x = half; x < img.size().width - half; x++) {
			float sum[3] = { 0.0, 0.0, 0.0 };

			for (int i = 0; i < mask_size; i++)
				for (int j = 0; j < mask_size; j++) {
					sum[0] += img.at<uchar>(y - half + j, x - half + i) * mask.at<float>(j, i);
				}

			result.at<uchar>(y, x) = saturate_cast<int>(sum[0]);
		}
	return result;
}



int main(int argc, char ** argv)
{
	
	string imageName("s4.jpg");

	if (argc > 1)
	{
		imageName = argv[1];
	}
	Mat image;
	image = imread(imageName.c_str(), IMREAD_GRAYSCALE);
	if (image.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	//cvtColor(image, image, CV_RGB2GRAY);

	Mat image2 = image.clone();
	int width = image.size().width;
	int height = image.size().height;
	
	float avg = (1.0 / 25.0);
	//average filter
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			double sum = 0;
			for (int i = -2; i < 2; i++) {
				for(int j=-2;j<2;j++){
					
					if ((x+i >= 0 && y+j >= 0) && (x+i < width && y+j < height))
					{
						sum = sum + ((double)image.at<uchar>(y + j, x + i)*(double)mask[2+j][2+i]);
					}
					
				}
			}
			image2.at<uchar>(y, x) = (uchar)(sum*avg);
		}
	}
	 
	Mat img2 = gaussian_filter(image, 2.0, 3);
	imshow("avg", image2);
	imshow("original", image);
	imshow("gaussian", img2);
	waitKey(0);

return 0;
}
*/
/*
double alpha = 0.5; double beta; double input;
Mat src1, src2, dst;

std::cout << " Simple Linear Blender" << std::endl;
std::cout << " ---------------------" << std::endl;
std::cout << " Enter Alpha [0-1]" << std::endl;
std::cin >> input;
if (input >= 0.0 && input <= 1.0)
{
alpha = input;
}

src1 = imread("s1.jpg");
src2 = imread("s2.jpg");

if (!src1.data) { printf("Error Loading src1 \n"); }
if (!src2.data) { printf("Error Loading src2 \n"); }
//namedWindow("Linear Blend", 1);
beta = (1.0 - alpha);

dst = src1.clone();
for (int x = 0; x < src1.size().width; x++)
{
for (int y = 0; y < src1.size().height;y++)
{


dst.at<Vec3b>(y, x)[0] = alpha * src1.at<Vec3b>(y, x)[0] + beta *src2.at<Vec3b>(y, x)[0];
dst.at<Vec3b>(y, x)[1] = alpha * src1.at<Vec3b>(y, x)[1] + beta *src2.at<Vec3b>(y, x)[1];

dst.at<Vec3b>(y, x)[2] = alpha * src1.at<Vec3b>(y, x)[2] + beta *src2.at<Vec3b>(y, x)[2];


}
}
*/
