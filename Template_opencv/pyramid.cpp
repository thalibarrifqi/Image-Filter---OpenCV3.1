#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

Mat src, dst, tmp;
char* window_name = "Pyramids Demo";

int main(int argc, char** argv)
{
	printf(" [u] -> Zoom in  \n");
	printf(" [d] -> Zoom out \n");

	src = imread("autumn.jpg");
	if (!src.data)
	{
		printf(" No data! -- Exiting the program \n");
		return -1;
	}

	tmp = src;
	dst = tmp;

	/// Create window
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
	imshow(window_name, dst);

	/// Loop
	while (true)
	{
		int c;
		c = waitKey(10);

		if ((char)c == 27)
		{
			break;
		}
		if ((char)c == 'u')
		{
			pyrUp(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
			printf("** Zoom In: Image x 2 \n");
		}
		else if ((char)c == 'd')
		{
			pyrDown(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
			printf("** Zoom Out: Image / 2 \n");
		}

		imshow(window_name, dst);
		tmp = dst;
	}
	return 0;
}