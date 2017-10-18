#include<opencv2\opencv.hpp>


int main()
{
	// Access specific pixels at color image 
	// In openCV image is in BGR format
	cv::Mat image = cv::imread("machine_learning_path.png", CV_LOAD_IMAGE_COLOR);
	cv::Mat modified = cv::imread("machine_learning_path.png", CV_LOAD_IMAGE_COLOR);

	// Iterate all over the image
	for (int r = 0; r < modified.rows; ++r)
	{
		for (int c = 0; c < modified.cols; ++c) {
			// We have loaded uint_8 from sdtint
			modified.at<cv::Vec3b>(r, c)[0] *= 0.5f;
			modified.at<cv::Vec3b>(r, c)[1] *= 0.5f; // Change intensity of image
			modified.at<cv::Vec3b>(r, c)[2] *= 0.5f;
		}
	}

	// Show images
	imshow("Original", image);
	imshow("Modified", modified);

	// Wait until any key is pressed
	cv::waitKey(0); 
	return 0;
}