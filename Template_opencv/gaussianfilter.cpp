#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <windows.h>

using namespace std;
using namespace cv;

int ct = 0;
char tipka;
char filename[100];
int c = 1;

int main(int, char**)
{
	Mat frame, img, grayImg, hasil;
	VideoCapture cap;
	cap.open(0);
	int deviceID = 0;
	int apiID = cv::CAP_ANY;

	cap.open(deviceID + apiID);

	if (!cap.isOpened()){
		cout << "ERROR open camera";
		return -1;
	}

	cout << "start grabbing" << endl;
	cout << "press q to terminate" << endl;

	for (;;){
		cap.read(frame);

		if (frame.empty()){
			cout << "ERROR capture image\n";
			break;
		}
		Sleep(1);

		imshow("CAMERA1", frame);
		tipka = cv::waitKey(30);

		if (tipka == 's'){
			sprintf_s(filename, "Frame_%d.jpg", c);
			waitKey(10);
			imshow("CAMERA1", frame);
			imwrite(filename, frame);
			cvtColor(frame, grayImg, CV_BGR2GRAY);
			GaussianBlur(grayImg, hasil, Size(9, 9), 8, 0);
			imwrite("GBlurGray.jpg", hasil);
			imshow("GBlurGray", hasil);
			cout << "Frame_" << c << endl;
			c++;
		}

		if (tipka == 'q'){
			cout << "terminate.." << endl;
			break;
		}

	}

	return 0;
}

/*int _tmain(int argc, _TCHAR* argv[])
{
	Mat img, grayImg, hasil;

	img = imread("autumn.jpg");
	imshow("Display window", img);
	cvtColor(img, grayImg, CV_BGR2GRAY);

	GaussianBlur(grayImg, hasil, Size(9, 9), 8, 0);
	imwrite("GBlurGray_2.jpg", hasil);
	imshow("BlurGray_1", hasil);

	GaussianBlur(img, hasil, Size(9, 9), 8, 0);
	imwrite("GBlurColor_2.jpg", hasil);
	imshow("BlurColor_1", hasil);

	waitKey(0);
	return 0;

}*/