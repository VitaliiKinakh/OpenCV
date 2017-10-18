#include<opencv2\opencv.hpp>
#include<iostream>


cv::Mat src, src_gray;
int maxCorners = 20, maxTrackbar = 100;
int thresh;


void shiThomas(int, void*)
{
	if (maxCorners < 1)
	{
		maxCorners = 1;
	}
	std::vector<cv::Point2f> corners;
	double quailityLabel = 0.01;
	double minDist = 10;
	int blockSize = 3;
	bool useHarris = false;
	double k = 0.04;
	cv::Mat copy = src.clone();

	goodFeaturesToTrack(src_gray, corners, maxCorners, quailityLabel, minDist);

	std::cout << "Numer of corners detected " << corners.size() << std::endl;
	for (size_t i = 0; i < corners.size(); ++i)
	{
		circle(copy, corners[i], 4, cv::Scalar(0, 255, 0));
	}
	cv::namedWindow("Image", CV_WINDOW_FREERATIO);
	cv::imshow("Image", copy);
}


int main()
{
	// Shi Thomas corner detection
	src = cv::imread("harris.jpg");
	cvtColor(src, src_gray, CV_BGR2GRAY);

	cv::namedWindow("Trackbar", CV_WINDOW_AUTOSIZE);
	cv::createTrackbar("Max Corners", "Trackbar", &maxCorners, maxTrackbar, shiThomas);

	shiThomas(0, 0);
	
	cv::waitKey(0);

	return 0;
}