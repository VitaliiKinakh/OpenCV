#include<opencv2\opencv.hpp>

void testMatch(cv::Mat original, cv::Mat templ)
{
	cv::Mat src, dst;

	src = original.clone();

	cv::Mat binI(src.size(), CV_8U);
	cv::Mat binT(templ.size(), CV_8U);

	// create colorful images
	cv::Mat rgb(original.size(), CV_8UC3);
	cv::cvtColor(src, rgb, CV_GRAY2BGR);
	cv::Mat rgbT(templ.size(), CV_8UC3);
	cv::cvtColor(templ, rgbT, CV_GRAY2BGR);
	cv::cvtColor(src, rgb, CV_GRAY2BGR);

	// get edges
	Canny(src, binI, 50, 200);
	Canny(templ, binT, 50, 200);

	// show edges
	cv::namedWindow("cannyI", CV_WINDOW_FREERATIO);
	imshow("cannyI", binI);

	cv::namedWindow("cannyT", 2);
	imshow("cannyT", binT);

	// save contours on image
	std::vector<std::vector<cv::Point>> storage;

	// find contours on main image
	findContours(binI, storage, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	int counter;
	// draw countours
	if (!storage.empty()) {
		for (counter = 0; counter < storage.size(); ++counter) {
			drawContours(rgb, storage, counter, cv::Scalar(0, 255, 0) , 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());

		}
	}
	// show them
	cv::namedWindow("cont", CV_WINDOW_FREERATIO);
	imshow("cont", rgb);

	// save contours on template
	std::vector<std::vector<cv::Point>> storageT;

	// find contours on template
	findContours(binT, storageT, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point>> seqT;
	double perimT = 0;

	if (!storageT.empty()) {
		// find the longest contour
		for (auto c : storageT) {
			double perim = cv::arcLength(c, true);
			if (perim>perimT) {
				perimT = perim;
				seqT.push_back(c);
			}
		}
	}
	// draw founded contour
	drawContours(rgbT, seqT, 0, cv::Scalar(36, 201, 197), 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
	//cv::namedWindow("contT", CV_WINDOW_FREERATIO);
	//imshow("contT", rgbT);


	std::vector<std::vector<cv::Point>> seqM;
	double matchM = 1000;
	// iterato throw storage to find best fit 
	counter = 0;
	if (!storage.empty()) {
		cv::Moments m;
		int cX;
		int cY;
		double match0;
		// looking for best fit using moments
		// temp variable to detect best fit
		for (auto c : storage) {
			m = moments(c);
			cX = int(m.m10 / m.m00);
			cY = int(m.m01 / m.m00);
			match0 = matchShapes(c, seqT[0], CV_CONTOURS_MATCH_I3, 0);
			if (match0 < 0.1) {
				seqM.push_back(c);
			}
			printf("[i] %d match: %.2f\n", ++counter, match0);
			putText(rgb, std::to_string(counter), cv::Point(cX, cY), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);
		}
	}
	// draw founded
	for (int i = 0; i < seqM.size(); ++i) {
		drawContours(rgb, seqM, i, cv::Scalar(0, 0, 255), 5, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
	}
	cv::namedWindow("find", CV_WINDOW_FREERATIO);
	imshow("find", rgb);

	// wait for any key pressed
	cv::waitKey(0);

	cv::destroyAllWindows();
}

int main()
{
	// Template matching
	cv::Mat original, templ;

	// Get image
	original = cv::imread("black-circles.jpg",0);
	// Get template image
	templ = cv::imread("circle.bmp",0);
	// Show them
	cv::namedWindow("original", CV_WINDOW_FREERATIO);
	imshow("original", original);
	cv::namedWindow("template", CV_WINDOW_FREERATIO);
	imshow("template", templ);

	// Compare
	testMatch(original, templ);
	
	cv::destroyAllWindows();
	
	cv::waitKey(0);
	return 0;
}