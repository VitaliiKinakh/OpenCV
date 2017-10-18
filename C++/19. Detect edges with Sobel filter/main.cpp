#include<opencv2\opencv.hpp>


int main()
{
	// Detect edges with Sobel filter
	cv::Mat image = cv::imread("dog.jpg", 0);
	
	cv::Mat sobelX, sobelY; // images for sobel filter
	
	Sobel(image, sobelX, CV_8U, 1, 0, 3, 0.4, 128);
	Sobel(image, sobelY, CV_8U, 0, 1, 3, 0.4, 128);
	
	cv::Mat sobel = abs(sobelX) + abs(sobelY);
	
	cv::Mat sobelThresholded;
	threshold(sobel, sobelThresholded, 186, 255, cv::THRESH_BINARY);
	
	resize(sobelThresholded, sobelThresholded, cv::Size(sobelThresholded.cols / 3, sobelThresholded.rows / 3));
	
	imshow("Sobel", sobelThresholded);
	
	cv::waitKey(0);
	return 0;
}