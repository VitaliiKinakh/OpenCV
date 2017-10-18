#include<opencv2\opencv.hpp>

using namespace std;

int main()
{
	// Image moments
	Mat src = imread("shapes-2.png");
	Mat image;
	cvtColor(src, image, CV_BGR2GRAY);
	Mat blurred;
	blur(image, blurred, Size(3, 3));
	Mat thresholded;
	threshold(blurred, thresholded, 128, 255, CV_THRESH_BINARY);
	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarhy;
	
	findContours(thresholded, contours,hierarhy, CV_RETR_TREE, CV_CHAIN_APPROX_TC89_L1, Point(0, 0));
	for (int i = 0; i < contours.size(); ++i)
	{
		drawContours(src, contours, i, Scalar(0, 0, 255), 5);
	}
	namedWindow("Image", CV_WINDOW_FREERATIO);
	imshow("Image", src);

	// Compute moments
	std::vector<Moments> mu(contours.size());
	for (int i = 0; i < contours.size(); ++i)
	{
		mu[i] = moments(contours[i]);
	}
	// mass center vector
	std::vector<Point2f> mc(contours.size());
	for (int i = 0; i < contours.size(); ++i)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01/mu[i].m00);
	}
	// compare area from OpenCV function and from moments
	for (int i = 0; i < contours.size(); ++i)
	{
		std::cout << "Contour[" << i << "] area from OpenCV function = " << contourArea(contours[i]) << " area from moments = " << mu[i].m00 << std::endl;
	}
	return 0;
}