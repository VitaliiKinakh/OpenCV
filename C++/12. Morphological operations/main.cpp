#include<opencv2\opencv.hpp>


int main()
{
	cv::Mat image = cv::imread("hungarian_nature-HD-1366x768.jpg", 0);
	
	cv::Mat thresholded; // thresholded image
	// create binary thresholded image
	threshold(image, thresholded, 128, 255, cv::THRESH_BINARY);
	
	// use erode and dilate functions
	cv::Mat eroded;
	erode(image, eroded, cv::Mat(7, 7, CV_8U, cv::Scalar::all(1)));
	imshow("Eroded image", eroded);
	
	cv::Mat dilated;
	dilate(image, dilated, cv::Mat(5, 5, CV_8U, cv::Scalar::all(1)));
	imshow("Dilated image", dilated);

	cv::Mat closed;
	morphologyEx(thresholded, closed, cv::MORPH_CLOSE, cv::Mat(5, 5, CV_8U, cv::Scalar::all(1)));
	imshow("Closed", closed);
	
	cv::Mat opened;
	morphologyEx(thresholded, opened, cv::MORPH_OPEN, cv::Mat(5, 5, CV_8U, cv::Scalar::all(1)));
	imshow("Opened", opened);
	
	cv::waitKey(0);
	return 0;
}