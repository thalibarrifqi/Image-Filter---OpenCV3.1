#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
	VideoCapture cap(1);
	if (cap.isOpened() == false)
	{
		cout << "Cannot open the video file" << endl;
		cin.get();
		return -1;
	}
	while (1)
	{
		Mat frame, gray_frame;
		cap >> frame;
		cap.read(frame);
		cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
		char c = (char)waitKey(1);
		if (c == 27)
			break;
		/// Establish the number of bins
		int histSize = 256;
		/// Set the ranges
		float range[] = { 0, 256 };
		const float* histRange = { range };
		bool uniform = true; bool accumulate = false;
		Mat b_hist;
		/// Compute the histograms:
		calcHist(&gray_frame, 1, 0, Mat(), b_hist, 1, &histSize, &histRange,
			uniform, accumulate);

		// Draw the histograms
		int hist_w = 512; int hist_h = 400;
		int bin_w = cvRound((double)hist_w / histSize);
		Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
		/// Normalize the result to [ 0, histImage.rows ]
		normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
		/// Draw Histogram
		for (int i = 1; i < histSize; i++)
		{
			line(histImage, Point(bin_w*(i - 1), hist_h -
				cvRound(b_hist.at<float>(i - 1))),
				Point(bin_w*(i), hist_h -
				cvRound(b_hist.at<float>(i))),
				Scalar(255, 0, 0), 2, 8, 0);
		}
		/// Display
		namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
		imshow("calcHist Demo", histImage);
		imshow("CAMERA", gray_frame);
	}
	waitKey();
	return EXIT_SUCCESS;
}