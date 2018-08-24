#include "stdafx.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int aamain(int argc, char** argv)
{
	VideoCapture cap(0); //capture the video from web cam

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 38;
	int iHighH = 75;

	int iLowS = 127;
	int iHighS = 255;

	int iLowV = 127;
	int iHighV = 255;

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	int valThres = 56;

	while (char(waitKey(1)) != 27)
	{
		Mat imgOriginal;//原圖片
		cap.read(imgOriginal);
		Mat imgHSV;//轉成hsv圖片
		Mat imgProcess;//圖片處理 過程
		Mat imgDst;//圖片處理 完成
		vector<Mat> hsvSplit;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2GRAY);//轉成hsv平面
		//為了做直方圖等化
		//split(imgHSV, hsvSplit);//分割
		//equalizeHist(hsvSplit[2], hsvSplit[2]);//直方圖等化
		//merge(hsvSplit, imgHSV);//合併

		GaussianBlur(imgHSV, imgProcess, Size(5, 5), 1.3, 1.3);//影像做高斯平滑
		//threshold(imgProcess, imgProcess, valThres, 255, THRESH_BINARY_INV);//固定閥值
		//illuminationChange

		//Mat imgProcessR = imgProcess(Rect(0, 0,imgOriginal.cols/2, imgOriginal.rows/2));

		//Contours (輪廓)
		vector< vector <Point> > contoursFind, contoursDraw;//包含所有輪廓之容器
		vector< Vec4i > imgHierarchy;//輸出向量，記錄所有輪廓
		Scalar contoursColor = Scalar(255, 0, 0);

		findContours(imgProcess,contoursFind, noArray(), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);//找輪廓
		//drawContours(imgOriginal, contoursDraw, -1, contoursColor, 1, 8, imgHierarchy);

		vector<Point2f> center(contoursFind.size());
		vector<float> radius(contoursFind.size());

		//for (int i =0 ; i < contoursFind.size(); i++) {
		//	minEnclosingCircle(contoursFind[i], center[i], radius[i]);
		//	int radius_int = cvRound(radius[i]);
		//	Point center_p = (Point)center[i];
		//	circle(imgOriginal, center_p, radius_int, Scalar(0, 0, 255), 1, CV_AA);
		//	circle(imgOriginal, center_p, 1, Scalar(0, 255, 0), -1, CV_AA);

		//}

		Mat imgThresholded;

		inRange(imgProcess, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
		//Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
		//morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
		//morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);

		imshow("Thresholded Image", imgProcess); //show the thresholded image
		imshow("Original", imgOriginal); //show the original image


	}

	return 0;

}