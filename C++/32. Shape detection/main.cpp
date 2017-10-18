#include<opencv2\opencv.hpp>
#include<iostream>
#include<string>


std::string DetectShape(std::vector<cv::Point> contour)
{
	std::vector<cv::Point> approx;
	// Approximate contour with accuracy proportional
	// to the contour perimeter
	cv::approxPolyDP(cv::Mat(contour), approx, cv::arcLength(cv::Mat(contour), true)*0.02, true);

	// Number of curves
	int vtc = approx.size();

	if (vtc == 3)
	{
		return "Triangle";
	}
	else if (approx.size() >= 4 && approx.size() <= 10)
	{
		// Use the degrees obtained above and the number of vertices
		// to determine the shape of the contour
		if (vtc == 4)
			return "Fourtangle";
		else if (vtc == 5)
			return "Pentagonal";
		else if (vtc == 6)
			return "Hexagonal";
		else if (vtc == 7)
			return "Heptagon";
		else if (vtc == 8)
			return "Octagon";
		else if (vtc == 9)
			return "9 - gon";
		else if (vtc == 10)
			return "10 - gon";
	}
	else
	{
		// Detect and label circles
		double area = cv::contourArea(contour);
		cv::Rect r = cv::boundingRect(contour);
		int radius = r.width / 2;

		if (isContourConvex(contour))
		{
			if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 && std::abs(1 - (area / (CV_PI * (radius*radius)))) <= 0.2) {
				return "Circle";
			}
			else {
				return std::to_string(vtc) + "-gonal";
			}
		}
		else {
			if(!isContourConvex(contour))
				return std::to_string(vtc) + "-gonal";
		}
	}
}

int main()
{
	// Shape detection
	cv::Mat src = cv::imread("hand.bmp");
	cv::Mat gray;
	cv::Mat bw;
	cv::Mat dst;
	std::vector<std::vector<cv::Point> > contours;
	
	// Convert to grayscale
	cv::cvtColor(src, gray, CV_BGR2GRAY);

	// Use Canny instead of threshold to catch squares with gradient shading
	blur(gray, bw, Size(3, 3));
	cv::Canny(gray, bw, 80, 240, 3);
		
	// Find contours
	cv::findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	src.copyTo(dst);

	for (std::vector<cv::Point>c : contours)
	{
		cv::Moments m = moments(c);
		int cX = int(m.m10 / m.m00);
		int cY = int(m.m01 / m.m00);
		std::string shape = DetectShape(c);
		drawContours(dst, std::vector<std::vector<cv::Point>>(1, c), -1, cv::Scalar(0, 0, 255), 2);
		putText(dst, shape, cv::Point(cX, cY), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);
	}

	cv::namedWindow("dst", CV_WINDOW_FREERATIO);
	cv::imshow("dst", dst);
	
	cv::waitKey(0);
	
	return 0;
}