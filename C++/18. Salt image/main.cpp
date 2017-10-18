#include<opencv2\opencv.hpp>


// Function for "salting" image - some random pixels became completely white
void salt(cv::Mat& image, int n)
{
	srand(NULL);
	// image is gray scaled image
	for (int i = 0; i < n; ++i)
	{
		int r = rand() % image.rows;
		int c = rand() % image.cols;
		image.at<uchar>(r, c) = 255;
	}
}
int main()
{
	// Salt image
	cv::Mat image = cv::imread("hungarian_nature-HD-1366x768.jpg", 0);

	salt(image, 250);
	imshow("Salted", image);

	// "Grab salt back" with medianBlur
	cv::Mat result;
	medianBlur(image, result, 5);
	imshow("Result", result);

	cv::waitKey(0);
	return 0;
}