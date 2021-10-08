#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int, char**)
{
	Mat img = imread("autumn.jpg", CV_LOAD_IMAGE_COLOR),grayImg, edges1, edges2, edges3, edges4, edges5;
	int width = img.cols, height = img.rows;
	cvtColor(img, grayImg, CV_BGR2GRAY);
	imshow("Asal", grayImg);
	cout << "Default Cols : " << grayImg.cols << endl;
	cout << "Default Rows : " << grayImg.rows << endl << endl;

	Canny(grayImg, edges1, 20, 25);
	imshow("Canny RGB1", edges1);
	imwrite("cany_1.jpg", edges1);

	Canny(grayImg, edges2, 40, 45);
	imshow("Canny RGB2", edges2);
	imwrite("cany_2.jpg", edges2);

	Canny(grayImg, edges3, 60, 65);
	imshow("Canny RGB3", edges3);
	imwrite("cany_3.jpg", edges3);

	Canny(grayImg, edges4, 80, 85);
	imshow("Canny RGB4", edges4);
	imwrite("cany_4.jpg", edges4);

	Canny(grayImg, edges5, 100, 105);
	imshow("Canny RGB5", edges5);
	imwrite("cany_5.jpg", edges5);

	waitKey(0);
	return 0;
}