#include<opencv2\opencv.hpp>
#include<iostream>


cv::Mat src, src_gray;
int thresh = 60;


void cornerDetection(int, void*)
{
	cv::Mat dst, dst_norm, dst_norm_scaled;
	dst = cv::Mat::zeros(src.size(), CV_32FC1);
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;
	cv::cornerHarris(src_gray, dst, blockSize, apertureSize, k);
	
	// normalize corners image
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1);

	dst_norm_scaled = src.clone();
	
	// Draw corners
	for (int i = 0; i < dst_norm.rows; ++i)
	{
		for (int j = 0; j < dst_norm.cols; ++j)
		{
			if (dst_norm.at<float>(i, j) > thresh)
			{
				circle(dst_norm_scaled, cv::Point(i, j), 2, cv::Scalar(0));
			}
		}
	}

	// Finally show image
	cv::namedWindow("Corners", CV_WINDOW_FREERATIO);
	cv::imshow("Corners", dst_norm_scaled);
}


int main()
{
	src = cv::imread("harris.jpg");
	cvtColor(src, src_gray, CV_BGR2GRAY);
	cv::namedWindow("Trackbar", CV_WINDOW_AUTOSIZE);
	createTrackbar("Thresh", "Trackbar", &thresh, 255, cornerDetection);

	cv::namedWindow("Image", CV_WINDOW_FREERATIO);
	cv::imshow("Image", src);

	cornerDetection(0, 0);
	cv::waitKey(0);
	
	return 0;
}