#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	//open video file
	VideoCapture cap("video1.mp4");
	//if not success exit program
	if (cap.isOpened() == false){
		cout << "cannot open the video file" << endl;
		cin.get();
		return -1;
	}
	//start video
	cap.set(CAP_PROP_POS_MSEC, 15000);

	//GET the frame rate
	double fps = cap.get(CAP_PROP_FPS);
	cout << "Frames per second : " << fps << endl;
	String window_name = "My First Video";
	namedWindow(window_name, WINDOW_NORMAL); //create a window

	while (true)
	{
		Mat frame;
		bool bSuccess = cap.read(frame); //read a new frame video

		//breaking the while loop at the end of video
		if (bSuccess == false){
			cout << "Found the end of the video" << endl;
			break;
		}
		//show the frame
		imshow(window_name, frame);
		if (waitKey(10) == 27){
			cout << "esc key is pressed by user. Stopping video" << endl;
			break;
		}
	}
	return 0;
}
