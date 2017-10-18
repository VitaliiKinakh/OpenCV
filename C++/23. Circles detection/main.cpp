#include<opencv2\opencv.hpp>

using namespace std;

int main()
{
	// Detect circles with HoughCircle
	Mat image = imread("hough.jpg", 0);
	Mat colorImage = imread("hough.jpg");
	
	Mat blurred;
	GaussianBlur(image, blurred, Size(3, 3), 10);
	
	std::vector<Vec3f> circles;
	HoughCircles(blurred, circles, CV_HOUGH_GRADIENT, 1, 10, 200, 100, 0, 0);
	
	// Draw circles
	for (size_t i = 0; i < circles.size(); ++i)
	{
		Point center = Point(circles[i][0], circles[i][1]);
		int rad = circles[i][2];
		circle(colorImage, center, rad, Scalar(0, 255, 0), 3);
		// draw center dot
		circle(colorImage, center, 3, Scalar(0, 255, 0), -1);
	}
	
	imshow("Circles", colorImage);
	waitKey(0);
	
	return 0;
}