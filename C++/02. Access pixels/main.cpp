#include<opencv2\opencv.hpp>


int main()
{
	// Access specific pixels of image using at method
	cv::Mat image = cv::imread("output.png", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat modified = cv::imread("output.png", CV_LOAD_IMAGE_GRAYSCALE);

	// Iterate all over the image
	for (int r = 0; r < modified.rows; ++r)
	{
		for (int c = 0; c < modified.cols; ++c) {
			// We have loaded uint_8 from sdtint
			modified.at<uint8_t>(r, c) *= 0.5f; // Change intensity of image
		}
	}
	
	// Show images
	imshow("Original", image);
	imshow("Modified", modified);

	// Wait until any key is pressed
	cv::waitKey(0); 
	return 0;
}