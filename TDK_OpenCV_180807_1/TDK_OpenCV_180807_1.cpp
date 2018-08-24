#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

int _main()
{
	VideoCapture cap(0);
	if (!cap.isOpened())
		return -1;

	Mat frame;
	while (1)
	{
		cap >> frame;
		imshow("Test", frame);
		if (waitKey(60) > 0)
			break;
	}
	return 0;


}
