#include<opencv2\opencv.hpp>


int main()
{
	// Fitering an image
	cv::Mat image = cv::imread("hungarian_nature-HD-1366x768.jpg");
	// Images for result
	cv::Mat blurred, gBlurred; 
	
	// Using bluring algorithm
	blur(image, blurred, cv::Size(5, 5));
	cv::GaussianBlur(image, gBlurred, cv::Size(5, 5), 0.4);
	
	cv::namedWindow("Orig image", CV_WINDOW_FREERATIO);
	cv::namedWindow("Blurred image", CV_WINDOW_FREERATIO);
	cv::namedWindow("Gaussian blurred image", CV_WINDOW_FREERATIO);
	
	imshow("Orig image", image);
	imshow("Blurred image", blurred);
	imshow("Gaussian blurred image", gBlurred);
	
	cv::waitKey(0);
	return 0;
}