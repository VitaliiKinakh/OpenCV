#include<opencv2\opencv.hpp>

using namespace std;

int main()
{
	// Hough line detection HoughLinesP - works better
	Mat image = imread("S.bmp", 0);
	Mat edges;
	Canny(image, edges, 0, 30);

	std::vector<Vec2f> lines;
	HoughLines(edges, lines, 1, CV_PI / 180, 128);
	// Draw lines
	Mat cImage = imread("S.bmp");
	for (int i = 0; i < lines.size(); ++i)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cImage, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
	}
	namedWindow("Image", CV_WINDOW_FREERATIO);
	imshow("Image", cImage);

	std::vector<Vec4i> linesP;
	HoughLinesP(edges, linesP, 1, CV_PI / 180, 128);
	Mat pImage = imread("S.bmp");
	for (int i = 0; i < linesP.size(); ++i)
	{
		Vec4i p = linesP[i];
		Point pt1, pt2;
		pt1.x = p[0];
		pt1.y = p[1];
		pt2.x = p[2];
		pt2.y = p[3];
		line(pImage, pt1, pt2, Scalar(0, 0, 255));
	}
	namedWindow("PImage", CV_WINDOW_FREERATIO);
	imshow("PImage", pImage);
	waitKey(0);
	return 0;
}