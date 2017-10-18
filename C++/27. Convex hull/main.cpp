#include<opencv2\opencv.hpp>

using namespace std;

int main()
{
	// Convex hull
	Mat src = imread("test1.jpg", 0);
	blur(src, src, Size(3, 3));
	Mat src_copy = src.clone();
	Mat threshold_output;
	std::vector<std::vector<Point> > contours;
	std::vector<Vec4i> hierarchy;

	/// Detect edges using Threshold
	threshold(src, threshold_output, 128, 255, THRESH_BINARY);

	/// Find contours
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Find the convex hull object for each contour
	std::vector<std::vector<Point> >hull(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		convexHull(Mat(contours[i]), hull[i], false);
	}

	/// Draw contours + hull results
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(0, 0, 255);
		drawContours(drawing, contours, i, Scalar(255, 0,0), 1, 8, std::vector<Vec4i>(), 0, Point());
		drawContours(drawing, hull, i, color, 1, 8, std::vector<Vec4i>(), 0, Point());
	}

	/// Show in a window
	namedWindow("Hull demo", CV_WINDOW_AUTOSIZE);
	imshow("Hull demo", drawing);
	waitKey(0);
	return 0;
}