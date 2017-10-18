#include<opencv2\opencv.hpp>
#include<iostream>
#include<string>


int main()
{
	// Remapping
	cv::Mat image = cv::imread("dog2.jpg");
	cv::Mat dst(image.size(), image.type()), map_x(image.size(), CV_32FC1), map_y(image.size(), CV_32FC1);

	// update map
	for (int i = 0; i < image.cols; ++i)
	{
		for (int j = 0; j < image.rows; ++j)
		{
			map_x.at<float>(j, i) = image.cols - i - 1;
			map_y.at<float>(j, i) = image.rows - j - 1;
		}
	}

	remap(image, dst, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

	cv::imshow("Image", dst);
	cv::waitKey(0);
	
	return 0;
}