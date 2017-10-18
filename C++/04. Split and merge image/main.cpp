#include<opencv2\opencv.hpp>


int main()
{
	// Split and merge images
	cv::Mat original = cv::imread("machine_learning_path.png", CV_LOAD_IMAGE_COLOR);
	cv::Mat splitColors[3]; // Array for each color - blue green and red
	split(original, splitColors);
	imshow("B", splitColors[0]);
	imshow("G", splitColors[1]);
	imshow("R", splitColors[2]);

	// Replace red color with zeros
	splitColors[2] = cv::Mat::zeros(splitColors[2].size(), CV_8UC1);

	// Merge channels back
	cv::Mat output; // object for output
	merge(splitColors, 3, output);
	
	// Show output
	imshow("Output", output);
	
	cv::waitKey(0);
	
	return 0;
}