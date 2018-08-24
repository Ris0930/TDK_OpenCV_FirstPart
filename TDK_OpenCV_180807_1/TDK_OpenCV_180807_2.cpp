// TDK_OpenCV_180807_2.cpp: 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

int Color_indentify(int argc, char const *argv[]) {
Mat cap_frame;
Mat hsv_frame;
Mat hsv_red_img_1, hsv_red_img;
Mat BGR_red_img;
VideoCapture cap(0);
while (1) {
	if (!cap.isOpened()) {
		cout << "!!!!!WEBCAM NOT OPEN!!!!!";
		return -1;
	} //if_loop_1

	cap >> cap_frame;
	namedWindow("cap_frame", WINDOW_NORMAL);			//namedWindow("camera");
	imshow("cap_frame", cap_frame);
//--------HSV-------------------------------------------------------------------------------
	cvtColor(cap_frame, hsv_frame, COLOR_BGR2HSV);		//convert BGR2HSV
	inRange(hsv_frame, Scalar(0, 43, 46), Scalar(10, 255, 255), hsv_red_img_1);
	hsv_red_img = hsv_red_img_1;
	inRange(hsv_frame, Scalar(156, 43, 46), Scalar(180, 255, 255), hsv_red_img_1);
	hsv_red_img = hsv_red_img + hsv_red_img_1;
	namedWindow("red_HSV_cap", WINDOW_NORMAL);
	imshow("red_HSV_cap", hsv_red_img);
//------------------------------------------------------------------------------------------
	if (waitKey(1) == 'q') {
		cout << "~~~~bye~~~~";
		break;
	} //if_loop_2
} //while_loop

//	return 0;
}
