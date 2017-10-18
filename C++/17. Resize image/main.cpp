#include<opencv2\opencv.hpp>


int main()
{
	// Resize images
	cv::Mat image = cv::imread("hungarian_nature-HD-1366x768.jpg");
	
	cv::Mat result; // image for result
	
	resize(image, result, cv::Size(image.cols / 3, image.rows / 3));
	
	imshow("Image", image);
	imshow("Resized", result);
	
	cv::waitKey(0);
	return 0;
}