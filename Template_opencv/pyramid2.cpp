#include <opencv2\opencv.hpp>
#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\imgproc\imgproc.hpp>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace std;
using namespace cv;

/// Global variables
Mat frame, dst, tmp, cropup, cropdown;
char* window_name = "Pyramids Demo";
time_t start, stop;
int counter = 1;

int main(int argc, char** argv)
{
	VideoCapture cap(0);

	time(&start);
	while (true)
	{

		int c;
		c = waitKey(10);
		cap >> frame;
		tmp = frame;

		dst = tmp;
		if ((char)c == 27)
		{
			break;
		}
		double sec = difftime(stop, start);
		time(&stop);
		cout << sec << endl;
		if (sec > 1 && sec <= 4)
		{
			cropup = frame(Rect(frame.cols / 3, frame.rows / 3, frame.cols / 2, frame.rows / 2));
			tmp = cropup;
			pyrUp(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
			pyrUp(dst, dst, Size(dst.cols * 2, dst.rows * 2));
			printf("** Zoom In: Image x 2 \n");
		}
		else if (sec > 4 && sec <= 8)
		{
			pyrDown(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
			printf("** Zoom Out: Image / 2 \n");

		}
		else if (sec > 8)
			time(&start);
		resizeWindow(window_name, 720, 480);
		imshow(window_name, dst);
		tmp = dst;
	}
	return 0;
}