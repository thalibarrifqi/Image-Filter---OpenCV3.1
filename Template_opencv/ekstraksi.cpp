#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;
/**
* @function main
*/
int main(int argc, char** argv)
{
	Mat src, dst, frame_hsv, frame_threshold1;
	int c;
	/// Load image
	src = imread("book2.jpg", 1);
	if (!src.data)
	{
		return -1;
	}
	/// Separate the image in 3 places ( B, G and R )
	vector<Mat> bgr_planes;
	split(src, bgr_planes);
	/// Establish the number of bins
	int histSize = 256;
	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true; bool accumulate = false;
	Mat b_hist, g_hist, r_hist;
	/// Compute the histograms:
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize,	&histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize,	&histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize,	&histRange, uniform, accumulate);
	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	namedWindow("Setting", 1);
	int LR = 0;
	createTrackbar("Low Hue", "Setting", &LR, 255);
	int LG = 0;
	createTrackbar("Low Saturation", "Setting", &LG, 255);
	int LB = 0;
	createTrackbar("Low Value", "Setting", &LB, 255);
	int HR = 0;
	createTrackbar("High Hue", "Setting", &HR, 255);
	int HG = 0;
	createTrackbar("High Saturation", "Setting", &HG, 255);
	int HB = 0;
	createTrackbar("High Value ", "Setting", &HB, 255);
	while (1)
	{
		c = waitKey(500);
		/// Press 'ESC' to exit the program
		if ((char)c == 27)
		{
			break;
		}
		/// Draw for each channel
		for (int i = 1; i < histSize; i++)
		{
			line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
				Point(bin_w*(i), hist_h -	cvRound(b_hist.at<float>(i))),Scalar(255, 0, 0), 2, 8, 0);
			line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			    Point(bin_w*(i), hist_h -	cvRound(g_hist.at<float>(i))),Scalar(0, 255, 0), 2, 8, 0);
			line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
				Point(bin_w*(i), hist_h - 	cvRound(r_hist.at<float>(i))),Scalar(0, 0, 255), 2, 8, 0);

		}
		cvtColor(src, frame_hsv, COLOR_BGR2HSV);
		inRange(frame_hsv, Scalar(LR, LG, LB), Scalar(HR, HG, HB), frame_threshold1);
		/// Display
		namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
		imshow("calcHist Demo", histImage);
		imshow("object", src);
		imshow("object_threshold", frame_threshold1);
	}
	waitKey(0);
	return 0;
}