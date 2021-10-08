#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;
using std::cout;
int main(int argc, char** argv)
{
	//memulai capture video
	VideoCapture cap(0);
	if (!cap.isOpened())
		return -1;

	//mendapatkan nilai dimensi video, disimpan dalam variabel, ditampilkan
	int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	printf("row %d\n", frame_width);
	printf("coloumn %d\n", frame_height);
	for (;;)
	{
		Mat frame; Mat hsv;
		cap >> frame;
		imshow("Frame", frame);
		if (waitKey(30) >= 0)
			break;
		cap.read(frame);
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		Mat dst;
		equalizeHist(frame, dst);
		imshow("Source image", frame);
		imshow("Equalized Image", dst);
		if (frame.empty())
		{
			cout << "ERROR blank frame\n";
			break;
		}

		/// Establish the number of bins
		int histSize = 256;
		/// Set the ranges
		float range[] = { 0, 256 };
		const float* histRange = { range };
		bool uniform = true; bool accumulate = false;
		Mat hist;
		/// Compute the histograms:
		calcHist(&frame, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate
			);
		// Draw the histograms
		int hist_w = 512; int hist_h = 400;
		int bin_w = cvRound((double)hist_w / histSize);
		Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
		/// Normalize the result to [ 0, histImage.rows ]
		normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
		/// Draw for channel
		for (int i = 1; i < histSize; i++)
		{
			line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
				Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
				Scalar(255, 255, 255), 2, 8, 0);
		}
		/// Display
		namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
		imshow("calcHist Demo", histImage);
	}
	return 0;
}