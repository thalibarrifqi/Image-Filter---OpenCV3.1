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
	frame = imread("book2.JPG", CV_LOAD_IMAGE_COLOR);
	imshow("RGB Image", frame);
	vector<Mat> bgr_planes;
	split(frame, bgr_planes);
	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	float rangered[] = { 125, 256 };
	const float* histRangered = { rangered };
	bool uniform = true; bool accumulate = false;
	Mat b_hist, g_hist, r_hist;
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange,
		uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange,
		uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange,
		uniform, accumulate);
	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	/// Draw for each channel
	for (int i = 1; i < histSize; i++)
	{
		/*line(histImage, Point(bin_w*(i - 1), hist_h -
			cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h -
			cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h -
			cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h -
			cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);*/
		line(histImage, Point(bin_w*(i - 1), hist_h -
			cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h -
			cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("Histogram of RGB Image", histImage);
	waitKey(0);
	return EXIT_SUCCESS;
}
