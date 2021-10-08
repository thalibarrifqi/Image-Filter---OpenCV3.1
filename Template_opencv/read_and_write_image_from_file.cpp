// Template_opencv.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat img;
	//Load
	img = imread("rice.png", CV_LOAD_IMAGE_COLOR);

	//Display
	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", img);

	//Info
	int row = img.rows;
	printf("row %d\n", row);
	int column = img.cols;
	printf("column %d\n", column);

	//Draw
	line(img, Point(92, 91), Point(182, 184), Scalar(0, 0, 100), 5, 8);
	imshow("Display result window", img);

	//save
	imwrite("result.jpg", img);

	waitKey(0);
	return 0;
}