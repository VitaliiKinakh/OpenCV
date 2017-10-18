#include<opencv2\opencv.hpp>


int main()
{
	cv::Mat image = cv::imread("caslte.jpg", 0);
	
	cv::Mat contours; // contours image for Canny edge detection
	
	Canny(image, contours, 128, 255);
	
	resize(contours, contours, cv::Size(contours.cols / 2, contours.rows / 2));
	
	cv::Mat contoursInv;
	
	threshold(contours, contoursInv, 60, 255, cv::THRESH_BINARY_INV);
	
	imshow("Canny", contoursInv);
	
	cv::waitKey(0);
	return 0;
}