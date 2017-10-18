#include<opencv2\opencv.hpp>


int main()
{
	// Arithmetic and other operations	
	cv::Mat image1 = cv::imread("3D-Matplotlib.png");
	cv::Mat image2 = cv::imread("mainsvmimage.png");
	cv::Mat output1;
	
	addWeighted(image1, 0.7, image2, 0.3, 0.0, output1); // result[i][j] = 0.7*image1[i][j] + 0.3 * image2[i][j] + 0.0
	
	imshow("Image1", image1);
	imshow("Image2", image2);
	imshow("Output", output1);
	
	cv::waitKey(0);
	return 0;
}