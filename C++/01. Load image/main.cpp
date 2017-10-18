#include<opencv2\opencv.hpp>


int main()
{
	// Load images
	cv::Mat image1 = cv::imread("output.png", CV_LOAD_IMAGE_COLOR);
	cv::Mat image2 = cv::imread("output.png", CV_LOAD_IMAGE_GRAYSCALE);

	// Windows
	cv::namedWindow("Color", CV_WINDOW_FREERATIO);
	cv::namedWindow("Gray", CV_WINDOW_AUTOSIZE);

	// Show images in windows
	imshow("Color", image1);
	imshow("Gray", image2);

	// Change windows size
	cv::resizeWindow("Color", image1.cols / 3, image1.rows / 3);
	cv::resizeWindow("Gray", image1.cols / 3, image1.rows / 3);

	// Move windows
	cv::moveWindow("Color", 300, 400);
	cv::moveWindow("Gray", 700, 400);
	
	// Wait for any key pressed
	cv::waikKey(0);
	return 0;
}