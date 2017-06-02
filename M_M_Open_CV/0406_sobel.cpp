/*
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <string>
#include<math.h>
using namespace cv;
using namespace std;
int mask1[3][3] = {
	{ -1,0,1 },
	{ -2,0,2 },
	{ -1,0,1 }
};
int mask2[3][3] = {
	{ -1,-2,-1 },
	{ 0,0,0 },
	{ 1,2,1 }
};
int lapMask[3][3] = {
	{ 0,-1,0 },
	{ -1,4,-1 },
	{ 0,-1,0 }
};

void rebuildHeap(int arr[], int root, int n)
{
	int child = 2 * root + 1;

	if (child <= n)
	{
		int rightchild = child + 1;

		if (rightchild <= n && arr[rightchild] > arr[child])
			child = rightchild;

		if (arr[root] < arr[child])
		{
			swap(arr[root], arr[child]);
			rebuildHeap(arr, child, n);
		}
	}
}

void heapsort(int arr[], int N)
{
	for (int root = N / 2 - 1; root >= 0; root--)
		rebuildHeap(arr, root, N);

	for (int last = N - 1; last > 0; )
	{
		swap(arr[last], arr[0]);
		last--;

		rebuildHeap(arr, 0, last);
	}
}

double sobel (Mat image, int x, int y, int i, int j ,int *pixel1,int *pixel2)
{
	int width = image.size().width;
	int height = image.size().height;

	if ((x + i >= 0 && y + j >= 0) && (x + i < width && y + j < height))
	{
		*pixel1 = ((int)image.at<char>(y + j, x + i)*mask1[1 + i][1 + j]);
		*pixel2 = ((int)image.at<char>(y + j, x + i)*mask2[1 + i][1 + j]);
	}
	/*
	else
	{
		if (x + i < 0 && y + j >= 0 & y + j<height) // 8번
		{
			*pixel1 = (double)image.at<char>(y + j, 0)*(double)mask1[1 + i][1 + j];
			*pixel2 = (double)image.at<char>(y + j, 0)*(double)mask2[1 + i][1 + j];
		}
		else if (x + i<width&&x + i >= 0 && y + j < 0) // 2번
		{
			*pixel1 = (double)image.at<char>(0, x + i)*(double)mask1[1 + i][1 + j];
			*pixel2 = (double)image.at<char>(0, x + i)*(double)mask2[1 + i][1 + j];
		}
		else if (x + i < 0 && y + j < 0) // 1번
		{
			*pixel1 = (double)image.at<char>(0, 0)*(double)mask1[1 + i][1 + j];
			*pixel2 = (double)image.at<char>(0, 0)*(double)mask2[1 + i][1 + j];
		}
		else if (x + i >= width && y + j >= 0 && y + j < height) //4번
		{
			*pixel1 = (double)image.at<char>(y + j, width - 1)*(double)mask1[1 + i][1 + j];
			*pixel2 = (double)image.at<char>(y + j, width - 1)*(double)mask2[1 + i][1 + j];
		}
		else if (x + i >= 0 && x + i < width && y + j >= height) //6번
		{
			*pixel1 = (double)image.at<char>(height - 1, x + i)*(double)mask1[1 + i][1 + j];
			*pixel2 = (double)image.at<char>(height - 1, x + i)*(double)mask2[1 + i][1 + j];
		}
		else if (x + i >= width && y + j >= height) // 5번
		{
			*pixel1 = (double)image.at<char>(height - 1, width - 1)*(double)mask1[1 + i][1 + j];
			*pixel2 = (double)image.at<char>(height - 1, width - 1)*(double)mask2[1 + i][1 + j];
		}
		else if (x + i < 0 && y + j >= height) // 7번
		{
			*pixel1 = (double)image.at<char>(height - 1, 0)*(double)mask1[1 + i][1 + j];
			*pixel2 = (double)image.at<char>(height - 1, 0)*(double)mask2[1 + i][1 + j];

		}
		else if (x + i > width && y + j < 0) //3 번
		{
			*pixel1 = (double)image.at<char>(0, width - 1)*(double)mask1[1 + i][1 + j];
			*pixel2 = (double)image.at<char>(0, width - 1)*(double)mask2[1 + i][1 + j];
		}

	}
	return 0.0;
}
double laplacian(Mat image, int x, int y, int i, int j, int *pixel1)
{
	int width = image.size().width;
	int height = image.size().height;

	if ((x + i >= 0 && y + j >= 0) && (x + i < width && y + j < height))
	{
		*pixel1 = ((int)image.at<char>(y + j, x + i)*lapMask[1 + i][1 + j]);
	}/*
	else
	{
		if (x + i < 0 && y + j >= 0 & y + j<height) // 8번
		{
			*pixel1 = (double)image.at<char>(y + j, 0)*(double)lapMask[1 + i][1 + j];
		}
		else if (x + i<width&&x + i >= 0 && y + j < 0) // 2번
		{
			*pixel1 = (double)image.at<char>(0, x + i)*(double)lapMask[1 + i][1 + j];
		}
		else if (x + i < 0 && y + j < 0) // 1번
		{
			*pixel1 = (double)image.at<char>(0, 0)*(double)lapMask[1 + i][1 + j];
		}
		else if (x + i >= width && y + j >= 0 && y + j < height) //4번
		{
			*pixel1 = (double)image.at<char>(y + j, width - 1)*(double)lapMask[1 + i][1 + j];
		}
		else if (x + i >= 0 && x + i < width && y + j >= height) //6번
		{
			*pixel1 = (double)image.at<char>(height - 1, x + i)*(double)lapMask[1 + i][1 + j];
		}
		else if (x + i >= width && y + j >= height) // 5번
		{
			*pixel1 = (double)image.at<char>(height - 1, width - 1)*(double)lapMask[1 + i][1 + j];
		}
		else if (x + i < 0 && y + j >= height) // 7번
		{
			*pixel1 = (double)image.at<char>(height - 1, 0)*(double)lapMask[1 + i][1 + j];

		}
		else if (x + i > width && y + j < 0) //3 번
		{
			*pixel1 = (double)image.at<char>(0, width - 1)*(double)lapMask[1 + i][1 + j];
		}

	}
	return 0.0;
}

int main(int argc, char ** argv)
{
	
	string imageName("lena.png");

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
	Mat image3 = image.clone();
	int width = image.size().width;
	int height = image.size().height;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int sum1 = 0;
			int sum2 = 0;
			int sum3 = 0;
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j<2; j++) {

					int pixel1 = 0;
					int pixel2 = 0;
					int pixel3 = 0;
					sobel(image, x, y, i, j, &pixel1, &pixel2);
					laplacian(image, x, y, i, j, &pixel3);
					sum1 += pixel1;
					sum2 += pixel2;
					sum3 += pixel3;
				}
			}

			sum1 *= sum1;
			sum2 *= sum2;
			sum1 = (sum1 + sum2);
			sum1 = sqrt(sum1);
			//printf("%lf\n",sum1);
			image2.at<uchar>(y, x) = saturate_cast<uchar>(sum1); //sobel
			image3.at<uchar>(y, x) = saturate_cast<uchar>(sum3 ); // lap
		}
	}


	imshow("sobel", image2);
	imshow("original", image);
	imshow("lap", image3);
	waitKey(0);

	return 0;
}*/