#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace cv;
using namespace std;

int ct = 0;
char tipka;
char filename[100];
int c = 1;

int main(int, char**)
{
	Mat frame;
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
