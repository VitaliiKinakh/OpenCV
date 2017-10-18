#include<opencv2\opencv.hpp>

using namespace std;

int main()
{
	/ Detect ellipsoids and circles
	// fitEllips - work very bad
	// minAreaRect - wors almost the same way as fitEllipd
	// minEnclosingCircle work bad
	cv::Mat shapes = cv::imread("black-circles.jpg", 0);
	cv::Mat image = cv::imread("black-circles.jpg");
	cv::Mat blurred;
	GaussianBlur(shapes, blurred, cv::Size(5, 5), 0);
	imshow("blurred", blurred);
	cv::Mat thresholded;
	threshold(blurred, thresholded, 60, 255, cv::THRESH_BINARY); // work with colorfull images
	imshow("thresholded", thresholded);
	std::vector<std::vector<cv::Point>> contours;
	findContours(thresholded, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<cv::Rect> boundRect(contours.size());
	std::vector<cv::Point2f>center(contours.size());
	std::vector<float>radius(contours.size());

	// Reduce noise 
	medianBlur(shapes, blurred, 5);
	std::vector<cv::Vec3f> circles; 
	// Detect circles
	HoughCircles(blurred, circles, cv::HOUGH_GRADIENT, 1,
		blurred.rows / 16, // change this value to detect circles with different distances to each other
		100, 30, 1, 30 // change the last two parameters
					   // (min_radius & max_radius) to detect larger circles
	);

	/// Draw polygonal contour +
	cv::Mat drawing = image;
	for (int i = 0; i< contours.size(); i++)
	{
		std::string shape = detectShape(contours[i]);
		cv::Scalar color = cv::Scalar(0, 255, 0);
		drawContours(drawing, contours, i, color, 5, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
		//
		
	}
	for (int i = 0; i < circles.size(); ++i)
	{
		cv::Vec3i c = circles[i];
		circle(drawing, cv::Point(c[0], c[1]), c[2], cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
		circle(drawing, cv::Point(c[0], c[1]), 2, cv::Scalar(0, 255, 0), 3, cv::LINE_AA);
	}
	cv::namedWindow("Image", CV_WINDOW_FREERATIO);
	imshow("Image", drawing);
	cv::waitKey();
	
	return 0;
}