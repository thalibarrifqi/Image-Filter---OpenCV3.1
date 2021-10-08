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
	Mat frame, gray_frame;
	//frame = imread("histo1.JPG", CV_LOAD_IMAGE_COLOR);
	//frame = imread("histo2.JPG", CV_LOAD_IMAGE_COLOR);
	frame = imread("histo3.JPG", CV_LOAD_IMAGE_COLOR);
	cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
	imshow("Gray Scale Image", gray_frame);
	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true; bool accumulate = false;
	Mat b_hist;
	calcHist(&gray_frame, 1, 0, Mat(), b_hist, 1, &histSize, &histRange,uniform, accumulate);
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h -
			cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h -
			cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}
	imshow("Histogram of Gray Scale Image", histImage);
	waitKey(0);
	return EXIT_SUCCESS;
}
