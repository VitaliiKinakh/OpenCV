#include<opencv2\opencv.hpp>

// Function to apply look-up tables 
cv::Mat applyLYT(const cv::Mat& image, const cv::Mat& table)
{
	// table is 1 x 256 Mat object with some rule to perform image
	cv::Mat result; // image for result
	LUT(image, table, result);
	return result;
}

int main()
{
	// Create simple look-up table 
	cv::Mat image = cv::imread("dog.jpg", 0);
	
	cv::Mat lookup(1, 256, CV_8U); // simple uchar image with one row and 256 columns
	for (int i = 0; i < 256; ++i)
	{
		lookup.at<uchar>(i) = 255 - i;
	}
	
	cv::imshow("Applid LUT", applyLYT(image, lookup));
	
	cv::waitKey(0);
	return 0;
}