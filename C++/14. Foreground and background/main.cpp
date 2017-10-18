#include<opencv2\opencv.hpp>


int main()
{
	cv::Mat animal = cv::imread("dog.jpg", 0); // read animal image
	// Extract background and foreground
	cv::Mat fg;
	cv::Mat binary; // binary image creatEd from animal
	
	threshold(animal, binary, 100, 128, cv::THRESH_BINARY);
	
	erode(binary, fg, cv::Mat(), cv::Point(-1, -1), 6); // process erode algorithm on image 6 times
	
	cv::Mat bg; // image for background
	
	cv::Mat binary2;
	threshold(animal, binary2, 100, 128, cv::THRESH_BINARY_INV);
	
	dilate(binary2, bg, cv::Mat(), cv::Point(-1, -1), 6);
	
	cv::Mat markers(binary.size(), CV_8U, cv::Scalar(0));
	markers = fg + bg;
	
	imshow("Background", bg);
	imshow("Foreground", fg);
	imshow("Markers", markers);
	
	cv::waitKey(0);
	return 0;
}