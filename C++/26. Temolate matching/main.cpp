#include<opencv2\opencv.hpp>

using namespace std;

int main()
{
	// Template matching
	Mat img; 
	Mat templ; 
	Mat result;
	Mat img_display;
	img = imread("image_t.jpg");
	templ = imread("template_t.jpg");
	img.copyTo(img_display);
	/// Create the result matrix
	int result_cols = img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;

	result.create(result_rows, result_cols, CV_32FC1);

	/// Do the Matching and Normalize
	matchTemplate(img, templ, result, CV_TM_CCOEFF);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	/// Localizing the best match with minMaxLoc
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;

	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
	if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}
	matchLoc = maxLoc;

	
	/// Show me what you got
	rectangle(img_display, matchLoc, Point(matchLoc.x - templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
	rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);

	imshow("Result", result);
	imshow("Image display", img_display);
	waitKey();
	return 0;
}