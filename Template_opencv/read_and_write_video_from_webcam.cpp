#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(1);
	
	if (!cap.isOpened()){
		cout << "ERROR open camera";
		return -1;
	}

	int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	printf("row %d\n", frame_width);
	printf("column %d", frame_height);

	VideoWriter video("outcpp.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));
	while (1){
		Mat frame;
		cap >> frame;
		if (frame.empty())
			break;

		video.write(frame);

		imshow("Frame", frame);

		char c = (char)waitKey(1);
		if (c == 27)
			break;
	}

	cap.release();
	video.release();
	destroyAllWindows();
	
	return 0;
}
