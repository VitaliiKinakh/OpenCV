#include<opencv2\opencv.hpp>
#include<iostream>


cv::Mat src, src_gray;
cv::Mat myHarris_dst; cv::Mat myHarris_copy; cv::Mat Mc;
cv::Mat myShiTomasi_dst; cv::Mat myShiTomasi_copy;
int myShiTomasi_qualityLevel = 50;
int myHarris_qualityLevel = 50;
int max_qualityLevel = 100;

double myHarris_minVal; double myHarris_maxVal;
double myShiTomasi_minVal; double myShiTomasi_maxVal;

void myShiTomasi_function(int, void*)
{
	myShiTomasi_copy = src.clone();
	if (myShiTomasi_qualityLevel < 1) { myShiTomasi_qualityLevel = 1; }
	for (int j = 0; j < src_gray.rows; j++)
	{
		for (int i = 0; i < src_gray.cols; i++)
		{
			if (myShiTomasi_dst.at<float>(j, i) > myShiTomasi_minVal + (myShiTomasi_maxVal - myShiTomasi_minVal)*myShiTomasi_qualityLevel / max_qualityLevel)
			{
				circle(myShiTomasi_copy, Point(i, j), 4, Scalar(255, 0, 0), -1, 8, 0);
			}
		}
	}
	//namedWindow("My ShiTomasi", CV_WINDOW_AUTOSIZE);
	imshow("My ShiTomasi", myShiTomasi_copy);
}


void myHarris_function(int, void*)
{
	myHarris_copy = src.clone();
	if (myHarris_qualityLevel < 1) { myHarris_qualityLevel = 1; }
	for (int j = 0; j < src_gray.rows; j++)
	{
		for (int i = 0; i < src_gray.cols; i++)
		{
			if (Mc.at<float>(j, i) > myHarris_minVal + (myHarris_maxVal - myHarris_minVal)*myHarris_qualityLevel / max_qualityLevel){
			
				circle(myHarris_copy, Point(i, j), 4, Scalar(0, 255, 0), -1, 8, 0);
			}
		}
	}
	//cv::namedWindow("My Harris", CV_WINDOW_FREERATIO);
	cv::imshow("My Harris", myHarris_copy);
}


int main()
{
	// Creating own corner detector
	src = imread("harris.jpg", IMREAD_COLOR);
	cv::cvtColor(src, src_gray, COLOR_BGR2GRAY);
	int blockSize = 3; int apertureSize = 3;
	myHarris_dst = cv::Mat::zeros(src_gray.size(), CV_32FC(6));
	Mc = cv::Mat::zeros(src_gray.size(), CV_32FC1);
	cornerEigenValsAndVecs(src_gray, myHarris_dst, blockSize, apertureSize, BORDER_DEFAULT);
		// calculate Mc 
	for (int j = 0; j < src_gray.rows; j++)
	{
		for (int i = 0; i < src_gray.cols; i++)
		{
			float lambda_1 = myHarris_dst.at<Vec6f>(j, i)[0];
			float lambda_2 = myHarris_dst.at<Vec6f>(j, i)[1];
			Mc.at<float>(j, i) = lambda_1*lambda_2 - 0.04f*pow((lambda_1 + lambda_2), 2);
		}
	}
	cv::minMaxLoc(Mc, &myHarris_minVal, &myHarris_maxVal, 0, 0, Mat());
	
	// Create Window and Trackbar 
	cv::namedWindow("Trackbar Harris", WINDOW_AUTOSIZE);
	cv::createTrackbar(" Quality Level:", "Trackbar Harris", &myHarris_qualityLevel, max_qualityLevel, myHarris_function);
	myHarris_function(0, 0);
	myShiTomasi_dst = Mat::zeros(src_gray.size(), CV_32FC1);
	cv::cornerMinEigenVal(src_gray, myShiTomasi_dst, blockSize, apertureSize, BORDER_DEFAULT);
	cv::minMaxLoc(myShiTomasi_dst, &myShiTomasi_minVal, &myShiTomasi_maxVal, 0, 0, Mat());
	
	// Create Window and Trackbar 
	cv::namedWindow("Trackbar ShiTomasi", WINDOW_AUTOSIZE);
	cv::createTrackbar(" Quality Level:", "Trackbar ShiTomasi", &myShiTomasi_qualityLevel, max_qualityLevel, myShiTomasi_function);
	myShiTomasi_function(0, 0);
	
	cv""waitKey(0);

	return 0;
}