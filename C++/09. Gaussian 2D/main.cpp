#include<opencv2\opencv.hpp>


// Function that creates simple Gaussian 2D
void createGaussian(cv::Size& size, cv::Mat& output, int uX, int uY, double sigmaX, double sigmaY, double amplitude = 1.0)
{
	// Create temp image for operating
	cv::Mat temp = cv::Mat(size, CV_32F);
	// Main loop for Gaussian
	for (int r = 0; r < size.height; ++r)
	{
		for (int c = 0; c < size.width; ++c)
		{
			// Values for gaussian
			float x = ((c - uX)*((float)c - uX)) / (2.0 * sigmaX * sigmaX);
			float y = ((r - uY)*((float)r - uY)) / (2.0 * sigmaY * sigmaY);
			float value = amplitude * exp(-(x + y));
			// Paste value in (r,c)
			temp.at<float>(r, c) = value;
		}
	}
	// Normalize image
	normalize(temp, temp, 1.0, cv::NORM_MINMAX);
	output = temp;
}


int main()
{
	// Create Gaussian 2D
	cv::Mat output;
	createGaussian(cv::Size(256, 256), output, 256 / 2, 256 / 2, 20, 20);
	
	imshow("Gaussian", output);
	
	cv::waitKey(0);
	return 0;
}